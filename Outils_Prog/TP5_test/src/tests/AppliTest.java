//binome Jeremy ROUSSEY - Bastien CHANEZ
package tests;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Test;
import org.junit.Before;
import org.junit.runner.RunWith;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;
import static org.mockito.ArgumentMatchers.anyInt;

// Mockito
import org.mockito.Mockito;
import org.mockito.junit.MockitoJUnitRunner;


// Systeme sous test
import fr.ufc.l3info.oprog.*;


@RunWith(MockitoJUnitRunner.class)

public class AppliTest {
    private ATM atm;
    private MyCard card;
    private Account account;

    @Before
    //Setting up the card, the account and the ATM
    public void setUp() {
        atm = new ATM();
        card = new MyCard();
        account = new Account(100);
    }

    //Testing the card
    @Test
    public void testCard(){

        //Test set pin
        assertEquals(false, card.setPin(99999));
        assertEquals(false, card.setPin(-1243));

        //Test checkpin
        assertEquals(false, card.checkPin(1234));

        //Test set account null
        assertEquals(false, card.setAccount(null));

        //Test card blocked
        assertEquals(true, card.isBlocked());

        assertEquals(false, card.endPersonalization());

        assertEquals(true, card.setPin(1234));
        card.setPin(1234);

        assertEquals(false, card.checkPin(1234));

        assertEquals(false, card.endPersonalization());

        assertEquals(true, card.setAccount(account));
        card.setAccount(account);

        assertEquals(true, card.endPersonalization());

        assertEquals(false, card.checkPin(0000));
        //remaining_tries = 2
        assertEquals(false, card.isBlocked());
        assertEquals(true, card.checkPin(1234));

        assertEquals(false, card.setAccount(null));
        assertEquals(false, card.setAccount(account));

        assertEquals(false, card.setPin(99999));
        assertEquals(false, card.setPin(-99999));
        assertEquals(false, card.setPin(1234));

        assertEquals(false, card.endPersonalization());

        card.checkPin(0001);
        //remaining tries = 2
        card.checkPin(0002);
        //remaining tries = 1
        card.checkPin(0003);
        //remaining tries = 0
        assertEquals(true, card.isBlocked());

        assertEquals(account, card.getAccount());
    }

    @Test
    public void testAccount(){
        assertEquals(true, account.debit(60));
        assertEquals(false, account.debit(60));

        account.credit(60);
        assertEquals(account.balance, 100);
    }

    //Method to init a card
    public void initCard(){
        card.setPin(1234);
        card.setAccount(account);
        card.endPersonalization();
    }

    //Method to init a blocked card
    public void initBlockedCard(){
        card.setPin(1234);
        card.setAccount(account);
        card.endPersonalization();
        for (int i = 0; i<3; i++){
            card.checkPin(0000);
        }
    }


    @Test(expected=ATM.NullCardException.class)
    public void testATMInsertCard0() throws ATM.NullCardException {
        atm.insertCard(null);
    }

    @Test
    public void testATMInsertCard1() throws ATM.NullCardException {
        initCard();
        int r = atm.insertCard(card);
        assertEquals(0, r);
        r = atm.insertCard(card);
        assertEquals(-1, r);
    }

    @Test
    public void testATMInsertCard2() throws ATM.NullCardException {
        initBlockedCard();
        int r = atm.insertCard(card);
        assertEquals(-2, r);
    }

    @Test
    public void testATMinputPin0(){
        assertEquals(-1, atm.inputPin(1234));
    }

    @Test
    public void testATMInputPin1() throws ATM.NullCardException{
        initCard();
        int r = atm.insertCard(card);
        assertEquals(0, r);
        r = atm.inputPin(0000);
        assertEquals(-2, r);
    }

    @Test
    public void testATMInputPin2() throws ATM.NullCardException{
        initCard();
        int r = atm.insertCard(card);
        assertEquals(0, r);
        r = atm.inputPin(1234);
        assertEquals(0, r);
    }

    @Test
    public void testATMInputPin3() throws ATM.NullCardException{
        initCard();
        int r = atm.insertCard(card);
        assertEquals(0, r);
        card.checkPin(0000);
        card.checkPin(0000);
        r = atm.inputPin(0000);
        assertEquals(-3, r);
    }

    @Test
    public void testATMChooseAmount0(){
        int r = atm.chooseAmount(10);
        assertEquals(-1, r);
    }

    @Test
    public void testATMChooseAmount1() throws ATM.NullCardException{
        initCard();
        int r = atm.insertCard(card);
        assertEquals(0, r);
        r = atm.inputPin(1234);
        assertEquals(0, r);
        r = atm.chooseAmount(-1);
        assertEquals(-2, r);
    }

    @Test
    public void testATMChooseAmount2() throws ATM.NullCardException{
        initCard();
        int r = atm.insertCard(card);
        assertEquals(0, r);
        r = atm.inputPin(1234);
        assertEquals(0, r);
        r = atm.chooseAmount(0);
        assertEquals(0, r);
        MyCard c = (MyCard) atm.takeCard();
        assertEquals(card, c);
        int[] b = atm.takeBills();
        assertEquals(null, b);
    }

    @Test
    public void testATMChooseAmount3() throws ATM.NullCardException {
        testChooseAmountPUT(20);
    }
    @Test
    public void testATMChooseAmount4() throws ATM.NullCardException {
        testChooseAmountPUT(30);
    }
    @Test
    public void testATMChooseAmount5() throws ATM.NullCardException {
        testChooseAmountPUT(40);
    }
    @Test
    public void testATMChooseAmount6() throws ATM.NullCardException {
        testChooseAmountPUT(50);
    }
    @Test
    public void testATMChooseAmount7() throws ATM.NullCardException {
        testChooseAmountPUT(80);
    }
    @Test
    public void testATMChooseAmount8() throws ATM.NullCardException {
        testChooseAmountPUT(100);
    }

    /** Demande de retrait d'une somme non autorisÃ©e */
    @Test
    public void testATMChooseAmount9() throws ATM.NullCardException {
        initCard();
        account.debit(100);
        int r = atm.insertCard(card);
        assertEquals(0, r);
        r = atm.inputPin(1234);
        assertEquals(0, r);
        r = atm.chooseAmount(20);
        assertEquals(-3, r);
    }




    private void testChooseAmountPUT(int a) throws ATM.NullCardException {
        initCard();
        int r = atm.insertCard(card);
        assertEquals(0, r);
        r = atm.inputPin(1234);
        assertEquals(0, r);
        r = atm.chooseAmount(a);
        assertEquals(0, r);
        Card c = atm.takeCard();
        assertEquals(card, c);
        int[] b = atm.takeBills();
        assertFalse(b == null);
        int total = 0;
        for (int i=0; i < b.length; i++) {
            total += b[i];
        }
        assertEquals(a, total);
    }

    @Test
    public void testATMTakeCard(){
        assertNull(atm.takeCard());
    }
}

//Result : 100% methods - 100% classes - 100% lines covered
//                  -- Decisions covered if possible
