#ifndef FSDICT_TRIE_CXX
#define FSDICT_TRIE_CXX FSDICT_TRIE_CXX


#include "./Trie.h"

namespace fsdict {

    Trie::Trie( char* binFile ) : TransTable< TT_PERFHASH >() {
	if( binFile ) loadFromFile( binFile );
	annotateByteOffset_ = false;
    }

    void Trie::compileDic( char* txtFile, char* compFile ) {
	TransTable_t::initConstruction();
	tempStates_ = new std::vector<TempState>( Global::lengthOfStr );

	std::ifstream fileHandle( txtFile );
        if( !fileHandle.good() ) {
            throw exceptions::badFileHandle( std::string( "Couldn't open dictionary file: " ) +
                                             std::string( txtFile ) );
        }

	wchar_t line[Global::lengthOfLongStr];
	unsigned char bytesIn[Global::lengthOfLongStr];

	count_ = 0;
	
	byteOffset_ = 0;
	key = 0; // does not point to anything
	*lastKey = 0; // reset the string to ""
	
	dotShot();
	while( fileHandle.getline( (char*)bytesIn, Global::lengthOfLongStr ) )  {
	    mbstowcs( line, (char*)bytesIn, Global::lengthOfLongStr );
//	    fprintf( stderr, "%d\t%ls\n", count_, line ); //DEBUG!
	    
	    addToken( line );
	    ++count_;
	    if( !( count_ %  10000 ) ) {
		std::cerr << "\r" << count_ << " tokens processed." << std::flush;
	    }
	    byteOffset_ = 42;
	}
	std::cerr << "\r" << count_ << " tokens processed." << std::endl;
	fileHandle.close();

	// store the very last word
	int i = wcslen( lastKey );
	for( ; i > 0; --i ) {
	    uint_t storedState = storeTempState( tempStates_->at( i ) );
	    tempStates_->at( i ).reset();
	    tempStates_->at( i-1 ).addTransition( lastKey[i-1], storedState, 0 ); // 3rd arg is for perfect hashing, not used here
	}

	setRoot( storeTempState( tempStates_->at( 0 ) ) ); // store root and give root's id to TransTable
	
	key = 0; // no more keys
	dotShot();


	TransTable_t::finishConstruction();

	// dump memory to file
	createBinary( compFile );
    }


    /**
       @except out_of_range 
    */
    void Trie::addToken( wchar_t* input ) {

	static int commonPrefix, i, lengthOfKey;
	static int storedState;


	/////////////////// PARSE THE INPUT STRING
	wchar_t *c, *begin;
	c = wcschr( input, Global::keyValueDelimiter );

	if( c ) {
	    *c = 0;
	    key = input;
	    valueString = ( c + 1 );
	} else { // no values given
	    key = input;
	    valueString[0] = 0;
	}
	lengthOfKey = wcslen( key );
	if( lengthOfKey > Global::lengthOfStr ) {
	    throw exceptions::outOfRange( "Trie.cxx: Global::string_length sets the maximum string length for an entry of a trie. maximum violated" );
	}

	// check alphabetical order
	if( *key && wcscmp( lastKey, key ) > 0 ) {
	    std::wcout << "Alphabetical order violated:" << std::endl
		      << lastKey << std::endl
		      << key << std::endl;
	    exit( 1 );
	}

//	printf( "addToken: %ls\n", key );

	///////////////////// store suffix of lastKey
	commonPrefix = 0;
	while( ( key[commonPrefix] == lastKey[commonPrefix] ) && key[commonPrefix] ) {
	    ++commonPrefix;
	}
	// e.g., commonPrefix==2 if first two letters of both words are equal

	i = wcslen( lastKey );
	for( ; i > commonPrefix; --i ) {
	    storedState = storeTempState( tempStates_->at( i ) );
	    tempStates_->at( i ).reset();
	    tempStates_->at( i-1 ).addTransition( lastKey[i-1], storedState, 0 ); // ignore 3rd arg (for perfect hashing)
	}


	//////////////////// set final state of key and add all the values
	tempStates_->at( lengthOfKey ).setFinal( true );

	if( *valueString ) { // if valueString not empty
	    begin = valueString;
	    c = begin;

	    do { // traverse valueString
		++c;
		if( *c == Global::valuesDelimiter || ( *c == 0 ) ) { // some avoidable loops are happening here,but nevermind
		    *c = 0;
		    tempStates_->at( lengthOfKey ).addAnnotation( atoi( (char*)begin ) ); // add annotation to tempState
		    begin = c + 1;
		}
	    } while ( *c );
	} else if( annotateByteOffset_ == true ) { // obviously there were no values given in the string.
	    tempStates_->at( lengthOfKey ).addAnnotation( byteOffset_ ); // use byte-offset as value
	} else if( annotateWordCount_ == true ) {
	    tempStates_->at( lengthOfKey ).addAnnotation( count_ ); // use wordcount as value
	}
	dotShot();
	wcscpy( lastKey, key );
    }

    void Trie::printDic( int initState ) const {
	if( initState == 0 ) initState = getRoot();
	count_ = 0;
	printDic_rec( initState, 0 );
    }

    void Trie::printDic_rec( int pos, int depth ) const {
	static uint_t newPos;
	static wchar_t w[Global::lengthOfStr];

 	for( Alphabet::ConstCharIterator charIt = getConstAlphabet().begin(); charIt != getConstAlphabet().end(); ++charIt ) {
	    if( ( newPos = walk( pos, *charIt ) ) ) {
		w[depth] = *charIt;

		if( isFinal( newPos ) ) {
		    w[depth+1] = 0;
		    printf("%ls", w );
		    
		    if( hasAnnotations( newPos ) ) {
			std::cout << Global::keyValueDelimiter;
			AnnIterator it( *this, newPos );
			while( it.isValid() ) {
			    printf( "%d, ", *it );
			    ++it;
			}
		    }
		    printf( "\n" );
		    
		    if( ( ++count_ % 100000 ) == 0 ) fprintf( stderr, "%d\n", count_ );
		} // if isFinal
		
		printDic_rec( newPos, depth + 1 );
	    } // if couldWalk
 	} // for
    } // Trie::printDic_rec

    void Trie::dotShot() const {
	Cell_t * cellArray = TransTable_t::getCells();
	printf( "Digraph TransTable_out { //DOTCODE\nrankdir=LR;ordering=out; //DOTCODE\n"  );
	for ( size_t i = 1; i < getSizeOfUsedCells(); ++i ) {
	    if ( cellArray[i].isOfType( Cell_t::TRANS ) ) {
		int base = i - cellArray[i].getKey();
		// depending on whether a pointer to an Alphabet-object was given,
		// print either the coded integer or the decoded character
		printf( "%d->%d[label=\"%lc\"] //DOTCODE\n", base, cellArray[i].getValue(), cellArray[i].getKey() );
	    } else if ( cellArray[i].isOfType( Cell_t::STATE ) ) {
		int peripheries = ( cellArray[i].isOfType( Cell_t::FINALSTATE ) ) ? 2 : 1;
		printf( "%d[peripheries=%d] //DOTCODE\n", i, peripheries );

		if ( cellArray[i].isOfType( Cell_t::HAS_ANN ) ) {
		    printf( "%d->%d[label=\"[", i, i );

		    AnnIterator it( *this, i );
		    while ( it.isValid() ) {
			printf( "%d,", *it );
			++it;
		    }
		    printf( "]\",fontcolor=blue,style=dotted,dir=none] //DOTCODE\n" );
		}
	    }
	}

	size_t lengthOfKey = ( key )? wcslen( key ) : 0;
	for( size_t i = 0; i < lengthOfKey; ++i ) {
	    const TempState& state = (*tempStates_)[i];
	    int peripheries = ( state.isFinal() ) ? 2 : 1;
	    printf( "t%d[peripheries=%d, shape=rectangle] //DOTCODE\n", i, peripheries );

	    for( TempState::ConstIterator it = state.getConstIterator(); it.isValid(); ++it ) {
		printf( "t%d->%d[label=\"%lc\"] //DOTCODE\n", i, it->getTarget(), it->getLabel() );
	    }
	    printf( "t%d->t%d[label=\"%lc\",color=gray] //DOTCODE\n", i, i+1, key[i] );
	}
	size_t i = lengthOfKey;
	const TempState& state = (*tempStates_)[i];
	int peripheries = ( state.isFinal() ) ? 2 : 1;
	printf( "t%d[peripheries=%d, shape=rectangle] //DOTCODE\n", i, peripheries );


	printf( "} //DOTCODE\n" );
	
    }


} //eon


#endif
