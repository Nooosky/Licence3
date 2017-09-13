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

    @Test
    public void testInsertCard1() {

        //assertFalse(ATMUnderTest.insertCard(null));
    }

    @Test
    public void testInsertCard2() {

        Card card = Mockito.mock(Card.class);
        card.isBlocked();
        ATMUnderTest.insertCard(card);
        Mockito.when(mockedCard.isBlocked()).thenReturn(false)
    }

    @Test
    public void testInsertCard3() {

        Card card = Mockito.mock(Card.class);
        card.isBlocked();
        assertEquals(ATMUnderTest.insertCard(card), -2);
    }

    @Test
    public void testInsertCard4() {

        Card card = Mockito.mock(Card.class);
        assertEquals(ATMUnderTest.insertCard(card), 0);
    }


    @Test
    public void testInputPin1() {

        assertEquals(ATMUnderTest.inputPin(0), -1);
    }

    @Test
    public void testInputPin2() {

        Card card = Mockito.mock(Card.class);

    }

    @Test
    public void testInputPin3() {

        Card card = Mockito.mock(Card.class);
        card.isBlcoked();
        assertEquals(ATMUnderTest.inputPin(0), -3);
    }

    @Test
    public void testInputPin4() {

        Card card = Mockito.mock(Card.class);
        assertEquals(ATMUnderTest.inputPin(0), -2);
    }



    @Test
    public void testChooseAmount1() {

        assertEquals(ATMUnderTest.chooseAmount(0), -1);
    }

        @Test
    public void testChooseAmount2() {

        assertEquals(ATMUnderTest.chooseAmount(1), -2);
    }

}