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







// A doubly linked list in which the values are arranged in ascending order.

template <class T>

class OrderedLinkedList {

    friend ostream& operator<<(ostream& out, const  OrderedLinkedList<T>& l) {

        out << "{ ";

        Node<T>* temp = l.headPtr;
        while (temp != nullptr) {
            if (temp->next != nullptr) {
                out << temp.value << ", ";
            }
            else out << temp->value;
            temp = temp.next;
        }

        out << "}";

        return out;

    }

private:

    Node<T>* headPtr, // a pointer to first node or null if list is empty.

        * tailPtr; // a pointer to last  node or null if list is empty.

    int length; // the list length




    // Return a pointer to first node containing v

    // or return nullptr if v is not found.

    Node<T>* findNodeWithValue(const T& v) const {
        Node<T>* temp = headPtr;
        while (temp != nullptr) {
            if (temp->value == v) return temp;
            temp = temp->next;
        }
        return nullptr;
        
        // FILL IN MISSING CODE

    }

public:




    // Set headPtr and nullPtr to null and set length to zero.

    OrderedLinkedList() {

        headPtr = nullptr;
        tailPtr = nullptr;
        length = 0;

    }




    // Copy constructor.

    OrderedLinkedList(const OrderedLinkedList& other) {
        if (other.headPtr == nullptr) {
            headPtr = tailPtr = nullptr;
            length = 0;
            return;
        }

        Node<T>* temp = other.headPtr;
        Node<T>* current = headPtr;
        while (temp != nullptr) {
            current->next = new Node(temp);
            current->prev->next = current;
            temp = temp->next;
            current = current->next;
        }
        tailPtr = current;
        length = other.length;
    }




    // Return value in node at given index

    // or throw logic_error if index < 0 or > length-1

    // Message should be "Index out of bounds"

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
            if (temp != nullptr) return count;
        }
        throw logic_error("Index out of bounds");
    }




    // Destructor

    ~OrderedLinkedList() {

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




    // Remove all values from the list.

    void clear() {
        Node<T>* temp = headPtr;
        while (temp!= nullptr) {
            Node<T>* toDelete = temp; 
            temp = temp->next;
            delete toDelete;
        }
        headPtr = nullptr;
        tailPtr = nullptr;
        length = 0;

    }




    // Return the number of occurrences of v in the list

    // or return 0 if v is not found.

    // Your code should call findNodeWithValue.

    int count(const T& v) {
        Node<T>* p = findNodeWithValue(v);
        if (p == nullptr) return 0;
        int count = 0;
        while (p != nullptr){
            if (p->value == v) count++;
            p = p->next;
        }
        return count;

    }



    // Print the list values in reverse order,

    // enclosed in angle brackets, e.g. < 4 3 2 1 >

    void printBackwards() const {

        cout << "< ";

        Node<T>* temp = tailPtr;
        while (temp != nullptr) {
            cout << temp->value;
            if(temp->prev == nullptr)
                cout << temp->value;
            temp = temp->prev;
        }

        cout << ">";

        cout << endl;

    }


    // Insert v in the correct position
    // in the list and update length
    // Update headPtr or tailPtr if necessary.
    // Avoid needless looping
    // when v is the new biggest or the new smallest value.

    void insert(const T& v) {
        Node<T>* toInsert = new Node(v);
        if (headPtr == nullptr) {
            headPtr->value = toInsert;
            tailPtr->value = toInsert;
        }
        else if (v <= headPtr) {
            toInsert->next = headPtr;
            headPtr->prev = toInsert;
            headPtr = toInsert;
        }
        else if (length == 1) {
            headPtr->next = toInsert;
        }
        else if (tailPtr->value <= v) {
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
        }
        length++;
    }




    // Return the list length

    int getLength() const {
        return length;
    }




    // Return true if the list is empty

    bool isEmpty() const {

        if (headPtr == nullptr) return true;
        return false;
    }




    // Set b to the biggest value or do nothing if the list is empty.

    void getBiggest(T& b) const {
        if (tailPtr != nullptr) {
            b = tailPtr->value;
        }
    }




    // Set s to the smallest value or do nothing if the list is empty.

    void getSmallest(T& s) const {

        if (headPtr != nullptr) s = headPtr->value;

    }




    // Remove the first occurence of v or do nothing if v isn't found.

    // Your code should call findNodeWithValue.

    void remove(const T& v) {
        void remove(const T & v) {
            if (headPtr == nullptr) return; //base case check if the linked list is empty
            Node<T>* toDelete = findNodeWithValue(v); //if its not were going to assign the node we want to delete toDelete 
            if (toDelete == nullptr) return; //if the function findNodeWithValue returned nullptr we can just return because that means its empty

            if (toDelete == headPtr) { //if toDelete was assigned the value of the headptr then we need to make sure we update what headptr is pointing to 
                headPtr = headPtr->next; //so we assign to it the value of headptr.next
                headPtr->prev = nullptr; //and we need to make sure the new headptr.prev points to nullptr
            }

            else if (toDelete == tailPtr) { //case in which it got assigned the tailptr value
                tailPtr = tailPtr->prev; //if so we update tail ptr to the previous node
                tailPtr->next = nullptr; //then we can make sure that it's next pointer points to nullptr
            }

            else {
                toDelete->prev->next = toDelete->next; //otherwise that means its in the middle and we need to make sure that the next value for toDelete gets as assigned to its previous value's next
                toDelete->next->prev = toDelete->prev; //the same for the previous value we need to make sure that its nexts value points to its previous node
            }

            delete toDelete; //now once the values have been updated to point to the correct value we can delete toDelete
            length--; //and we decrement the length since we have one less
        }
    };

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




int main()

{

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


