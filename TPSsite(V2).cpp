#include <iostream>
#include <sstream>
#include<cstring>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

// MAX number of each user type
const int MAX_CLIENTS   = 20;  
const int MAX_FAMILY    = 20;
const int MAX_COUNSELOR = 20; 
const int MAX_GOALS_PER_CLIENT = 5;

struct patient
{
    
    char patientPriority;
    string patientReview;
    string usernameP;
    string passwordsP;
    string noteToPatient;
    string patientGoals[MAX_GOALS_PER_CLIENT];
};

struct family
{              
    string usernamePF;
    string passwordsPF;
    string noteToFamily;

};

struct therapist
{
    string usernamesT;
    string passwordsT;
    string sessionDates;
    string noteToTherapist;

};

// Frequently used aesthetic functions
void printHeader(void);
void coutFancy(string fancy);
void askToContinue(void);

void initializeArrays(patient clients[], family familyMember[], therapist counselor[]);

// Functions related to getting valid choices as input from user
int choiceValidatoin(string choice, char start, char end);
int MainMenuInputPrompt(void);
int getAdminInput(void);
int getPatientInput(void);
int getFamilyInput(void);
int getTherapistInput(void);
int getUserType(void);

string dateVerify(void);
string getUsername(void);
string getPassword(void);
string getAnote(void);
char checkPriority(void);

// Functions about searching and displaying data
bool searchUser(string username, int maxUsers, patient clients[], int &reqUserIndex );
bool searchUser(string username, int maxUsers, family familyMember[], int &reqUserIndex );
bool searchUser(string username, int maxUsers, therapist counselor[], int &reqUserIndex );
void displayList(patient clients[], family familyMember[], therapist counselor[], int maxUsers);

// Functions about file handling
void saveData (patient clients[], family familyMember[], therapist counselor[]);;

void loadData(patient clients[], family familyMember[], therapist counselor[]);;


int main()
{


    const string ADMIN_USERNAME = "TPS";
    const string ADMIN_PASSWORD = "TPSTPS909";


    // user structs
    patient clients[MAX_CLIENTS];
    family familyMember[MAX_FAMILY];
    therapist counselors[MAX_COUNSELOR];
    

    // users search flags
    bool therapistFlag = false;
    bool patientFlag = false;   
    bool familyFlag = false;
    bool userFound = false;


    // variables used for functionalities in main
    const string emptyUser  = {};
    const string emptyPwd   = {};
    string user = {};
    string pwd  = {};
    string reqUser = {};
    char garbage = '0';
    string StressRelief = {};

    int input = 0;
    int loginIndexP = 0, loginIndexA = 0, loginIndexT = 0, loginIndexPF = 0;
    int userUpdatingIndex = 0;
    int userType = 0;

    bool goalAdded = false;
    int loggedInUserType = -10; //1 for administrator, 2 for client, 3 for client's family, 4 for Therapist, -10 when user logs out
    

    //initializing all arrays 
    initializeArrays(clients, familyMember, counselors);

    // loading the data into the arrays
    loadData(clients, familyMember, counselors);
    
    // starting main execution
    do
    {
        printHeader();
        input = MainMenuInputPrompt();

        switch (input)
        {

        // Admin login
        case 1:
            user = getUsername();
            pwd = getPassword();
            

            if (user == ADMIN_USERNAME && pwd == ADMIN_PASSWORD)
                loggedInUserType = 1;
            else
                loggedInUserType = -1;
            break;

        // Client/Patient Login
        case 2:
            user = getUsername();
            pwd  = getPassword();

            patientFlag = searchUser(user, MAX_CLIENTS, clients, loginIndexP);

            if (patientFlag == true)
            {
                if(pwd == clients[loginIndexP].passwordsP)
                {
                    loggedInUserType = 2;

                }
                else
                    loggedInUserType = -1;
            }
            else
            {
                loggedInUserType = -1;
            }
            break;

        // user's family login
        case 3:
            user = getUsername();
            pwd  = getPassword();

            familyFlag = searchUser(user, MAX_FAMILY, familyMember, loginIndexPF);

            if (familyFlag == true)
            {
                if(pwd == familyMember[loginIndexPF].passwordsPF)
                {
                    loggedInUserType = 3;

                }
                else
                    loggedInUserType = -1;

            }
            else
            {
                loggedInUserType = -1;
            }
            break;

        // Thereapist Login
        case 4:
            user = getUsername();
            pwd  = getPassword();

            therapistFlag = searchUser(user, MAX_COUNSELOR, counselors, loginIndexT);

            if (therapistFlag == true)
            {
                if(pwd == counselors[loginIndexT].passwordsT)
                {
                    loggedInUserType = 4;

                }
                else
                    loggedInUserType = -1;
            }
            else
            {
                loggedInUserType = -1;
            }
            break;

        case 0:  // user has exited the system
            loggedInUserType = -10; 
            cout  << setw(115) << "**********************************************************************************\n";
            cout  << setw(115) << "                      BYE, THANKS FOR BEING PART OF TPS :)                        \n";
            cout  << setw(115) << "**********************************************************************************\n";
            break;

        default:
            cout << "Invalid choice. Please retry.";
            break;
        }

        if (loggedInUserType == 1) // Admin
        {
            do
            {
                input = getAdminInput();

                switch (input)
                {

                // add users(patient, patient family, therapist)
                case 1:
                    userType = getUserType(); 
                    switch (userType)
                    {
                    case 1:

                        userUpdatingIndex = 0;
                        userFound = searchUser(emptyUser, MAX_CLIENTS, clients, userUpdatingIndex);
                        if(userFound)
                        {
                            clients[userUpdatingIndex].usernameP = getUsername();
                            clients[userUpdatingIndex].passwordsP = getPassword();

                            coutFancy("PATIENT ADDED SUCCESSFULLY");      
                        }
                        else
                        {
                            coutFancy("PATIENT NOT FOUND");
                        }
                        askToContinue();
                        break;

                    case 2:
                        userUpdatingIndex = 0;
                        userFound = searchUser(emptyUser, MAX_FAMILY, familyMember, userUpdatingIndex);
                        if(userFound)
                        {
                            familyMember[userUpdatingIndex].usernamePF = getUsername();
                            familyMember[userUpdatingIndex].passwordsPF = getPassword();

                            coutFancy("FAMILY MEMBER ADDED SUCCESSFULLY");
                        }
                        else
                        {
                            coutFancy("FAMILY MEMBER NOT FOUND");
                        }

                        askToContinue();
                        break;

                    case 3:
                        userUpdatingIndex = 0;
                        userFound = searchUser(emptyUser, MAX_CLIENTS, counselors, userUpdatingIndex);
                        if(userFound)
                        {
                            counselors[userUpdatingIndex].usernamesT = getUsername();
                            counselors[userUpdatingIndex].passwordsT = getPassword();

                            coutFancy("THERAPIST ADDED SUCCESSFULLY");
                            
                        }
                        else
                        {
                            coutFancy("THERAPIST NOT FOUND");
                        }

                        askToContinue();
                        break;
                    
                    default:
                        break;
                    }
                    break;
                
                // edit users(patient, patient family, therapist)
                case 2:
                    reqUser = "";
                    userType = getUserType(); 
                    switch (userType)
                    {
                    case 1:

                        userUpdatingIndex = 0;
                        reqUser = getUsername();

                        userFound = searchUser(reqUser, MAX_CLIENTS, clients, userUpdatingIndex);
                        if(userFound)
                        {
                            cout << "Enter New Credentials \n";
                            clients[userUpdatingIndex].usernameP = getUsername();
                            clients[userUpdatingIndex].passwordsP = getPassword();

                            coutFancy("PATIENT UPDATED SUCCESSFULLY");
                            
                        }
                        else
                        {
                            coutFancy("PATIENT NOT FOUND");
                        }
                        askToContinue();       
                        break;

                    case 2:
                        userUpdatingIndex = 0;
                        reqUser = getUsername();

                        userFound = searchUser(reqUser, MAX_FAMILY, familyMember, userUpdatingIndex);
                        if(userFound)
                        {
                            cout << "Enter new Credentials \n";
                            familyMember[userUpdatingIndex].usernamePF = getUsername();
                            familyMember[userUpdatingIndex].passwordsPF = getPassword();

                            coutFancy("FAMILY MEMBER UPDATED SUCCESSFULLY");
                            
                        }
                        else
                        {
                            coutFancy("FAMILY MEMBER NOT FOUND");
                        }

                        askToContinue();
                        break;

                    case 3:
                        userUpdatingIndex = 0;
                        reqUser = getUsername();

                        userFound = searchUser(reqUser, MAX_CLIENTS, counselors, userUpdatingIndex);
                        if(userFound)
                        {
                            cout << "Enter new Credentials \n";
                            counselors[userUpdatingIndex].usernamesT = getUsername();
                            counselors[userUpdatingIndex].passwordsT = getPassword();

                            coutFancy("THERAPIST ADDED SUCCESSFULLY");    
                        }
                        else
                        {
                            coutFancy("THERAPIST NOT FOUND");
                        }
                        askToContinue();
                        
                    break;

                    default:
                        cout << "How did you even get here????";
                        break;
                    }
                    break;

                // delete users(patient, patient family, therapist)
                case 3:
                    reqUser = "";
                    userType = getUserType(); 
                    switch (userType)
                    {
                    case 1:

                        userUpdatingIndex = 0;
                        reqUser = getUsername();

                        userFound = searchUser(reqUser, MAX_CLIENTS, clients, userUpdatingIndex);
                        if(userFound)
                        {
                            clients[userUpdatingIndex].usernameP = emptyUser;
                            clients[userUpdatingIndex].passwordsP = emptyPwd;

                            coutFancy("PATIENT DELETED SUCCESSFULLY");
                        }
                        else
                        {
                            coutFancy("PATIENT NOT FOUND");
                        }

                        break;

                    case 2:
                        userUpdatingIndex = 0;
                        reqUser = getUsername();

                        userFound = searchUser(reqUser, MAX_FAMILY, familyMember, userUpdatingIndex);
                        if(userFound)
                        {
                            familyMember[userUpdatingIndex].usernamePF = emptyUser;
                            familyMember[userUpdatingIndex].passwordsPF = emptyPwd;

                            coutFancy("FAMILY MEMBER DELETED SUCCESSFULLY");
                        }
                        else
                        {
                            coutFancy("FAMILY MEMBER NOT FOUND");
                        }
                        
                        break;

                    case 3:
                        userUpdatingIndex = 0;
                        reqUser = getUsername();

                        userFound = searchUser(reqUser, MAX_CLIENTS, counselors, userUpdatingIndex);
                        if(userFound)
                        {
                            counselors[userUpdatingIndex].usernamesT = emptyUser;
                            counselors[userUpdatingIndex].passwordsT = emptyPwd;

                            coutFancy("THERAPIST DELETED SUCCESSFULLY");
                        }
                        else
                        {
                            coutFancy("THERAPIST NOT FOUND");
                        }

                    break;
                    
                    default:
                        cout << "How did you even get here??????";
                        break;
                    }

                    askToContinue();
                    break;

                // displays list of all users 
                case 4:
                    displayList(clients,  familyMember, counselors, MAX_CLIENTS);
                    break;

                // allows admin to see general trends
                case 5:
                    coutFancy("GENERAL TRENDS");
                    cout << setw(50) << "PATIENTS" << setw(50) << "PRIORITY?" << '\n';
                    for(int i = 0; i < MAX_CLIENTS; i++)
                    {
                        cout << setw(50) << clients[i].usernameP << setw(50) << clients[i].patientPriority << '\n';
                    }

                    cout << "\n\n";
                    break;

                // alllows admin to contact therapist
                case 6:
                    counselors[loginIndexA].noteToTherapist = getAnote();
                    coutFancy("Note successfully sent to therapist");

                    break;

                // just to alleviate some stress
                case 7:
                    coutFancy("BUTTON MASHING");
                    cout << "MASH BUTTINS TO YOUR HEARTH'S CONTENT!!!! (press enter to exit):";
                    getline(cin, StressRelief);
                    cin.ignore(1000, '\n');

                    break;
                
                case 0:
                
                    coutFancy("ADMIN LOGGED OUT");
                    break;

                default:

                    cout << "Invalid choice!!!";
                    break;
                }

                askToContinue();
                 
            } while (input != 0);
            input = -1; //this statment is to make sure that do not exit from outer loop
        }
        else if (loggedInUserType == 2) //Client
        {
            
            do
            {
                input = getPatientInput();

                switch (input)
                {

                case 1:
                    coutFancy("NOTE TO THERAPIST");
                    counselors[loginIndexP].noteToTherapist = getAnote();
                    clients[loginIndexP].patientPriority = checkPriority();

                    break;
                case 2:
                    coutFancy("NOTE TO FAMILY");
                    familyMember[loginIndexP].noteToFamily = getAnote();

                    break;
                case 3:
                    coutFancy("BOOK SESSION");
                    counselors[loginIndexPF].sessionDates = dateVerify();

                    coutFancy("SESSION BOOKED SUCCESSFULLY");

                    break;
                case 4:
                    coutFancy("ADD GOALS");
                    for(int i = 0; i < MAX_GOALS_PER_CLIENT; i++)
                    {
                        if(clients[loginIndexP].patientGoals[i] == "")
                        {
                            cout << "Enter new goal(only keywords if possible): ";
                            cin.ignore();
                            getline(cin, clients[loginIndexP].patientGoals[i]);
                            goalAdded = true;

                            break;
                        }
                    }

                    if(!goalAdded)
                        cout << "No room for more goals. Please complete one of the existing goals first \n";

                    break;
                
                case 5:
                    coutFancy("CURRENT GOALS");
                    for(int i = 0; i < MAX_GOALS_PER_CLIENT; i++)
                    {
                        if(clients[loginIndexP].patientGoals[i] != "")
                        {
                            cout << '\t'  << i+1 << ". " << clients[loginIndexP].patientGoals[i] << '\n';
                        }
                    }

                    break;
                
                case 6:
                    coutFancy("REMOVE COMPLETED GOALS");
                    for(int i = 0; i < MAX_GOALS_PER_CLIENT; i++)
                    {
                        if(clients[loginIndexP].patientGoals[i] != "")
                        {
                            cout << '\t'  << i+1 << ". " << clients[loginIndexP].patientGoals[i] << '\n';
                        }
                    }
                    cout << "Enter index to complete: ";
                    cin  >> userUpdatingIndex;

                    clients[loginIndexP].patientGoals[userUpdatingIndex - 1] = "";
                    coutFancy("GOAL COMPLETED!!");
                    break;
                
                case 0:
                    coutFancy("LOGGED OUT");
                    cout << endl << endl;

                    break;

                default:
                    cout << "Invalid choice!!!";
                    break;
                }

                askToContinue();

            } while (input != 0);
            input = -1; //this statment is to make sure that do not exit from outer loop
        }
        else if (loggedInUserType == 3) //user family
        {
            
            do
            {
                input = getFamilyInput();
                switch (input)
                {

                case 1:
                    if(clients[loginIndexPF].patientPriority == 'y' || clients[loginIndexPF].patientPriority == 'Y')
                    {
                        coutFancy("PATIENT NEEDS HELP!!!");
                    }
                    else
                    {
                        coutFancy("PATIENT IS FINE(PROBABLY)");
                    }

                    cout << clients[loginIndexPF].usernameP << ": " << familyMember[loginIndexPF].noteToFamily;

                    break;
                case 2:
                    coutFancy("THERAPIST NOTES");
                    if(clients[loginIndexPF].patientReview == "")
                    {
                        cout << "No Review has been given by the therapist";
                    }
                    else
                    {
                        cout << "Therapist: ";
                        cout << clients[loginIndexPF].patientReview;
                    }

                    break;
                case 3: 
                    coutFancy("BOOK SESSION");
                    counselors[loginIndexPF].sessionDates = dateVerify();

                    coutFancy("SESSION BOOKED SUCCESSFULLY");

                    break;

                case 0:
                    coutFancy("LOGGED OUT");
                    cout << endl << endl;
                    break;

                default:
                    cout << "Invalid choice!!!";
                    break;
                }

                askToContinue();

            } while (input != 0);
            input = -1; //this statment is to make sure that do not exit from outer loop
        }
        else if (loggedInUserType == 4) //counselor / Therapist
        {
            
            do
            {
                input = getTherapistInput();
                switch (input)
                {

                case 1:
                    coutFancy("PRIORITY PATIENTS");
                    for(int i = 0; i < MAX_CLIENTS; i++)
                    {
                        if(clients[i].patientPriority == 'y' || clients[i].patientPriority == 'Y')
                        {
                            cout << "\n" << clients[i].usernameP;
                        }

                    }

                    break;
                case 2:
                    coutFancy("ALL PATIENTS");
                    for(int i = 0; i < MAX_CLIENTS; i++)
                    {
                        if(clients[i].usernameP != "")
                        {
                            cout << "\n" << clients[i].usernameP;
                        }

                    }

                    break;
                case 3:
                    coutFancy("SESSION REVIEW");
                    userUpdatingIndex = 0;
                    cout << "\tAdd info of patient\n ";
                    user = getUsername();
                    userFound = searchUser(user, MAX_CLIENTS, clients, userUpdatingIndex);

                    if(userFound)
                    {
                        cout << "Enter review about " << clients[userUpdatingIndex].usernameP << ":";
                        getline(cin, clients[userUpdatingIndex].patientReview);
                    }
                    else
                    {
                        cout << "User not found. Please Contact Admin for help";
                    }

                    break;
                case 4:
                    coutFancy("PATIENT FEEDBACK");
                    cout << "\t" << clients[loginIndexT].usernameP << '\t' << counselors[loginIndexT].noteToTherapist;
                    break;
                case 5:
                    coutFancy("CONTACT PATIENT");
                    cout << "\n\tEnter message: ";
                    getline(cin, clients[loginIndexT].noteToPatient);
                    cin.ignore(50, '\n');

                    break;

                case 6:
                    coutFancy("BOOKED SESSIONS");
                    cout << "\n\n";
                    cout << "***********************************************************************************************************************\n";
                    cout << setw(10) << "" << setw(30) << left << "Session" << setw(30) << left << "Date" << endl;
                    cout << "***********************************************************************************************************************\n";

                    if(counselors[loginIndexT].sessionDates != "")
                    {
                        cout << setw(10) << " " << setw(30) << left << clients[loginIndexT].usernameP 
                             << setw(30) << left << counselors[loginIndexT].sessionDates << '\n';
                    }

                    break;
                case 0:
                    coutFancy("LOGGED OUT");
                    cout << endl << endl;
                    break;

                default:
                    cout << "Invalid choice!!!";
                    break;
                }

                askToContinue();

            } while (input != 0);
            input = -1; //this statment is to make sure that do not exit from outer loop
        }
        else if (loggedInUserType == -1) // user entered wrong credentials
        {
            cout << "You have entered invalid Credentials!" << endl;
            askToContinue();
        }
    } while (input != 0);

    saveData(clients, familyMember, counselors);

    return 0;
}

// prints Main Header of the program
void printHeader(void)
{
    system("cls");
    //program header
    cout  << endl;
    cout  << setw(110) << "***************************************************************\n";
    cout  << setw(110) << "                       Welcome to TPS                          \n";
    cout  << setw(110) << "***************************************************************\n";
}
 
// outputs string in an appealing manner
void coutFancy(string fancy)
{

    cout  << '\n';
    cout  << setw(120) << "     ***********************************************************************************\n";
    cout  << setw(65)  << "                     "<<  fancy << "                             \n";
    cout  << setw(120) << "     ***********************************************************************************\n";
}

// initializes all the arrays 
void initializeArrays(patient clients[], family familyMember[], therapist counselor[]) 
{
    for (int i = 0; i < MAX_CLIENTS; i++) 
    {
        clients[i].patientPriority = '\0';
        clients[i].patientReview = "";
        clients[i].usernameP = "";
        clients[i].passwordsP = "";
        clients[i].noteToPatient = "";
    }

    for(int i = 0; i < MAX_CLIENTS; i++)
    {
        for(int j = 0; j < MAX_GOALS_PER_CLIENT; j++)
        {
            clients[i].patientGoals[j] = "";

        }
    }

    for (int i = 0; i < MAX_FAMILY; i++) 
    {
        familyMember[i].usernamePF = "";
        familyMember[i].passwordsPF = "";
        familyMember[i].noteToFamily = "";
    }

    for (int i = 0; i < MAX_COUNSELOR; i++) 
    {
        counselor[i].usernamesT = "";
        counselor[i].passwordsT = "";
        counselor[i].sessionDates = "";
        counselor[i].noteToTherapist = "";
    }
}

// prints admin sub menu and asks input for action to  perform
int getAdminInput(void)
{
    printHeader();
    string checkValid = "";
    int adminChoice = 0;

    cout << endl;
    cout << "Choose the desired option\n";
    cout << left << setw(25) << "\tUsers" // all 4 will contain further 3 choices for patient,patient family and therapist
            << setw(25) << "1. Add user"
            << setw(25) << "2. Edit user"
            << setw(25) << "3. Delete user "
            << setw(25) << "4. List";
    cout << '\n';

    cout << setw(25) << "\tGeneral"
            << setw(25) << "5. General Trends" //maybe histogram type
            << setw(25) << "6. Contact Therapist"
            << setw(25) << "7. Stress Relief :)"
            << setw(25) << "0. Logout"
            << '\n';


    cout.unsetf(ios::left);
    cout.unsetf(ios::right);


    cout << "Enter choice: ";
    cin >> checkValid;
    adminChoice = choiceValidatoin(checkValid, '0' , '7');

    return adminChoice;

}

// prints patient sub menu and asks input for action to  perform
int getPatientInput(void)
{
    printHeader();

    string checkValid = "";
    int patientChoice = 0;

    cout << endl;
    cout << "Choose the desired option\n";
    cout << left << setw(10) << "\t Help"
         << setw(25) << "1. Contact Therapist"
         << setw(25) << "2. Contact Family"
         << setw(25) << "3. Book session";
    cout << '\n';

    cout << left << setw(10) << "\t Goals";
    cout << setw(25) << "4. Set new goals"
         << setw(25) << "5. View current goals"
         << setw(25) << "6. Progress goals"
         << setw(25) << "0. Logout";  
    cout << '\n';        

    cout.unsetf(ios::left);
    cout.unsetf(ios::right);

    cout << "Enter choice: ";
    cin >> checkValid;
    patientChoice = choiceValidatoin(checkValid, '0' , '6');


    return patientChoice;

}

// prints family sub menu and asks input for action to  perform
int getFamilyInput(void)
{
    printHeader();

    string checkValid = "";
    int familyChoice = 0;
    cout << endl;
    cout << "Choose the desired option\n";
    cout << left << setw(10) << "\t"
            << setw(30) << "1. View Patient's State"
            << setw(30) << "2. See Therapist's Notes"
            << setw(30) << "3. Book Session"
            << setw(30) << "0. Logout";
    cout << endl;

    cout.unsetf(ios::left);
    cout.unsetf(ios::right);

    cout << "Enter choice: ";
    cin >> checkValid;
    familyChoice = choiceValidatoin(checkValid, '0' , '3');
    
    return familyChoice;

}

// prints therapist sub menu and asks input for action to  perform
int getTherapistInput(void)
{
    printHeader();

    string checkValid = "";
    int therapistChoice = 0;

    cout << endl;
    cout << "Choose the desired option:\n";
    cout << left << setw(10) << "\t"
            << setw(30) << "1. VIew Priority Patients"
            << setw(30) << "2. View All Patients"
            << setw(30) << "3. Write Session Notes"
            << setw(30) << "4. See Patient Feedback";
    cout << '\n';

    cout << left << setw(10) << "\t"
            << setw(30) << "5. Contact Patient"
            << setw(30) << "6. Booked Sessions"
            << setw(30) << "0. Logout";
    cout << '\n';

    cout.unsetf(ios::left);
    cout.unsetf(ios::right);

    cout << "Enter choice: ";
    cin >> checkValid;
    therapistChoice = choiceValidatoin(checkValid, '0' , '6');

    return therapistChoice;

}

// prints Main menu and asks input for action to  perform
int MainMenuInputPrompt(void)
{
        string checkValid = "";
        int userChoice = 0;
        cout << endl;
        cout << "Choose the desired option\n";
        cout << left << setw(10) << "\t"
             << setw(25) << "1. Administrator Login"
             << setw(20) << "2. Client Login"
             << setw(25) << "3. Family Memeber Login"
             << setw(25) << "4. Therapist Login"
             << setw(25) << "0. Exit Program";
        cout << endl;

        cout.unsetf(ios::left);
        cout.unsetf(ios::right);

        cout << "Enter choice: ";
        cin >> checkValid;
        userChoice = choiceValidatoin(checkValid, '0' , '4');

        

        return userChoice;
}

//gets username
string getUsername(void)
{
    string username = {};

    cout << "Enter Username: ";
    cin >> username;
    cin.ignore(50, '\n');

    return username;
}

//gets a password
string getPassword(void)
{

    string password = {};
    do
    {
        cout << "Enter Password(b/w 8 and 32 characters): ";
        cin >> password;
        cin.ignore(50, '\n');       

    }while (password.length() < 8 || password.length() > 32);

    return password;
}

// geta a note to send from user
string getAnote(void)
{
    string note = "";
    cout << "Please write a  note to send: ";
    getline(cin, note);
    cin.ignore(50, '\n');

    return note;
}

// asks if patient needs priority (Y/N)
char checkPriority(void)
{
    char choice = 'N';
    do
    {
        cout << "Are you in urgent need of a session?(Y/N): ";
        cin  >> choice;
        cin.ignore(50, '\n');

    } while (choice != 'N' && choice != 'n' && choice != 'Y' && choice != 'y' );
    
    return choice;

}

// prints list of 3 user Types and asks which one is needed  
int getUserType(void)
{
    printHeader();

    string checkValid = "";
    int userType = 0;
    cout << "\n\n";
    cout << setw(115) << "*************************************************************************\n";
    cout << setw(115) << "                   SELECT USER TYPE TO PERFORM ACTION ON                 \n";
    cout << setw(115) << "*************************************************************************\n";
    cout << setw(30) << "1. Patient " << setw(30) << "2. Patient's Relative" << setw(30) <<  "3.Therapist" << '\n';

  
        cout << "Enter choice: ";
        cin >> checkValid;
        userType = choiceValidatoin(checkValid, '1' , '3');

    return userType;
}

// searches client in the array
bool searchUser(string username, int maxUsers, patient clients[] , int &reqUserIndex)
{
    bool userSearchFlag = false;
    for (int i = 0; i < maxUsers; i++)
    {
        if (username == clients[i].usernameP)
        {
            userSearchFlag = true;
            reqUserIndex = i; // stores which user entered system
            return userSearchFlag;
        }

        
    }
    return userSearchFlag;

}

// searches family member in the array
bool searchUser(string username, int maxUsers, family familyMember[] , int &reqUserIndex)
{
    bool userSearchFlag = false;
    for (int i = 0; i < maxUsers; i++)
    {
        if (username == familyMember[i].usernamePF)
        {
            userSearchFlag = true;
            reqUserIndex = i; // stores which user entered system
            return userSearchFlag;
        }

        
    }
    return userSearchFlag;

}

// searches therapist in the array
bool searchUser(string username, int maxUsers, therapist counselor[] , int &reqUserIndex)
{
    bool userSearchFlag = false;
    for (int i = 0; i < maxUsers; i++)
    {
        if (username == counselor[i].usernamesT)
        {
            userSearchFlag = true;
            reqUserIndex = i; // stores which user entered system
            return userSearchFlag;
        }

        
    }
    return userSearchFlag;

}

// displays list of users
void displayList(patient clients[], family familyMember[], therapist counselor[], int maxUsers)
{

    cout << "*********************************************************************************"
         << "********************************************************************" << endl;

    cout << setw(55) << left << "     PATIENTS" 
         << setw(55) << left << "FAMILY MEMBERS" << setw(55) << left << "THERAPISTS" << endl;

    cout << "**********************************************************************************"
         << "********************************************************************" << endl;
           
    for (int i = 0; i < maxUsers; i++)
    {
        if(clients[i].usernameP != "" || familyMember[i].usernamePF != "" || counselor[i].usernamesT != "")
        {
            cout << i + 1 << "    " << setw(55) << left << clients[i].usernameP 
                 << setw(55) << left << familyMember[i].usernamePF << setw(55) << left << counselor[i].usernamesT << endl;
        }
    }
    
    cout.unsetf(ios::left);
    cout.unsetf(ios::right);

}


// prompt to ask user to continue
void askToContinue(void)
{
    char gar;
    cout << "\n\n\nEnter any key to continue: ";
    getchar();
    cin.ignore(999, '\n');
}

// gets and verifies if date in correct format
string dateVerify(void) 
{
    string date = "";

    while (true) 
    {
        cout << "Please enter date of session (DD-MM-YY): ";
        cin >> date;

        if (date.length() == 8 && date[2] == '-' && date[5] == '-') 
        {
            int day = (date[0] - '0') * 10 + (date[1] - '0'); 
            int month = (date[3] - '0') * 10 + (date[4] - '0'); 

            if (month >= 1 && month <= 12) 
            {
                int maxDays = 31;

                // Determine the number of days in the month
                if (month == 4 || month == 6 || month == 9 || month == 11) 
                {
                    maxDays = 30;
                } 
                else if (month == 2) 
                {
                    maxDays = 28; // no leap year 
                }

                if (day >= 1 && day <= maxDays) 
                {
                    return date; // Valid date
                } else 
                {
                    cout << "Invalid day for the given month. Try again.\n";
                }
            } 
            else 
            {
                cout << "Invalid month. Try again.\n";
            }
        } 
        else 
        {
            cout << "Invalid format. Please use DD-MM-YY format.\n";
        }
    }
}

// checks if input is within bounds and return it
int choiceValidatoin(string choice, char start, char end) 
{
    
    while((choice[0] < start || choice[0] > end) || choice.length() != 1)
    {
        if (cin.fail() || cin.peek() != '\n') 
        {
        cin.clear();                                          // Clear the error flag
        cin.ignore(999, '\n'); // Discard invalid input
        choice = '\0'; // Reset choice to ensure the loop continues
        }

        cout << "Invalid Choice\n"
             << "Enter a choice (b/w " << start << "-" << end << " ) :";
        cin  >> choice;

    }

    
    return (choice[0] - '0');
}

// Funtion Saves the data in a file when user Exits
void saveData(patient clients[], family familyMember[], therapist counselor[])
{
    ofstream fout ("Clients.csv");
    fout << "Client " << "," << "Password " << "," << "Prority "  << "," 
         << "Therapist Review "  << "," << "Note to Patient " << '\n';
    for (int i = 0; i < MAX_CLIENTS; i++) 
    {
        fout << clients[i].usernameP << "," << clients[i].passwordsP << "," << clients[i].patientPriority << ","
             << clients[i].patientReview << "," << clients[i].noteToPatient << '\n' ;
    }
    fout.close();

    fout.open("Client's Goals.csv");
    for(int i = 0; i < MAX_CLIENTS; i++)
    {
        fout << clients[i].usernameP << ",";
        for(int j = 0; j < MAX_GOALS_PER_CLIENT; j++)
        {
            fout << clients[i].patientGoals[j] << ",";

        }
        fout << '\n';

    }
    fout.close();

    fout.open("Client's Family.csv");
    fout << "Family Member "<< "," << "Password "  << "," << "Note by Patient" << '\n';
    for (int i = 0; i < MAX_FAMILY; i++) 
    {
        fout << familyMember[i].usernamePF << "," << familyMember[i].passwordsPF << "," << familyMember[i].noteToFamily << '\n' ;

    }
    fout.close();

    fout.open("Therapists.csv");
    fout << "Therapist "<< "," << "Password "  << "," << "Session Dates" <<"," << "Note by Client's Fmamily" << '\n';
    for (int i = 0; i < MAX_COUNSELOR; i++) 
    {
        fout << counselor[i].usernamesT << "," << counselor[i].passwordsT << "," << counselor[i].sessionDates << "," << counselor[i].noteToTherapist << '\n' ;
        
    }
    fout.close();


}

// loads the data from various files into the program arrays
void loadData(patient clients[], family familyMember[], therapist counselor[])
 {
    ifstream fin;

    fin.open("Clients.csv");
    if (!fin) 
    {
        cout << "Error: Unable to open  the file \"Clients.csv\" (Please recheck the file name and position)";
        return;
    }
    fin.ignore(9999, '\n');
    int i = 0;
    while (i < MAX_CLIENTS && !fin.eof()) 
    {
        getline(fin, clients[i].usernameP, ',');
        getline(fin, clients[i].passwordsP, ',');
        fin >> clients[i].patientPriority;
        fin.ignore();
        getline(fin, clients[i].patientReview, ',');
        getline(fin, clients[i].noteToPatient, '\n');
        i++;
    }
    fin.close();

    fin.open("Client's Goals.csv");
    if (!fin) 
    {
        cout << "Error: Unable to open the file \"Client's Goals.csv\" (Please recheck the file name and position)\n";
        return;
    }
    int j = 0;
    i = 0;
    while (i < MAX_CLIENTS && !fin.eof()) 
    {
        fin.ignore(',');
        j = 0;
        while (j < MAX_GOALS_PER_CLIENT && fin.peek() != '\n' ) 
        {
            getline(fin, clients[i].patientGoals[j], ',');
            cout << j << "     ";
            j++;
            
        }
        fin.ignore('\n');
        i++;
        
    }
    fin.close();

    fin.open("Client's Family.csv");
    if (!fin) 
    {
        cout << "Error: Unable to open the file \"Client's Family.csv\" (Please recheck the file name and position)\n";
        return;
    }
    fin.ignore(9999, '\n');
    i = 0;
    while (i < MAX_FAMILY && !fin.eof()) 
    {
        getline(fin, familyMember[i].usernamePF, ',');
        getline(fin, familyMember[i].passwordsPF, ',');
        getline(fin, familyMember[i].noteToFamily, '\n');
        i++;
    }
    fin.close();

    fin.open("Therapists.csv");
    if (!fin) 
    {
        cout << "Error: Unable to open the file \"Therapists.csv\" (Please recheck the file name and position)\n";
        return;
    }
    fin.ignore(9999, '\n');
    i = 0;
    while (i < MAX_COUNSELOR && !fin.eof()) 
    {
        getline(fin, counselor[i].usernamesT, ',');
        getline(fin, counselor[i].passwordsT, ',');
        getline(fin, counselor[i].sessionDates, ',');
        getline(fin, counselor[i].noteToTherapist, '\n');
        i++;
    }
    fin.close();
}
