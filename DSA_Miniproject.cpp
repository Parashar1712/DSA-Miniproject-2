#include <iostream>
#include <string>

using namespace std;

struct Student {
    int roll;
    string name;
    string course;
    float marks;
    Student* next;
};

struct Queue {
    string tickets[5];
    int front;
    int rear;

    Queue() {
        front = -1;
        rear = -1;
    }

    void enqueue(string query) {
        if ((front == 0 && rear == 4) || (rear == (front - 1) % 4)) {
            cout << "\nQueue is full!\n";
            return;
        }
        if (front == -1) {
            front = 0;
            rear = 0;
        } else {
            rear = (rear + 1) % 5;
        }
        tickets[rear] = query;
        cout << "\nTicket submitted successfully.\n";
    }

    void dequeue() {
        if (front == -1) {
            cout << "\nNo tickets to resolve.\n";
            return;
        }
        cout << "\nResolving query: " << tickets[front] << "\n";
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % 5;
        }
    }

    void printQueue() {
        if (front == -1) {
            cout << "\nNo pending tickets.\n";
            return;
        }
        cout << "\n--- Pending Support Tickets ---\n";
        int i = front;
        while (true) {
            cout << "- " << tickets[i] << "\n";
            if (i == rear) break;
            i = (i + 1) % 5;
        }
    }
};

Student* head = NULL;
Queue supportQ;

void insertStudent() {
    Student* temp = new Student();
    cout << "Enter Roll No: ";
    cin >> temp->roll;
    cout << "Enter Name: ";
    cin >> temp->name;
    cout << "Enter Course: ";
    cin >> temp->course;
    cout << "Enter Marks: ";
    cin >> temp->marks;
    temp->next = NULL;

    if (head == NULL) {
        head = temp;
    } else {
        Student* p = head;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = temp;
    }
    cout << "\nStudent record added!\n";
}

void displayStudents() {
    if (head == NULL) {
        cout << "\nNo records found!\n";
        return;
    }
    cout << "\nRoll\tName\tCourse\tMarks\n";
    cout << "-------------------------------------\n";
    Student* temp = head;
    while (temp != NULL) {
        cout << temp->roll << "\t" << temp->name << "\t" << temp->course << "\t" << temp->marks << "\n";
        temp = temp->next;
    }
}

void searchStudent() {
    if (head == NULL) {
        cout << "\nList is empty!\n";
        return;
    }
    int r;
    cout << "Enter Roll No to search: ";
    cin >> r;

    Student* temp = head;
    while (temp != NULL) {
        if (temp->roll == r) {
            cout << "\nStudent Found:\n";
            cout << "Name: " << temp->name << "\nCourse: " << temp->course << "\nMarks: " << temp->marks << "\n";
            return;
        }
        temp = temp->next;
    }
    cout << "\nStudent not found.\n";
}

void deleteStudent() {
    if (head == NULL) {
        cout << "\nList is empty!\n";
        return;
    }
    int r;
    cout << "Enter Roll No to delete: ";
    cin >> r;

    if (head->roll == r) {
        Student* temp = head;
        head = head->next;
        delete temp;
        cout << "\nRecord deleted.\n";
        return;
    }

    Student* curr = head;
    Student* prev = NULL;
    while (curr != NULL && curr->roll != r) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        cout << "\nRecord not found.\n";
    } else {
        prev->next = curr->next;
        delete curr;
        cout << "\nRecord deleted.\n";
    }
}

void sortStudents() {
    if (head == NULL || head->next == NULL) {
        cout << "\nNot enough records to sort.\n";
        return;
    }

    int ch;
    cout << "\n1. Sort by Marks\n2. Sort by Name\nChoice: ";
    cin >> ch;

    for (Student* i = head; i->next != NULL; i = i->next) {
        for (Student* j = i->next; j != NULL; j = j->next) {
            bool swapNeeded = false;
            
            if (ch == 1 && i->marks < j->marks) swapNeeded = true;
            if (ch == 2 && i->name > j->name) swapNeeded = true;

            if (swapNeeded) {
                swap(i->roll, j->roll);
                swap(i->name, j->name);
                swap(i->course, j->course);
                swap(i->marks, j->marks);
            }
        }
    }
    cout << "\nList sorted successfully!\n";
}

int main() {
    int choice;
    while (true) {
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Sort Records\n";
        cout << "6. Add Support Query\n";
        cout << "7. Resolve Support Query\n";
        cout << "8. View Support Queries\n";
        cout << "9. Exit\n";
        cout << "Select option: ";
        cin >> choice;

        switch (choice) {
            case 1: insertStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: sortStudents(); break;
            case 6: {
                string q;
                cout << "Enter support query (single word): ";
                cin >> q;
                supportQ.enqueue(q);
                break;
            }
            case 7: supportQ.dequeue(); break;
            case 8: supportQ.printQueue(); break;
            case 9: 
                cout << "\nExiting program...\n";
                return 0;
            default: 
                cout << "\nInvalid selection.\n";
        }
    }
    return 0;
}