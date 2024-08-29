#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
struct ListNode {
    T val;
    ListNode* next;
    ListNode() : val(T()), next(nullptr) {}
    ListNode(T x) : val(x), next(nullptr) {}
    ListNode(T x, ListNode* next) : val(x), next(next) {}
};

template <typename T>
class ListNodeOperations {
private:
    ListNode<T>* head;

public:
    ListNodeOperations() : head(nullptr) {}

    // Manipulación básica
    void pushfront(T val);
    void popfront();
    void pushback(T val);
    void popback();
    void connect(T val);
    void swap(int index1, int index2);
    void swapPairs();
    void removeElements(T target);
    void insertGreatestCommonDivisors();
    void reverse();
    void clear();
    void display();

    // Acceso
    int size();
    T front();
    T back();
    T& operator[](int index);
    ListNode<T>* getHead();

    // Utilidades y operaciones adicionales
    bool isCycle();
    bool empty();
    int howmanyonloop();
    ListNode<T>* addTwoNumbers(ListNode<T>* l1, ListNode<T>* l2);
    ListNode<T>* removeNthFromEnd(ListNode<T>* head, int n);
    ListNode<T>* mergeTwoLists(ListNode<T>* list1, ListNode<T>* list2);
    T GCD(T val1, T val2);
};

// Implementación de funciones

// Manipulación básica
template <typename T>
void ListNodeOperations<T>::pushfront(T val) {
    head = new ListNode<T>(val, head);
}

template <typename T>
void ListNodeOperations<T>::popfront() {
    if (head) {
        ListNode<T>* curr = head;
        head = head->next;
        delete curr;
    }
}

template <typename T>
void ListNodeOperations<T>::pushback(T val) {
    if (!head) {
        head = new ListNode<T>(val);
        return;
    }
    ListNode<T>* curr = head;
    while (curr->next) {
        curr = curr->next;
    }
    curr->next = new ListNode<T>(val);
}

template <typename T>
void ListNodeOperations<T>::popback() {
    if (!head) {
        return;
    }
    if (!head->next) {
        delete head;
        head = nullptr;
        return;
    }
    ListNode<T>* curr = head;
    while (curr->next->next) {
        curr = curr->next;
    }
    delete curr->next;
    curr->next = nullptr;
}

template <typename T>
void ListNodeOperations<T>::connect(T val) {
    if (!head) {
        head = new ListNode<T>(val);
        return;
    }
    ListNode<T>* curr = head;
    while (curr->next) {
        curr = curr->next;
    }
    curr->next = head; 
}

template <typename T>
void ListNodeOperations<T>::swap(int index1, int index2) {
    if (index1 < 0 || index2 < 0) {
        return;
    }

    ListNode<T>* curr1 = head;
    ListNode<T>* curr2 = head;

    for (int i = 0; i < index1 && curr1; i++) {
        curr1 = curr1->next;
    }

    for (int i = 0; i < index2 && curr2; i++) {
        curr2 = curr2->next;
    }

    if (curr1 && curr2) {
        T temp = curr1->val;
        curr1->val = curr2->val;
        curr2->val = temp;
    }
}

template <typename T>
void ListNodeOperations<T>::swapPairs() {
    ListNode<T>* curr = head;
    while (curr && curr->next) {
        swap(curr->val, curr->next->val);
        curr = curr->next->next;
    }
}

template <typename T>
void ListNodeOperations<T>::removeElements(T target) {
    while (head && head->val == target) {
        ListNode<T>* temp = head;
        head = head->next;
        delete temp;
    }

    ListNode<T>* curr = head;
    while (curr && curr->next) {
        if (curr->next->val == target) {
            ListNode<T>* temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
        } else {
            curr = curr->next;
        }
    }
}

template <typename T>
void ListNodeOperations<T>::insertGreatestCommonDivisors() {
    if (!head) {
        return;
    }
    ListNode<T>* curr = head;
    while (curr && curr->next) {
        T val1 = curr->val;
        T val2 = curr->next->val;
        while (val2 != 0) {
            T temp = val2;
            val2 = val1 % val2;
            val1 = temp;
        }
        ListNode<T>* temp = new ListNode<T>(val1);
        temp->next = curr->next;
        curr->next = temp;
        curr = temp->next;
    }
}

template <typename T>
void ListNodeOperations<T>::reverse() {
    ListNode<T>* prev = nullptr;
    ListNode<T>* current1 = head;
    ListNode<T>* siguiente = nullptr;

    while(current1 != nullptr) {
        siguiente = current1->next;
        current1->next = prev;
        prev = current1;
        current1 = siguiente;
    }
    head = prev;
}

template <typename T>
void ListNodeOperations<T>::clear() {
    if (!head) {
        return;
    }
    ListNode<T>* curr1 = head;
    while (curr1) {
        ListNode<T>* curr2 = curr1->next; 
        delete curr1;                   
        curr1 = curr2;                  
    }
    head = nullptr;
}

template <typename T>
void ListNodeOperations<T>::display() {
    ListNode<T>* curr = head;
    while (curr) {
        cout << curr->val;
        if (curr->next) {
            cout << ", ";
        }
        curr = curr->next;
    }
    cout << endl;
}

// Acceso
template <typename T>
int ListNodeOperations<T>::size() {
    ListNode<T>* curr = head;
    int size = 0;
    while (curr) {
        curr = curr->next;
        size++;
    }
    return size;
}

template <typename T>
T ListNodeOperations<T>::front() {
    if (!head) {
        throw runtime_error("La lista está vacía");
    }
    return head->val;
}

template <typename T>
T ListNodeOperations<T>::back() {
    if (!head) {
        throw runtime_error("La lista está vacía");
    }
    ListNode<T>* curr = head;
    while (curr->next) {
        curr = curr->next;
    }
    return curr->val;
}

template <typename T>
T& ListNodeOperations<T>::operator[](int index) {
    if (index < 0) {
        throw out_of_range("no negativo");
    }

    ListNode<T>* current = head;
    int currentIndex = 0;

    while (current != nullptr && currentIndex < index) {
        current = current->next;
        currentIndex++;
    }

    if (current == nullptr) {
        throw out_of_range("Fuera de rango");
    }

    return current->val;
}

template <typename T>
ListNode<T>* ListNodeOperations<T>::getHead() {
    return head;
}

// Utilidades y operaciones adicionales
template <typename T>
bool ListNodeOperations<T>::isCycle() {
    if (!head || !head->next) {
        return false;
    }
    ListNode<T>* slow = head;
    ListNode<T>* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

template <typename T>
bool ListNodeOperations<T>::empty() {
    return head == nullptr;
}

template <typename T>
int ListNodeOperations<T>::howmanyonloop() {
    if (!isCycle()) {
        return 0;
    }

    ListNode<T>* slow = head;
    ListNode<T>* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) { 
            break;
        }
    } 
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }

    int count = 1;
    ListNode<T>* current = slow->next;
    while (current != slow) {
        count++;
        current = current->next;
    }

    return count;
}

template <typename T>
ListNode<T>* ListNodeOperations<T>::addTwoNumbers(ListNode<T>* l1, ListNode<T>* l2) {
    ListNode<T>* dummyHead = new ListNode<T>(0);
    ListNode<T>* curr = dummyHead;
    int carry = 0;

    while (l1 != nullptr || l2 != nullptr || carry) {
        int sum = carry;
        if (l1 != nullptr) {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2 != nullptr) {
            sum += l2->val;
            l2 = l2->next;
        }

        carry = sum / 10;
        curr->next = new ListNode<T>(sum % 10);
        curr = curr->next;
    }

    ListNode<T>* result = dummyHead->next;
    delete dummyHead;
    return result;
}

template <typename T>
ListNode<T>* ListNodeOperations<T>::removeNthFromEnd(ListNode<T>* head, int n) {
    if (!head) return nullptr;
    ListNode<T>* dummy = new ListNode<T>(0, head);
    ListNode<T>* curr = dummy;
    int size = 0;

    while (curr) {
        curr = curr->next;
        size++;
    }

    int NthFromEnd = size - n - 1;
    curr = dummy;
    while (NthFromEnd > 0) {
        curr = curr->next;
        NthFromEnd--;
    }
    ListNode<T>* temp = curr->next;
    curr->next = curr->next->next;
    delete temp;

    ListNode<T>* newHead = dummy->next;
    delete dummy;

    return newHead;
}

template <typename T>
ListNode<T>* ListNodeOperations<T>::mergeTwoLists(ListNode<T>* list1, ListNode<T>* list2) {
    if (!list1) {
        return list2;
    }
    if (!list2) {
        return list1;
    }

    ListNode<T>* dummy = new ListNode<T>();
    ListNode<T>* curr = dummy;

    while (list1 && list2) {
        if (list1->val < list2->val) {
            curr->next = list1;
            list1 = list1->next;
        } else {
            curr->next = list2;
            list2 = list2->next;
        }
        curr = curr->next;
    }
    if (list1) {
        curr->next = list1;
    } else {
        curr->next = list2;
    }

    ListNode<T>* mergedList = dummy->next;
    delete dummy; 
    return mergedList;
}

template <typename T>
T ListNodeOperations<T>::GCD(T val1, T val2) {
    while (val2 != 0) {
        T temp = val2;
        val2 = val1 % val2;
        val1 = temp;
    }
    return val1;
}

// Pruebas en main
int main() {
    ListNodeOperations<int> list;

    // Pruebas básicas
    list.pushback(1);
    list.pushback(2);
    list.pushback(3);
    list.pushback(4);

    cout << "List after pushback operations: ";
    list.display();

    list.popfront();
    cout << "List after popfront operation: ";
    list.display();

    list.popback();
    cout << "List after popback operation: ";
    list.display();

    list.pushfront(5);
    cout << "List after pushfront operation: ";
    list.display();

    list.swap(0, 1);
    cout << "List after swap operation: ";
    list.display();

    list.swapPairs();
    cout << "List after swapPairs operation: ";
    list.display();

    list.removeElements(5);
    cout << "List after removeElements operation (removing 5): ";
    list.display();

    // Insert GCD values
    list.insertGreatestCommonDivisors();
    cout << "List after insertGreatestCommonDivisors operation: ";
    list.display();

    // Test reverse
    list.reverse();
    cout << "List after reverse operation: ";
    list.display();

    // Test access
    try {
        cout << "Element at index 0: " << list[0] << endl;
        cout << "Element at index 1: " << list[1] << endl;
        cout << "Element at index 2: " << list[2] << endl;
        cout << "Element at index 3: " << list[3] << endl;
    } catch (const std::out_of_range& e) {
        cout << "Error: " << e.what() << endl;
    }

    // Test list properties
    cout << "Front element: " << list.front() << endl;
    cout << "Back element: " << list.back() << endl;
    cout << "Size of the list: " << list.size() << endl;
    cout << "Is the list empty? " << (list.empty() ? "Yes" : "No") << endl;

    // Test addTwoNumbers
    ListNode<int>* l1 = new ListNode<int>(2, new ListNode<int>(4, new ListNode<int>(3)));
    ListNode<int>* l2 = new ListNode<int>(5, new ListNode<int>(6, new ListNode<int>(4)));
    ListNode<int>* result = list.addTwoNumbers(l1, l2);
    cout << "Result of addTwoNumbers: ";
    while (result) {
        cout << result->val << " ";
        result = result->next;
    }
    cout << endl;

    // Test mergeTwoLists
    ListNode<int>* list1 = new ListNode<int>(1, new ListNode<int>(3, new ListNode<int>(5)));
    ListNode<int>* list2 = new ListNode<int>(2, new ListNode<int>(4, new ListNode<int>(6)));
    ListNode<int>* merged = list.mergeTwoLists(list1, list2);
    cout << "Merged list: ";
    while (merged) {
        cout << merged->val << " ";
        merged = merged->next;
    }
    cout << endl;

    // Test removeNthFromEnd
    ListNode<int>* listToRemove = new ListNode<int>(1, new ListNode<int>(2, new ListNode<int>(3, new ListNode<int>(4, new ListNode<int>(5)))));
    ListNode<int>* newHead = list.removeNthFromEnd(listToRemove, 2);
    cout << "List after removing 2nd from end: ";
    while (newHead) {
        cout << newHead->val << " ";
        newHead = newHead->next;
    }
    cout << endl;

    // Clean up
    list.clear();

    return 0;
}
