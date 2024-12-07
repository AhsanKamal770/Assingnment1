
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void initializeCourses(string codeList[], string nameList[], int crtHrsList[], int semList[], int size);
void initializeUsers(string usernames[], string passwords[], int size);
void intializestd(string stdname[],string stdreg[],string stdcour[],int Max_STUDENTS=40);
// function for data persistent
bool saveCourse(string codeList[], string nameList[], int crtHrsList[], int semList[], int size);
bool loadCourses(string codeList[], string nameList[], int crtHrsList[], int semList[], int size);
bool loadUser(string usersList[], string passwordList[], int size);
bool savestudents(string stdname[],string stdreg[],string stdcour[],int MAX_STUDENTS=40);
bool loadstudents(string stdname[],string stdreg[],string stdcour[],int MAX_STUDENTS=40);

// COURSE MANAGEMENT
int searchCourseCode(string codeList[], int size, string courseCode);
bool addCourses(string codeList[], string nameList[], int creditHours[], int semList[], int size, string courseCode, string courseName, int credit, int semester);
void viewCourses(string codeList[], string nameList[], int creditHours[], int semList[], int size);
void viewSemesterCourse(string codeList[], string nameList[], int creditHours[], int semList[], int size, int semester);
bool updateCourse(string codeList[], string nameList[], int creditHours[], int semList[], int size, string oldCourseCode, string courseCode, string courseName, int credit, int semester);
bool deleteCourse(string codeList[], string nameList[], int creditHours[], int semList[], int size, string courseCode);

// VALIDATION FUNCTIONS
bool isValidCourseCode(string code);
bool isValidCreditHours(int creditHours);
bool isValidSemester(int semester);
bool isValidCourseName(string name);
bool validateAllData(string courseCode, string courseName, int credit, int semester);
bool isvalidstdname(string stdname);
bool isvalidstdreg(string stdreg);

// USER MANAGEMENT
bool userExist(string user[], string pass[], string users, string passs, int size);
void login(string &userName, string &password);

// STUDENT MANAGEMENTT
bool unregistercour(string stdreg[], string reg, string stdcour[], string name);
bool registercour(string stdreg[], string reg, string codeList[], string stdcour[], string name);
bool updatestd(string stdname[], string name, string stdreg[], string reg, string newreg);
bool deletestd(string stdreg[], string reg, string stdname[], string stdcour[]);
bool addstudent(string stdname[], string name, string stdreg[], string reg);
int findstdind(string stdreg[], string reg, int MAX_STUDENTS = 40);


int main()
{

    const int MAX_COURSES = 10;
    const int MAX_USERS = 10;
    const int MAX_STUDENTS = 40;

    // Variables for Input
    string oldCourseCode;         // Stores the old course code for updates
    string userName;              // Stores the username for login
    string password;              // Stores the password for login
    string courseCode;            // Stores the course code
    string courseName;            // Stores the course name
    string studentName;           // Stores the student name
    string regNo;                 // Stores the student registration number
    string newRegNo;              // Stores a new registration number during updates
    int credit;                   // Stores the credit hours of a course
    int semester;                 // Stores the semester number
    int input;                    // User menu input
    bool flag = false;            // General-purpose flag for conditions

    // Arrays for Courses
    string codeList[MAX_COURSES];       // Stores course codes
    string nameList[MAX_COURSES];       // Stores course names
    int creditHours[MAX_COURSES];       // Stores credit hours for courses
    int semList[MAX_COURSES];           // Stores semesters for courses

    // Arrays for Users
    string usersList[MAX_USERS];        // Stores user names
    string passwordList[MAX_USERS];     // Stores user passwords

    // Arrays for Students
    string stdname[MAX_STUDENTS];       // Stores student names
    string stdreg[MAX_STUDENTS];        // Stores student registration numbers
    string stdcour[MAX_STUDENTS];       // Stores student courses

    // Initialize All Arrays
    initializeCourses(codeList, nameList, creditHours, semList, MAX_COURSES);
    initializeUsers(usersList, passwordList, MAX_USERS);
    intializestd(stdname,stdreg,stdcour,MAX_STUDENTS);

    // Load Data into Arrays 
    loadstudents(stdname, stdreg, stdcour); // Load student data
    loadCourses(codeList, nameList, creditHours, semList, MAX_COURSES); // Load course data
    loadUser(usersList, passwordList, MAX_USERS); // Load user data

    // Login Function
    login(userName, password);
    do
    {
    	if((userName == "" && password == "")){
    		login(userName, password);
    	}
        else
        while (userExist(usersList, passwordList, userName, password, MAX_USERS) != true )
        {
            cout << "Incorrect info please reenter username and password" << endl;
            cout << "Enter User name: ";
            cin >> userName;
            cout << "Enter Password: ";
            cin >> password;
            cout << endl;
        }

        if (userExist(usersList, passwordList, userName, password, MAX_USERS))
        {

            cout << "Choose the following option" << endl;
            cout << "1   Add Courses" << endl;
            cout << "2   Update Courses" << endl;
            cout << "3   Delete Courses" << endl;
            cout << "4   View All Courses" << endl;
            cout << "5   View Courses of a Semester" << endl;
            cout << "6   Add New Student" << endl;
            cout << "7   Update Student" << endl;
            cout << "8   Delete Student" << endl;
            cout << "9   View All Students" << endl;
            cout << "10  Register the course for student" << endl;
            cout << "11  Unregister the course for student" << endl;
            cout << "12  Logout of the system" << endl;
            cout << "13  Exit Program" << endl;
            cout << "Enter the option: ";
            cin >> input;
            switch (input)
            {
            // This case for adding the course details
            case 1:
{
                cout << "Enter the details of the course: ";
                cin >> courseCode;
                cin >> credit;
                cin >> semester;
                cin.ignore();
                getline(cin, courseName);

                // Check validity of all inputs
                if (validateAllData(courseCode, courseName, credit, semester))
                {
                    // Call addCourse function
                    if (addCourses(codeList, nameList, creditHours, semList, MAX_COURSES, courseCode, courseName, credit, semester))
                    {
                        cout << "Course Successfully added" << endl;
                    }
                    else
                    {
                        cout << "Sorry No space to add new course" << endl;
                    }
                }
                else
                {
                    // If any validity is false it will not add the course
                    cout << "Invalid details" << endl;
                }

                break;
}
            // This case for Updating the course details
            case 2:
{
                cout << "Enter the course code" << endl;
                cin >> oldCourseCode;

                // check validity of courseCode
                if (isValidCourseCode(oldCourseCode))
                {

                    // Find the index of courseCode which user entered to update the course details

                    cout << "Enter the details of the course: ";
                    cin >> courseCode;
                    cin >> credit;
                    cin >> semester;
                    cin.ignore();
                    getline(cin, courseName);
                    // Check validity of all details entered by user
                    if (validateAllData(courseCode, courseName, credit, semester))
                    {

                        if (updateCourse(codeList, nameList, creditHours, semList, MAX_COURSES, oldCourseCode, courseCode, courseName, credit, semester))
                        {
                            cout << "Course successfully updated" << endl;
                        }
                        else
                        {
                            cout << "No course found" << endl;
                        }
                    }
                    else
                    {
                        cout << "Invalid data" << endl;
                    }
                }
                else
                {
                    // here we will show message of not valid data
                    cout << "Invalid Data" << endl;
                }

                break;
}
                // This case for deleting the course details

            case 3:
{               cout << "Enter Course code" << endl;
                cin >> courseCode;
                // Validate the course Code
                if (isValidCourseCode(courseCode))
                {
                    // call function to delete the course detail which has same course code as user enter
                    if (deleteCourse(codeList, nameList, creditHours, semList, MAX_COURSES, courseCode))
                    {
                        cout << "Course Successfully deleted" << endl;
                    }
                    else
                    {
                        cout << "Sorry No Course found " << endl;
                    }
                }
                else
                {
                    // if course code is invalid then this message will show
                    cout << "Invalid Course code" << endl;
                }

                break;
}
                // This case for displaying all details of all courses

            case 4:
{               // View All details of All courses
                viewCourses(codeList, nameList, creditHours, semList, MAX_COURSES);
                break;

}            // This case for displaying course details of specific semester
            case 5:
{               cout << "Enter the semester:";
                cin >> semester;
                // Check valildidty of semester entered by user
                if (isValidSemester(semester))
                {
                    // Show All details of course of the semester entered by user
                    viewSemesterCourse(codeList, nameList, creditHours, semList, MAX_COURSES, semester);
                }
                else
                {
                    // If our semester is invalid
                    cout << "Invalid data" << endl;
                }

                break;
}            // For Closing the Program
            case 6: // Add Student
 {              cout << "Enter details of Student (RegNo Name): ";
                cin >> regNo;
                cin.ignore();
                getline(cin, studentName);
                if (addstudent(stdname, studentName, stdreg, regNo))
                    cout << "Student has been added successfully.\n";
                else
                    cout << "Failed to add student.\n";
                break;
}
            case 7: // Update Student
 {              cout << "Enter registration number to edit: ";
                cin >> regNo;
                cin.ignore();
                cout << "Enter new details (RegNo Name): ";
                string newreg;
                cin>>newreg;
                cin.ignore();
                getline(cin, studentName);
                if (updatestd(stdname, studentName, stdreg, regNo,newreg))
                    cout << "Student has been updated successfully.\n";
                else
                    cout << "Failed to update student.\n";
                break;
}
            case 8: // Delete Student
 {               cout << "Enter registration number to delete: ";
                cin >> regNo;
                if (deletestd(stdreg, regNo, stdname, stdcour))
                    cout << "Student has been deleted successfully.\n";
                else
                    cout << "Failed to delete student.\n";
                break;
}
            case 9:
  {          	cout<<left;
                cout<<"--------------------------------------------------------------------------------"<<endl;
				cout <<setw(20)<< "Name"<<setw(20)<<"Reg. No."<<setw(20)<<"Course/s"<<endl;
                cout<<"--------------------------------------------------------------------------------"<<endl;
				for (int i=0;i<MAX_STUDENTS;i++){
                	if(stdname[i]!=" "&&stdreg[i]!=" "){
                		cout<<setw(20)<<stdname[i]<<setw(20)<<stdreg[i]<<setw(20)<<stdcour[i]<<endl;
					}
				}
				cout<<"--------------------------------------------------------------------------------"<<endl;
				break;
}
            case 10: // Register Course
 {               cout << "Enter registration number to register course: ";
                cin >> regNo;
                cout << "Enter course code: ";
                cin >> courseCode;           
                if (registercour(stdreg, regNo,codeList, stdcour, courseCode))
                    cout << "Course has been registered for student.\n";
                else
                    cout << "Failed to register course.\n";
                break;
}
            case 11: // Unregister Course
 {               cout << "Enter registration number to unregister course: ";
                cin >> regNo;          
                cout << "Enter course code: ";
                cin >> courseCode;
                if (unregistercour(stdreg, regNo,stdcour, courseCode))
                    cout << "Course has been unregistered.\n";
                else
                    cout << "Failed to unregister course.\n";
                break;
}
            case 12:
 {               cout << "Saving data to file...\n";
                if (saveCourse(codeList, nameList, creditHours, semList, MAX_COURSES)&&savestudents(stdname, stdreg, stdcour,40))
                    cout << "Data saved successfully.\n";
                else
                    cout << "Failed to save data.\n";
                userName="";password="";
                break;
  }
            case 13:
  {          	 cout << "Saving data to file...\n";
                if(saveCourse(codeList, nameList, creditHours, semList, MAX_COURSES)&&savestudents(stdname, stdreg, stdcour,40)){
            		cout<<"Courses & student/s data saved successfully!"<<endl;
				}
				else{
					cout<<"Error opening file!"<<endl;
				}
				break;
}
            default:
 {               cout << "Invalid option.\n";
                break;
}
			}
        }
    } while (input != 13);

    return 0;
}

void initializeCourses(string codeList[], string nameList[], int crtHrsList[], int semList[], int size)
{
    for (int s = 0; s < size; s++)
    {
        codeList[s] = " ";
        nameList[s] = " ";
        crtHrsList[s] = 0;
        semList[s] = 0;
    }
}

void initializeUsers(string usernames[], string passwords[], int size)
{
    for (int s = 0; s < size; s++)
    {
        usernames[s] = " ";
        passwords[s] = " ";
    }
}

bool saveCourse(string codeList[], string nameList[], int crtHrsList[], int semList[], int size)
{
    // This variable for read data from file
    ofstream myfile;
    /*Open the file if exist if not exist then make new file of this name ios::app maens that the new data will append in file and
    not remove previous content of file */
    myfile.open("Course.txt");
    // This function will check if the file open then write data from file
    if (myfile.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            if (codeList[i] != " " && nameList[i] != " " && crtHrsList[i] != 0 && semList[i] != 0)
            {
                // These lines will write all array data to the file and make a comma separated file
                myfile << codeList[i] << ",";
                myfile << nameList[i] << ",";
                myfile << crtHrsList[i] << ",";
                myfile << semList[i] << endl;
            }
        }

        myfile.close();
        return true;
    }
    else
    {
        // If there is error while opening file this function will return false
        return false;
    }
}
// Function to load course in arrays
bool loadCourses(string codeList[], string nameList[], int crtHrsList[], int semList[], int size)
{
    ifstream fin;
    fin.open("Course.txt"); // Changed this function because stoi does not work on my IDE (DEV C++)

    if (!fin)
    {
        cout << "Error opening the file for loading courses!" << endl;
        return false;
    }

    int k = 0;
    while (getline(fin, codeList[k], ',') && k < size)
    {

        if (codeList[k].empty() || codeList[k] == "\n"||codeList[k]==" ")
        {
            codeList[k] = " ";
            break;
        }
        else
        {
            getline(fin, nameList[k], ',');
            fin >> crtHrsList[k];
            fin.ignore();
            fin >> semList[k];
            fin.ignore();
        }
        k++;
    }
    fin.close();
    return true;
}

// Fuunction to read users from file and load then onto the arrays
bool loadUser(string usersList[], string passwordList[], int size)
{
    int i = 0;
    ifstream getUsers("loaduser.txt");
    if (!getUsers.is_open())
    {
        cout << "File failed to open" << endl;
        return false;
    }
    else
    {
        string username, password;
        string line;
        while (!getUsers.eof() && i < size)
        {
            getline(getUsers, line);
            stringstream ss(line);
            getline(ss, username, ',');
            usersList[i] = username;
            getline(ss, password, ',');
            passwordList[i] = password;
            i++;
        }

        getUsers.close();
        return true;
    }
}

int searchCourseCode(string codeList[], int size, string courseCode)
{
    int index = -1;
    for (int i = 0; i < size; i++)
    {

        if (codeList[i] == courseCode)
        {
            index = i;
            break;
        }
    }
    return index;
}
// This Function Will add the function
bool addCourses(string codeList[], string nameList[], int creditHours[], int semList[], int size, string courseCode, string courseName, int credit, int semester)
{
    bool flag = false;
    int i = searchCourseCode(codeList, size, " ");
    if (i != -1)
    {

        codeList[i] = courseCode;
        nameList[i] = courseName;
        creditHours[i] = credit;
        semList[i] = semester;
        flag = true;
    }
    return flag;
}

// This Function will display all course details
void viewCourses(string codeList[], string nameList[], int creditHours[], int semList[], int size)
{

    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;
    cout << left;
    cout << setw(10) << "Course"
         << setw(50) << "Course"
         << setw(10) << "Credit"
         << setw(10) << "Semester" << endl;
    cout << setw(10) << "Code"
         << setw(50) << "Name"
         << setw(10) << "Hours"
         << setw(10) << "Number" << endl;
    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        if (codeList[i] != " "&&nameList[i]!=" "&&creditHours[i]!=0&&semList[i]!=0)
        {

            cout << setw(10) << codeList[i]
                 << setw(50) << nameList[i]
                 << setw(10) << creditHours[i]
                 << setw(10) << semList[i] << endl;
        }
    }
    cout << endl;
    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;
}

// This function will display the course details of the specific semester
void viewSemesterCourse(string codeList[], string nameList[], int creditHours[], int semList[], int size, int semester)
{

    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;
    cout << left;
    cout << setw(10) << "Course"
         << setw(50) << "Course"
         << setw(10) << "Credit"
         << setw(10) << "Semester" << endl;
    cout << setw(10) << "Code"
         << setw(50) << "Name"
         << setw(10) << "Hours"
         << setw(10) << "" << endl;
    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < size; i++)
    {
        if (semList[i] == semester && codeList[i] != "")
        {
            cout << setw(10) << codeList[i]
                 << setw(50) << nameList[i]
                 << setw(10) << creditHours[i]
                 << setw(10) << semList[i] << endl;
        }
    }
    cout << endl;
    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;
}

// This function will update the course by using courseCode index which we define as globel varaible
bool updateCourse(string codeList[], string nameList[], int creditHours[], int semList[], int size, string oldCourseCode, string courseCode, string courseName, int credit, int semester)
{

    bool flag = false;
    int updateIndex = searchCourseCode(codeList, size, oldCourseCode);
    cout << "Upate Index " << updateIndex << endl;
    if (updateIndex != -1)
    {
        codeList[updateIndex] = courseCode;
        nameList[updateIndex] = courseName;
        creditHours[updateIndex] = credit;
        semList[updateIndex] = semester;
        flag = true;
    }
    return flag;
}

// This function will delete the course by using courseCode
bool deleteCourse(string codeList[], string nameList[], int creditHours[], int semList[], int size, string courseCode)
{
    bool flag = false;
    int i = searchCourseCode(codeList, size, courseCode);
    if (i != -1)
    {
        codeList[i] = " ";
        nameList[i] = " ";
        creditHours[i] = 0;
        semList[i] = 0;
        flag = true;
    }

    return flag;
}
// checking validity of coursecode
bool isValidCourseCode(string code)
{
    int x = code.length();
    bool flag = true;
    if (x == 5)
    {

        for (int i = 0; i < 2; i++)
        {
            if (!((code[i] >= 'a' && code[i] <= 'z') || (code[i] >= 'A' && code[i] <= 'Z')))
            {
                flag = false;
                break;
            }
        }

        for (int i = 2; i < 5 && flag; i++)
        {
            if (!(code[i] >= '0' && code[i] <= '9'))
            {
                flag = false;
                break;
            }
        }
    }

    return flag;
}

// checking the credit hours
bool isValidCreditHours(int creditHours)
{
    bool flag = true;
    if (!(creditHours >= 1 && creditHours <= 3))
    {
        flag = false;
    }

    return flag;
}

// checking semester
bool isValidSemester(int semester)
{
    bool flag = true;
    if (!(semester >= 1 && semester <= 9))
    {
        flag = false;
    }
    return flag;
}

// checking coursename
bool isValidCourseName(string name)
{
    bool flag = true;
    if (name.length() <= 50)
    {
        for (int i = 0; i < name.length(); i++)
        {
            if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z') || (name[i] == ' ')))
                flag = false;
        }
    }
    else
        flag = false;

    return flag;
}

bool validateAllData(string courseCode, string courseName, int credit, int semester)
{
    if (!(isValidCourseCode(courseCode) && isValidCreditHours(credit) && isValidSemester(semester) && isValidCourseName(courseName)))
    {
        return false;
    }
    return true;
}

bool userExist(string user[], string pass[], string users, string passs, int size)
{
    bool flag = false;
    int i;
    for (i = 0; i < size; i++)
    {
        if (user[i] == users && pass[i] == passs)
        {
            flag = true;
            break;
        }
    }

    return flag;
}

void login(string &userName, string &password)
{

    system("cls");
    cout << endl;
    cout << "** Welcome To University Learning Management System ** " << endl;
    cout << "Dear users current software is intended for authorized users only." << endl;
    cout << "Login to the system to get access" << endl;
    cout << "Enter User name: ";
    cin >> userName;
    cout << "Enter Password: ";
    cin >> password;
    cout << endl;
}

bool isvalidstdreg(string stdreg)
{
    if (stdreg.length() != 11 || stdreg[4] != '-' || stdreg[7] != '-')
        return false;
    if (!(stdreg[0] == '2' && stdreg[1] == '0' && stdreg[2] == '2' && (stdreg[3] >= '0' || stdreg[3] <= '4')))
        return false;
    if (!((stdreg[5] >= 'A' || stdreg[5] <= 'Z') && (stdreg[5] >= 'A' || stdreg[5] <= 'Z') && (stdreg[3] >= '0' || stdreg[3] <= '9') && (stdreg[3] >= '0' || stdreg[3] <= '9') && (stdreg[3] >= '0' || stdreg[3] <= '9')))
        return false;
    return true;
}

bool isvalidstdname(string stdname)
{
    if (stdname == "" || stdname.length() > 40)
        return false;
    else if (stdname[0] < 'A' || stdname[0] > 'Z')
        return false;
    for (int i=0;i<stdname.length();i++)
    {
        if (!((stdname[i] >= 'A' && stdname[i] <= 'Z') || (stdname[i] >= 'a' && stdname[i] <= 'z') || stdname[i] == ' '))
            return false;
    }
    return true;
}

int findstdind(string stdreg[], string reg, int MAX_STUDENTS )
{
    for (int i = 0; i < MAX_STUDENTS; i++)
    {
        if (stdreg[i] == reg)
        {
            return i;
        }
    }
    return -1;
}

bool addstudent(string stdname[], string name, string stdreg[], string reg)
{
    if (!isvalidstdname(name) || !isvalidstdreg(reg))
        return false;
    int k = findstdind(stdname, " ");if (k == -1) return false;
    stdname[k] = name;
    stdreg[k] = reg;
    return true;
}

bool deletestd(string stdreg[], string reg, string stdname[], string stdcour[])
{
    if (!isvalidstdreg(reg))
        return false;
    int k = findstdind(stdname, " ") ; if (k == -1) return false;
    stdname[k] = " ";
    stdreg[k] = " ";
    for (int i = 0; i < 10; i++)
    {
        stdcour[k] = " ";
    }

    return true;
}

bool updatestd(string stdname[], string name, string stdreg[], string reg,string newreg)
{
    int k = findstdind(stdreg, reg);
    if (k == -1){
    	cout<<"0";
        return false;
	}
    else if (!isvalidstdname(name) || !isvalidstdreg(newreg))
        return false;

    stdname[k] = name;
    stdreg[k] = newreg;
    return true;
}

bool registercour(string stdreg[], string reg, string codeList[], string stdcour[], string name)
{
    int k = findstdind(stdreg, reg);  
    if (k == -1)
        return false;  
    else if (!isValidCourseCode(name))
        return false;  
    int i=findstdind(codeList,name,10);
    if (k!=-1)
    if (stdcour[k] == " ") {
        stdcour[k] = name; 
        return true;
    } else {
        int position = stdcour[k].find(name);
        if (position != string::npos) { 
            return false;
        }

        stdcour[k] += ":" + name;
        return true;
    }
    else return false;
}
bool unregistercour(string stdreg[], string reg, string stdcour[], string name)
{
    int st = -1, end;
    bool flag;
    string res = "";
    
    int k = findstdind(stdreg, reg);
    if (k == -1)
        return false;

    if (!isValidCourseCode(name))
        return false;

    for (int i = 0; i <= stdcour[k].length() - name.length(); i++)
    {
        flag = true;
        for (int j = 0; j < name.length(); j++)
        {
            if (stdcour[k][i + j] != name[j])
            {
                flag = false;
                break;
            }
        }

        if (flag)
        {
            st = i;                
            end = st + name.length();
            res = stdcour[k].substr(0, st);
            res += stdcour[k].substr(end);  
            stdcour[k] = res;               
            return true;
        }
    }

    return false;
}

bool savestudents(string stdname[],string stdreg[],string stdcour[],int MAX_STUDENTS)
{
    ofstream fout;
    fout.open("students.txt");
    if (!fout.is_open())
    {
        cout << "Error opening File!" << endl;
        return false;
    }
    for (int i = 0; i < 40; i++)
    {
        if (stdreg[i] != " " && stdname[i] !=" ")
            fout << stdreg[i] << "," << stdname[i] << ",";
        for (int j = 0; j < 10; j++)
        {
            if (stdcour[i] != " ")
                fout << stdcour[i];
        }
    }
    fout.close();
    return true;
}
bool loadstudents(string stdname[],string stdreg[],string stdcour[],int MAX_STUDENTS)
{
    ifstream fin;
    fin.open("students.txt");
    if (!fin.is_open())
    {
        cout << "Error openig File!" << endl;
        return false;
    }
    int k = 0;
    while (getline(fin, stdreg[k], ',') && k < 40)
    {
        if (stdreg[k].empty() || stdreg[k] == "\n")
        {
            stdreg[k] = " ";
            break;
        }
        getline(fin, stdname[k], ',');
        getline(fin, stdcour[k], ' '); if (stdcour[k].empty() || stdcour[k] == "\n")
        {
            stdcour[k] = " ";
        }
        k++;
    }
}
void intializestd(string stdname[],string stdreg[],string stdcour[],int MAX_STUDENTS){
	for(int i=0;i<MAX_STUDENTS;i++){
		stdreg[i]=" ";
		stdname[i]=" ";
		stdcour[i]=" ";
	}
}

