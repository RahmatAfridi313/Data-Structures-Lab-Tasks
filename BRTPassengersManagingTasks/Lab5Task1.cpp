#include<iostream>
using namespace std;

struct Node {
    int passengerId;
    Node *next;

    Node(int id) : passengerId(id), next(nullptr) {}
};

class LinkedList {
private:
    Node *head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        Node *curr = head;
        while (curr) {
            Node *nxt = curr->next;
            delete curr;
            curr = nxt;
        }
    }

    void insertAtBeginning(int val) {
        Node *node = new Node(val);
        node->next = head;
        head = node;
    }

    void insertAtEnd(int val) {
        Node *node = new Node(val);
        if (head == nullptr) {
            head = node;
            return;
        }
        Node *curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = node;
    }

    void insertAtPosition(int value, int pos) {
        if (pos == 0) {
            insertAtBeginning(value);
            return;
        }
        Node* cur = head;
        for (int i = 0; cur != nullptr && i < pos - 1; i++) {
            cur = cur->next;
        }
        if (cur == nullptr) {
            insertAtEnd(value); 
            return;
        }
        Node* node = new Node(value);
        node->next = cur->next;
        cur->next = node;
    }

    bool deleteFromBeginning(int* removedValue = nullptr) {
        if (head == nullptr) return false;
        Node* temp = head;
        if (removedValue) {
            *removedValue = temp->passengerId;
        }
        head = head->next;
        delete temp;
        return true;
    }

    void display() const {
        Node* cur = head;
        while (cur) {
            cout << cur->passengerId;
            if (cur->next) cout << " -> ";
            cur = cur->next;
        }
        cout << "\n";
    }
};

int main() {
    LinkedList list;

    // Step 1: Add 3 passengers at the end
    list.insertAtEnd(101);
    list.insertAtEnd(102);
    list.insertAtEnd(103);
    cout << "Initial Queue after adding passengers:\n";
    list.display();

    // Step 2: Emergency passenger at beginning
    list.insertAtBeginning(999);
    cout << "After adding an emergency passenger at beginning:\n";
    list.display();

    // Step 3: Special booking passenger at position 2
    list.insertAtPosition(555, 2);
    cout << "After inserting special booking passenger at position 2:\n";
    list.display();

    // Step 4: First passenger boards (delete from beginning)
    int removed;
    list.deleteFromBeginning(&removed);
    cout << "After first passenger boards (deletion):\n";
    list.display();

    return 0;
}
