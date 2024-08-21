#include<iostream>
#include<string>
#include<limits>
#include<unordered_map>
using namespace std;

string salt="random_salt_value";

string simpleHash(string input){
    unsigned long hash=5381;
    for(char c:input){
        hash=((hash<<5)+hash)+c;
    }
    return to_string(hash);
}

string saltedHash(string password){
    return simpleHash(password+salt);
}

string stretchedHash(string password,int iterations=1000){
    string hash=saltedHash(password);
    for(int i=0;i<iterations;i++){
        hash=simpleHash(hash);
    }
    return hash;
}

struct User{
    string hashedPassword;
    int graphicalPassword[5];
    string twoFactorCode;
    int failedAttempts;
    bool isLocked;
};

unordered_map<string,User> userDatabase;

void signUp(){
    string username,textualPassword,twoFactorCode;
    int graphicalPassword[5];

    cout<<"Enter username: ";
    cin>>username;

    if(userDatabase.find(username)!=userDatabase.end()){
        cout<<"Username already exists. Please choose a different one."<<endl;
        return;
    }

    cout<<"Enter textual password: ";
    cin>>textualPassword;

    cout<<"Set graphical password pattern (5 integers): ";
    for(int i=0;i<5;i++)
        cin>>graphicalPassword[i];

    cout<<"Set two-factor authentication code: ";
    cin>>twoFactorCode;

    User newUser;
    newUser.hashedPassword=stretchedHash(textualPassword);
    for(int i=0;i<5;i++)
        newUser.graphicalPassword[i]=graphicalPassword[i];
    newUser.twoFactorCode=twoFactorCode;
    newUser.failedAttempts=0;
    newUser.isLocked=false;

    userDatabase[username]=newUser;
    cout<<"Account created successfully!"<<endl;
}

bool validateTextualPassword(string hashedPassword,string enteredPassword){
    return stretchedHash(enteredPassword)==hashedPassword;
}

bool validateGraphicalPassword(int pattern[],int correctPattern[]){
    for(int i=0;i<5;i++){
        if(pattern[i]!=correctPattern[i])
            return false;
    }
    return true;
}

bool validateTwoFactorCode(string correctCode,string enteredCode){
    return enteredCode==correctCode;
}

void handleLogin(){
    string username,textualPassword,twoFactorCode;
    int graphicalPassword[5];
    const int maxAttempts=3;

    cout<<"Enter username: ";
    cin>>username;

    if(userDatabase.find(username)==userDatabase.end()){
        cout<<"Username not found. Please sign up first."<<endl;
        return;
    }

    User& currentUser=userDatabase[username];

    if(currentUser.isLocked){
        cout<<"Account is locked due to too many failed attempts."<<endl;
        return;
    }

    while(currentUser.failedAttempts<maxAttempts){
        cout<<"Enter textual password: ";
        cin>>textualPassword;

        if(!validateTextualPassword(currentUser.hashedPassword,textualPassword)){
            cout<<"Textual Password Incorrect"<<endl;
            currentUser.failedAttempts++;
            if(currentUser.failedAttempts>=maxAttempts){
                currentUser.isLocked=true;
                cout<<"Maximum attempts reached. Access locked!"<<endl;
                return;
            }
            continue;
        }

        cout<<"Enter graphical password pattern (5 integers): ";
        for(int i=0;i<5;i++)
            cin>>graphicalPassword[i];

        if(!validateGraphicalPassword(graphicalPassword,currentUser.graphicalPassword)){
            cout<<"Graphical Password Incorrect"<<endl;
            currentUser.failedAttempts++;
            if(currentUser.failedAttempts>=maxAttempts){
                currentUser.isLocked=true;
                cout<<"Maximum attempts reached. Access locked!"<<endl;
                return;
            }
            continue;
        }

        cout<<"Enter two-factor authentication code: ";
        cin>>twoFactorCode;

        if(!validateTwoFactorCode(currentUser.twoFactorCode,twoFactorCode)){
            cout<<"Incorrect 2FA code"<<endl;
            currentUser.failedAttempts++;
            if(currentUser.failedAttempts>=maxAttempts){
                currentUser.isLocked=true;
                cout<<"Maximum attempts reached. Access locked!"<<endl;
                return;
            }
            continue;
        }

        cout<<"Access Granted!"<<endl;
        currentUser.failedAttempts=0;
        return;
    }

    cout<<"Access locked due to too many failed attempts."<<endl;
}

void displayMainMenu(){
    cout<<"\n*** Welcome to the Secure Login System ***"<<endl;
    cout<<"1. Sign Up"<<endl;
    cout<<"2. Login"<<endl;
    cout<<"3. Exit"<<endl;
    cout<<"Please select an option: ";
}

void clearInputBuffer(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
}

int main(){
    int choice;
    do{
        displayMainMenu();
        cin>>choice;

        if(cin.fail()){
            clearInputBuffer();
            cout<<"Invalid input. Please enter a number."<<endl;
            continue;
        }

        switch(choice){
            case 1:
                signUp();
                break;
            case 2:
                handleLogin();
                break;
            case 3:
                cout<<"Exiting... Goodbye!"<<endl;
                break;
            default:
                cout<<"Invalid choice. Please select a valid option."<<endl;
                break;
        }
    }while(choice!=3);

    return 0;
}
