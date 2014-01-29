package csl.candidateExtractor;

import java.io.*;
/**
 * This class provides efficient extraction of correction candidates from
 * large dictionaries. Basically this will be a wrapper for the c++ class 
 * 'MSMatch' and/ or 'Bestmatch' from csl.
 * The interface as it is sketched here is far from fixed ...
 * 
 * @author Uli Reffle
 *
 */
public class CandidateExtractor {

    static {
	System.loadLibrary( "CandidateExtractor" );
    }

    public CandidateExtractor( int levDistance, String dicFile, String revDicFile ) {
    	initNativeCandExtractor( levDistance, dicFile, revDicFile );
    }

    protected void finalize() {
	destroyNativeCandExtractor();
    }
    
    /**
     * At the moment, this is a 1:1 - forwarder. Maybe the native function should get this name here ...
     */
    public void findCandidates( String pattern, int levDistance, CandidateReceiver candReceiver ) {
    	nativeQuery( pattern, levDistance, candReceiver );
    }

    public boolean lookup( String word ) {
    	return nativeLookup( word );
    }

    public static void main( String[] argv ) throws IOException {
	if( argv.length < 3 ) {
	    System.out.println( "Give a levDistance and two dicfiles" );
	    System.exit( 1 );
	}
	CandidateExtractor candExtractor = new CandidateExtractor( Integer.parseInt( argv[0] ), argv[1], argv[2] );

	MyCandReceiver candReceiver = new MyCandReceiver();

	BufferedReader reader = new BufferedReader( new InputStreamReader( System.in ) );
	String str;
	while( ( str = reader.readLine() ) != null ) {
	    System.out.println( "TOKEN: " + str );
 	    if( candExtractor.lookup( str ) ) {
 	    	System.out.println( str + " is in lex.");
 	    }
	    candExtractor.findCandidates( str, 2, candReceiver );
	}
    }

    private native void initNativeCandExtractor( int levDistance, String dicFile, String revDicFile );
    private native void destroyNativeCandExtractor();
    private native void nativeQuery( String pattern, int levDistance, CandidateReceiver candReceiver );
    
    /**
     * @param[in] word
     * @return true if word was found in the dict
     */
    public native boolean nativeLookup( String word );

    private long msMatchPointer_;
    
}

class MyCandReceiver implements CandidateReceiver {
    public void receive( String str, float levDistance, float frequency ) {
    	System.out.println( "(" + str +", " + levDistance + ", " + frequency + ")" );
    }
}
