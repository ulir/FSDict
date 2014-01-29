
import java.util.*;
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
	System.loadLibrary( "JNICandidateExtractor" );
    }

    public CandidateExtractor( String alphFile, int levDistance, String dicFile, String revDicFile ) {
    	initNativeCandExtractor( alphFile, levDistance, dicFile, revDicFile );
    }

    protected void finalize() {
	destroyNativeCandExtractor();
    }
    
    /**
     * At the moment, this is a 1:1 - forwarder. Maybe the native function should get this name here ...
     */
    public void findCandidates( String pattern, int levDistance, CandidateReceiver candReceiver  ) {
	nativeQuery( pattern, levDistance, candReceiver );
    }

    public static void main( String[] argv ) throws IOException {
	if( argv.length < 4 ) {
	    System.out.println( "Give alphfile, a levDistance and two dicfiles" );
	}
	CandidateExtractor candExtractor = new CandidateExtractor( argv[0], Integer.parseInt( argv[1] ), argv[2], argv[3] );

	MyCandReceiver candReceiver = new MyCandReceiver();

	BufferedReader reader = new BufferedReader( new InputStreamReader( System.in ) );
	String str = "test";
	while( ( str = reader.readLine() ) != null ) {
	    candExtractor.findCandidates( str, 2, candReceiver );
	}
    }

    private native void initNativeCandExtractor( String alphFile, int levDistance, String dicFile, String revDicFile );
    private native void destroyNativeCandExtractor();
    private native void nativeQuery( String pattern, int levDistance, CandidateReceiver candReceiver );
    
    /**
     * @param[in] pattern
     * @param[out] frequency
     */
    public native boolean lookup( String pattern, Float frequency );

    private long msMatchPointer_;
    private long alphPointer_;

}

class MyCandReceiver implements CandidateReceiver {
    public void receive( String str, float levDistance, float frequency ) {
	System.out.println( "(" + str +", " + levDistance + ", " + frequency + ")" );
    }
}
