/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package csl.DictSearch;

import java.util.ArrayList;
import java.util.List;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author uli
 */
public class DictSearchTest {
    
    public DictSearchTest() {
    }

    @BeforeClass
    public static void setUpClass() throws Exception {
    }

    @AfterClass
    public static void tearDownClass() throws Exception {
    }
    
    @Before
    public void setUp() {
    }
    
    @After
    public void tearDown() {
    }

    /**
     * Test of query method, of class DictSearch.
     */
    @Test
    public void testConstructor() {
        DictSearch instance;
        try {
            instance = new DictSearch("/no/such/inifile");
            fail( "Expected an exception to be thrown.");
        } catch (DictSearchException ex) {
            // is expected
        }
        
    }

    /**
     * Test of query method, of class DictSearch.
     */
    @Test
    public void testQuery() {
        System.out.println("query");

        try {
            DictSearch instance = new DictSearch("/daten/implement/OCRC_trunk/dictionaries/ocrc.ini");
            
            List<Interpretation> l = instance.query( "theil" );
            
            assertEquals( 1, l.size() );

        } catch (DictSearchException ex) {
            fail( "Unexpected exception" + ex.getMessage() );
        }
        
    }

}
