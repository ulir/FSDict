namespace csl {

	inline MinDic2::MinDic2( const char* dicFile ) {
		if( dicFile ) {
			loadFromFile( dicFile );
		}	
	}

	inline void MinDic2::loadFromFile( const char* binFile ) {
		FILE* fi = fopen( binFile, "rb" );

		if( ! fi ) {
			throw exceptions::badFileHandle( std::string( "MinDic2: Couldn't open file '" ) +
				std::string( binFile ) +
				std::string( "' for reading." ) );
		}

		loadFromStream( fi );
		fclose( fi );
	}


	inline void MinDic2::loadFromStream( FILE* fi ) {
	    // read the MinDic2-Header
	    size_t elementsRead = fread( &header_, sizeof( Header ), 1, fi );
	    if( elementsRead != 1 ) {
		throw exceptions::badInput( "csl::MinDic2::loadFromStream: could not read Header" );
	    }
	    
	    if( header_.getMagicNumber() != magicNumber_ ) {
		throw exceptions::badDictFile( "MinDic2: Magic number comparison failed.\n" );
	    }
	    
	    nrOfKeys_ = header_.getNrOfKeys();
	    
	    // read the TransTable
	    TransTable_t::loadFromStream( fi );
	}

	inline void MinDic2::writeToFile( char const* binFile ) const {
		FILE* fo = fopen( binFile, "wb" );
		if( ! fo ) {
			throw exceptions::badFileHandle( "MinDic2: Couldn't open file '" +
				std::string( binFile ) +
				"' for writing." );
		}
		writeToStream( fo );
		fclose( fo );
	}


	inline void MinDic2::writeToStream( FILE* fo ) const {

		// write the header
		fwrite( &header_, sizeof( Header ), 1, fo );
		// write the TransTable
		TransTable_t::writeToStream( fo );

	}

	inline void MinDic2::initConstruction() {
		TransTable_t::initConstruction();
		tempStates_ =( TempState_t* ) malloc( Global::lengthOfStr * sizeof( TempState_t ) ); // allocate memory for all tempStates
		for( size_t i = 0; i < Global::lengthOfStr; ++i ) {
			new( &( tempStates_[i] ) ) TempState_t(); // call constructor for all tempStates
		}

		hashtable_ = new StateHash< TransTable_t >( *this );

		nrOfKeys_ = 0;
		*lastKey_ = 0; // reset the string to ""
	}

	inline void MinDic2::finishConstruction() {
		// store the very last word
		int i = wcslen( lastKey_ ); // let this be an integer, because it has to get -1 to break the loop below
		StateId_t storedState = 0;
		for(	 ; i >= 0; --i ) {
			storedState = replaceOrRegister( tempStates_[i] );
			tempStates_[i].reset();
			if( i > 0 ) tempStates_[i-1].addTransition( lastKey_[i-1], storedState, tempStates_[i].getPhValue() );
		}
		setRoot( storedState ); // declare tempStates_[0] to be the root

		// call destructors for tempStates and free the allocated memory
		for( size_t i = 0; i < Global::lengthOfStr; ++i ) {
			tempStates_[i].~TempState_t();
		}
		free( tempStates_ );
		delete( hashtable_ );

		TransTable_t::finishConstruction();

		header_.set( *this );
	}

	inline void MinDic2::compileDic( const char* txtFile ) {
		wchar_t* key = 0;

		std::wcout<<"csl::MinDic2::Before initConstruction()"<<std::endl;
		initConstruction();
		std::wcout<<"csl::MinDic2::After initConstruction()"<<std::endl;

		std::wifstream fileHandle( txtFile );
		fileHandle.imbue( CSL_UTF8_LOCALE ); // imbue the stream with csl's custom utf8 locale
		if( !fileHandle.good() ) {
		    throw exceptions::badFileHandle( "Couldn't open file '" + 
						     std::string( txtFile ) + 
						     "' for reading." );
		}

		std::wstring line;
		
		size_t lineCount = 0;
		while( std::getline( fileHandle, line ).good() )  {

			if ( line.length() > Global::lengthOfLongStr ) {
				throw exceptions::badInput( "csl::MinDic2::compileDic: Maximum length of input line violated (set by Global::lengthOfLongStr)" );
			}
			AnnType_t annotation;
			parseAnnotation( &line, &annotation );

			addToken( line.c_str(), annotation );
			++lineCount;
		}
		if( errno == EILSEQ ) { // catch encoding error
		    throw exceptions::badInput( "MinDic2::compileDic: Encoding error in input sequence." );
		}

		fileHandle.close();
		finishConstruction();
	}

	inline void MinDic2::parseAnnotation( std::wstring* str, AnnType_t* annotation ) const {

		size_t delimPos = str->find_first_of( Global::keyValueDelimiter );

		if( delimPos != str->npos ) {
			*annotation = wcstol( (str->substr( delimPos + 1 ) ).c_str() , 0, 0 );
			str->resize( delimPos );

		}
		else *annotation = 0;
	}

	inline void MinDic2::addToken( const wchar_t* key, const AnnType_t& annotation ) {
	    static size_t commonPrefix, lengthOfKey;
		static StateId_t storedState;

		key = key;

		// printf("input: %ls -> %d\n", key, annotation );


		// remark: maybe this could be spared if we remember the length during widechar-conversion
		lengthOfKey = wcslen( key );


		if( lengthOfKey == 0 ) {
			throw exceptions::badInput( "csl::MinDic2: Insertion of empty key " );
		}

		if( lengthOfKey > Global::lengthOfStr - 1 ) {
			throw exceptions::badInput( "MinDic2: Global::string_length sets the maximum string length for an entry of a MinDic2. Maximum violated" );
		}

		// check alphabetical order
		if( *lastKey_ && ( wcscmp( lastKey_, key ) >= 0 ) ) {
			std::wcerr<<"Alphabetical order violated:"<<std::endl
				<<"**********"<<std::endl
				<<lastKey_<<std::endl
				<<key<<std::endl
				<<"**********"<<std::endl;
			throw exceptions::badInput( "MinDic2::addToken: Alphabetical order violated" );
			exit( 1 );
		}

		///////////////////// store suffix of lastKey_
		commonPrefix = 0;
		while( ( key[commonPrefix] == lastKey_[commonPrefix] ) && key[commonPrefix] ) {
			++commonPrefix;
		}
		// e.g., commonPrefix==2 if first two letters of both words are equal


		for( size_t i = wcslen( lastKey_ ); i > commonPrefix; --i ) {
			storedState = replaceOrRegister( tempStates_[i] );
			tempStates_[i-1].addTransition( lastKey_[i-1], storedState, tempStates_[i].getPhValue() );
			tempStates_[i].reset();
		}

		//////////////////// set final state of key
		tempStates_[lengthOfKey].setFinal();
		tempStates_[lengthOfKey].setAnnotation( annotation );

		wcscpy( lastKey_, key );
		++nrOfKeys_;

		if( ! ( nrOfKeys_ %  100000 ) ) {
			std::wcerr	<< nrOfKeys_ /1000 << "k tokens processed. "
						<< TransTable_t::getNrOfStates() / 1000 << "k states."
						<< "key was: " << key 
						<< std::endl;
		}

	} // method addToken()

	inline StateId_t MinDic2::replaceOrRegister( TempState_t& state ) {
		StateId_t storedState = 0;
		if ( ( storedState = hashtable_->findState( state ) ) == 0 ) { // if equiv. state doesn't exist
			storedState = storeTempState( state ); // store it
			hashtable_->insert( state, storedState ); // add it to the hashtable
		}

		return storedState;
	}


	inline bool MinDic2::lookup( const wchar_t* key, AnnType_t* annotation ) const {
	    State st = getRootState();
	    while( *key && st.isValid() ) {
		st.walk( *key );
		++key;
	    }
	    if( ( *key == 0 ) && ( st.isFinal() ) ) {
		*annotation = st.getAnnotation();
		return true;
	    }
	    else {
		return false;
	    }
	}

	inline bool MinDic2::lookup( std::wstring const& key, AnnType_t* annotation ) const {
	    return lookup( key.c_str(), annotation );
	}

	inline bool MinDic2::hasPrefix( std::wstring const& prefix ) const {
		size_t state = getRoot();
		for( std::wstring::const_iterator c = prefix.begin(); c != prefix.end() && (state != 0) ; ++c ) {
			//std::wcout<<L"Walk with "<<(int)*c << std::endl;
			if( *c >200 ) {
				return false;
				// state.walk( 0 );
				//std::wcout << L"Walked "<< (int)*c << std::endl;
			}
			else state = walk( state, *c );
			//std::wcout << L"Walked"<< std::endl;
		}
		if( state > 0 ) {
			//std::wcout<<L"prefix"<<" is a prefix"<<std::endl;
			return true;
		}
		else {
			//std::wcout<<L"prefix"<<" is not a prefix"<<std::endl;
			return false;
		}
	}

	inline size_t MinDic2::getNrOfKeys() const {
		return nrOfKeys_;
	}

	inline void MinDic2::printDic() const {
	    std::wcout << "csl::MinDic2::printDic not implemented!" << std::endl;
	    exit( 1 );
		count_ = 0;
		printDic_rec( getRoot(), 0 );
	}

	inline void MinDic2::printDic_rec( StateId_t pos, int depth ) const {
// 		int newPos;
// 		static wchar_t w[Global::lengthOfStr];
// 		size_t newPerfHashValue;

// 		const wchar_t* transitions = getSusoString( pos );
// 		while( *transitions ) {
// 			newPerfHashValue = perfHashValue;;
// 			if( ( newPos = walkPerfHash( pos, *transitions, newPerfHashValue ) ) ) {
// 				w[depth] = *transitions;
// 				if( isFinal( newPos ) ) {
// 				    w[depth+1] = 0;
// 				    std::wcout<<w<<"#"<<getAnnotation( newPerfHashValue )<<std::endl;

// 					if( ( ++count_ % 100000 ) == 0 ) fprintf( stderr, "%d\n", (int)count_ );
// 				} // if isFinal
// 				printDic_rec( newPos, depth + 1, newPerfHashValue );

// 			} // if couldWalk
// 			else {
// 				throw exceptions::badDictFile( "suso-string seems to be corrupted." ); 
// 			}
// 			++transitions;
// 		} // while
	} // end of method


	inline void MinDic2::doAnalysis() const {

		TransTable_t::doAnalysis();
		printf( "**********\nMinDic2 Analysis\n**********\nnr of keys:\t%zd\n\n",
			nrOfKeys_
			);


	}

} //eon


