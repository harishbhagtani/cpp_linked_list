#include <iostream>
using namespace std;

class Student{
public:
    string name;
    int roll{};
    Student* next{};
};

int getLength(Student*);
Student* getNewStudent(Student);
Student* deleteStudent(int, Student*);
Student* getPreviousStudent(int, Student*);
Student* getStudentByRollNumber(int, Student*);
Student* insertNewStudentAtFront(const Student&, Student*);
Student* insertNewStudentAtEnd(const Student&, Student*);
Student* insertNewStudentInTheMiddle(const Student&, Student*, int);
void printList(Student*);

int main() {

    const char FRONT = 'f';
    const char MIDDLE = 'm';
    const char END = 'e';

    const char INSERT = 'i';
    const char SEARCH = 's';
    const char DELETE = 'd';
    const char UPDATE = 'u';
    const char PRINT_LIST = 'p';
    const char EXIT = 'e';

    char operationChoice;
    Student* head = nullptr;

    while(true) {

        cout << "Which operation do you want to perform?" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Search" << endl;
        cout << "3. Update" << endl;
        cout << "4. Delete" << endl;
        cout << "5. Print List" << endl;
        cout << "6. Exit" << endl;
        cout << "Please enter your choice (i/s/u/d/p/e): ";
        cin >> operationChoice;

        switch (operationChoice) {
            case INSERT: {
                int insertMore = 1;
                char insertPosition;

                while (insertMore == 1) {

                    Student student;

                    cout << "Please enter name: ";
                    getline(cin >> ws, student.name);
                    cout << "Please enter roll number: ";
                    cin >> student.roll;

                    enterInsertPosition:
                    cout << "Where do you want to insert? (f/m/e): ";
                    cin >> insertPosition;

                    if (head == nullptr && insertPosition == 'm') {
                        cout << "List is empty. You cannot enter in the middle." << endl;
                        cout << "Please select again." << endl;
                        goto enterInsertPosition;
                    }

                    switch (insertPosition) {
                        case FRONT: {
                            head = insertNewStudentAtFront(student, head);
                            cout << "Student inserted at front. Details: " << endl;
                            cout << "Name: " << head->name << endl;
                            cout << "Roll: " << head->roll << endl;
                        }
                            break;
                        case MIDDLE: {
                            int insertAfterRollNumber;
                            cout << "Please enter the roll number of student you want to insert after: ";
                            cin >> insertAfterRollNumber;

                            Student *insertedStudent = insertNewStudentInTheMiddle(student, head,
                                                                                   insertAfterRollNumber);
                            if (insertedStudent != nullptr) {
                                cout << "Student with roll number " << insertAfterRollNumber << " found." << endl;
                                cout << "Student inserted after the student with above roll number. Details: "<< endl;
                                cout << "Name: " << insertedStudent->name << endl;
                                cout << "Roll: " << insertedStudent->roll << endl;
                            } else {
                                cout << "No student found at position " << insertAfterRollNumber << ".";
                            }

                        }
                            break;
                        case END: {
                            Student *insertedStudent;
                            if (head == nullptr) {
                                insertedStudent = insertNewStudentAtEnd(student, head);
                                head = insertedStudent;
                            } else {
                                insertedStudent = insertNewStudentAtEnd(student, head);
                            }
                            cout << "Student inserted at end. Details: " << endl;
                            cout << "Name: " << insertedStudent->name << endl;
                            cout << "Roll: " << insertedStudent->roll << endl;
                        }
                            break;
                        default: {
                            cout << "You entered wrong input, please enter again." << endl;
                            goto enterInsertPosition;
                        }
                    }

                    cout << "Do you want to insert more? (0/1): ";
                    cin >> insertMore;

                    if (insertMore == 0) {
                        break;
                    }
                }
            }
                break;
            case SEARCH: {
                int searchRollNumber;
                int searchMore = 1;
                while (searchMore == 1) {
                    cout << "Please enter search roll number: ";
                    cin >> searchRollNumber;
                    Student *searchStudentRecord = getStudentByRollNumber(searchRollNumber, head);
                    if (searchStudentRecord == nullptr) {
                        cout << "Student not found." << endl;
                        cout << "Do you want to search again? (0/1): ";
                        cin >> searchMore;
                    }else{
                        cout<<"Record found: "<<endl;
                        cout<<"Name: "<<searchStudentRecord->name<<endl;
                        cout<<"Roll Number: "<<searchStudentRecord->roll<<endl;
                        cout << "Do you want to search again? (0/1): ";
                        cin >> searchMore;
                    }
                }
            }
                break;
            case UPDATE: {
                int updateAgain = 1;
                while (updateAgain == 1) {
                    int updateStudentRollNumber;
                    Student *updateStudentRecord;
                    Student newDetails;
                    cout << "Please enter the roll number of student you want to update: ";
                    cin >> updateStudentRollNumber;
                    updateStudentRecord = getStudentByRollNumber(updateStudentRollNumber, head);
                    if(updateStudentRecord == nullptr){
                        cout<<"Student doesn't exists."<<endl;
                    }else{
                        cout<<"Student exists with details: "<<endl;
                        cout<<"Student Name: "<<updateStudentRecord->name<<endl;
                        cout<<"Student Roll Number: "<<updateStudentRecord->roll<<endl;
                        cout<<"Please enter new details: "<<endl;
                        cout<<"Please enter name: ";
                        getline(cin>>ws,newDetails.name);
                        cout<<"Roll Number: ";
                        cin>>newDetails.roll;
                        updateStudentRecord->name = newDetails.name;
                        updateStudentRecord->roll = newDetails.roll;
                        cout<<"Student record updated with above details."<<endl;
                    }
                    cout<<"Do you want to try again? (0/1): ";
                    cin>>updateAgain;
                }
            }
                break;
            case DELETE: {
                if(head == nullptr){
                    cout<<"List is already empty."<<endl;
                    break;
                }else{
                    int deleteAgain = 1;
                    while(deleteAgain == 1){

                        int deleteRollNumber;
                        Student* nextStudent;
                        cout<<"Please enter the roll number of student you want to delete: ";
                        cin>>deleteRollNumber;

                        Student* studentDetails = getStudentByRollNumber(deleteRollNumber, head);

                        if(studentDetails == nullptr){
                            cout<<"Student details not found.";
                        }else{
                            int confirmDelete;
                            cout<<"Do you really want to delete student with following details: "<<endl;
                            cout<<"Name: "<<studentDetails->name<<endl;
                            cout<<"Roll: "<<studentDetails->roll<<endl;
                            cout<<"Confirm? (0/1): ";
                            cin>>confirmDelete;
                            if(confirmDelete != 1){
                                goto doNotDelete;
                            }
                        }

                        nextStudent = deleteStudent(deleteRollNumber, head);

                        if(nextStudent == nullptr){
                            cout<<"Student cannot be deleted."<<endl;
                        }else{
                            if(nextStudent->roll == -1){
                                head = nullptr;
                                cout<<"Record with roll "<<deleteRollNumber<<" was the only record in the list and is now deleted. (Head node)"<<endl;
                            }else if(nextStudent->roll == -2){
                                cout<<"Record with roll "<<deleteRollNumber<<" deleted."<<endl;
                            }else{
                                head = nextStudent;
                                cout<<"Record with roll "<<deleteRollNumber<<" deleted. (Head node)"<<endl;
                            }
                        }

                        doNotDelete:
                        if(head == nullptr){
                            cout<<"List is now empty"<<endl;
                            deleteAgain = 0;
                        }else{
                            cout<<"Do you want to delete any other record?(0/1): ";
                            cin>>deleteAgain;
                        }
                    }
                }
            }
                break;
            case PRINT_LIST: {
                cout<<endl<<"There are "<<getLength(head)<<" students in record: "<<endl<<endl;
                printList(head);
                cout<<endl;
            }break;
            case EXIT: {
                exit(0);
            }
            default: {
                cout << "You entered wrong input. Please enter again." << endl;
            }
        }
    }
}

Student* insertNewStudentAtFront(const Student& student, Student* studentList){
    if(studentList == nullptr){
        studentList = getNewStudent(student);
        return studentList;
    }else{
        Student* ptr = getNewStudent(student);
        ptr->next = studentList;
        return ptr;
    }
}

Student* insertNewStudentAtEnd(const Student& student, Student* studentList){
    if(studentList == nullptr){
        studentList = getNewStudent(student);
        return studentList;
    }else{
        Student* ptr = studentList;
        while(ptr->next != nullptr){
            ptr = ptr->next;
        }
        ptr->next = getNewStudent(student);
        return ptr->next;
    }
}

Student* insertNewStudentInTheMiddle(const Student& student, Student* studentList, int afterRollNumber){
    Student* prevStudent = getStudentByRollNumber(afterRollNumber, studentList);
    if(prevStudent == nullptr){
        return nullptr;
    }else{
        Student* newStudent = getNewStudent(student);
        newStudent->next = prevStudent->next;
        prevStudent->next = newStudent;
        return newStudent;
    }
}

Student* deleteStudent(int deleteRollNumber, Student* studentList){

    auto* emptyStudent = new Student();
    emptyStudent->name = "";
    emptyStudent->roll = -1;
    emptyStudent->next = nullptr;

    if(studentList == nullptr){
        return nullptr;
    }

    if(studentList->next == nullptr){
        if(studentList->roll == deleteRollNumber) {
            delete studentList;
            return emptyStudent;
        }else{
            return nullptr;
        }
    }

    Student* deleteRecord = getStudentByRollNumber(deleteRollNumber, studentList);

    if(deleteRecord == nullptr){
        return nullptr;
    }else{
        Student* prevStudent = getPreviousStudent(deleteRollNumber, studentList);
        if(prevStudent != nullptr){
            prevStudent->next = deleteRecord->next;
            delete deleteRecord;
            emptyStudent->roll = -2;
            return emptyStudent;
        }else{
            Student* nextStudent = deleteRecord->next;
            delete deleteRecord;
            return nextStudent;
        }
    }
}



Student* getStudentByRollNumber(int rollNumber, Student* studentList){
    if(studentList == nullptr){
        return studentList;
    }else{
        Student* ptr = studentList;
        while(ptr->roll != rollNumber && ptr->next != nullptr){
            ptr = ptr->next;
        }
        if(ptr->next == nullptr && ptr->roll != rollNumber){
            return nullptr;
        }else{
            return ptr;
        }
    }
}



Student* getPreviousStudent(int rollNumber, Student* studentList){
    if(studentList == nullptr){
        return studentList;
    } else{
        Student* ptr = studentList;
        Student* prevPtr = nullptr;
        while(ptr->roll != rollNumber && ptr->next != nullptr){
            prevPtr = ptr;
            ptr = ptr->next;
        }
        if(ptr->next == nullptr && ptr->roll != rollNumber){
            return nullptr;
        }else{
            return prevPtr;
        }
    }
}


Student* getNewStudent(Student student){
    auto* newStudent = new Student();
    newStudent->name = std::move(student.name);
    newStudent->roll = student.roll;
    newStudent->next = nullptr;
    return newStudent;
}


void printList(Student* head){
    if(head == nullptr){
        cout<<"The list is empty."<<endl;
    }
    while(head != nullptr){
        cout<<"Student Name: "<<head->name<<endl;
        cout<<"Student roll: "<<head->roll<<endl;
        cout<<endl;
        head = head->next;
    }
}


int getLength(Student* studentList){
    int counter = 0;
    Student* ptr = studentList;
    if(studentList == nullptr){
        return counter;
    }
    do{
        counter++;
        ptr = ptr->next;
    }while(ptr != nullptr);

    return counter;
}
