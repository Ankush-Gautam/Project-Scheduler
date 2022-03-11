/*  TITLE       :      PROJECT SCHEDULER
 *  DESCRIPTION :      This program helps to schedule the teams of a class or group in a random manner and systematic way.
 *  DEVELOPER   :      Ankush Gautam
 */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <cstdio>
#include <ctype.h> //for isalpha
using namespace std;

/* ==========================================================================================================
    MY DEFINED FUNCTIONS
    ========================================================================================================= */
void HEADER(char* title)
{
    system("cls");
    cout << "\n" << title << "\n\n";

    for(int i = 0; i < 156; i++)
    {
        cout << char(176);
    }

    cout << "\n\n\n";
}

bool isValidName(char* name)
{
    int i = 0;
    while(name[i] != '\0')
    {
        //if the character is not alpha or space
        if((!isalpha(name[i])) && (name[i] != ' '))
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
    while(roll > 0)
    {
        ++length;
        roll /= 10;
    }

    //if rollnumber is not natural number
    if(og <= 0 )
        return false;
    else if(length != 6)
        return false;
    else
        return true;
}

/* ==========================================================================================================
    MY CLASS
    ========================================================================================================= */
class MyClass
{
private:
    int teamID;   //serial Number will be the project leader rollnumber
    int roll[3];
    char memberName[3][24];
    char projectName[50];

public:
    void inputRecord();
    void displayRecord();
    void menu();
    void addTeam();
    void viewAllTeams();

    void editTeam();
    void deleteTeam();
    void searchTeam();
    void schedule();

    //file handling
    int numOfRecords();
    void storeData();
    void readData();

};  //end of MyClass


void MyClass::inputRecord()
{
    cout << "\tRecord No." << numOfRecords() + 1 << "\n\n";

    cout << "\tEnter Project Name: ";
    cin.ignore();
    cin.getline(projectName, 50);

    //Record of project Leader
    cout << "\n\tPROJECT LEADER";
    cout << "\n\t--------------";

    cout << "\n\t(Your Project Leader's is Your Team's ID)\n";
roll_again:
    cout << "\tEnter Rollnumber of Project Leader :  ";
    cin >> roll[0];
    if(!isValidRoll(roll[0]))
    {
        cout << "\t(Invalid Rollnumber!)" << '\n';
        goto roll_again;
    }
name_again:
    cout << "\n\tEnter Name of Project Leader : ";
    cin.ignore();
    cin.getline(memberName[0], 24);
    if(!isValidName(memberName[0]))
    {
        cout << "\t(Invalid Name! Please use Alphabets Only.)" << '\n';
        goto name_again;
    }

    //making project leader's rollnumber as team's id
    teamID = roll[0];

    //details of other two members
    for(int i = 1; i < 3; i++)
    {
        cout << "\n\tMEMBER " << i + 1;
        cout << "\n\t--------\n";

        cout << "\tEnter Rollnumber of Member" << i + 1 << " : ";
        cin >> roll[i];

        cout << "\tEnter Name of Member" << i + 1 << " : ";
        cin.ignore();
        cin.getline(memberName[i], 24);
    }

}

void MyClass::displayRecord()
{
    cout << '\t'  << left  << setw(10) << teamID << setw(49) << projectName;

    for(int i = 0; i <= 3; i++)
    {
        cout << setw(24) << memberName[i];
    }

    cout << '\n';
}

void MyClass::addTeam()
{
    HEADER("\tADD A TEAM");

    inputRecord();
    storeData();

    cout << "\n\n\tTeam Successfully Added.";

    cout << "\n\t";
    system("pause");
}
void MyClass::viewAllTeams()
{
    HEADER("\tALL TEAMS");

    //if there is records than only show the headings and stuff
    if(numOfRecords() > 0)
    {
        cout << '\t' << left << setw(10) << "TEAM ID" << setw(49) << "PROJECT NAME" << setw(24) << "MEMBER 1" << setw(24) << "MEMBER 2" << setw(24) << "MEMBER 3" << "\n\t";
        //line after headings
        for(int i = 0; i < 150; i++)
        {
            cout << "-";
        }

        cout << "\n";
        readData();
    }
    else
    {
        cout << "\tNo Records Found! Add Records First.";
    }

    cout << "\n\t";
    system("pause");
}
void MyClass::editTeam()
{
    HEADER("\tEDIT A TEAM's DETAILS");

    int leaderRoll;
    int found = 0;

    fstream fp, tempfile;
    fp.open("myRecords.txt", ios::in);
    tempfile.open("tempfile.txt", ios::out);

    if(fp.is_open())
    {
        //showing data so the user can choose and have clarity
        cout << left << setw(10) << "\tTEAM ID"  << setw(49) << "PROJECT NAME" << setw(24) << "MEMBER 1" << setw(24) << "MEMBER 2" << setw(24) << "MEMBER 3" << "\n\t";
        //line after headings
        for(int i = 0; i < 150; i++)
        {
            cout << "-";
        }


        cout << "\n";
        readData();

        //asking rollnumber to compare and update if that rollnumber exists
        cout << "\n\tEnter the Group Leader's Rollnumber to Edit: ";
        cin >> leaderRoll;

        while(fp.read((char*)this, sizeof(*this)))
        {
            if(leaderRoll == this->roll[0])
            {
                found = 1;
                cout << "\n\tEnter New Details\n";
                cout << "\t-----------------\n";
                inputRecord();

                //storing the new updated details in the temp file
                tempfile.write((char*)this, sizeof(*this));
            }
            else
            {
                tempfile.write((char*)this, sizeof(*this));
            }
        }
    }
    else
    {
        cout << "\tNo Records Found! Add Records First.";
    }

    //closing the files to perform remove & rename
    fp.close();
    tempfile.close();

    //if the record is found and updated , Now renaming the tempfile
    if(found)
    {
        remove("myRecords.txt");
        rename("tempfile.txt", "myRecords.txt");
        cout << "Record Successfully Updated.";
    }
    else
    {
        cout << "\tNo Match Found!";
    }

    cout << "\n\t";
    system("pause");
}

void MyClass::searchTeam()
{
    HEADER("\tSEARCH A TEAM");

    int leaderRoll;
    int found = 0;

    fstream fp;
    fp.open("myRecords.txt", ios::in);

    if(fp.is_open())
    {
        //asking rollnumber to compare and search if that rollnumber exists
        cout << "\n\tEnter the Group Leader's Rollnumber to Search: ";
        cin >> leaderRoll;

        while(fp.read((char*)this, sizeof(*this)))
        {
            if(leaderRoll == this->roll[0])
            {
                found = 1;
                displayRecord();
            }

        }
    }
    else
    {
        cout << "\tNo Records Found! Add Records First.";
    }

    //closing the files to perform remove & rename
    fp.close();

    if(!found)
        cout << "\tNo Match Found!";

    cout << "\n\t";
    system("pause");
}
void MyClass::deleteTeam()
{
    HEADER("\tDELETE A TEAM");

    int leaderRoll;
    int found = 0;

    fstream fp, tempfile;
    fp.open("myRecords.txt", ios::in);
    tempfile.open("tempfile.txt", ios::out);

    if(fp.is_open())
    {
        //showing data so the user can choose and have clarity
        cout << left << setw(10) << "\tTEAM ID" <<  setw(49) << "PROJECT NAME" << setw(24) << "MEMBER 1" << setw(24) << "MEMBER 2" << setw(24) << "MEMBER 3" << "\n\t";
        //line after headings
        for(int i = 0; i < 150; i++)
        {
            cout << "-";
        }


        cout << "\n";
        readData();

        //asking rollnumber to compare and delete if that rollnumber exists
        cout << "\n\tEnter the Group Leader's Rollnumber to Delete: ";
        cin >> leaderRoll;

        while(fp.read((char*)this, sizeof(*this)))
        {
            if(leaderRoll == this->roll[0])
            {
                found = 1;
            }
            else
            {
                tempfile.write((char*)this, sizeof(*this));
            }
        }
    }
    else
    {
        cout << "\tNo Records Found! Add Records First.";
    }

    //closing the files to perform remove & rename
    fp.close();
    tempfile.close();

    //if the record is found and updated , Now renaming the tempfile
    if(found)
    {
        remove("myRecords.txt");
        rename("tempfile.txt", "myRecords.txt");
        cout << "\n\tRecord Successfully Deleted.";
    }
    else
    {
        cout << "\tNo Match Found!";
    }

    cout << "\n\t";
    system("pause");
}
int MyClass::numOfRecords()
{
    ifstream in;
    in.open("myRecords.txt", ios::in);
    //if file is empty
    if(!in.is_open())
    {
        return 0;
    }

    in.seekg(0, ios::end);  //moving cursor to the end of the file
    int n = in.tellg() / sizeof(*this);    //gives total bytes of the file

    return n; //returns total number of recors as totalsize/size_per_one_obj
}
void MyClass::storeData()
{
    ofstream fp;
    fp.open("myRecords.txt", ios::app);
    fp.write((char*)this, sizeof(*this));
    fp.close();
}

void MyClass::readData()
{
    ifstream fin;
    fin.open("myRecords.txt", ios::in);
    if(fin.is_open() && numOfRecords() > 0)
    {
        while(fin.read((char*)this, sizeof(*this)))
        {
            this->displayRecord();
        }

        fin.close();
    }
    else
    {
        cout << "\tNo Records Found! Add Records First.";
    }
}

void MyClass::menu()
{
    int choice;
    do
    {
        HEADER("\tPROJECT SCHEDULER");

        cout << "\t1. ADD a TEAM" << '\n';
        cout << "\t2. VIEW all TEAMs" << '\n';
        cout << "\t3. EDIT a team details" << '\n';
        cout << "\t4. SEARCH a TEAM" << '\n';
        cout << "\t5. DELETE a TEAM" << '\n';
        cout << "\t6. Schedule TEAMs" << '\n';
        cout << "\t7. TOTAL TEAMs" << '\n';
        cout << "\t0. EXIT" << '\n';

        cout << "\n\tEnter your choice:\n\t>> ";
        cin >> choice;

        switch(choice)
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
        case 7:
            HEADER("\tTOTAL TEAMS");
            cout << "\n\n\tTotal Number of TEAMs = " << numOfRecords();

            cout << "\n\t";
            system("pause");
            break;
        }

    }
    while(choice != 0);
}

//schedule the core of this project
void MyClass::schedule()
{
    HEADER("\tSCHEDULE BY RANDOM");

    fstream fptr;
    fptr.open("myRecords.txt", ios::in);


    int n = numOfRecords();
    MyClass *obj, temp;

    //dynamically making object array
    obj = new MyClass[n];

    //copying file data in the object array
    for(int i = 0; i < n; i++)
    {
        fptr.read((char*)&obj[i], sizeof(obj[i]));
    }

    //sorting
    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(obj[i].roll[0] > obj[j].roll[0])
            {
                temp = obj[i];
                obj[i] = obj[j];
                obj[j]  = temp;
            }
        }
    }

    //displaying
    for(int i = 0; i < n; i++)
    {
        obj[i].displayRecord();
    }


    delete obj;
    cout << "\n\t";
    system("pause");
}


/* ==========================================================================================================
    MAIN FUNCTION
    ========================================================================================================= */
int main()
{
    system("color f8");
    MyClass obj;

    obj.menu();

    return 0;
}
