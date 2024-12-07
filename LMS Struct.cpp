#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

struct User
{
    string username;
    string password;
};

struct Course
{
    string courseCode;
    string courseName;
    int crtHrs;
    int semester;
};

struct CourseEnrollment
{
    string courseCode;
};

struct Student
{
    string regNo;
    string name;
    CourseEnrollment courses[10];
};

void initialize2Darr(Student arr[], int size, int length, string value);
void initializeCourses(Course detail[], int size);
void initializeUsers(User name[], int size);
void initializeStudent(Student arr[], int size, string value);
long long unsigned int stringtoint(string num);

//function for data persistent
bool saveCourse(Course detail[], int size);
bool loadCourses(Course detail[], int size);
bool loadUser(User name[], int size);
bool saveStudent(Student regd[], int size);
bool loadStudent(Student regd[], int size);

//COURSE MANAGEMENT
int searchCourseCode(string codeList[], int size, string courseCode);
bool addCourses(Course detail[], int size, string courseCode, string courseName, int credit, int semester);
void viewCourses(Course detail[], int size);
void viewSemesterCourse(Course detail[], int size, int semester);
bool updateCourse(Course detail[], int size, string oldCourseCode, string courseCode, string courseName, int credit, int semester);
bool deleteCourse(Course detail[], int size, string courseCode);

void addStudent(Student regd[], int size);
void editStudent(Student regd[],string edit, int size);
void delStudent(Student regd[],string del, int size);
void viewStudent(Student regd[], int size);

void registerStd(Student regd[],string regdNo,string course, Course courseCode[], int stdSize, int size);
void unregisterStd(Student regd[],string regdNo,string course, int stdSize);

//VALIDATION FUNCTIONS
bool isValidCourseCode(string code);
bool isValidCreditHours(int creditHours);
bool isValidSemester(int semester);
bool isValidCourseName(string name);
bool validateAllData(string courseCode, string courseName, int credit, int semester);

//USER MANAGEMENT
bool userExist(User name[], string users, string passs, int size);
void login(string &userName, string &password);

int main()
{

    //Maximum Size of All arrays
    int MAX_COURSES = 10;
    int MAX_USERS = 10;
    int const MAX_STUDENTS = 50;

    User name[MAX_USERS];
    Course detail[MAX_COURSES];
    Student credential[MAX_STUDENTS];

    string oldCourseCode;
    bool flag = false;
    string userName;
    string password;
    string courseCode;
    string courseName;
    int credit;
    int semester;
    int input;
    string edit;                
    string reg;
    string course;
    
    //Initialize all arrays
    initializeCourses(detail, MAX_COURSES);
    initializeUsers(name, MAX_USERS);
    initializeStudent(credential, MAX_STUDENTS, "N/A");
    initialize2Darr(credential,MAX_COURSES,MAX_STUDENTS,"N/A");

    //This function will load the courses in arrays
    loadCourses(detail, MAX_COURSES);

    //This function will load the users in array
    loadUser(name, MAX_USERS);


    loadStudent(credential,MAX_STUDENTS);

    //For starting code
    login(userName, password);

    do
    {

        while (userExist(name, userName, password, MAX_USERS) != true || (userName == "" && password == ""))
        {
            cout << "Incorrect info please reenter username and password" << endl;
            cout << "Enter User name: ";
            cin >> userName;
            cout << "Enter Password: ";
            cin >> password;
            cout << endl;
        }

        if (userExist(name, userName, password, MAX_USERS))
        {

            cout << "Choose the following option" << endl;
            cout << "1   Add Courses" << endl;
            cout << "2   Update Courses" << endl;
            cout << "3   Delete Courses" << endl;
            cout << "4   View All Courses" << endl;
            cout << "5   View Courses of a Semester" << endl;
            cout << "6   Add a Student          " << endl;
            cout << "7   Update a Student       " << endl;
            cout << "8   Delete a Student       " << endl;
            cout << "9   View All Student       " << endl;
            cout << "10  Register a Student     " << endl;
            cout << "11  Unregister a Student   " << endl;
            cout << "12  Logout of the system" << endl;
            cout << "13  Exit Program" << endl;
            cout << "Enter the option: ";
            cin >> input;
            switch (input)
            {
            // This case for adding the course details
            case 1:

                cout << "Enter the details of the course: ";
                cin >> courseCode;
                cin >> credit;
                cin >> semester;
                cin.ignore();
                getline(cin, courseName);

                //Check validity of all inputs
                if (validateAllData(courseCode, courseName, credit, semester))
                {
                    //Call addCourse function
                    if (addCourses(detail, MAX_COURSES, courseCode, courseName, credit, semester))
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
                    //If any validity is false it will not add the course
                    cout << "Invalid details" << endl;
                }

                break;

            // This case for Updating the course details
            case 2:

                cout << "Enter the course code" << endl;
                cin >> oldCourseCode;

                //check validity of courseCode
                if (isValidCourseCode(oldCourseCode))
                {

                    //Find the index of courseCode which user entered to update the course details

                    cout << "Enter the details of the course: ";
                    cin >> courseCode;
                    cin >> credit;
                    cin >> semester;
                    cin.ignore();
                    getline(cin, courseName);
                    //Check validity of all details entered by user
                    if (validateAllData(courseCode, courseName, credit, semester))
                    {

                        if (updateCourse(detail, MAX_COURSES,oldCourseCode, courseCode, courseName, credit, semester))
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
                    //here we will show message of not valid data
                    cout << "Invalid Data" << endl;
                }

                break;

                //This case for deleting the course details

            case 3:
                cout << "Enter Course code" << endl;
                cin >> courseCode;
                //Validate the course Code
                if (isValidCourseCode(courseCode))
                {
                    //call function to delete the course detail which has same course code as user enter
                    if (deleteCourse(detail, MAX_COURSES, courseCode))
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
                    //if course code is invalid then this message will show
                    cout << "Invalid Course code" << endl;
                }

                break;

                //This case for displaying all details of all courses

            case 4:
                //View All details of All courses
                viewCourses(detail, MAX_COURSES);
                break;

            //This case for displaying course details of specific semester
            case 5:
                cout << "Enter the semester:";
                cin >> semester;
                //Check valildidty of semester entered by user
                if (isValidSemester(semester))
                {
                    //Show All details of course of the semester entered by user
                    viewSemesterCourse(detail, MAX_COURSES, semester);
                }
                else
                {
                    //If our semester is invalid
                    cout << "Invalid data" << endl;
                }

                break;
            case 6:
                addStudent(credential,MAX_STUDENTS);
                
                break;
            case 7:
                cout << "Enter Registration No. to Edit  :  ";
                cin >> edit;
                editStudent(credential,edit,MAX_STUDENTS);

                break;
            case 8:
                cout << "Enter Registration No. to Delete  :  ";
                cin >> edit;
                delStudent(credential,edit,MAX_STUDENTS);

                break;
            case 9:
                cout << left;
                cout << "         " << setw(20) << "Sr." << setw(40) << "Student Name" << setw(30) << "Registration No." << "Enrolled Course" <<endl;
                cout << endl << endl;
                viewStudent(credential,MAX_STUDENTS);
                cout << endl << endl;        

                break;
            case 10:
                cout << "Enter Student Registration No.  :  ";
                cin.ignore();
                getline(cin, reg);
                cout << "Enter Course Code  :  ";
                getline(cin, course);
                cout << course;
                registerStd(credential,reg,course,detail,MAX_STUDENTS,MAX_COURSES);

                break;
            case 11:
                cout << "Enter Student Registration No.  :  ";
                cin.ignore();
                getline(cin, reg);
                cout << "Enter Course Code  :  ";
                getline(cin, course);
                unregisterStd(credential,reg,course,MAX_STUDENTS);

                break;
            // For Closing the Program
            case 12:
                if (saveCourse(detail, MAX_COURSES))
                {
                    saveStudent(credential,MAX_STUDENTS);
                    cout << "All courses Data Saved successfully" << endl;
                }
                else
                {
                    cout << "All data you entered is lost due to some error" << endl;
                }
                userName = "";
                password = "";
                login(userName, password);
                break;
            case 13:
                if (saveCourse(detail, MAX_COURSES))
                {
                    saveStudent(credential,MAX_STUDENTS);
                    cout << "All courses Data Saved successfully" << endl;
                }
                else
                {
                    cout << "All data you entered is lost due to some error" << endl;
                }
                cout << "Program closed ";
                break;
            default:
                cout << "Invalid choice";
            }
        }
    } while (input != 13);

    return 0;
}

void initializeCourses(Course detail[], int size)
{
    for (int s = 0; s < size; s++)
    {
        detail[s].courseCode = " ";
        detail[s].courseName = " ";
        detail[s].crtHrs = 0;
        detail[s].semester = 0;
    }
}

void initializeUsers(User name[], int size)
{
    for (int s = 0; s < size; s++)
    {
        name[s].username = " ";
        name[s].password = " ";
    }
}

void initializeStudent(Student arr[], int size, string value) 
{
    for (int i = 0; i < size; i++) 
    {
        arr[i].name = value;
        arr[i].regNo = value;
    }
}

void initialize2Darr(Student arr[], int size, int length, string value)
{                                                                     
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < size; j++)
        {
            arr[i].courses[j].courseCode = value;
        }
    }
}

bool saveCourse(Course detail[], int size)
{
    // This variable for read data from file
    ofstream myfile;
    /*Open the file if exist if not exist then make new file of this name ios::app maens that the new data will append in file and 
	not remove previous content of file */
    myfile.open("Course.txt");
    //This function will check if the file open then write data from file
    if (myfile.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            if (detail[i].courseCode != "" && detail[i].courseName != "" && detail[i].crtHrs != 0 && detail[i].semester != 0)
            {
                //These lines will write all array data to the file and make a comma separated file
                myfile << detail[i].courseCode << ",";
                myfile << detail[i].courseName << ",";
                myfile << detail[i].crtHrs << ",";
                myfile << detail[i].semester << endl;
            }
        }

        myfile.close();
        return true;
    }
    else
    {
        //If there is error while opening file this function will return false
        return false;
    }
}
//Function to load course in arrays
bool loadCourses(Course detail[], int size)
{
    int i = 0;
    ifstream getCourse("Course.txt");
    if (!getCourse.is_open())
    {
        //cout << "File failed to open" << endl;
        return false;
    }
    else
    {
        string courseCode, courseName;
        string creditHours, semester;
        int credit, sem;
        string line;
        while (!getCourse.eof() && i < size)
        {
            getline(getCourse, line);
            if (line == "")
                continue;
            stringstream ss(line);
            getline(ss, courseCode, ',');
            detail[i].courseCode = courseCode;
            getline(ss, courseName, ',');
            detail[i].courseName = courseName;
            getline(ss, creditHours, ',');
            credit = stringtoint(creditHours);
            detail[i].crtHrs = credit;
            getline(ss, semester, ',');
            sem = stringtoint(semester);
            detail[i].semester = sem;
            i++;
        }

        getCourse.close();
        return true;
    }
}

//Fuunction to read users from file and load then onto the arrays
bool loadUser(User name[], int size)
{
    int i = 0;
    ifstream getUsers("loadUser.txt");
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
            name[i].username = username;
            getline(ss, password, ',');
            name[i].password = password;
            i++;
        }

        getUsers.close();
        return true;
    }
}

int searchCourseCode(Course code[], int size, string courseCode)
{
    int index = -1;
    for (int i = 0; i < size; i++)
    {
      
        if (code[i].courseCode == courseCode)
        {
            index = i;
            break;
        }
    }
    return index;
}
//This Function Will add the function
bool addCourses(Course detail[], int size, string courseCode, string courseName, int credit, int semester)
{
    bool flag = false;
    int i = searchCourseCode(detail, size, " ");
    if (i != -1)
    {

        detail[i].courseCode = courseCode;
        detail[i].courseName = courseName;
        detail[i].crtHrs = credit;
        detail[i].semester = semester;
        flag = true;
    }
    return flag;
}

// This Function will display all course details
void viewCourses(Course detail[], int size)
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
        if (detail[i].courseCode != " ")
        {

            cout << setw(10) << detail[i].courseCode
                 << setw(50) << detail[i].courseName
                 << setw(10) << detail[i].crtHrs
                 << setw(10) << detail[i].semester << endl;
        }
    }
    cout << endl;
    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;
}

long long unsigned int stringtoint(string num)
{
    int res = 0;
    for (int i = 0; i < num.length(); i++)
    {
        res *= 10;
        res += int(num[i]-'0');
    }
    return res;
}
bool saveStudent(Student name[], int size)
{
    ofstream fout("students.txt");
    for (int i = 0; i < size; i++)
    {
        if (name[i].name != "N/A" && name[i].name != "")
        {
            fout << name[i].name << "," << name[i].regNo << ",";
            for (int j = 0; j < 10; j++)
            {
                fout << name[i].courses[j].courseCode << ":";
            }
        }
    }
    fout.close();
}

bool loadStudent(Student name[], int size)
{
    ifstream fin("students.txt");
    int i = 0;
    while (!fin.eof())
    {
        getline(fin, name[i].name, ',');
        cout << name[i].name << endl;
        getline(fin, name[i].regNo, ',');
        for (int j = 1; j < 10; j++)
        {           
            getline(fin, name[i].courses[j].courseCode, ':');
        }
        i = i+1;
    }
    fin.close();
}

//This function will display the course details of the specific semester
void viewSemesterCourse(Course detail[], int size, int semester)
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
        if (detail[i].semester == semester && detail[i].courseCode != "")
        {
            cout << setw(10) << detail[i].courseCode
                 << setw(50) << detail[i].courseName
                 << setw(10) << detail[i].crtHrs
                 << setw(10) << detail[i].semester << endl;
        }
    }
    cout << endl;
    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;
}

// This function will update the course by using courseCode index which we define as globel varaible
bool updateCourse(Course name[], int size,string oldCourseCode, string courseCode, string courseName, int credit, int semester)
{

    bool flag = false;
    int updateIndex = searchCourseCode(name, size, oldCourseCode);
    cout<<"Upate Index "<<updateIndex<<endl;
    if (updateIndex != -1)
    {
        name[updateIndex].courseCode = courseCode;
        name[updateIndex].courseName = courseName;
        name[updateIndex].crtHrs = credit;
        name[updateIndex].semester = semester;
        flag = true;
    }
    return flag;
}

// This function will delete the course by using courseCode
bool deleteCourse(Course detail[], int size, string courseCode)
{
    bool flag = false;
    int i = searchCourseCode(detail, size, courseCode);
    if (i != -1)
    {
        detail[i].courseCode = " ";
        detail[i].courseName = " ";
        detail[i].crtHrs = 0;
        detail[i].semester = 0;
        flag = true;
    }

    return flag;
}
//checking validity of coursecode
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

//checking semester
bool isValidSemester(int semester)
{
    bool flag = true;
    if (!(semester >= 1 && semester <= 9))
    {
        flag = false;
    }
    return flag;
}

//checking coursename
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

bool isValidName(string name)
{
    bool flag = true;
    int size = name.length();
    for (int i = 0; i < size; i++)
    {
        flag = true;
        if (((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z')) && size <= 40)
        {
            flag = false;
        }
        else
        {
            return true;
        }
    }
    return false;
}

bool isValidRegd(string regd)
{
    bool flag = true;
    int size = regd.length();
    if (regd >= "2000-CA-001" && regd <= "2030-CZ-999" && size <= 11)
    {
        return false;
    }
    return true;
}

bool userExist(User name[], string users, string passs, int size)
{
    bool flag = false;
    int i;
    for (i = 0; i < size; i++)
    {
        if (name[i].username == users && name[i].password == passs)
        {
            flag = true;
            break;
        }
    }

    return flag;
}

void addStudent(Student name[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if(name[i].name == "N/A")
        {
            do
            {
                cout << "Enter Name of Student  :  ";
                cin.ignore();
                getline(cin, name[i].name);
                cout << "Enter Registrion No. of Student  :  ";
                getline(cin, name[i].regNo);
            } 
            while 
            (isValidName(name[i].name) || isValidRegd(name[i].regNo));

            cout << "Student Added Successfully" << endl;
            return;
        }
    }
    cout << "Unable To Store" << endl;
}

void editStudent(Student credential[],string edit, int size)
{
    for (int i = 0; i < size; i++)
    {
        if(credential[i].regNo == edit)
        {
            do
            {
                cout << "Enter Name of Student  :  ";
                getline(cin, credential[i].name);
                cout << "Enter REgistration No. :  ";
                getline(cin, credential[i].regNo);
            } 
            while 
            (isValidName(credential[i].name) || isValidRegd(credential[i].regNo));

            cout << endl << "Student Updated Successfully" << endl;
            return;
        }
    }
    cout << endl << "Student does not exist" << endl;

}

void delStudent(Student credential[],string del, int size)
{
    for (int i = 0; i < size; i++)
    {
        if(credential[i].regNo == del)
        {
            credential[i].regNo = "N/A";
            credential[i].name = "N/A";
            cout << endl << "Student Updated Sussessfully" << endl;
            return;
        }
    }
    cout << endl << "Student does not Exist" << endl;

}

void viewStudent(Student credential[], int size)
{
    bool flag;
    for (int i = 0; i < size; i++)
    {
        if (credential[i].name != "N/A" && credential[i].name != "")
        {
            cout  << "         " << setw(20) << i+1 << setw(40) << credential[i].name << setw(30) << credential[i].regNo;
            for (int j = 0; j < 10; j++)
            {
                if (credential[i].courses[j].courseCode != "N/A")
                {
                    cout << credential[i].courses[j].courseCode <<" : ";
                }
            }
            cout << endl;
            flag = false;
        }
    }
    if (flag)
    {
        cout << endl << endl;
        cout << "No Student Added Yet";
        cout << endl << endl;
    }
}

void registerStd(Student regd[],string regdNo,string course, Course courseCode[], int stdSize, int size)
{
    bool flag = false;
    for (int i = 0; i < size; i++)
    {
        if (course == courseCode[i].courseCode)
        {
            flag = true;
            break;
        }
    }
    if (flag)
    {
        for (int i = 0; i < stdSize; i++)
        {
            if (regd[i].regNo == regdNo)
            {
                for (int j = 0; j < 10; j++)
                {
                    if (regd[i].courses[j].courseCode == "N/A")
                    {
                        regd[i].courses[j].courseCode = course;
                        break;
                    }
                }
                cout << "Student Registered Successfully" << endl;
                return;
            }
        }
    }
    cout << "Unable to Register" << endl;
    return;
}

void unregisterStd(Student regd[],string regdNo,string course, int stdSize)
{
    for (int i = 0; i < stdSize; i++)
    {
        if (regd[i].regNo == regdNo)
        {
            for (int j = 0; j < 10; j++)
            {
                if (regd[i].courses[j].courseCode == course)
                {
                    regd[i].courses[j].courseCode = "N/A";
                    break;
                }
            }
            cout << "Student Unregistered Successfully" << endl;
            return;
        }
    }

    cout << "Invaild Registration no./Course Code" << endl;
    return;
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

