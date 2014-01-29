package csl.DictSearch;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author uli
 */
public class DictSearch {

    static {
        System.loadLibrary( "JNIDictSearch" );
    }
    
    
    public DictSearch( String configFile ) throws DictSearchException {
        pointer_ = native_init(configFile);  
    }
    
    /**
     *
     */
    private class ResultReceiver {
        ResultReceiver( List<Interpretation> init_l ) {
            l = init_l;
        }
        void receive( String answerString ) {
            Interpretation i = new Interpretation( answerString );
            l.add( i );
            
        }
        
        private List<Interpretation> l;
    }
    
    public List<Interpretation> query( String q ) {
        List answerList = new ArrayList<Interpretation>();
        native_query( q, new ResultReceiver( answerList ) );
        
        return answerList;
    }
    
    
    
    private native long native_init( String config ) throws DictSearchException;

    private native void native_query(String q, ResultReceiver answerList );
    
    private long pointer_;
    
    
    public static void main( String[] argv ) {
        try {
            DictSearch ds = new DictSearch( argv[0] );
            java.io.BufferedReader stdin = new java.io.BufferedReader(new java.io.InputStreamReader(System.in));
            String line;
            List<Interpretation> cands;
            while( ( line = stdin.readLine() ) != null ) {
                cands = ds.query( line );
                Iterator<Interpretation> it  = cands.iterator();
                while( it.hasNext() ) {
                    System.out.println( it.next().toString() );
                }
            }
        } catch (Exception ex) {
            Logger.getLogger(DictSearch.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }
    
} // class DictSearch
