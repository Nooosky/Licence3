//binome Jeremy ROUSSEY - Bastien CHANEZ
package tests;

// JUnit
import org.junit.Test;
import org.junit.Before;
import org.junit.runner.RunWith;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;

// Mockito
import org.mockito.Mockito;
import org.mockito.junit.MockitoJUnitRunner;

// Systeme sous test
import fr.ufc.l3info.oprog.*;


@RunWith(MockitoJUnitRunner.class)
public class MyCardTest {

    private MyCard testCard;
    private Account mockedAccount;

    @Before
    public void setUp() {
        testCard = new MyCard();
        mockedAccount = Mockito.mock(Account.class);
    }

    /**
     *  Card personalization.
     */
    private void personalizeCard() {
        testCard.setAccount(mockedAccount);
        testCard.setPin(1234);
        testCard.endPersonalization();
    }

    /**
     * Tests de la phase de personnalisation de la carte
     */

    @Test
    public void testPerso0() {
        assertNull(testCard.getAccount());
    }

    @Test
    public void testPerso1() {
        assertFalse(testCard.setAccount(null));
    }

    @Test
    public void testPerso2() {
        assertTrue(testCard.setAccount(mockedAccount));
        assertEquals(mockedAccount, testCard.getAccount());
        assertFalse(testCard.endPersonalization());
    }

    @Test
    public void testPerso3() {
        assertFalse(testCard.setPin(-1));
    }

    @Test
    public void testPerso4() {
        assertTrue(testCard.setPin(1234));
        assertFalse(testCard.endPersonalization());
    }

    @Test
    public void testPerso5() {
        assertTrue(testCard.setAccount(mockedAccount));
        assertTrue(testCard.setPin(1234));
        assertTrue(testCard.endPersonalization());
    }

    @Test
    public void testPerso6() {
        Account a = Mockito.mock(Account.class);
        assertTrue(testCard.setAccount(mockedAccount));
        assertTrue(testCard.setAccount(a));
        assertTrue(testCard.setPin(1234));
        assertTrue(testCard.setPin(4321));
        assertTrue(testCard.endPersonalization());
        assertEquals(a, testCard.getAccount());
        assertTrue(testCard.checkPin(4321));
    }

    @Test
    public void testPerso7() {
        Account a = Mockito.mock(Account.class);
        assertTrue(testCard.setAccount(mockedAccount));
        assertTrue(testCard.setPin(1234));
        assertTrue(testCard.endPersonalization());
        assertFalse(testCard.setAccount(a));
        assertEquals(mockedAccount, testCard.getAccount());
        assertFalse(testCard.setPin(4321));
        assertFalse(testCard.checkPin(4321));
        assertTrue(testCard.checkPin(1234));
    }


    /**
     * Tests de la phase d'utilisation de la carte
     */

    @Test
    public void testUse0() {
        assertTrue(testCard.setPin(1234));
        assertFalse(testCard.checkPin(1234));
    }

    @Test
    public void testUse1() {
        personalizeCard();
        assertFalse(testCard.checkPin(-1));
    }

    @Test
    public void testUse2() {
        personalizeCard();
        assertTrue(testCard.checkPin(1234));
    }

    @Test
    public void testUse3() {
        personalizeCard();
        assertFalse(testCard.checkPin(4321));
        assertFalse(testCard.checkPin(4321));
        assertTrue(testCard.checkPin(1234));
    }


    /**
     * Tests de la phase de blocage de la carte
     */

     //Testing the card
     @Test
     public void testCard(){

         //Test set pin
         assertEquals(false, testCard.setPin(99999));
         assertEquals(false, testCard.setPin(-1243));

         //Test checkpin
         assertEquals(false, testCard.checkPin(1234));

         //Test set account null
         assertEquals(false, testCard.setAccount(null));

         //Test card blocked
         assertEquals(true, testCard.isBlocked());

         assertEquals(false, testCard.endPersonalization());

         assertEquals(true, testCard.setPin(1234));
         testCard.setPin(1234);

         assertEquals(false, testCard.checkPin(1234));

         assertEquals(false, testCard.endPersonalization());

         assertEquals(true, testCard.setAccount(mockedAccount));
         testCard.setAccount(mockedAccount);

         assertEquals(true, testCard.endPersonalization());

         assertEquals(false, testCard.checkPin(0000));
         //remaining_tries = 2
         assertEquals(false, testCard.isBlocked());
         assertEquals(true, testCard.checkPin(1234));

         assertEquals(false, testCard.setAccount(null));
         assertEquals(false, testCard.setAccount(mockedAccount));

         assertEquals(false, testCard.setPin(99999));
         assertEquals(false, testCard.setPin(-99999));
         assertEquals(false, testCard.setPin(1234));

         assertEquals(false, testCard.endPersonalization());

         testCard.checkPin(0001);
         //remaining tries = 2
         testCard.checkPin(0002);
         //remaining tries = 1
         testCard.checkPin(0003);
         //remaining tries = 0
         assertEquals(true, testCard.isBlocked());

         assertEquals(mockedAccount, testCard.getAccount());
     }

     //Testing the card
     @Test
     public void testCard2(){

         //Test set pin
         assertEquals(false, testCard.setPin(99999));
         assertEquals(false, testCard.setPin(-1243));

         //Test checkpin
         assertEquals(false, testCard.checkPin(1234));

         //Test set account null
         assertEquals(false, testCard.setAccount(null));

         //Test card blocked
         assertEquals(true, testCard.isBlocked());

         assertEquals(false, testCard.endPersonalization());

         assertEquals(true, testCard.setPin(1234));
         testCard.setPin(1234);

         assertEquals(false, testCard.checkPin(1234));

         assertEquals(false, testCard.endPersonalization());

         assertEquals(true, testCard.setAccount(mockedAccount));
         testCard.setAccount(mockedAccount);

         assertEquals(true, testCard.endPersonalization());

         assertEquals(false, testCard.checkPin(0000));
         //remaining_tries = 2
         assertEquals(false, testCard.isBlocked());
         assertEquals(true, testCard.checkPin(1234));

         assertEquals(false, testCard.setAccount(null));
         assertEquals(false, testCard.setAccount(mockedAccount));

         assertEquals(false, testCard.setPin(99999));
         assertEquals(false, testCard.setPin(-99999));
         assertEquals(false, testCard.setPin(1234));

         assertEquals(false, testCard.endPersonalization());

         testCard.checkPin(0001);
         //remaining tries = 2
         testCard.checkPin(0002);
         //remaining tries = 1
         testCard.checkPin(0003);
         //remaining tries = 0
         assertEquals(true, testCard.isBlocked());

         assertEquals(mockedAccount, testCard.getAccount());
     }
}
