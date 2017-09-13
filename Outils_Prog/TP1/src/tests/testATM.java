package tests;

import org.junit.Test;
import org.junit.Before;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertEquals;

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

    @Test(expected = ATM.NullCardException.class)
    public void testInsertCard1() throws ATM.NullCardException {

        ATMUnderTest.insertCard(null);
    }

    @Test(expected = ATM.NullCardException.class)
    public void testInsertCard2() throws ATM.NullCardException {

        Card card = Mockito.mock(Card.class);
        ATMUnderTest.insertCard(card);
        assertEquals(ATMUnderTest.insertCard(card), -1);       
    }

    @Test(expected = ATM.NullCardException.class)
    public void testInsertCard3() throws ATM.NullCardException {

        Card card = Mockito.mock(Card.class);
        Mockito.when(card.isBlocked()).thenReturn(true);
        assertEquals(ATMUnderTest.insertCard(card), -2);
    }

    @Test(expected = ATM.NullCardException.class)
    public void testInsertCard4() throws ATM.NullCardException {

        Card card = Mockito.mock(Card.class);
        assertEquals(ATMUnderTest.insertCard(card), 0);
    }


    @Test(expected = ATM.NullCardException.class)
    public void testInputPin1() throws ATM.NullCardException {
        Card card = Mockito.mock(Card.class);
        Mockito.when(card.isBlocked()).thenReturn(true);
        ATMUnderTest.insertCard(card);
        assertEquals(ATMUnderTest.inputPin(0), -1);
    }

    @Test
    public void testInputPin2() {

        Card card = Mockito.mock(Card.class);
        Mockito.when(card.checkPin(0)).thenReturn(true);
        assertEquals(ATMUnderTest.inputPin(0), 0);
    }

    @Test
    public void testInputPin3() {

        Card card = Mockito.mock(Card.class);
        Mockito.when(card.isBlocked()).thenReturn(true);
        assertEquals(ATMUnderTest.inputPin(0), -3);
    }

    @Test
    public void testInputPin4() {

        Card card = Mockito.mock(Card.class);
        Mockito.when(card.checkPin(0)).thenReturn(false);
        Mockito.when(card.isBlocked()).thenReturn(false);
        assertEquals(ATMUnderTest.inputPin(0), -2);
    }



    @Test
    public void testChooseAmount1() {

        assertEquals(ATMUnderTest.chooseAmount(0), -1);
    }

    @Test(expected = ATM.NullCardException.class)
    public void testChooseAmount2() throws ATM.NullCardException {

        Card card = Mockito.mock(Card.class);
        ATMUnderTest.insertCard(card);

        for (int a = 0; a<100; ++a)
        {
            if (a != 0 && a != 20 && a != 30 && a != 40 && a != 50 && a != 80 && a != 100)
                assertEquals(ATMUnderTest.chooseAmount(a), -2);
        }
    }

    @Test
    public void testChooseAmount3() {

        Card card = Mockito.mock(Card.class);
        Mockito.when(card.getAccount().canWithdraw(-1)).thenReturn(false);

        assertEquals(ATMUnderTest.chooseAmount(0), 0);
        assertEquals(ATMUnderTest.chooseAmount(-1), 0);
    }

    @Test
    public void testChooseAmount4() {

        Card card = Mockito.mock(Card.class);
        Mockito.when(card.checkPin(0)).thenReturn(true);
        ATMUnderTest.inputPin(0);
        assertEquals(ATMUnderTest.chooseAmount(20), -3);
    }
}