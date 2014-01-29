namespace csl {

    inline ErrDic::ErrDic() :
	originals_( 0 ),
	errorPatterns_( 0 ),
	originalHash_( 0 ),
	patternHash_( 0 ),
	keyValueDelimiter_( Global::keyValueDelimiter )
    {
    }

    inline ErrDic::~ErrDic() {
	if( originals_ ) delete( originals_ );
	if( errorPatterns_ ) delete( errorPatterns_ );
    }

    inline bool ErrDic::lookup( wchar_t* key, Entry* entry ) const {
	size_t tokID;
	if( TransTable_t::getTokID( key, &tokID ) ) {
	    *entry = Entry( *this, tokID );
	    return true;
	}
	else return false;
    }
    
    inline void ErrDic::loadFromFile( char* dicFile ) {
	FILE* fi = fopen( dicFile, "rb" );
	if ( !fi ) {
	    throw exceptions::badFileHandle( "csl::ErrDic: Couldn't open file '" +
					     std::string( dicFile ) +
					     "' for reading." );
	}
	loadFromStream( fi );
	fclose( fi );
    }
    
    inline void ErrDic::loadFromStream( FILE* fi ) {
	fread( &header_, sizeof( Header ), 1, fi );
	if ( ( header_.magicNumber_ != magicNumber_ ) ) {
	    throw exceptions::badDictFile( "ErrDic: Magic number comparison failed.\n" );
	}
	MinDic_t::loadFromStream( fi );
	originals_ = (wchar_t*) malloc( header_.sizeOfOriginals_ * sizeof( wchar_t ) );
	fread( originals_, sizeof( wchar_t ), header_.sizeOfOriginals_, fi );

	errorPatterns_ = (wchar_t*) malloc( header_.sizeOfErrorPatterns_ * sizeof( wchar_t ) );
	fread( errorPatterns_, sizeof( wchar_t ), header_.sizeOfErrorPatterns_, fi );
    }

    inline void ErrDic::writeToFile( char* dicFile ) const {
	FILE* fo = fopen( dicFile, "wb" );
	if ( !fo ) {
	    throw exceptions::badFileHandle( "ErrDic: Couldn't open file '" +
					     std::string( dicFile ) +
					     "' for writing." );
	}
	writeToStream( fo );
	fclose( fo );
    }
    
    inline void ErrDic::writeToStream( FILE* fo ) const {
	fwrite( &header_, sizeof( Header ), 1, fo );
	MinDic_t::writeToStream( fo );
	fwrite( originals_, sizeof( wchar_t ), header_.sizeOfOriginals_, fo );
	fwrite( errorPatterns_, sizeof( wchar_t ), header_.sizeOfErrorPatterns_, fo );
    }

    inline void ErrDic::initConstruction() {
	MinDic_t::initConstruction();
	
    }

    inline void ErrDic::finishConstruction() {
	MinDic_t::finishConstruction();
    }

    inline void ErrDic::compileDic( const char* lexFile ) {
	initConstruction();
	
	std::ifstream fileHandle( lexFile );
	if( !fileHandle.good() ) {
	    throw exceptions::badFileHandle( "Couldn't open file '" + 
					     std::string( lexFile ) + 
					     "' for reading." );
	}

	
// 	struct stat f_stat;
// 	stat( lexFile, &f_stat );
// 	size_t estimatedNrOfKeys = f_stat.st_size / 30;
// 	std::cerr<<"Estimate about "<< estimatedNrOfKeys << " Keys."<< std::endl;
	
	originalHash_ =  new Hash< wchar_t >( 100000, originals_, header_.sizeOfOriginals_ );
	patternHash_ =  new Hash< wchar_t >( 10000, errorPatterns_, header_.sizeOfErrorPatterns_ );


	uchar bytesIn[Global::lengthOfLongStr];
	// set the last byte to 0. So we can recognize when an overlong string was read by getline().
	bytesIn[Global::lengthOfLongStr - 1] = 0; 

	wchar_t wideIn[Global::lengthOfLongStr];
	wchar_t* key = 0;
	wchar_t* original = 0;
	wchar_t* errorPattern = 0;

	while( fileHandle.getline(( char* ) bytesIn, Global::lengthOfLongStr ) )  {
 	    if ( bytesIn[Global::lengthOfLongStr-1] != 0 ) {
		throw exceptions::badInput( "csl::ErrDic::compileDic: Maximum length of input line violated (set by Global::lengthOfLongStr)" );
	    }
	    
	    if( mbstowcs( wideIn, (const char*)bytesIn, Global::lengthOfLongStr ) == (size_t)-1 ) {
		// continue;
		throw exceptions::badInput( "csl::ErrDic::compileDic: Invalid utf-8 sequence" );
	    }

	    /////////////////// PARSE THE INPUT STRING
	    wchar_t* c; // go through the string with this pointer
	    wchar_t* restString = wideIn;

	    // cut off the key
	    c = wcschr( wideIn, keyValueDelimiter_ );
	    if( c ) {
		*c = 0;
		key = restString;
		restString = c + 1;
	    }
	    else throw exceptions::badInput( "csl::ErrDic::compileDic: Input format violated." );

	    // cut off the original
	    c = wcschr( restString, L' ' );
	    if( c ) {
		*c = 0;
		original = restString;
		restString = c + 1;
	    }
	    else throw exceptions::badInput( "csl::ErrDic::compileDic: Input format violated." );

	    // cut off the error pattern
	    c = wcschr( restString, L' ' );
	    if( ! c ) throw exceptions::badInput( "csl::ErrDic::compileDic: Input format violated." );
	    ++c;
	    c = wcschr( c, L' ' );
	    if( c ) {
		*c = 0;
		errorPattern = restString;
		++c;
	    }
	    else throw exceptions::badInput( "csl::ErrDic::compileDic: Input format violated." );
	    

	    size_t originalOffset = originalHash_->findOrInsert( original );
	    size_t patternOffset = patternHash_->findOrInsert( errorPattern );
	    

//	    printf( "Insert entry: key=%ls, original=%ls, pattern=%ls\n", key, original, errorPattern );
	    MinDic_t::addToken( key, MdAnnType( originalOffset, patternOffset ) );

	}
	fileHandle.close();

	finishConstruction();
    }

    void ErrDic::printDic() const {
	count_ = 0;
	printDic_rec( getRoot(), 0, 0 );
    }

    void ErrDic::printDic_rec( int pos, int depth, size_t perfHashValue ) const {
	int newPos;
	static wchar_t w[Global::lengthOfStr];
	size_t newPerfHashValue;
	
	const wchar_t* transitions = getSusoString( pos );
	while( *transitions ) {
	    newPerfHashValue = perfHashValue;;
	    if( ( newPos = walkPerfHash( pos, *transitions, newPerfHashValue ) ) ) {
		w[depth] = *transitions;
		
		if( isFinal( newPos ) ) {
		    w[depth+1] = 0;
		    // printf( "%ls#%s\n", w, annStrings_ + getAnnotation( newPerfHashValue ) );
		    //printf( "%ls#%d\n", w, newPerfHashValue );
		    
		    if( ( ++count_ % 100000 ) == 0 ) fprintf( stderr, "%d\n", (int)count_ );
		} // if isFinal
		printDic_rec( newPos, depth + 1, newPerfHashValue );

	    } // if couldWalk
	    else {
		throw exceptions::badDictFile( "suso-string seems to be corrupted." ); 
	    }
	    ++transitions;
	} // while
    } // end of method


    inline void ErrDic::doAnalysis() const {
	float originals_MB = (float)( header_.sizeOfOriginals_ * sizeof( wchar_t ) ) / 1000000;
	float errorPatterns_MB = (float)( header_.sizeOfErrorPatterns_ * sizeof( wchar_t ) ) / 1000000;

	MinDic_t::doAnalysis();
	printf( "**********\nErrDic Analysis\n**********\noriginals-buffer:\t%.3f MB\npattern-buffer:\t%.3f MB\n\n",
		originals_MB,
		errorPatterns_MB
	    );
    }

} // namespace csl

