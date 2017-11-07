//binome Jeremy ROUSSEY - Bastien CHANEZ
package fr.ufc.l3info.oprog;

public class MyCard implements Card {

    Account account;
    int pin = -1;
    boolean canBePerso = true;
    int remaining_tries = 3;

    public Account getAccount() {
        return account;
    }

    public boolean isBlocked(){
        if(canBePerso == true){
            return true;
        }else if(remaining_tries == 0){
            return true;
        }
        return false;
    }

    public boolean checkPin(int p) {
        if(canBePerso){
            return false;
        }else if(p != pin){
            remaining_tries --;
            return false;
        }
        remaining_tries = 3;
        return true;
    }

    public boolean setAccount(Account a){
        if (canBePerso && a != null){
            account = a;
            return true;
        }
        return false;
    }

    public boolean setPin(int p){
        if (canBePerso && p >= 0 && p <=9999){
            pin = p;
            return true;
        }
        return false;
    }

    public boolean endPersonalization(){
        if (canBePerso && pin != -1 && account != null){
            canBePerso = false;
            return true;
        }
        return false;
    }
}
