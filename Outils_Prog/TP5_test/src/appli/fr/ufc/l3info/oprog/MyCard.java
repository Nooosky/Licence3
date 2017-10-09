package fr.ufc.l3info.oprog;

public class MyCard implements Card {

    private Account account;
    private int pin;
    private boolean personalizationDone;
    private int numberFailPin;
    private boolean cardIsblocked;


    public MyCard()
    {
      account = null;
      pin = 0;
      personalizationDone = false;
      numberFailPin = 0;
      cardIsblocked = true;
    }

    public boolean setAccount(Account a)
    {
      if (personalizationDone)
        return false;
      if (a == null)
        return false;
      else
        account = a;
      return true;
    }

    public boolean setPin(int p)
    {
      if (personalizationDone)
        return false;
      if (1000 > p || p > 9999)
        return false;
      else
        pin = p;
      return true;
    }

    public boolean endPersonalization()
    {
      if (pin == 0 || account == null)
      {
        personalizationDone = false;
        return false;
      }
      else
      {
        personalizationDone = true;
        cardIsblocked = false;
        return true;
      }
    }

    public Account getAccount()
    {
      if (account == null)
        return null;
      else
        return account;
    }

    public boolean isBlocked()
    {
        return cardIsblocked;
    }

    public boolean checkPin(int p)
    {
      if (!personalizationDone)
        return false;
      if (cardIsblocked)
        return false;
      if (p != pin)
      {
        numberFailPin++;
        if (numberFailPin == 3)
          cardIsblocked =  true;

        return false;
      }
      else
      {
        numberFailPin = 0;
        return true;
      }
    }
}
