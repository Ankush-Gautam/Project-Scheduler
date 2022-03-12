/***************************************************************************************************************************
 *  TITLE       :   PROJECT SCHEDULER                                                                                      *
 *  DESCRIPTION :   This program helps to schedule the teams of a class or group in a random manner and systematic way.    *
 *  DEVELOPER   :   Ankush Gautam                                                                                          *
 ***************************************************************************************************************************/

#include "Colors.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <cstdio>
#include <ctype.h>
using namespace std;

/* ==========================================================================================================
    MY DEFINED FUNCTIONS
   ========================================================================================================== */

void line(char ch)
{
    cout << "\n\t";
    for (int i = 0; i < 122; i++)
    {
        cout << char(ch);
    }
    cout << '\n';
}

void HEADER(char *title)
{
    system("cls");
    blue();
    cout << "\n\t" << title << "\n\n";

    for (int i = 0; i < 156; i++)
    {
        cout << char(176);
    }
    black();
    cout << "\n\n\n";
}

bool isValidName(char *name)
{
    int i = 0;
    while (name[i] != '\0')
    {
        // if the character is not alpha or space
        if ((!isalpha(name[i])) && (name[i] != ' '))
        {
            return false;
        }
        i++;
    }
    return true;
}

bool isValidRoll(int roll)
{
    int length = 0;
    int og = roll;
    while (roll > 0)
    {
        ++length;
        roll /= 10;
    }

    // if rollnumber is not natural number
    if (og <= 0)
        return false;
    else if (length != 6)
        return false;
    else
        return true;
}

/* ==========================================================================================================
    MY MAIN CLASS
   ========================================================================================================== */
class MyClass
{
private:
    int teamID; // serial Number will be the project leader rollnumber
    int roll[3];
    char memberName[3][24];
    char projectName[50];

public:
    void inputRecord();
    void displayRecord();
    void displayHeadings();
    void menu();
    void addTeam();
    void viewAllTeams();
    bool rollExist(int);

    void editTeam();
    void deleteTeam();
    void searchTeam();
    void schedule();
    int *randomGenerator(int *, int);

    // file handling
    int numOfRecords();
    void storeData();
    void readData();

}; // end of MyClass
/* ===================================================== DISPLAY HEADINGS =============================================== */
void MyClass::displayHeadings()
{
    darkblue();
    cout << '\t' << std::left << setw(10) << "TeamID" << setw(49) << "PROJECT NAME"
         << setw(24) << "MEMBER 1" << setw(24) << "MEMBER 2" << setw(24) << "MEMBER 3";
    // line after headings
    line('=');

    black();
}
/* ===================================================== ROLL EXISTS ==================================================== */
bool MyClass::rollExist(int rn)
{
    ifstream in;
    in.open("data.dat", ios::in);

    while(in.read((char*)this, sizeof(*this)))
    {
        if(rn == this->roll[0])
        {
            in.close();
            return true;
        }
    }
    in.close();
    return false;
}
/* ================================================ INPUT RECORD ===================================================== */
void MyClass::inputRecord()
{
    green();
    cout << "\tRecord No." << numOfRecords() + 1;
    cout << "\n\t------------";
    black();
    cout << "\n\n\tEnter Project Name: ";
    fflush(stdin);
    cin.getline(projectName, 50);

    // Record of project Leader
    green();
    cout << "\n\tPROJECT LEADER";
    cout << "\n\t--------------";
    black();

    darkgreen();
    cout << "\n\t(Your Project Leader's is Your Team's ID)\n";
    black();
roll_again:
    cout << "\tEnter Rollnumber of Project Leader :  ";
    fflush(stdin);
    cin >> roll[0];
    if (!isValidRoll(roll[0]))
    {
        red();
        cout << "\t(Invalid Rollnumber!)" << '\n';
        black();
        goto roll_again;
    }
    if(rollExist(roll[0]))
    {
        red();
        cout << "\t(This Rollnumber already exists!)\n";
        black();
        goto roll_again;
    }
name_again:
    cout << "\tEnter Name of Project Leader : ";
    fflush(stdin);
    cin.getline(memberName[0], 24);
    if (!isValidName(memberName[0]))
    {
        red();
        cout << "\t(Invalid Name! Please Use Alphabets Only.)" << '\n';
        black();
        goto name_again;
    }

    // making project leader's rollnumber as team's id
    teamID = roll[0];

    // details of other two members
    for (int i = 1; i < 3; i++)
    {
        //member index title
        green();
        cout << "\n\tMEMBER " << i + 1;
        cout << "\n\t--------\n";
        black();

        //rollnumbers of member
roll_again2:
        cout << "\tEnter Rollnumber of Member" << i + 1 << " : ";
        fflush(stdin);
        cin >> roll[i];
        fflush(stdin);
        if (!isValidRoll(roll[i]))
        {
            red();
            cout << "\t(Invalid Rollnumber!)" << '\n';
            black();
            goto roll_again2;
        }
        if((rollExist(roll[i])) || (roll[i] == roll[0]) || (roll[1] == roll[2]))
        {
            red();
            cout << "\t(This Rollnumber already exists!)\n";
            black();
            goto roll_again2;
        }

        //name of members
name_again2:
        cout << "\tEnter Name of Member" << i + 1 << " : ";
        fflush(stdin);
        cin.getline(memberName[i], 24);
        if (!isValidName(memberName[i]))
        {
            red();
            cout << "\t(Invalid Name! Please Use Alphabets Only.)" << '\n';
            black();
            goto name_again2;
        }

    }//end of input_details for 2members
}
/* ================================================== DISPLAY A TEAM ======================================================= */
void MyClass::displayRecord()
{
    cout << '\t' << std::left << setw(10) << teamID << setw(49) << projectName;
    for (int i = 0; i < 3; i++)
    {
        cout << setw(24) << memberName[i];
    }
    cout << '\n';
}
/* ===================================================== ADD TEAM =========================================================== */
void MyClass::addTeam()
{
    HEADER("ADD A TEAM");
    char yesno;

    this->inputRecord();
    this->storeData();

    darkgreen();
    cout << "\n\tTeam Successfully Added.";
    black();

    line('.');
    cout << "\tDo you want to Add Another?(Press 'y' for Yes)\n\t>> ";
    cin >> yesno;

    if (yesno == 'y' || yesno == 'Y')
        addTeam();
}
/* ================================================== VIEW ALL TEAMS ======================================================== */
void MyClass::viewAllTeams()
{
    HEADER("ALL TEAMS");

    // if there is records than only show the headings and stuff
    if (numOfRecords() > 0)
    {
        darkgreen();
        cout << "\tTOTAL TEAMs = " << numOfRecords() << "\n\n";
        displayHeadings();
        readData();
    }
    else
    {
        red();
        cout << "\tNo Records Found! Add Records First.";
        black();
    }

    cout << "\n\t";
    purple();
    system("pause");
    black();
}
/* ===================================================== EDIT TEAM ========================================================== */
void MyClass::editTeam()
{
    HEADER("EDIT A TEAM's DETAILS");

    int leaderRoll;
    int found = 0;

    ifstream fp;
    ofstream tempfile;
    fp.open("data.dat", ios::in);
    tempfile.open("tempfile.dat", ios::out);

    if (fp.is_open() && numOfRecords() > 0)
    {
        // showing data so the user can choose and have clarity
        displayHeadings();
        readData();

        // asking rollnumber to compare and update if that rollnumber exists
        green();
        cout << "\n\tEnter the Group Leader's Rollnumber to Edit: ";
        black();
        cin >> leaderRoll;

        // searching for the records and copying the data in tempfile
        while (fp.read((char *)this, sizeof(*this)))
        {
            if (leaderRoll == this->roll[0])
            {
                found = 1;
                cout << "\n\tEnter New Details\n";
                cout << "\t-----------------\n";
                inputRecord();

                // storing the new updated details in the temp file
                tempfile.write((char *)this, sizeof(*this));
            }
            else
            {
                tempfile.write((char *)this, sizeof(*this));
            }
        }

        // closing the files to perform remove & rename
        fp.close();
        tempfile.close();

        // if the record is found and updated , Now renaming the tempfile
        if (found)
        {
            remove("data.dat");
            rename("tempfile.dat", "data.dat");
            green();
            cout << "Record Successfully Updated.";
            black();
        }
        else
        {
            red();
            cout << "\tNo Match Found!";
            black();
        }

        line('.');
        char yesno;
        cout << "\tDo you want to Edit Another?(Press 'y' for Yes)\n\t>> ";
        cin >> yesno;

        if (yesno == 'y' || yesno == 'Y')
            editTeam();
    }
    else
    {
        red();
        cout << "\tNo Records Found! Add Records First.";
        black();
    }

    cout << "\n\t";
    purple();
    system("pause");
    black();
}

/* ===================================================== SEARCH TEAM ============================================================== */
void MyClass::searchTeam()
{
    HEADER("SEARCH A TEAM");

    int leaderRoll;
    int found = 0;

    ifstream fp;
    fp.open("data.dat", ios::in);

    if (fp.is_open())
    {
        // asking rollnumber to compare and search if that rollnumber exists
        green();
        cout << "\n\tEnter the Group Leader's Rollnumber to Search: ";
        black();
        cin >> leaderRoll;

        while (fp.read((char *)this, sizeof(*this)))
        {
            if (leaderRoll == this->roll[0])
            {
                system("cls");
                HEADER("SEARCH A TEAM");

                found = 1;
                displayHeadings();
                displayRecord();
            }
        }
        fp.close();

        if (!found)
        {
            red();
            cout << "\tNo Match Found!";
            black();
        }

        //If user wants to search again
        line('.');
        char yesno;
        cout << "\tDo you want to Search Another?(Press 'y' for Yes)\n\t>> ";
        cin >> yesno;
        if (yesno == 'y' || yesno == 'Y')
            searchTeam();
    }
    else
    {
        red();
        cout << "\tNo Records Found! Add Records First.";
        cout << "\n\t";
        purple();
        system("pause");
        black();
    }
}
/* ===================================================== DELETE TEAM ============================================================== */
void MyClass::deleteTeam()
{
    HEADER("DELETE A TEAM");

    int leaderRoll;
    int found = 0;

    ifstream fp;
    ofstream tempfile;
    fp.open("data.dat", ios::in);
    tempfile.open("tempfile.dat", ios::out);

    if (fp.is_open())
    {
        // showing data so the user can choose and have clarity
        displayHeadings();
        readData();

        // asking rollnumber to compare and delete if that rollnumber exists
        darkgreen();
        cout << "\n\n\tEnter the Group Leader's Rollnumber to Delete: ";
        black();
        cin >> leaderRoll;

        while (fp.read((char *)this, sizeof(*this)))
        {
            if (leaderRoll == this->roll[0])
            {
                found = 1;
            }
            else
            {
                tempfile.write((char *)this, sizeof(*this));
            }
        }

        // closing the files to perform remove & rename
        fp.close();
        tempfile.close();

        // if the record is found and updated , Now renaming the tempfile
        if (found)
        {
            remove("data.dat");
            rename("tempfile.dat", "data.dat");
            darkgreen();
            cout << "\n\tRecord Successfully Deleted.";
            black();
        }
        else
        {
            red();
            cout << "\tNo Match Found!";
            black();
        }

        line('.');
        char yesno;
        cout << "\tDo you want to Delete Another?(Press 'y' for Yes)\n\t>> ";
        cin >> yesno;

        if (yesno == 'y' || yesno == 'Y')
            deleteTeam();

    }
    else
    {
        red();
        cout << "\tNo Records Found! Add Records First.\n\t";
        purple();
        system("pause");
        black();
    }
}

/* ===================================================== NUM OF RECORDS ======================================================= */
int MyClass::numOfRecords()
{
    ifstream in;
    in.open("data.dat", ios::in);
    // if file is empty
    if (!in.is_open())
    {
        return 0;
    }

    in.seekg(0, ios::end);              // moving cursor to the end of the file
    int n = in.tellg() / sizeof(*this); // gives total bytes of the file

    return n; // returns total number of recors as totalsize/size_per_one_obj
}
/* ===================================================== STORE DATA =============================================================== */
void MyClass::storeData()
{
    ofstream fp;
    fp.open("data.dat", ios::app);
    fp.write((char *)this, sizeof(*this));
    fp.close();
}

void MyClass::readData()
{
    ifstream fin;
    fin.open("data.dat", ios::in);
    if (fin.is_open() && numOfRecords() > 0)
    {
        while (fin.read((char *)this, sizeof(*this)))
        {
            this->displayRecord();
        }

        fin.close();
    }
    else
    {
        red();
        cout << "\tNo Records Found! Add Records First.";
        black();
    }
}
/* ===================================================== MENU ================================================================== */
void MyClass::menu()
{
    int choice;
    do
    {
        HEADER("PROJECT SCHEDULER");

        cout << "\t1. ADD a TEAM" << '\n';
        cout << "\t2. VIEW all TEAMs" << '\n';
        cout << "\t3. EDIT a team details" << '\n';
        cout << "\t4. SEARCH a TEAM" << '\n';
        cout << "\t5. DELETE a TEAM" << '\n';
        cout << "\t6. Schedule TEAMs" << '\n';
        cout << "\t0. EXIT" << '\n';

        darkgreen();
        cout << "\n\tEnter your choice:\n\t>> ";
        black();
        cin >> choice;

        switch (choice)
        {
        case 1:
            addTeam();
            break;
        case 2:
            viewAllTeams();
            break;
        case 3:
            editTeam();
            break;
        case 4:
            searchTeam();
            break;
        case 5:
            deleteTeam();
            break;
        case 6:
            schedule();
            break;
        }
    }
    while (choice != 0);
}
/* ===================================================== SCHEDULE ================================================================== */
void MyClass::schedule()
{
    HEADER("SCHEDULE TEAMS");

    ifstream fptr;
    fptr.open("data.dat", ios::in);
    int n = numOfRecords();

    // if the file exists or atleast has a record to schedule
    if (fptr.is_open() && n > 0)
    {
        int sortChoice;
        MyClass *obj, temp;
        // dynamically making object array
        obj = new MyClass[n];

        // copying file data in the object array
        for (int i = 0; i < n; i++)
        {
            fptr.read((char *)&obj[i], sizeof(obj[i]));
        }
        do
        {
            HEADER("SCHEDULE TEAMS");

            /*----------------- Sub-Menu to Choose which type of sorting -------------------*/
            cout << "\t1. Schedule by Team ID" << '\n';
            cout << "\t2. Schedule by Project Name" << '\n';
            cout << "\t3. Schedule by Leader Name" << '\n';
            cout << "\t4. Randomizer" << '\n';
            cout << "\t0. Back to Menu" << '\n';

            green();
            cout << "\n\tEnter your choice:\n\t>> ";
            black();
            cin >> sortChoice;

            switch (sortChoice)
            {
            case 1:
                // sorting by team ID
                HEADER("SCHEDULE BY TEAM ID");
                for (int i = 0; i < n; i++)
                {
                    for (int j = i + 1; j < n; j++)
                    {
                        if (obj[i].roll[0] > obj[j].roll[0])
                        {
                            temp = obj[i];
                            obj[i] = obj[j];
                            obj[j] = temp;
                        }
                    }
                }
                break;
            case 2:
                // sorting by Project Name
                HEADER("SCHEDULE BY PROJECT NAME");
                for (int i = 0; i < n; i++)
                {
                    for (int j = i + 1; j < n; j++)
                    {
                        if (strcmp(obj[i].projectName, obj[j].projectName) > 0)
                        {
                            temp = obj[i];
                            obj[i] = obj[j];
                            obj[j] = temp;
                        }
                    }
                }
                break;
            case 3:
                // sorting by Leader Name
                HEADER("SCHEDULE BY LEADER NAME");
                for (int i = 0; i < n; i++)
                {
                    for (int j = i + 1; j < n; j++)
                    {
                        if (strcmp(obj[i].memberName[0], obj[j].memberName[0]) > 0)
                        {
                            temp = obj[i];
                            obj[i] = obj[j];
                            obj[j] = temp;
                        }
                    }
                }
                break;
            case 4:
                // sorting randomly
                HEADER("SCHEDULE RANDOMLY");

                // making array to store random index numbers
                int *myArr;
                myArr = new int[n];
                myArr = randomGenerator(myArr, n);

                for (int i = 0; i < n; i++)
                {
                    for (int j = i + 1; j < n; j++)
                    {
                        temp = obj[myArr[i]];
                        obj[myArr[i]] = obj[myArr[j]];
                        obj[myArr[j]] = temp;
                    }
                }
                delete myArr;
                break;
            }

            /*----------------- Displaying the teams after sorting -------------------*/
            if (sortChoice >= 1 && sortChoice <= 4)
            {
                displayHeadings();
                for (int i = 0; i < n; i++)
                {
                    obj[i].displayRecord();
                }

                cout << "\n\t";
                purple();
                system("pause");
                black();
            }
        }
        while (sortChoice != 0);

        delete obj;
    }
    else
    {
        red();
        cout << "\tNo Records Found! Add Records First.";
        black();
        cout << "\n\t";
        purple();
        system("pause");
        black();
    }
}

/* ===================================================== RANDOM GENERATOR ========================================================= */
int *MyClass::randomGenerator(int *num, int n)
{
    srand(time(0));
    int temp;

    // new array
    int *arr;
    arr = new int[n];

    // initializing array
    for (int i = 0; i < n; i++)
    {
        arr[i] = i;
    }

    // shuffling the indexes
    for (int i = n - 1; i > 0; --i)
    {
        int j = rand() % i;

        // swapping the initialized array with the random one
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    // displaying the array
    for (int i = 0; i < n; i++)
    {
        num[i] = arr[i];
    }
    delete arr;

    return num;
}

/* ==========================================================================================================
    AUTHENTICATION CLASS
   ========================================================================================================== */
class UserValidation
{
private:
    char username[10], password[10];
    static int guess;
    int totalguess = 5;

public:
    void inputUser()
    {
        HEADER("LOGIN PAGE");
        fflush(stdin);
        cout << "\tEnter username: ";
        cin >> username;
        fflush(stdin);
        cout << "\tEnter password: ";
        cin >> password;
    }

    bool validateUser()
    {
        while (guess < totalguess)
        {
            inputUser();
            if ((strcmp(username, "admin") == 0) && (strcmp(password, "password") == 0))
            {
                return true;
            }
            else
            {
                red();
                cout << "\n\tInvalid Username or Password! Try Again.\n\t(You have " << totalguess - guess - 1 << " try left.)\n\t";
                purple();
                system("pause");
                black();
                guess++;
            }
        }
        return false;
    }
};
int UserValidation::guess = 0;

/* ==========================================================================================================
    MAIN FUNCTION
    ========================================================================================================= */
int main()
{
    system("title Project Scheduler");
    system("color f8");
    UserValidation user;

    // if vaidateuser returns true goto the menu
    if (user.validateUser())
    {
        MyClass obj;
        obj.menu();
    }
    else
    {
        system("cls");
        red();
        cout << "\n\n\tYou tried 5 times and could not validate yourself.\n\tSomething's Fishy!! ";
        system("pause");
    }
    return 0;
}
