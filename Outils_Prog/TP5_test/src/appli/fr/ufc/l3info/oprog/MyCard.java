package fr.ufc.l3info.oprog;

public class MyCard implements Card {

    private Account account;
    private int pin;


    public MyCard()
    {

    }

    public boolean setAccount(Account a)
    {
      if (a == null)
        return false;
      else
        account = a;
      return true;
    }

    public boolean setPin(int p)
    {
      if (p < 0)
        return false;
      else
        pin = p;
      return true;
    }

    public boolean endPersonalization()
    {
      if (pin == 0 || account == null)
        return false;
      else
        return true;
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
      return true;
    }

    public boolean checkPin(int p)
    {
      return true;
    }
}
