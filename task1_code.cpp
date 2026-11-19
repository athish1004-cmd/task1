

#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    // Encapsulated data members - not accessible directly from outside the class
    string name;
    int rollNo;
    float marks;

    static int studentCount;   // Static member - tracks total students

public:
    // Default constructor
    Student() {
        name = "Unnamed";
        rollNo = 0;
        marks = 0.0;
        studentCount++;
    }

    // Parameterized constructor (overloaded with the default constructor above)
    Student(string n, int r, float m) {
        name = n;
        rollNo = r;
        marks = m;
        studentCount++;
    }

    // Destructor - decrements the static count whenever an object is destroyed
    ~Student() {
        studentCount--;
    }

    // Overloaded function #1 - displays the student's details
    void display() {
        cout << "Name: " << name
             << " | Roll No: " << rollNo
             << " | Marks: " << marks << endl;
    }

    // Overloaded function #2 - same name 
    void display(string heading) {
        cout << heading << endl;
        display();
    }

    // controlled access to private data 
    string getName() {
        return name;
    }

    float getMarks() {
        return marks;
    }

    // Static member function - can be called without creating an object
    static int getStudentCount() {
        return studentCount;
    }

    // Friend function declaration - defined outside the class but can access
    // private members of Student objects passed to it
    friend void compareStudents(Student &s1, Student &s2);

    // Overloaded '>' operator - compares two students based on marks
    bool operator>(Student &other) {
        return marks > other.marks;
    }
};

// initialization of the static data member - must be done outside the class
int Student::studentCount = 0;

// Friend function definition
// Because it is declared 'friend' inside Student, it can directly access
// the private members (name, marks) of both Student objects
void compareStudents(Student &s1, Student &s2) {
    cout << "\n[Friend function] Comparing " << s1.name << " and " << s2.name << ":" << endl;
    if (s1.marks > s2.marks)
        cout << s1.name << " scored higher (" << s1.marks << ") than "
             << s2.name << " (" << s2.marks << ")" << endl;
    else if (s2.marks > s1.marks)
        cout << s2.name << " scored higher (" << s2.marks << ") than "
             << s1.name << " (" << s1.marks << ")" << endl;
    else
        cout << s1.name << " and " << s2.name << " scored equal marks." << endl;
}

int main() {
    cout << "===== Student Management - Task 1 =====" << endl;

    // 
    Student *s1 = new Student("Athish M", 209, 88.5);
    Student *s2 = new Student("Darshan", 210, 92.0);
    Student *s3 = new Student("Vijay", 211, 75.25);

    cout << "\n--- Student Records ---" << endl;
    s1->display();
    s2->display();
    s3->display();


    s1->display("\n--- Highlighted Student Record ---");

    // Static member usage - total number of Student objects at present 
    cout << "\nTotal students created so far (static member studentCount): "
         << Student::getStudentCount() << endl;

    // Friend function usage - compares two students by accessing private marks directly
    compareStudents(*s1, *s2);

    // Overloaded '>' operator usage
    cout << "\n[Overloaded '>' operator] ";
    if (*s2 > *s1)
        cout << s2->getName() << " has greater marks than " << s1->getName() << endl;
    else
        cout << s1->getName() << " has greater or equal marks than " << s2->getName() << endl;

    // ---- Freeing dynamically allocated memory ----
    delete s1;
    delete s2;
    delete s3;

    cout << "\nStudent count after releasing dynamic memory: "
         << Student::getStudentCount() << endl;

    return 0;
}