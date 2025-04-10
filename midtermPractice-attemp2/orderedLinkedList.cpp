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
        headPtr = new Node<T>(*temp); // Copy the first node
        Node<T>* current = headPtr;
        temp = temp->next;

        while (temp != nullptr) {
            current->next = new Node<T>(*temp);
            current->next->prev = current;
            current = current->next;
            temp = temp->next;
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
        Node<T>* toInsert = new Node(v); //allocate new memory for the node and pass to it v as its value
        if (headPtr == nullptr) { //in the case in which the linked list is empty
            headPtr = toInsert; //we need to assign toInsert to headPtr 
            tailPtr= toInsert; //the address from toInsert is being assigned to tailPtr
        }
        else if (v <= headPtr->value) { //if our value that were trying to insert is less than the headptr.value then insert it before the headptr
            toInsert->next = headPtr; //we make sure to conenct the toInsert.next to the current headptr
            headPtr->prev = toInsert; //and take the current headptr.prev and make sure it points to toInsert
            headPtr = toInsert; //then we simply update headptr so that instead of it pointing to the previous address it pointed to it now points to toInserts address
        }
        else if (tailPtr->value <= v) { // the case in whic the value were inserting is greater than the tailptr.value meaning it should be last in line
            tailPtr->next = toInsert; // we should update the current tailptr.next address to be assigned the address of the new node we are trying to insert
            toInsert->prev = tailPtr; // we now update the node we are inserting's previous ptr to point to what is currently the tailptr
            tailPtr = toInsert; //now once its all connected we can make sure that tailptr points to the new tailptr's address in this case its the new address since it should be last
        }
        else { //in any other case that means its in the middle so we have to traverse
            Node<T>* current = headPtr; //we create a temp/current that gets assigned the address of the headPtr
            while (current->next != nullptr && current->next->value < toInsert->value) { //this loop runs as long as the current.next is not null and the 
                //current.next.value is less than the value we are trying to insert
                current = current->next; //simply update current until we reach the point where current.next is either null making sure it doesnt keep looping past the last value
                //or will still if its no longer less than the value we are going to inser
            } //here weve stopped at the value that will be before our new node were inserting
            toInsert->next = current->next; //we need to make sure toInsert points to whatever is currently current's next address
            toInsert->prev = current; //and we need to make sure that its prev points to current

            if (current->next != nullptr) { 
                current->next->prev = toInsert; //we need to make sure the node after current has a prev that points to toInsert
            }
            current->next = toInsert; //lastly we can assign toInsert to current.next's address
            }
        }
        length++; //simply increment the length for all cases since we added a node to the list
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

        void removeBiggest() {
            if (headptr == nullptr) return;
            Node<T>* toDelete = tailPtr;
            tailPtr = tailPtr->prev;
            delete toDelete;
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


