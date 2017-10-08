package tests;

import org.junit.Test;
import org.junit.Before;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotEquals;

import org.mockito.Mockito;
import org.mockito.junit.MockitoJUnitRunner;

import org.junit.runner.RunWith;

import fr.ufc.l3info.oprog.*;

@RunWith(MockitoJUnitRunner.class)
public class testATM {

    ATM ATMUnderTest = null;

    @Before
    public void setUp() {
        ATMUnderTest = new ATM();
    }

    @Test
    public void testInsertCard2() throws ATM.NullCardException {
        Card card = Mockito.mock(Card.class);
        Mockito.when(card.isBlocked()).thenReturn(false);
        ATMUnderTest.insertCard(card);

        assertEquals(ATMUnderTest.insertCard(card), -1);
    }

    @Test
    public void testInsertCard3() throws ATM.NullCardException {
      Card card = Mockito.mock(Card.class);
      Mockito.when(card.isBlocked()).thenReturn(true);

      assertEquals(ATMUnderTest.insertCard(card), -2);
    }

    @Test
    public void testInsertCard4() throws ATM.NullCardException {
      Card card = Mockito.mock(Card.class);
      Mockito.when(card.isBlocked()).thenReturn(false);

      assertEquals(ATMUnderTest.insertCard(card), 0);
    }


    @Test
    public void testInputPin1() {

      assertEquals(ATMUnderTest.inputPin(0), -1);
    }


    @Test
    public void testInputPin2() throws ATM.NullCardException {
      Card card = Mockito.mock(Card.class);
      Mockito.when(card.isBlocked()).thenReturn(false);
      ATMUnderTest.insertCard(card);
      Mockito.when(card.checkPin(0000)).thenReturn(true);

      assertEquals(ATMUnderTest.inputPin(0000), 0);
    }

    @Test
    public void testInputPin3() throws ATM.NullCardException {
      Card card = Mockito.mock(Card.class);
      Mockito.when(card.isBlocked()).thenReturn(false);
      ATMUnderTest.insertCard(card);
      Mockito.when(card.checkPin(0000)).thenReturn(false);
      Mockito.when(card.isBlocked()).thenReturn(true);

      assertEquals(ATMUnderTest.inputPin(0000), -3);
    }


    @Test
    public void testInputPin4() throws ATM.NullCardException {
      Card card = Mockito.mock(Card.class);
      Mockito.when(card.isBlocked()).thenReturn(false);
      ATMUnderTest.insertCard(card);
      Mockito.when(card.checkPin(0000)).thenReturn(false);

      assertEquals(ATMUnderTest.inputPin(0000), -2);
    }

    @Test
    public void testChooseAmount1() {

      assertEquals(ATMUnderTest.chooseAmount(0), -1);
    }

    @Test
    public void testChooseAmount2() throws ATM.NullCardException {
      Card card = Mockito.mock(Card.class);
      Mockito.when(card.isBlocked()).thenReturn(false);
      ATMUnderTest.insertCard(card);
      Mockito.when(card.checkPin(0000)).thenReturn(true);
      ATMUnderTest.inputPin(0000);

        for (int a = 0; a<100; ++a)
        {
            if (a != 0 && a != 20 && a != 30 && a != 40 && a != 50 && a != 80 && a != 100)
                assertEquals(ATMUnderTest.chooseAmount(a), -2);
        }
    }

    @Test
     public void testChooseAmount3_1() throws ATM.NullCardException {
       Card card = Mockito.mock(Card.class);
       Account account = Mockito.mock(Account.class);
       Mockito.when(card.isBlocked()).thenReturn(false);
       ATMUnderTest.insertCard(card);
       Mockito.when(card.checkPin(0000)).thenReturn(true);
       ATMUnderTest.inputPin(0000);

       assertEquals(ATMUnderTest.chooseAmount(0), 0);
     }

   @Test
    public void testChooseAmount3_2() throws ATM.NullCardException {
      Card card = Mockito.mock(Card.class);
      Account account = Mockito.mock(Account.class);
      Mockito.when(card.isBlocked()).thenReturn(false);
      ATMUnderTest.insertCard(card);
      Mockito.when(card.checkPin(0000)).thenReturn(true);
      ATMUnderTest.inputPin(0000);
      Mockito.when(card.getAccount()).thenReturn(account);
      Mockito.when(account.canWithdraw(20)).thenReturn(true);

      assertEquals(ATMUnderTest.chooseAmount(20), 0);
    }

    @Test
     public void testChooseAmount4() throws ATM.NullCardException {
       Card card = Mockito.mock(Card.class);
       Account account = Mockito.mock(Account.class);
       Mockito.when(card.isBlocked()).thenReturn(false);
       ATMUnderTest.insertCard(card);
       Mockito.when(card.checkPin(0000)).thenReturn(true);
       ATMUnderTest.inputPin(0000);
       Mockito.when(card.getAccount()).thenReturn(account);

       Mockito.when(account.canWithdraw(20)).thenReturn(false);
       assertEquals(ATMUnderTest.chooseAmount(20), -3);

       Mockito.when(account.canWithdraw(30)).thenReturn(false);
       assertEquals(ATMUnderTest.chooseAmount(30), -3);

       Mockito.when(account.canWithdraw(40)).thenReturn(false);
       assertEquals(ATMUnderTest.chooseAmount(40), -3);

       Mockito.when(account.canWithdraw(50)).thenReturn(false);
       assertEquals(ATMUnderTest.chooseAmount(50), -3);

       Mockito.when(account.canWithdraw(80)).thenReturn(false);
       assertEquals(ATMUnderTest.chooseAmount(80), -3);

       Mockito.when(account.canWithdraw(100)).thenReturn(false);
       assertEquals(ATMUnderTest.chooseAmount(100), -3);
     }

     @Test
      public void takeCard1() {

        assertEquals(ATMUnderTest.takeCard(), null);
      }

    @Test
     public void takeCard2_prepareBills100() throws ATM.NullCardException {
      Card card = Mockito.mock(Card.class);
      Account account = Mockito.mock(Account.class);
      Mockito.when(card.isBlocked()).thenReturn(false);
      ATMUnderTest.insertCard(card);
      Mockito.when(card.checkPin(0000)).thenReturn(true);
      ATMUnderTest.inputPin(0000);
      Mockito.when(card.getAccount()).thenReturn(account);
      Mockito.when(account.canWithdraw(100)).thenReturn(true);
      ATMUnderTest.chooseAmount(100);

      assertEquals(ATMUnderTest.takeCard(), card);
    }

    @Test
     public void takeCard2_prepareBills50() throws ATM.NullCardException {
      Card card = Mockito.mock(Card.class);
      Account account = Mockito.mock(Account.class);
      Mockito.when(card.isBlocked()).thenReturn(false);
      ATMUnderTest.insertCard(card);
      Mockito.when(card.checkPin(0000)).thenReturn(true);
      ATMUnderTest.inputPin(0000);
      Mockito.when(card.getAccount()).thenReturn(account);
      Mockito.when(account.canWithdraw(50)).thenReturn(true);
      ATMUnderTest.chooseAmount(50);

      assertEquals(ATMUnderTest.takeCard(), card);
    }

    @Test
     public void takeCard2_prepareBills20() throws ATM.NullCardException {
      Card card = Mockito.mock(Card.class);
      Account account = Mockito.mock(Account.class);
      Mockito.when(card.isBlocked()).thenReturn(false);
      ATMUnderTest.insertCard(card);
      Mockito.when(card.checkPin(0000)).thenReturn(true);
      ATMUnderTest.inputPin(0000);
      Mockito.when(card.getAccount()).thenReturn(account);
      Mockito.when(account.canWithdraw(20)).thenReturn(true);
      ATMUnderTest.chooseAmount(20);

      assertEquals(ATMUnderTest.takeCard(), card);
    }

    @Test
     public void takeCard2_prepareBills0() throws ATM.NullCardException {
      Card card = Mockito.mock(Card.class);
      Account account = Mockito.mock(Account.class);
      Mockito.when(card.isBlocked()).thenReturn(false);
      ATMUnderTest.insertCard(card);
      Mockito.when(card.checkPin(0000)).thenReturn(true);
      ATMUnderTest.inputPin(0000);
      ATMUnderTest.chooseAmount(0);

      assertEquals(ATMUnderTest.takeCard(), card);
    }

    @Test
     public void takeBills1() {

      assertEquals(ATMUnderTest.takeBills(), null);
    }

    @Test
     public void takeBills2() throws ATM.NullCardException {
      Card card = Mockito.mock(Card.class);
      Account account = Mockito.mock(Account.class);
      Mockito.when(card.isBlocked()).thenReturn(false);
      ATMUnderTest.insertCard(card);
      Mockito.when(card.checkPin(0000)).thenReturn(true);
      ATMUnderTest.inputPin(0000);
      Mockito.when(card.getAccount()).thenReturn(account);
      Mockito.when(account.canWithdraw(20)).thenReturn(true);
      ATMUnderTest.chooseAmount(20);
      ATMUnderTest.takeCard();

      assertNotEquals(ATMUnderTest.takeBills(), null);
    }
}
