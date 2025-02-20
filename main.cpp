#include <iostream>
#include <string>
#include <fstream> 
using namespace std;

const string user_name = "admin";
const string password = "1234";

void showname() {
    ifstream inFile("students.txt");
    string line3;
    bool foundStudent = false;
    while (getline(inFile, line3)) {
        if (line3.find("Student Name:") != string::npos) {
            // نمایش نام دانشجو
            cout << line3 << endl;
            foundStudent = true;
        } else if (line3.find("Student Number:") != string::npos && foundStudent) {
            // نمایش شماره دانشجویی
            cout << line3 << endl;
            cout << "-------------------------" << endl;
            foundStudent = false;
        }
    }
    inFile.close();
}
void rotbebandi() {
    ifstream inFile("students.txt");
    string line;
    double moadel[1000]; // آرایه برای ذخیره معدل‌ها
    int count = 0; // تعداد معدل‌های خوانده‌شده
    int count2 = 0;
    string wordss[1000];
    // خواندن معدل‌ها از فایل
    while (getline(inFile, line)) {
        if (line.find("Average:") != string::npos) {
            size_t pos = line.find(":");
            if (pos != string::npos) {
                string avgStr = line.substr(pos + 1);
                double avg = stod(avgStr);
                moadel[count] = avg;
                count++;
            }
        }
        if (line.find("Student Name:") != string::npos) {
            wordss[count2] = line;
            count2++;
        }
    }
    double moadel2[1000];
    for(int i=0;i<count;i++){
        moadel2[i] = moadel[i];
    }
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (moadel[i] < moadel[j]) {
                swap(moadel[i], moadel[j]); // جابجایی مقادیر برای مرتب سازی معدل ها
            }
        }
    }
    // نمایش معدل‌ها به ترتیب نزولی
    int counters[1000]={0};
    cout << "Ranking based on average (highest to lowest):" << endl;
    for (int i = 0; i < count; i++) {
        for(int j = 0; j < count; j++){
            if(moadel[i] == moadel2[j] && counters[j]==0){
            cout << i + 1 << ". " << wordss[j] <<" | "<<"Average: " << moadel[i] << endl;
            counters[j]++;
            break;
            }
        }
    }
}

int main() {
    int mojaz = 5;
    for (int i = 0; i < 5; i++) {
        cout << "you have " << mojaz << " requests else." << endl;
        string username;
        cout << "please enter the valid username : ";
        cin >> username;
        string password1;
        cout << "please enter the valid password : ";
        cin >> password1;
        if (username == user_name && password1 == password) {
            cout << "Welcome to your cms system!" << endl << endl;
            break;
        } else if (username != user_name || password1 != password) {
            cout << "You entered invalid username or password!" << endl;
            mojaz--;
        }
        if (i == 4) {
            cout << "dadash eshtebah mizani, felan khodafez" << endl;
            return 0;
        }
    }
    int edame;
    cout<<"if you want to continue press any key except -1 : ";
    while(cin>>edame && edame!=-1){
    cout<<endl;
    int f; // اینکه کدام گزینه رو انتخاب میکنه
    cout << "You have 4 options to choose:" << endl;
    cout << "1 . view the ranks of students" << endl
         << "2 . add a student to list" << endl
         << "3 . how many students do you have? with their names" << endl
         << "4 . see the card of a student" << endl << endl;
    cout << "choose the one option << ";
    cin >> f;
    cout<<endl;

    string words[1000]; // حداکثر تعداد دانش آموزانی که در دیتابیس ذخیره میشوند
    int students = 0; // تعداد دانش آموزانی که تا الان به سیستم اضافه شده اند
    double moadel[1000];
    if (f == 1) {
        rotbebandi();
        cout<<"if you want to continue press any key except -1 : ";
    }
    if (f == 2) {
        string name; // نام به همراه نام خانوادگی دانش آموز
        long long int student_number; // شماره دانش آموزش شخص مورد نظر
        int dars = 0; // تعداد دروسی که میخواهید نمره آن را وارد کنید
        cin.ignore();
        cout << "enter the name of your student : ";
        getline(cin, name);
        cout << "enter the student_number of your student : ";
        cin >> student_number;
        words[students] = name;
        cout << "how many lessons that you want? ";
        cin >> dars;
        string lessons[dars];
        double marks[dars];
        int zarib[dars];
        double sum = 0;
        int zaribha = 0;

        for (int i = 0; i < dars; i++) {
            cout << "Enter lesson name: ";
            cin >> lessons[i];
            cout << "Enter mark for " << lessons[i] << ": ";
            cin >> marks[i];
            cout << "Enter zarib for " << lessons[i] << ": ";
            cin >> zarib[i];
            sum = sum + marks[i] * zarib[i];
            zaribha = zaribha +  zarib[i];
        }
        moadel[students] = sum / zaribha;
        students++;

        // ذخیره اطلاعات در فایل
        ofstream outFile("students.txt", ios::app); // باز کردن فایل برای افزودن اطلاعات
        if (outFile.is_open()) {
            outFile << "Student Name: " << name << endl;
            outFile << "Student Number: " << student_number << endl;
            outFile << "Lessons and Marks:" << endl;
            for (int i = 0; i < dars; i++) {
                outFile << lessons[i] << " - Mark: " << marks[i] << " - Zarib: " << zarib[i] << endl;
            }
            outFile << "Average: " << moadel[students - 1] << endl;
            outFile << "-------------------------" << endl;
            outFile.close();
            cout << "Student information saved to file!" << endl;
        } else {
            cout << "Unable to open file for saving!" << endl;
        }
        cout<<"if you want to continue press any key except -1 : ";
    }
    if (f == 3) {
        showname();
        cout<<"if you want to continue press any key except -1 : ";
    }
    if (f == 4) {
    string line3;
    string previousLine;
    cout<<"please enter the student number of student that you want see his/her card : ";
    cin>>line3;
    ifstream inFile("students.txt");
    string line4;
    cout<<endl;
    while (getline(inFile, line4)) {
        if (line4.find(line3) != string::npos) {
            if (!previousLine.empty()) {
            cout << previousLine << std::endl;
            }
            cout << line4 << endl;
        if (getline(inFile, line4)) {
            cout << line4 << endl;
        }
        if (getline(inFile, line4)) {
            cout << line4 << endl;
        }
        if (getline(inFile, line4)) {
            cout << line4 << endl;
        }
        if (getline(inFile, line4)) {
            cout << line4 << endl;
        }
        if (getline(inFile, line4)) {
            cout << line4 << endl;
        }
    }
    previousLine = line4;
        }
    inFile.close();
        cout<<"if you want to continue press any key except -1 : ";
    }
    else if (f > 4 || f < 1) {
        cout << "you entered an invalid number" << endl;
    }
}
    return 0;
}