#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <functional>


class Descriptor {
private:
    std::string lastName;
    std::string initials;
    int groupIndex;
    int departmentNumber;

public:
    
    Descriptor(): lastName(""), initials(""), groupIndex(0), departmentNumber(0) {}

    Descriptor(const std::string& lName, const std::string& init, int group, int deptNum)
        : lastName(lName), initials(init), groupIndex(group), departmentNumber(deptNum) {}


    std::string getFullName() const {
        return lastName + " " + initials;
    }

    int getGroupIndex() const {
        return groupIndex;
    }

    int getDepartmentNumber() const {
        return departmentNumber;
    }

    void changeGroupIndex(int newGroupIndex) {
        groupIndex = newGroupIndex;
    }

    Descriptor(const Descriptor& other): lastName(other.lastName), initials(other.initials),groupIndex(other.groupIndex), departmentNumber(other.departmentNumber) {}
    /*Descriptor(Descriptor&&) = delete;*/
};

class Student {
private:
    int studentCode;
    Descriptor descriptor;
    std::vector<int> sessionGradesEmpty;

public:
    Student(): studentCode(0), descriptor() {}
    Student(int code, const Descriptor& desc) : studentCode(code), descriptor(desc) {}
    virtual Student* clone() const
    {
        return new Student(*this);
    }
    void getStudentInfo() const {
        std::cout << "Student Code: " << studentCode << std::endl;
        std::cout << "Full Name: " << descriptor.getFullName() << std::endl;
        std::cout << "Group Index: " << descriptor.getGroupIndex() << std::endl;
        std::cout << "Department Number: " << descriptor.getDepartmentNumber() << std::endl;
    }

    int getStudentCode() const {
        return studentCode;
    }

    virtual std::string getStudentCategory() const {
        return "Unknown Student";
    }

    const Descriptor& getDescriptor() const {
        return descriptor;
    }

    virtual const std::vector<int>& getSessionGrades() const {
        return sessionGradesEmpty;
    }

    virtual void setSessionGrades(const std::vector<int>& grades) {}

    void changeGroupIndex(int newGroupIndex) {
        descriptor.changeGroupIndex(newGroupIndex);
    }    

   // Student(const Student&) = delete;
    //Student(Student&&) = delete;

};

class Junior : public Student {
private:
    std::vector<int> sessionGrades;  
public:
    Junior(): Student(), sessionGrades(0) {}
    Junior(int code, const Descriptor& desc, const std::vector<int>& sessionsGrades1) : Student(code, desc) {
        sessionGrades = sessionsGrades1;
    }
    virtual Junior* clone() const
    {
        return new Junior(*this);
    }


    std::string getStudentCategory() const override {
        return "Junior";
    }

    const std::vector<int>& getSessionGrades() const override {
        return sessionGrades;
    }

    void setSessionGrades(const std::vector<int>& grades) override {
        sessionGrades = grades;
    }

    
};

class SeniorGrad : public Student {
private:
    std::vector<int> sessionGrades; 
    std::string uirTopic;
    std::string uirLocation;
    int advisorGrade;
    int committeeGrade;

public:
    SeniorGrad(): Student(), sessionGrades(0), uirTopic(""), uirLocation(), advisorGrade(0), committeeGrade(0) {}
    SeniorGrad(int code, const Descriptor& desc, const std::vector<int>& sessionGrades1) : Student(code, desc), advisorGrade(0), committeeGrade(0) {
        sessionGrades = sessionGrades1;
    }
    virtual SeniorGrad* clone() const
    {
        return new SeniorGrad(*this);
    }


    std::string getStudentCategory() const override {
        return "Senior Graduate";
    }

    const std::vector<int>& getSessionGrades() const override {
        return sessionGrades;
    }

    void setSessionGrades(const std::vector<int>& grades) override {
        sessionGrades = grades;
    }

    std::string getUirTopic() const {
        return uirTopic;
    }

    void changeUirTopic(const std::string& newTopic) {
        uirTopic = newTopic;
    }

    std::string getUirLocation() const {
        return uirLocation;
    }

    void changeUirLocation(const std::string& newLocation) {
        uirLocation = newLocation;
    }

    int getAdvisorGrade() const {
        return advisorGrade;
    }

    void setAdvisorGrade(int grade) {
        if (grade > 100 || grade < 0 ) throw std::invalid_argument("Grade must be <= 100 and >= 0");
        else advisorGrade = grade;
    }

    int getCommitteeGrade() const {
        return committeeGrade;
    }

    void setCommitteeGrade(int grade) {
        if (grade > 100 || grade < 0) throw std::invalid_argument("Grade must be <= 100 and >= 0");
        else committeeGrade = grade;
    }
    

};

class Graduate : public Student {
private:
    std::string dpTopic;
    std::string dpLocation;
    int advisorGrade;
    int reviewerGrade;
    int gecGrade;

public:
    Graduate(): dpTopic(""), dpLocation(""), advisorGrade(0), reviewerGrade(0), gecGrade(0){}
    Graduate(int code, const Descriptor& desc) : Student(code, desc), advisorGrade(0), reviewerGrade(0), gecGrade(0) {}
    virtual Graduate* clone() const
    {
        return new Graduate(*this);
    }


    std::string getStudentCategory() const override {
        return "Graduate";
    }

    std::string getDpTopic() const {
        return dpTopic;
    }

    void changeDpTopic(const std::string& newTopic) {
        dpTopic = newTopic;
    }

    std::string getDpLocation() const {
        return dpLocation;
    }

    void changeDpLocation(const std::string& newLocation) {
        dpLocation = newLocation;
    }

    int getAdvisorGrade() const {
        return advisorGrade;
    }

    void setAdvisorGrade(int grade) {
        if (grade > 100 || grade < 0) throw std::invalid_argument("Grade must be <= 100 and >= 0");
        else advisorGrade = grade;
    }

    int getReviewerGrade() const {
        return reviewerGrade;
    }

    void setReviewerGrade(int grade) {
        if (grade > 100 || grade < 0) throw std::invalid_argument("Grade must be <= 100 and >= 0");
        else reviewerGrade = grade;
    }

    int getGecGrade() const {
        return gecGrade;
    }

    void setGecGrade(int grade) {
        if (grade > 100 || grade < 0) throw std::invalid_argument("Grade must be <= 100 and >= 0");
        else gecGrade = grade;
    }
};

class StudentTable {
private:
    //std::map<int, Student*> students;
    std::set<Student*, std::function<bool(const Student*, const Student*)>> students{
        [](const Student* lhs, const Student* rhs) {
            return lhs->getStudentCode() < rhs->getStudentCode();
        }
    };

public:

    void addStudent(int studentCode, const Student* stud) {
        students.insert(stud->clone());
    }

    /*void addStudent(int studentCode, Student* student) {
        students[studentCode] = student;
    }*/

    Student* findStudent(int studentCode) const {
        auto it = std::find_if(students.begin(), students.end(),
            [studentCode](const Student* student) { return student->getStudentCode() == studentCode; });

        return (it != students.end()) ? *it : nullptr;
    }

    /*Student* findStudent(int studentCode) const {
        auto it = students.find(studentCode); 
        return (it != students.end()) ? it->second : nullptr;
    }*/

    void removeStudent(int studentCode) {
        auto it = std::find_if(students.begin(), students.end(),
            [studentCode](const Student* student) { return student->getStudentCode() == studentCode; });

        if (it != students.end()) {
            delete* it;
            students.erase(it);
        }
    }

    /*void removeStudent(int studentCode) {
        auto it = students.find(studentCode);
        if (it != students.end()) {
            delete it->second; 
            students.erase(it); 
        }
    }*/

    void showTableContents() const {
        for (const auto& student : students) {
            student->getStudentInfo();
        }
    }

    /*void showTableContents() const {
        for (const auto& entry : students) {
            const int studentCode = entry.first;
            const Student* student = entry.second;

            std::cout << "Student Code: " << studentCode << std::endl;
            student->getStudentInfo();  
        }
    }*/

    std::set<Student*>::iterator begin() {
        return students.begin();
    }

    std::set<Student*>::iterator end() {
        return students.end();
    }

    auto rbegin() {
        return std::prev(students.end());
    }

    bool empty() const {
        return students.empty();
    }

    ~StudentTable() {
        for (auto& student : students) {
            delete student;
        }
    }
};

class Application {
private:
    StudentTable studentTable;
public:
    void enrollStudent(int studentCode, Student* student) {
        if (studentTable.findStudent(studentCode)) {
            std::cout << "Student with code " << studentCode << " already registered" << std::endl;
        }
        else {
            Junior* juniorStudent = new Junior(studentCode, student->getDescriptor(), student->getSessionGrades());
            studentTable.addStudent(studentCode, juniorStudent);
            std::cout << "Junior with code " << studentCode << " successfully enrolled" << std::endl;
        }
    }

    void transferToNewSemester(Junior* newSemesterStudent) {
        int newStudentCode = 1; 
        if (!studentTable.empty()) {
            auto lastStudent = *studentTable.rbegin(); 
            newStudentCode = lastStudent->getStudentCode() + 1;
        }

        SeniorGrad* transferredStudent = new SeniorGrad{ newStudentCode, newSemesterStudent->getDescriptor(), transferredStudent->getSessionGrades()};
        studentTable.addStudent(newStudentCode, transferredStudent);
        std::cout <<" JUNIOR PROMOTED TO SENIOR " << std::endl;
    }

    /*void enrollStudent(Student* student) {
        if (studentTable.findStudent(student->getDescriptor())) {
            std::cout << "Student already registered" << std::endl;
        }
        else {
            studentTable.addStudent(student);
            std::cout << "Student successfully enrolled" << std::endl;
        }
    }*/

    void transferToCategory(Junior& jrStud) {
        SeniorGrad* seniorStud = new SeniorGrad(jrStud.getStudentCode(), jrStud.getDescriptor(), jrStud.getSessionGrades());
        studentTable.removeStudent(jrStud.getStudentCode());
        studentTable.addStudent(seniorStud->getStudentCode(), seniorStud);
    }

    void transferToCategory(SeniorGrad& seniorStud) {
        Graduate* graduator = new Graduate(seniorStud.getStudentCode(), seniorStud.getDescriptor());
        studentTable.removeStudent(seniorStud.getStudentCode());
        studentTable.addStudent(graduator->getStudentCode(), graduator);
    }

    void transferToCategory(Graduate& graduator) {
        std::cout << "Promotion limit reached";
    }

    void expelStudent(int studentCode) {
        studentTable.removeStudent(studentCode);
        std::cout << "Expelled student with code " << studentCode << " from the institute." << std::endl;
    }

    void calculateAverageGradesByGroup() {
        double totalGrades = 0.0;
        int studentCount = 0;

        for (auto& entry : studentTable) {
            Student* currentStudent = entry;
            const std::vector<int>& grades = currentStudent->getSessionGrades();
            for (int grade : grades) {
                totalGrades += grade;
                studentCount++;
            }
        }

        double averageGrade = (studentCount > 0) ? (totalGrades / studentCount) : 0.0;
        std::cout << "Average grade for all students: " << averageGrade << std::endl;
    }
};

int main() {
    
    Application app;
    int option;
    bool exitFlag = false;
    try
    {
        while (!exitFlag)
        {
            std::cout << "1)Enroll\n";
            std::cout << "2)Expel\n";
            std::cout << "3)Transfer\n";
            std::cout << "4)Calc\n";
            std::cout << "5)Exit" << std::endl;
            
            try
            {
                std::cin >> option;
                if (std::cin.fail()) {
                    std::cin.clear(); 
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                    throw std::invalid_argument("Invalid input. Please enter a valid option.");
                }

                switch (option)
                {
                case 1:
                {
                    Student stud; 
                    app.enrollStudent(stud.getStudentCode(), &stud);
                    break;
                }
                
                case 2:
                {
                    Student stud;
                    app.enrollStudent(stud.getStudentCode(), &stud);
                    app.expelStudent(stud.getStudentCode());
                    break;
                }
                break;
                case 3:
                {
                    Descriptor juniorDescriptor("Ivan", "K.A", 1, 101);
                    Junior juniorStudent(123, juniorDescriptor, { 1, 3, 5 });
                    app.transferToCategory(juniorStudent);
                }
                break;
                case 4:
                {
                    Descriptor juniorDescriptor("Ivan", "K.A", 1, 101);
                    Junior juniorStudent(123, juniorDescriptor, {});
                    juniorStudent.setSessionGrades({ 80, 90, 85 });

                    Descriptor seniorDescriptor("Bob", "A.B", 2, 102);
                    SeniorGrad seniorStudent(456, seniorDescriptor, {});
                    seniorStudent.setSessionGrades({ 75, 85, 80 });

                    app.enrollStudent(juniorStudent.getStudentCode(), &juniorStudent);
                    app.enrollStudent(seniorStudent.getStudentCode(), &seniorStudent);

                    app.calculateAverageGradesByGroup();
                }
                break;
                case 5:
                {
                    exitFlag = true;
                    break;

                }

                default:
                    std::cout << "No such command. AGAIN" << std::endl;
                }
            }
            catch (const std::invalid_argument)
            {
                std::cout << "Invalid argument" << std::endl;
                continue;
            }
            catch (const std::bad_alloc)
            {
                std::cout << "Memory Error" << std::endl;
            }

        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }


    return 0;
}
