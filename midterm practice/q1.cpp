/*
Fill in the missing code for an OrderedLinkedList class.The values in an OrderedLinkedList are always in either ascending order or flat, starting with the smallest value in the head node.
Copy paste your edited file, You don't need to include a sample run
*/

#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class Node {
public:
    T value;
    Node* prev, * next;
    Node(const T& v, Node* p = nullptr, Node* n = nullptr) {
        prev = p; next = n; value = v;
    }
};


template <class T>
class OrderedLinkedList {
    friend ostream& operator<<(ostream& out, const  OrderedLinkedList<T>& l) {
        out << "{ ";
        Node<T>* temp = l.headPtr;
        while (temp != nullptr) {
            if (temp->next != nullptr)
                out << temp->value << ", ";
            else out << temp->value;
            temp = temp->next;
        }
        out << "}";

        return out;
    }

private:
    Node<T>* headPtr, // a pointer to first node or null if list is empty.
        * tailPtr; // a pointer to last  node or null if list is empty.
    int length; // the list length


    Node<T>* findNodeWithValue(const T& v) const {
        Node<T>* temp = headPtr;
        while (temp != nullptr) {
            if (temp->value == v) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

public:
    OrderedLinkedList() {
        headPtr = nullptr;
        tailPtr = nullptr;
        length = 0;
    }


    OrderedLinkedList(const OrderedLinkedList& other) {
        if (other.headPtr == nullptr) {
            headPtr = nullptr;
            length = 0;
            return;
        }
        headPtr = new Node<T>(other.headPtr);
        Node<T>* temp = other.headPtr->next;
        Node<T>* current = headPtr;
        while (temp != nullptr) {
            current->next = new Node<T>(temp);
            current->prev->next = current;
            current = current->next;
            temp = temp->next;
        }
        tailPtr = current;
        length = other.length;
    }


    T& operator[](int index) {
        if (index < 0 || index > length - 1)
            throw logic_error("Index out of bounds");

        else {
            Node<T>* temp = headPtr;
            int count = 0;
            while (count < index && temp != nullptr) {
                count++;
                temp = temp->next;
            }
            if (temp != nullptr) return temp->value;
        }
        throw logic_error("Index out of bounds");
    }


    ~OrderedLinkedList() {
        Node<T>* temp = headPtr;
        while (temp != nullptr){
            Node<T>* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
        headPtr = nullptr;
        tailPtr = nullptr;
        length = 0;
    }


    void clear() {
        //~OrderedLinkedList();
        Node<T>* temp = headPtr;
        while (temp != nullptr) {
            Node<T>* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
        headPtr = nullptr;
        tailPtr = nullptr;
        length = 0;
    }


    int count(const T& v) {
        Node<T>* p = findNodeWithValue(v);
        if (p == nullptr) return 0;
        int count = 0;
        while (p != nullptr) {
            if(p->value == v)
                count++;
            p = p->next;
        }
        return count;
    }

    void printBackwards() const {
        cout << "< ";
        Node<T>* temp = tailPtr;
        while (temp != nullptr) {
            cout << temp->value;
            if (temp->prev != nullptr)
                cout << " ";
            temp = temp->next;
        }
        cout << ">";
        cout << endl;
    }

    void insert(const T& v) {
        Node<T>* toInsert = new Node<T>(v);
        if (headPtr == nullptr) {
            headPtr = toInsert;
            tailPtr = toInsert;
        }
        else if (toInsert->value <= headPtr->value) {
            toInsert->next = headPtr;
            headPtr->prev = toInsert;
            headPtr = toInsert;
        }
        else if (toInsert->value >= tailPtr->value) {
            tailPtr->next = toInsert;
            toInsert->prev = tailPtr;
            tailPtr = toInsert;
        }
        else {
            Node<T>* current = headPtr;
            while (current->next != nullptr && current->next->value < toInsert->value) {
                current = current->next;
            }
            toInsert->next = current->next;
            toInsert->prev = current;

            if (current->next != nullptr) {
                current->prev = toInsert;
            }
            current->next = toInsert;
        }
        length++;
    }

    int getLength() const {
        return length;
    }


    bool isEmpty() const {
        if (headptr == nullptr) return true;
        return false;
    }


    void getBiggest(T& b) const {
        if (tailPtr != nullptr)
            b = tailPtr->value;
    }


    void getSmallest(T& s) const {
        if (headPtr != nullptr)
            s = headPtr->value;
    }


    void remove(const T& v) {
        if (headPtr == nullptr) return;
        Node<T>* toDelete = findNodeWithValue(v);
        if (toDelete == nullptr) return;                    
        
        if (toDelete == headPtr) {
            headPtr = headPtr->next;
            headPtr->prev = nullptr;
        }

        else if (toDelete == tailPtr) {
            tailPtr = tailPtr->prev;
            tailPtr->next = nullptr;
        }
        
        else {
            toDelete->prev->next = toDelete->next;
            toDelete->next->prev = toDelete->prev;
        }
        
        delete toDelete;
        length--;
    }
};

template <class T>

void testList(OrderedLinkedList<T> list) {

    cout << endl << "BEGIN TESTLIST" << endl;
    cout << "Length = " << list.getLength() << endl;
    cout << "Forwards: " << list << endl;
    cout << "Backwards: ";

    list.printBackwards();

    if (list.isEmpty()) cout << "The list is empty." << endl;

    else {
        T v;

        cout << "getSmallest returns ";
        list.getSmallest(v);
        cout << v << "." << endl;
        cout << "getBiggest returns ";
        list.getBiggest(v);
        cout << v << "." << endl;

    }

    try {
        cout << list[list.getLength()] << endl;
    }

    catch (logic_error e) {
        cout << e.what() << endl;
    }

    try {
        cout << list[-1] << endl;
    }

    catch (logic_error e) {
        cout << e.what() << endl;
    }

    for (int i = 0; i < list.getLength() / 2; i++)
        swap(list[i], list[list.getLength() - i - 1]);

    cout << "After reversing values " << list << endl;
    list.clear();
    cout << "After clear: " << list << endl;
    cout << "END TESTLIST" << endl << endl;
}




int main(){
    OrderedLinkedList<int> list;
    cout << "Initial list = " << list << endl;
    cout << "Initial list length = " << list.getLength() << endl;
    list.insert(11);
    list.insert(3);
    list.insert(5);
    list.insert(7);
    list.insert(6);
    list.insert(4);
    list.insert(2);
    list.insert(8);
    list.insert(5);
    list.insert(1);
    list.insert(0);
    list.insert(11);
    list.insert(10);
    list.insert(5);
    list.insert(11);
    list.insert(0);
    list.insert(8);
    list.insert(4);

    cout << "After insertions, list = " << list << endl;
    testList(list);
    cout << "After testList, list = " << list << endl;
    char response = 'n';
    int v = -1;

    do {
        cout << "Enter a value to remove or -1 to quit: ";
        cin >> v;

        if (v != -1) {
            cout << "old count: " << list.count(v) << endl;
            list.remove(v);
            cout << "new count: " << list.count(v) << endl;
            testList(list);
            cout << list << endl;
        }
    } while (v != -1);

    do {
        cout << "Enter a value to insert or -1 to quit: ";
        cin >> v;

        if (v != -1) {
            cout << "old count: " << list.count(v) << endl;
            list.insert(v);
            cout << "new count: " << list.count(v) << endl;
            testList(list);
            cout << list << endl;
        }
    } while (v != -1);

    cout << "Bye" << endl;

    return 0;

}

