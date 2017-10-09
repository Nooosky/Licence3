package fr.ufc.l3info.oprog;

public class MyCard {

    private Account account;


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

    public void setPin(int p)
    {

    }

    public void endPersonalization()
    {

    }

    public Account getAccount()
    {

    }

    public boolean isBlocked()
    {

    }

    public boolean checkPin(int p)
    {

    }
}
