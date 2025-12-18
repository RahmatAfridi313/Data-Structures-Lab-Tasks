#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <cctype>

using namespace std;

struct Student {
    int id;
    string name;
    string dept;
    int semester;
    float cgpa;
    int credits;
    int year;
    Student* next;
};

// Linked list class
class StudentList {
private:
    Student* head;
    int count;

public:
    StudentList() : head(nullptr), count(0) {}

    ~StudentList() {
        clear();
    }

    void addStudent(int id, string name, string dept, int sem, float cgpa, int cred, int year) {
        Student* newStudent = new Student{id, name, dept, sem, cgpa, cred, year, nullptr};
        if (!head) {
            head = newStudent;
        } else {
            Student* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newStudent;
        }
        count++;
    }

    Student* getHead() { return head; }

    int getCount() { return count; }

    int getLength() {
        int len = 0;
        Student* temp = head;
        while (temp) {
            len++;
            temp = temp->next;
        }
        return len;
    }

    void clear() {
        Student* temp = head;
        while (temp) {
            Student* next = temp->next;
            delete temp;
            temp = next;
        }
        head = nullptr;
        count = 0;
    }

    void bubbleSortCGPA() {
        if (!head) return;
        bool swapped;
        do {
            swapped = false;
            Student* current = head;
            while (current->next) {
                bool shouldSwap = false;
                if (current->cgpa < current->next->cgpa) {
                    shouldSwap = true;
                } else if (current->cgpa == current->next->cgpa && current->credits < current->next->credits) {
                    shouldSwap = true;
                }
                if (shouldSwap) {
                    swapNodes(current, current->next);
                    swapped = true;
                } else {
                    current = current->next;
                }
            }
        } while (swapped);
    }

    void insertionSortEnrollment() {
        if (!head || !head->next) return;
        Student* sorted = nullptr;
        Student* current = head;
        while (current) {
            Student* next = current->next;
            if (!sorted || sorted->year > current->year ||
                (sorted->year == current->year && sorted->id > current->id)) {
                current->next = sorted;
                sorted = current;
            } else {
                Student* temp = sorted;
                while (temp->next && (temp->next->year < current->year ||
                       (temp->next->year == current->year && temp->next->id < current->id))) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
            current = next;
        }
        head = sorted;
    }


    static bool cmpCGPA(Student* a, Student* b) {
        if (a->cgpa != b->cgpa) return a->cgpa > b->cgpa;
        return a->credits > b->credits;
    }

    static bool cmpEnrollment(Student* a, Student* b) {
        if (a->year != b->year) return a->year < b->year;
        return a->id < b->id;
    }

    static bool cmpDepartment(Student* a, Student* b) {
        if (a->dept != b->dept) return a->dept < b->dept;
        if (a->semester != b->semester) return a->semester < b->semester;
        return a->cgpa > b->cgpa;
    }


    void mergeSortCGPA() {
        mergeSortIterative(cmpCGPA);
    }


    void mergeSortEnrollment() {
        mergeSortIterative(cmpEnrollment);
    }

    void mergeSortDepartment() {
        mergeSortIterative(cmpDepartment);
    }

private:
    Student* mergeIterative(Student* left, Student* right, bool (*cmp)(Student*, Student*)) {
        if (!left) return right;
        if (!right) return left;

        Student* dummy = new Student{0, "", "", 0, 0.0, 0, 0, nullptr};
        Student* tail = dummy;

        while (left && right) {
            if (cmp(left, right)) {
                tail->next = left;
                left = left->next;
            } else {
                tail->next = right;
                right = right->next;
            }
            tail = tail->next;
        }

        tail->next = left ? left : right;

        Student* result = dummy->next;
        delete dummy;
        return result;
    }

    Student* split(Student* head, int n) {
        if (!head) return nullptr;
        Student* curr = head;
        for (int i = 1; curr && i < n; i++) curr = curr->next;
        if (!curr) return nullptr;
        Student* next = curr->next;
        curr->next = nullptr;
        return next;
    }

    void mergeSortIterative(bool (*cmp)(Student*, Student*)) {
        if (!head || !head->next) return;
        int len = getLength();
        Student* dummy = new Student{0, "", "", 0, 0.0, 0, 0, nullptr};
        Student* curr = head;
        for (int size = 1; size < len; size *= 2) {
            dummy->next = nullptr;
            Student* tail = dummy;
            Student* left = curr;
            while (left) {
                Student* right = split(left, size);
                Student* next = right ? split(right, size) : nullptr;
                tail->next = mergeIterative(left, right, cmp);
                while (tail->next) tail = tail->next;
                left = next;
            }
            curr = dummy->next;
        }
        head = dummy->next;
        delete dummy;
    }

private:
    void swapNodes(Student* a, Student* b) {

        swap(a->id, b->id);
        swap(a->name, b->name);
        swap(a->dept, b->dept);
        swap(a->semester, b->semester);
        swap(a->cgpa, b->cgpa);
        swap(a->credits, b->credits);
        swap(a->year, b->year);
    }
};


bool readInputFile(StudentList& list, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening input file: " << filename << endl;
        return false;
    }

    int numStudents;
    file >> numStudents;
    file.ignore();

    for (int i = 0; i < numStudents; i++) {
        string line;
        getline(file, line);
        if (line.empty()) continue;

        size_t pos = 0;

        size_t space1 = line.find(' ', pos);
        int id = stoi(line.substr(pos, space1 - pos));
        pos = space1 + 1;


        stringstream ss(line);
        int id2, sem, cred, year;
        float cgpa;
        string name, dept;

        ss >> id2 >> name;

        string word;
        while (ss >> word) {

            if (word.length() == 3 && isalpha(word[0])) {
                dept = word;
                break;
            } else {
                name += " " + word;
            }
        }
        ss >> sem >> cgpa >> cred >> year;

        list.addStudent(id2, name, dept, sem, cgpa, cred, year);
    }

    file.close();
    return true;
}

void writeRankedByCGPA(StudentList& list, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening output file: " << filename << endl;
        return;
    }

    file << "====================================================" << endl;
    file << "        STUDENTS RANKED BY CGPA" << endl;
    file << "====================================================" << endl;
    file << left << setw(5) << "Rank" << setw(10) << "ID" << setw(20) << "Name" << setw(8) << "Dept" << setw(5) << "Sem" << setw(6) << "CGPA" << setw(8) << "Credits" << setw(6) << "Year" << endl;
    file << "-----|----------|--------------------|--------|-----|------|--------|------" << endl;

    Student* current = list.getHead();
    int rank = 1;
    while (current) {
        file << left << setw(5) << rank << setw(10) << current->id << setw(20) << current->name << setw(8) << current->dept << setw(5) << current->semester << fixed << setprecision(2) << setw(6) << current->cgpa << setw(8) << current->credits << setw(6) << current->year << endl;
        current = current->next;
        rank++;
    }

    file << "====================================================" << endl;
    file.close();
}


void writeSortedByEnrollment(StudentList& list, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening output file: " << filename << endl;
        return;
    }

    file << "====================================================" << endl;
    file << "        STUDENTS SORTED BY ENROLLMENT YEAR" << endl;
    file << "====================================================" << endl;

    Student* current = list.getHead();
    int currentYear = -1;
    float totalCGPA = 0.0;
    int yearCount = 0;

    while (current) {
        if (current->year != currentYear) {
            if (currentYear != -1) {
                file << "Average CGPA for " << currentYear << ": " << fixed << setprecision(2) << (totalCGPA / yearCount) << endl << endl;
            }
            currentYear = current->year;
            totalCGPA = 0.0;
            yearCount = 0;
            file << "Enrollment Year: " << currentYear << endl;
            file << left << setw(10) << "ID" << setw(20) << "Name" << setw(8) << "Dept" << setw(5) << "Sem" << setw(6) << "CGPA" << setw(8) << "Credits" << endl;
            file << "----------|--------------------|--------|-----|------|--------" << endl;
        }
        file << left << setw(10) << current->id << setw(20) << current->name << setw(8) << current->dept << setw(5) << current->semester << fixed << setprecision(2) << setw(6) << current->cgpa << setw(8) << current->credits << endl;
        totalCGPA += current->cgpa;
        yearCount++;
        current = current->next;
    }
    if (currentYear != -1) {
        file << "Average CGPA for " << currentYear << ": " << fixed << setprecision(2) << (totalCGPA / yearCount) << endl;
    }

    file << "====================================================" << endl;
    file.close();
}

void writeDepartmentAnalysis(StudentList& list, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening output file: " << filename << endl;
        return;
    }

    file << "====================================================" << endl;
    file << "        DEPARTMENT ANALYSIS" << endl;
    file << "====================================================" << endl;

    Student* current = list.getHead();
    string currentDept = "";
    int deptCount = 0;
    float totalCGPA = 0.0;
    float maxCGPA = 0.0;
    float minCGPA = 4.0;
    int totalCredits = 0;

    while (current) {
        if (current->dept != currentDept) {
            if (!currentDept.empty()) {
                file << "Total Students: " << deptCount << endl;
                file << "Average CGPA: " << fixed << setprecision(2) << (totalCGPA / deptCount) << endl;
                file << "Highest CGPA: " << fixed << setprecision(2) << maxCGPA << endl;
                file << "Lowest CGPA: " << fixed << setprecision(2) << minCGPA << endl;
                file << "Average Credits: " << fixed << setprecision(2) << (static_cast<float>(totalCredits) / deptCount) << endl << endl;
            }
            currentDept = current->dept;
            deptCount = 0;
            totalCGPA = 0.0;
            maxCGPA = 0.0;
            minCGPA = 4.0;
            totalCredits = 0;
            file << "Department: " << currentDept << endl;
            file << left << setw(10) << "ID" << setw(20) << "Name" << setw(5) << "Sem" << setw(6) << "CGPA" << setw(8) << "Credits" << setw(6) << "Year" << endl;
            file << "----------|--------------------|-----|------|--------|------" << endl;
        }
        file << left << setw(10) << current->id << setw(20) << current->name << setw(5) << current->semester << fixed << setprecision(2) << setw(6) << current->cgpa << setw(8) << current->credits << setw(6) << current->year << endl;
        deptCount++;
        totalCGPA += current->cgpa;
        if (current->cgpa > maxCGPA) maxCGPA = current->cgpa;
        if (current->cgpa < minCGPA) minCGPA = current->cgpa;
        totalCredits += current->credits;
        current = current->next;
    }
    if (!currentDept.empty()) {
        file << "Total Students: " << deptCount << endl;
        file << "Average CGPA: " << fixed << setprecision(2) << (totalCGPA / deptCount) << endl;
        file << "Highest CGPA: " << fixed << setprecision(2) << maxCGPA << endl;
        file << "Lowest CGPA: " << fixed << setprecision(2) << minCGPA << endl;
        file << "Average Credits: " << fixed << setprecision(2) << (static_cast<float>(totalCredits) / deptCount) << endl;
    }

    file << "====================================================" << endl;
    file.close();
}

// Function to write performance tiers
void writePerformanceTiers(StudentList& list, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening output file: " << filename << endl;
        return;
    }

    file << "====================================================" << endl;
    file << "        PERFORMANCE TIERS" << endl;
    file << "====================================================" << endl;

    int elite = 0, high = 0, good = 0, satisfactory = 0, needs = 0;
    Student* current = list.getHead();
    while (current) {
        if (current->cgpa >= 3.70) elite++;
        else if (current->cgpa >= 3.30) high++;
        else if (current->cgpa >= 3.00) good++;
        else if (current->cgpa >= 2.50) satisfactory++;
        else needs++;
        current = current->next;
    }

    int total = list.getCount();
    file << "Elite Tier (CGPA >= 3.70): " << elite << " students (" << fixed << setprecision(2) << (static_cast<float>(elite)/total*100) << "%)" << endl;
    file << "High Achievers (3.30 <= CGPA < 3.70): " << high << " students (" << fixed << setprecision(2) << (static_cast<float>(high)/total*100) << "%)" << endl;
    file << "Good Standing (3.00 <= CGPA < 3.30): " << good << " students (" << fixed << setprecision(2) << (static_cast<float>(good)/total*100) << "%)" << endl;
    file << "Satisfactory (2.50 <= CGPA < 3.00): " << satisfactory << " students (" << fixed << setprecision(2) << (static_cast<float>(satisfactory)/total*100) << "%)" << endl;
    file << "Needs Improvement (CGPA < 2.50): " << needs << " students (" << fixed << setprecision(2) << (static_cast<float>(needs)/total*100) << "%)" << endl << endl;

    file << "Elite Tier:" << endl;
    current = list.getHead();
    while (current) {
        if (current->cgpa >= 3.70) {
            file << left << setw(10) << current->id << setw(20) << current->name << setw(8) << current->dept << setw(5) << current->semester << fixed << setprecision(2) << setw(6) << current->cgpa << setw(8) << current->credits << setw(6) << current->year << endl;
        }
        current = current->next;
    }
    file << endl;


    file << "High Achievers:" << endl;
    current = list.getHead();
    while (current) {
        if (current->cgpa >= 3.30 && current->cgpa < 3.70) {
            file << left << setw(10) << current->id << setw(20) << current->name << setw(8) << current->dept << setw(5) << current->semester << fixed << setprecision(2) << setw(6) << current->cgpa << setw(8) << current->credits << setw(6) << current->year << endl;
        }
        current = current->next;
    }
    file << endl;

    file << "Good Standing:" << endl;
    current = list.getHead();
    while (current) {
        if (current->cgpa >= 3.00 && current->cgpa < 3.30) {
            file << left << setw(10) << current->id << setw(20) << current->name << setw(8) << current->dept << setw(5) << current->semester << fixed << setprecision(2) << setw(6) << current->cgpa << setw(8) << current->credits << setw(6) << current->year << endl;
        }
        current = current->next;
    }
    file << endl;

    file << "Satisfactory:" << endl;
    current = list.getHead();
    while (current) {
        if (current->cgpa >= 2.50 && current->cgpa < 3.00) {
            file << left << setw(10) << current->id << setw(20) << current->name << setw(8) << current->dept << setw(5) << current->semester << fixed << setprecision(2) << setw(6) << current->cgpa << setw(8) << current->credits << setw(6) << current->year << endl;
        }
        current = current->next;
    }
    file << endl;

    file << "Needs Improvement:" << endl;
    current = list.getHead();
    while (current) {
        if (current->cgpa < 2.50) {
            file << left << setw(10) << current->id << setw(20) << current->name << setw(8) << current->dept << setw(5) << current->semester << fixed << setprecision(2) << setw(6) << current->cgpa << setw(8) << current->credits << setw(6) << current->year << endl;
        }
        current = current->next;
    }

    file << "====================================================" << endl;
    file.close();
}

int main() {
    StudentList list;

    if (!readInputFile(list, "students_data.txt")) {
        return 1;
    }

    StudentList cgpaList = list; 

    list.mergeSortCGPA();
    writeRankedByCGPA(list, "ranked_by_cgpa.txt");

    list.clear();
    readInputFile(list, "students_data.txt");

    list.mergeSortEnrollment();
    writeSortedByEnrollment(list, "sorted_by_enrollment.txt");

    list.clear();
    readInputFile(list, "students_data.txt");

    list.mergeSortDepartment();
    writeDepartmentAnalysis(list, "department_analysis.txt");

    list.clear();
    readInputFile(list, "students_data.txt");

    writePerformanceTiers(list, "performance_tiers.txt");

    cout << "All output files generated successfully." << endl;

    return 0;
}
