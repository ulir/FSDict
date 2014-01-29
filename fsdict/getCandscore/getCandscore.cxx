#include "../Global.h"
#include "../MSMatch/MSMatch.h"
#include "../ResultSet/ResultSet.h"
#include "../Alphabet/Alphabet.h"
#include<iostream>
#include<vector>
using namespace fsdict;

class Pair {
public:
    Pair( uchar* w, int f, int c ) {
	strncpy( (char*)word, (char*)w, Global::lengthOfWord );
	if( word[Global::lengthOfWord-1] != 0 ) {
	    throw exceptions::badInput("Input word too long");
	}
	freq = f;
	candscore = c;
    }
    uchar word[Global::lengthOfWord]; // perhaps lengthOfWord would be enough ...
    int freq;
    int candscore;
};

int main(int argc, char** args) {
    if(argc!=5) {
	std::cerr<<"Use like: ./bin/getCandscore alph.azb tokens.alph.dic tokens.rev.dic tokens.freq.lex"<<std::endl;
	exit(1);
    }

    Alphabet alph(args[1]);
    MSMatch< FW_BW > ms( alph, 1, args[2], args[3] );
    ResultSet rset( alph );

//     int tableSize = 200000;
//     Pair* table = (Pair*)malloc( tableSize * sizeof(Pair) );
//     memset(table,0,tableSize * sizeof(Pair));

    std::vector<Pair> table;

    size_t nrOfWords;


    uchar line[Global::lengthOfLongStr];
    uchar *word, *freqStr;

    // read file
    std::cerr<<"Read file ... "<<std::flush;
    FILE* FREQLIST = fopen( args[4], "r" );
    if( ! FREQLIST ) {
	std::cerr<<"Couldn't open freq file: "<<args[3]<<std::endl;
	exit(1);
    }
    while( 
	fgets( (char*)line, Global::lengthOfLongStr, FREQLIST ) ) {
	if( line[Global::lengthOfStr - 1] != 0 ) {
	    throw exceptions::badInput( "getCandscore: query string too long." );
	}
	line[strlen( ( char* )line )-1] = 0; // delete newline

	word = line;
	freqStr = (uchar*)strchr( (char*)line, (char)Global::keyValueDelimiter );
	*freqStr = 0;
	++freqStr;
	// printf( "Token is '%s', value is '%s'\n", word, freqStr ); // DEBUG
	table.push_back( Pair( word, atoi((char*)freqStr ), 0 ) );
    }
    nrOfWords = table.size();
    fclose( FREQLIST );
    std::cerr<<"ok, read "<<nrOfWords<<" lines."<<std::endl;

    for( size_t count=0; count < nrOfWords; ++count) {
	try {
	    rset.reset();
	
 	    ms.query( table.at(count).word, rset );
	    
	    for(int i=0;i<rset.getSize();++i) {
		table.at( rset[i].getAnn() ).candscore += table.at( count ).freq;
	    }
	    if(count%10000 == 0) std::cerr<<"\rProcessed "<<count<<" words."<<std::flush;
	}
	catch( exceptions::fsdictException ex ) {
	    std::cerr<<"getCandscore: Caught exception: skipped candidate production for one token"<<std::endl;
	} 
    }

    // print the dictionary with the computed annotations to stdout
    fprintf(stderr, "nrOfWords=%d\n", nrOfWords );
    for( size_t count=0; count<nrOfWords; ++count ) {
//	fprintf(stderr, "count=%d\n", count );
	printf( "%s#%d\n", table[count].word, table[count].candscore );
    }

    std::cerr<<"done"<<std::endl;
    return( 0 );
}
