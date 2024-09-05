#include <iostream>
using namespace std;

// Plantilla para el nodo de lista
template <typename T>
struct ListNode {
    T val;
    ListNode *next;
    ListNode() : val(T()), next(nullptr) {}
    ListNode(T x) : val(x), next(nullptr) {}
    ListNode(T x, ListNode *next) : val(x), next(next) {}
};

// Plantilla para las operaciones de la lista
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
    void removeElements(T target);
    void reverse();
    void clear();
    void display();
    void selectionSort();
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
    ListNode<T>* insertGreatestCommonDivisors();
    ListNode<T>* swapPairs();
    ListNode<T>* deleteDuplicates();
    ListNode<T>* rotateRight(ListNode<T>* head, int k);
    ListNode<T>* deleteDuplicates2(ListNode<T>* head);
    ListNode<T>* partition(ListNode<T>* head, T x);
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
    if (index1 < 0 || index2 < 0 || index1 == index2) {
        return;
    }

    ListNode<T>* prev1 = nullptr;
    ListNode<T>* curr1 = head;
    for (int i = 0; i < index1 && curr1; i++) {
        prev1 = curr1;
        curr1 = curr1->next;
    }

    ListNode<T>* prev2 = nullptr;
    ListNode<T>* curr2 = head;
    for (int i = 0; i < index2 && curr2; i++) {
        prev2 = curr2;
        curr2 = curr2->next;
    }

    if (curr1 && curr2) {
        if (prev1) {
            prev1->next = curr2;
        } else {
            head = curr2;
        }
        if (prev2) {
            prev2->next = curr1;
        } else {
            head = curr1;
        }
        ListNode<T>* temp = curr2->next;
        curr2->next = curr1->next;
        curr1->next = temp;
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
void ListNodeOperations<T>::reverse() {
    ListNode<T>* prev = nullptr;
    ListNode<T>* curr = head;
    ListNode<T>* next = nullptr;

    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

template <typename T>
void ListNodeOperations<T>::clear() {
    if (!head) {
        return;
    }
    ListNode<T>* curr = head;
    while (curr) {
        ListNode<T>* next = curr->next; 
        delete curr;                   
        curr = next;                  
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

template <typename T>
void ListNodeOperations<T>::selectionSort() {
    if (!head || !head->next) return;

    ListNode<T>* current = head;
    
    while (current) {
        ListNode<T>* minNode = current;
        ListNode<T>* runner = current->next;
        
        // Encuentra el nodo con el valor mínimo
        while (runner) {
            if (runner->val < minNode->val) {
                minNode = runner;
            }
            runner = runner->next;
        }
        
        // Intercambia los valores del nodo actual y el nodo mínimo encontrado
        if (minNode != current) {
            T temp = current->val;
            current->val = minNode->val;
            minNode->val = temp;
        }
        
        current = current->next;
    }
}


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
        throw out_of_range("Índice no válido");
    }

    ListNode<T>* curr = head;
    int currentIndex = 0;

    while (curr != nullptr && currentIndex < index) {
        curr = curr->next;
        currentIndex++;
    }

    if (curr == nullptr) {
        throw out_of_range("Índice fuera de rango");
    }

    return curr->val;
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
            ListNode<T>* temp = slow;
            int count = 0;
            do {
                temp = temp->next;
                count++;
            } while (temp != slow);
            return count;
        }
    }
    return 0;
}

template <typename T>
ListNode<T>* ListNodeOperations<T>::addTwoNumbers(ListNode<T>* l1, ListNode<T>* l2) {
    ListNode<T>* dummy = new ListNode<T>(0);
    ListNode<T>* p = l1, *q = l2, *curr = dummy;
    int carry = 0;
    while (p != nullptr || q != nullptr || carry != 0) {
        int sum = carry;
        if (p != nullptr) {
            sum += p->val;
            p = p->next;
        }
        if (q != nullptr) {
            sum += q->val;
            q = q->next;
        }
        carry = sum / 10;
        curr->next = new ListNode<T>(sum % 10);
        curr = curr->next;
    }
    return dummy->next;
}

template <typename T>
ListNode<T>* ListNodeOperations<T>::removeNthFromEnd(ListNode<T>* head, int n) {
    ListNode<T>* dummy = new ListNode<T>(0);
    dummy->next = head;
    ListNode<T>* first = dummy;
    ListNode<T>* second = dummy;
    for (int i = 1; i <= n + 1; i++) {
        first = first->next;
    }
    while (first != nullptr) {
        first = first->next;
        second = second->next;
    }
    second->next = second->next->next;
    return dummy->next;
}

template <typename T>
ListNode<T>* ListNodeOperations<T>::mergeTwoLists(ListNode<T>* list1, ListNode<T>* list2) {
    ListNode<T>* dummy = new ListNode<T>(0);
    ListNode<T>* tail = dummy;
    while (list1 != nullptr && list2 != nullptr) {
        if (list1->val < list2->val) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }
    tail->next = (list1 != nullptr) ? list1 : list2;
    return dummy->next;
}

template <typename T>
T ListNodeOperations<T>::GCD(T val1, T val2) {
    if (val2 == 0) return val1;
    return GCD(val2, val1 % val2);
}

template <typename T>
ListNode<T>* ListNodeOperations<T>::insertGreatestCommonDivisors() {
    if (!head || !head->next) return head;

    ListNode<T>* curr = head;
    while (curr->next) {
        T gcd_val = GCD(curr->val, curr->next->val);
        ListNode<T>* newNode = new ListNode<T>(gcd_val, curr->next);
        curr->next = newNode;
        curr = curr->next->next;
    }
    return head;
}

template <typename T>
ListNode<T>* ListNodeOperations<T>::swapPairs() {
    ListNode<T>* dummy = new ListNode<T>(0);
    dummy->next = head;
    ListNode<T>* prev = dummy;
    while (head && head->next) {
        ListNode<T>* first = head;
        ListNode<T>* second = head->next;
        prev->next = second;
        first->next = second->next;
        second->next = first;
        prev = first;
        head = first->next;
    }
    return dummy->next;
}

template <typename T>
ListNode<T>* ListNodeOperations<T>::deleteDuplicates() {
    ListNode<T>* dummy = new ListNode<T>(0);
    dummy->next = head;
    ListNode<T>* prev = dummy;
    ListNode<T>* curr = head;
    while (curr) {
        bool isDuplicate = false;
        while (curr->next && curr->val == curr->next->val) {
            curr = curr->next;
            isDuplicate = true;
        }
        if (isDuplicate) {
            prev->next = curr->next;
        } else {
            prev = prev->next;
        }
        curr = curr->next;
    }
    return dummy->next;
}

template <typename T>
ListNode<T>* ListNodeOperations<T>::rotateRight(ListNode<T>* head, int k) {
    if (!head || k == 0) return head;

    ListNode<T>* old_tail = head;
    int n;
    for (n = 1; old_tail->next; n++) {
        old_tail = old_tail->next;
    }

    old_tail->next = head;

    int new_head_index = n - k % n;
    ListNode<T>* new_tail = head;
    for (int i = 1; i < new_head_index; i++) {
        new_tail = new_tail->next;
    }

    ListNode<T>* new_head = new_tail->next;
    new_tail->next = nullptr;

    return new_head;
}

template <typename T>
ListNode<T>* ListNodeOperations<T>::deleteDuplicates2(ListNode<T>* head) {
    ListNode<T>* dummy = new ListNode<T>(0);
    dummy->next = head;
    ListNode<T>* prev = dummy;
    ListNode<T>* curr = head;

    while (curr) {
        bool hasDuplicates = false;
        while (curr->next && curr->val == curr->next->val) {
            curr = curr->next;
            hasDuplicates = true;
        }
        if (hasDuplicates) {
            prev->next = curr->next;
        } else {
            prev = prev->next;
        }
        curr = curr->next;
    }
    return dummy->next;
}

template <typename T>
ListNode<T>* ListNodeOperations<T>::partition(ListNode<T>* head, T x) {
    ListNode<T> less_dummy(0), greater_dummy(0);
    ListNode<T>* less = &less_dummy;
    ListNode<T>* greater = &greater_dummy;

    while (head) {
        if (head->val < x) {
            less->next = head;
            less = less->next;
        } else {
            greater->next = head;
            greater = greater->next;
        }
        head = head->next;
    }

    greater->next = nullptr;
    less->next = greater_dummy.next;

    return less_dummy.next;
}

// Pruebas
int main() {
    ListNodeOperations<int> l;
    
    // Pruebas básicas
    l.pushfront(1);
    l.pushfront(2);
    l.pushback(3);
    l.display();  // 2, 1, 3
    
    l.popfront();
    l.display();  // 1, 3
    
    l.popback();
    l.display();  // 1

    l.pushback(2);
    l.pushback(3);
    l.pushback(4);
    l.display();  // 1, 2, 3, 4
    
    l.swap(1, 3);
    l.display();  // 1, 4, 3, 2

    l.removeElements(3);
    l.display();  // 1, 4, 2

    l.reverse();
    l.display();  // 2, 4, 1

    cout << "Front: " << l.front() << endl;  // 2
    cout << "Back: " << l.back() << endl;    // 1
    cout << "Size: " << l.size() << endl;    // 3

    l.selectionSort();
    l.display();  // 1, 2, 4

    l.clear();
    l.display();  // (Vacío)

    return 0;
}
