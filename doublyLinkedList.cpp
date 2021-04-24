#include <iostream>
using namespace std;

class Student{
public:
    Student* prevStudent{};
    string name;
    int rollNumber{};
    Student* nextStudent{};
};

//Function Prototypes
Student* getNewStudent(Student&);
void printList(Student*);
int getSize(Student*);
Student* getNextStudent(Student&, Student*);
Student* getPrevStudent(Student&, Student*);
void movePointerToNextNode(Student*&, int&);
void movePointerToPrevNode(Student*&, int&);
void insertNewStudentAtFront(Student*&, Student&);
void insertNewStudentAtEnd(Student*&, Student&);
void insertNewStudentAfterStudent(Student*&, Student&, int);
void deleteNodeAtFront(Student*&);
void deleteNodeAtEnd(Student*&);
void deleteNodeAtRollNumber(Student*&, int);
void editNodeAtRoll(Student* headNode, int);

int main() {
    Student* head = nullptr;
    Student* ptr = nullptr;
    int ptrPosition = 0;
    Student student;
    int choice;

    reEnterChoice:

    cout<<"Which operation? "<<endl;
    cout<<"1. Insert"<<endl;
    cout<<"2. Print"<<endl;
    cout<<"3. Traverse"<<endl;
    cout<<"4. Get Student After"<<endl;
    cout<<"5. Get Student Before"<<endl;
    cout<<"6. Delete"<<endl;
    cout<<"7. Modify"<<endl;
    cout<<"8. Exit"<<endl;
    cout<<"Please enter your choice: ";
    cin>>choice;

    switch (choice){
        case 1:{
            reInsertStudent:

            cout<<"Please enter student Name: ";
            getline(cin>>ws, student.name);
            cout<<"Please enter roll number: ";
            cin>>student.rollNumber;

            cout<<"Please enter where you want to insert (1. f/2. e/3. m): ";
            cin>>choice;

            if(choice == 1){
                insertNewStudentAtFront(head,student);
            }else if (choice == 2){
                insertNewStudentAtEnd(head, student);
            } else if (choice == 3){
                int afterRoll;
                cout<<"Please enter the roll number of student you want to insert after: ";
                cin>>afterRoll;
                insertNewStudentAfterStudent(head, student, afterRoll);
            }

            cout<<"Insert again? (0/1): ";
            cin>>choice;

            if(choice == 1){
                goto reInsertStudent;
            }
            printList(head);
        }break;
        case 2:{
            printList(head);
        }break;
        case 3:{
            if(head != nullptr){
                ptr = head;
                ptrPosition++;
                cout<<"Currently the pointer is at position "<<ptrPosition<<endl;
                cout<<"Name: "<<ptr->name<<endl;
                cout<<"Roll: "<<ptr->rollNumber<<endl;
                reEnterTraversal:
                cout<<"Where do you want to move? (1. prev / 2. next/ 3. Quit): ";
                cin>>choice;
                if(choice == 1){
                    movePointerToPrevNode(ptr, ptrPosition);
                } else if (choice == 2){
                    movePointerToNextNode(ptr, ptrPosition);
                } else if (choice == 3){
                    break;
                }
                goto reEnterTraversal;
            }else{
                cout<<"The list is empty."<<endl;
            }
        }break;
        case 4:{
            cout<<"Please enter roll number: ";
            cin>>student.rollNumber;
            getNextStudent(student, head);
        }break;
        case 5:{
            cout<<"Please enter roll number: ";
            cin>>student.rollNumber;
            getPrevStudent(student, head);
        }break;
        case 6:{
            reDelete:
            cout<<"From where do you want to deleted? (1. f/2. e/3. m/4. cancel): ";
            cin>>choice;
            if(choice == 1){
                deleteNodeAtFront(head);
            } else if (choice == 2){
                deleteNodeAtEnd(head);
            } else if (choice == 3){
                int deleteRoll;
                cout<<"Please enter roll you want to delete: ";
                cin>>deleteRoll;
                deleteNodeAtRollNumber(head,deleteRoll);
            } else if (choice == 4){
                break;
            }
            goto reDelete;
        }break;
        case 7:{
            int modificationRoll;
            cout<<"Please enter roll you want to modify: ";
            cin>>modificationRoll;
            editNodeAtRoll(head, modificationRoll);
        }break;
        case 8:{
            exit(0);
        }
        default:{

        }
    }
    goto reEnterChoice;
}

void insertNewStudentAtFront(Student*& headNode, Student& student){
    if(headNode == nullptr){
        cout<<"The list is empty."<<endl;
        headNode = getNewStudent(student);
        cout<<"First student inserted"<<endl;
        cout<<headNode->name<<endl;
    }else{
        Student* newNode = getNewStudent(student);
        headNode->prevStudent = newNode;
        newNode->nextStudent = headNode;
        headNode = newNode;
        cout<<"Student "<<getSize(headNode)<<" added"<<endl;
    }
}

void insertNewStudentAfterStudent(Student*& headNode, Student& student, int afterRoll){
    Student* temp = headNode;
    if(temp == nullptr){
        cout<<"List is empty. Inserting at headnode."<<endl;
        insertNewStudentAtFront(headNode, student);
        return;
    }
    while (temp != nullptr && temp->rollNumber != afterRoll) {
        temp = temp->nextStudent;
    }
    if(temp != nullptr){
        if(temp->rollNumber == afterRoll){
            Student* newStudent = getNewStudent(student);
            if(temp->nextStudent != nullptr){
                newStudent->prevStudent = temp;
                newStudent->nextStudent = temp->nextStudent;
                temp->nextStudent->prevStudent = temp;
                temp->nextStudent = newStudent;
                cout<<"Student inserted next to roll "<<afterRoll<<"."<<endl;
                cout<<"Name: "<<temp->nextStudent->name<<endl;
                cout<<"Roll: "<<temp->nextStudent->rollNumber<<endl;
            }else{
                newStudent->prevStudent = temp;
                temp->nextStudent = newStudent;
                cout<<"Student inserted next to roll "<<afterRoll<<"."<<endl;
                cout<<"Name: "<<temp->nextStudent->name<<endl;
                cout<<"Roll: "<<temp->nextStudent->rollNumber<<endl;
            }
        }
    }else{
        cout<<"Student with roll "<<afterRoll<<" not found in the list."<<endl;
    }
}

void insertNewStudentAtEnd(Student*& headNode, Student& student){
    if(headNode == nullptr){
        headNode = getNewStudent(student);
    }else{
        Student* newNode = getNewStudent(student);
        Student* ptr = headNode;
        while (ptr->nextStudent != nullptr){
            ptr = ptr->nextStudent;
        }
        ptr->nextStudent = newNode;
        newNode->prevStudent = ptr;
    }
}

int getSize(Student* studentList){
    Student* tempList = studentList;
    int count = 0;
    while (tempList != nullptr){
        tempList = tempList->nextStudent;
        count++;
    }
    return count;
}

Student* getNewStudent(Student& student){
    auto* newStudentNode = new Student();
    newStudentNode->name = student.name;
    newStudentNode->rollNumber = student.rollNumber;
    newStudentNode->prevStudent = nullptr;
    newStudentNode->nextStudent = nullptr;
    return newStudentNode;
}

//TODO: Write a function to print the list
void printList(Student* studentList){
    Student* tempList = studentList;
    if(tempList == nullptr){
        cout<<"No student found."<<endl;
    }else{
        cout<<endl;
        cout<<"Total "<<getSize(studentList)<<" students found."<<endl<<endl;
        while(tempList != nullptr){
            cout<<tempList->name<<endl;
            cout<<tempList->rollNumber<<endl;
            tempList = tempList->nextStudent;
        }
        cout<<endl<<endl;
    }
}


Student* getNextStudent(Student& student, Student* headNode){
    Student* temp = headNode;
    while(temp != nullptr && temp->rollNumber != student.rollNumber){
        temp = temp->nextStudent;
    }
    if(temp != nullptr && temp->rollNumber == student.rollNumber){
        if(temp->nextStudent != nullptr){
            cout<<"Details of next student: "<<endl;
            cout<<"Name of next student: "<<temp->nextStudent->name<<endl;
            cout<<"Roll of next student: "<<temp->nextStudent->rollNumber<<endl;
            return temp->nextStudent;
        }else{
            cout<<temp->name<<" is the last student in list."<<endl;
            return temp;
        }
    }else{
        cout<<"Given student with roll "<<student.rollNumber<< " not found"<<endl;
        return nullptr;
    }
}

void movePointerToPrevNode(Student*& ptr, int& position){
    if(ptr == nullptr){
        cout<<"list is empty."<<endl;
        return;
    }
    if(ptr->prevStudent != nullptr){
        ptr = ptr->prevStudent;
        position--;
        cout<<"Pointer is at position "<<position<<"."<<endl;
        cout<<"Name: "<<ptr->name<<endl;
        cout<<"Roll Number: "<<ptr->rollNumber<<endl;
    }else{
        cout<<"Cannot move to previous position."<<endl;
        cout<<ptr->name<<" is first student."<<endl;
    }
}

void movePointerToNextNode(Student*& ptr, int& position){
    if(ptr == nullptr){
        cout<<"list is empty."<<endl;
        return;
    }
    if(ptr->nextStudent != nullptr){
        ptr = ptr->nextStudent;
        position++;
        cout<<"Pointer is at position "<<position<<"."<<endl;
        cout<<"Name: "<<ptr->name<<endl;
        cout<<"Roll Number: "<<ptr->rollNumber<<endl;
    }else{
        cout<<"Cannot move to next position."<<endl;
        cout<<ptr->name<<" is last student."<<endl;
    }
}


Student* getPrevStudent(Student& student, Student* headNode){
    Student* temp = headNode;
    while(temp != nullptr && temp->rollNumber != student.rollNumber){
        temp = temp->nextStudent;
    }
    if(temp != nullptr && temp->rollNumber == student.rollNumber){
        if(temp->prevStudent != nullptr){
            cout<<"Details of prev student: "<<endl;
            cout<<"Name of next student: "<<temp->prevStudent->name<<endl;
            cout<<"Roll of next student: "<<temp->prevStudent->rollNumber<<endl;
        }else{
            cout<<temp->name<<" is the first student in list."<<endl;
        }
        return temp->prevStudent;
    }else{
        cout<<"Given student with roll "<<student.rollNumber<< " not found"<<endl;
        return nullptr;
    }
}

//TODO: Write a function to delete the student at a particular position
void deleteNodeAtRollNumber(Student*& headNode, int deleteRollNumber){
    if(headNode == nullptr){
        cout<<"List is empty."<<endl;
        return;
    }

    if(headNode->rollNumber == deleteRollNumber){
        deleteNodeAtFront(headNode);
        return;
    }

    Student* tempNode = headNode;

    while (tempNode != nullptr && tempNode->rollNumber != deleteRollNumber){
        tempNode = tempNode->nextStudent;
    }

    if(tempNode != nullptr){
        if(tempNode->nextStudent != nullptr){
            tempNode->prevStudent->nextStudent = tempNode->nextStudent;
            tempNode->nextStudent->prevStudent = tempNode->prevStudent;
            delete tempNode;
        }else{
            tempNode->prevStudent->nextStudent = nullptr;
            delete tempNode;
        }
        cout<<"Student will roll "<<deleteRollNumber<<" deleted."<<endl;
    }else{
        cout<<"Deletion failed. Student with roll "<<deleteRollNumber<<" not found"<<endl;
    }
}

//TODO: Write a function to delete the student at front
void deleteNodeAtFront(Student*& headNode){
    if(headNode == nullptr){
        cout<<"List is empty"<<endl;
        return;
    }

    Student* tempNode = headNode;

    if(tempNode->nextStudent != nullptr){
        headNode = tempNode->nextStudent;
        headNode->prevStudent = nullptr;
        delete tempNode;
    }else{
        delete headNode;
        headNode = nullptr;
    }

    cout<<"Front student deleted"<<endl;

}

//TODO: Write a function to delete the student at end
void deleteNodeAtEnd(Student*& headNode){
    if(headNode == nullptr){
        cout<<"List is empty"<<endl;
        return;
    }

    Student* tempNode = headNode;

    while (tempNode->nextStudent != nullptr){
        tempNode = tempNode->nextStudent;
    }

    if(tempNode->prevStudent == nullptr){
        deleteNodeAtFront(headNode);
    }else{
        tempNode->prevStudent->nextStudent = nullptr;
        delete tempNode;
        cout<<"Node deleted"<<endl;
    }
}

void editNodeAtRoll(Student* headNode, int editRollNumber){
    if(headNode == nullptr){
        cout<<"List is empty."<<endl;
    }

    Student* tempNode = headNode;

    while(tempNode != nullptr && tempNode->rollNumber != editRollNumber){
        tempNode = tempNode->nextStudent;
    }

    if(tempNode != nullptr){
        string newName;
        int newRollNmber;
        int choice;
        cout<<"Student found: "<<endl;
        cout<<"Name: "<<tempNode->name<<endl;
        cout<<"Roll: "<<tempNode->rollNumber<<endl;
        cout<<"Please enter new name: ";
        getline(cin>>ws, newName);
        cout<<"Please enter new roll: ";
        cin>>newRollNmber;
        cout<<"These changes will be made: "<<endl;
        cout<<"Name: "<<tempNode->name<<" -> "<<newName<<endl;
        cout<<"Roll: "<<tempNode->rollNumber<<" -> "<<newRollNmber<<endl;
        cout<<"Are you sure?(0/1): "<<endl;
        cin>>choice;
        if(choice == 0){
            cout<<"Changes Not Saved."<<endl;
        }else{
            tempNode->name = newName;
            tempNode->rollNumber = newRollNmber;
            cout<<"Changes saved."<<endl;
        }
    }else{
        cout<<"Student with roll "<<editRollNumber<<" not found."<<endl;
    }
}
