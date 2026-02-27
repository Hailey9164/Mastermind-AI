/*
    Hailey Campbell
    CSC 7 Template for Mastermind AI
    May 28th, 2024
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
using namespace std;

//Function Prototypes
string AI(char,char);
bool eval(string,string,char &,char &);
string set();

int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare variables
    string code,guess;  //code to break, and current guess
    char rr,rw;         //right digit in right place vs. wrong place
    int nGuess;         //number of guesses

    //Initialize Values
    nGuess=0;
    code=set();
    rr=rw=0;

    //Loop until solved and count to find solution
    do{
       nGuess++;
       guess=AI(rr,rw);
    }while(eval(code,guess,rr,rw));
    //Check evaluation
    cout<<nGuess<<" "<<code<<" "<<guess<<endl;
    guess=AI(rr,rw);
    cout<<code<<endl;
    /*for(int i=0;i<10000;i++){
        guess=AI(0,0);
        eval(code,guess,rr,rw);
        cout<<setw(5)<<code<<setw(5)<<guess
                <<setw(2)<<static_cast<int>(rr)
                <<setw(2)<<static_cast<int>(rw)<<endl;
    }*/

    //Exit the program
    return 0;
}

string AI(char rr,char rw){
    //Save the historical values of guesses and results
    static const int SIZE=10000;//How many guesses to save
    static string aGuess[SIZE]; //Save the guesses
    static char grr[SIZE];      //Save right guess in right spot
    static char grw[SIZE];      //Save right guess in wrong spot
    static int guess=0;         //Increment the guess number
    string sGuess="0000";       //Size the guest string
    static char digits[4]={'a', 'a', 'a', 'a'};      //Save the digits
    static int digPos=0;        //Increment the digit position
    static int digwork=0;       //used to tell what digit is bring worked on. 
    static int digitsPos=0;       //used to place digits int eh digits array

    //Store the results from the last guess
    grr[guess]=rr;
    grw[guess]=rw;

    //set sGuess to the last guess
    if(guess!=0){
        for (int i=0; i<4; i++){
            sGuess=aGuess[guess-1];
        }
    }

    //Version 1: Determine the digits in the code
    if (digits[3]=='a'){
        //Add the rr digits to the digits array
        for (int i=0; i<rr; i++){
            digits[digitsPos] = sGuess[0];
            digitsPos++;
        }
        //if 9999 if left set remaining digits to 9
        if (sGuess == "8888"){
            for (; digitsPos<4; digitsPos++){
                digits[digitsPos] = '9';
            }
        }
        //test to find the other digits 
        if ((guess != 0) && (digits[3] == 'a')){
            for (int i=0; i<4; i++){
                sGuess[i]++;
            }
        }
    }

    //Version2: Find location of the first digit
        //guess the first digit in the first position 
        if((digits[3]!='a') && (digwork==0)){
            cout << "Digits: ";
            for(int i =0; i<4; i++){
                cout << digits[i] << " ";
            }
            cout << endl;
            sGuess[0]=digits[0];
            for (int i=1; i<4; i++){
                sGuess[i]='b';
            }
            digwork=1;
            rr=0;
        }
        if(digwork==1){
            // if the first digit is not in the right place move to next location
            if((rw==1) && (rr==0)){
                digPos++;
                for(int i=0; i<4; i++){
                    sGuess[i]='b';
                }
                sGuess[digPos]=digits[0];
            }
            // if the digit is in the right place move to next digit
            if((rw==0) && (rr==1)){
                digwork++;
                cout << "Position of the first digit: " << digPos << endl;
                digPos=0;
            }
        }
    //Version3: Find the location of the second digit
        //guess the second digit in the first position where the first digit is not
        if((digwork==2) && (rw==0) && (rr==1)){
            bool dig2=false;
            do{
                if (sGuess[digPos]=='b'){
                    dig2=true;
                    sGuess[digPos]=digits[1];
                }
                else{
                    digPos++;
                    if (digPos>=4){
                        digPos=0;
                    }
                }
            } while(dig2==false && digPos<4);
        }
        if(digwork==2){
            // if the second digit is not in the right place move to next location
            if((rw==1) && (rr==1)){
                sGuess[digPos]='b';
                digPos++;
                bool dig2=false;
                do{
                    if(sGuess[digPos]=='b'){
                        dig2=true;
                        sGuess[digPos]=digits[1];
                    }
                    else{
                        digPos++;
                        if(digPos>=4){
                            digPos=0;
                        }
                    }
                } while(dig2==false && digPos<4);
            }
            if((rw==0) && (rr==2)){
                digwork++;
                cout << "Position of the second digit: " << digPos << endl;
                digPos=0;
            }
        }

    //Version 4: Find the location of the third digit
        //guess the third digit in the first position where the first and second digits are not
        if((digwork==3) && (rw==0) && (rr==2)){
            bool dig3=false;
            do{
                if (sGuess[digPos]=='b'){
                    dig3=true;
                    sGuess[digPos]=digits[2];
                }
                else{
                    digPos++;
                    if (digPos>=4){
                        digPos=0;
                    }
                }
            } while(dig3==false&& digPos<4);
        }
        if(digwork==3){
            // if the second digit is not in the right place move to next location
            if((rw==1) && (rr==2)){
                sGuess[digPos]='b';
                digPos++;
                bool dig3=false;
                do{
                    if(sGuess[digPos]=='b'){
                        dig3=true;
                        sGuess[digPos]=digits[2];
                    }
                    else{
                        digPos++;
                        if(digPos>=4){
                            digPos=0;
                        }
                    }
                } while(dig3==false&& digPos<4);
            }
            if((rw==0) && (rr==3)){
                digwork++;
                cout << "Position of the third digit: " << digPos << endl;
                digPos=0;
            }
        }

    //Version 5: Place the fourth digit
    if(digwork==4){
        bool dig4=false;
        do{
            if(sGuess[digPos]=='b'){
                dig4=true;
                sGuess[digPos]=digits[3];
            }
            else{
                digPos++;
            }
        } while(dig4==false && digPos<4);
    }

    //save guess 
    aGuess[guess]=sGuess;

    //increment the guess
    guess++;

    //Return the result
    return sGuess;
}

bool eval(string code,string guess,char &rr,char &rw){
    string check="    ";
    rr=0,rw=0;
    //Check how many are right place
    for(int i=0;i<code.length();i++){
        if(code[i]==guess[i]){
            rr++;
            check[i]='x';
            guess[i]='x';
        }
    }
    //Check how many are wrong place
    for(int j=0;j<code.length();j++){
        for(int i=0;i<code.length();i++){
            if((i!=j)&&(code[i]==guess[j])&&(check[i]==' ')){
                rw++;
                check[i]='x';
                break;
            }
        }
    }

    //Found or not
    if(rr==4)return false;
    return true;
}

string set(){
    string code="0000";
    for(int i=0;i<code.length();i++){
        code[i]=rand()%10+'0';
    }
    return code;
}