#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class ListNodeOperations {
private:
    ListNode* head;

public:
    ListNodeOperations() : head(nullptr) {}

    // Manipulación básica
    void pushfront(int val);
    void popfront();
    void pushback(int val);
    void popback();
    void connect(int val);
    void swap(int index1, int index2);
    void removeElements(int target);
    void reverse();
    void clear();
    void display();
    //Selection sort
    void selectionSort();
    // Acceso
    int size();
    int front();
    int back();
    int& operator[](int index);
    ListNode* getHead();

    // Utilidades y operaciones adicionales
    bool isCycle();
    bool empty();
    int howmanyonloop();
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);
    ListNode* removeNthFromEnd(ListNode* head, int n);
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2);
    int GCD(int val1, int val2);
    ListNode* insertGreatestCommonDivisors();
    ListNode* swapPairs();
    ListNode* deleteDuplicates();
    ListNode* rotateRight(ListNode* head, int k);
    ListNode* deleteDuplicates2(ListNode* head);
    ListNode* partition(ListNode* head, int x);
};

// Implementación de funciones

// Manipulación básica
void ListNodeOperations::pushfront(int val) {
    head = new ListNode(val, head);
}

void ListNodeOperations::popfront() {
    if (head) {
        ListNode* curr = head;
        head = head->next;
        delete curr;
    }
}

void ListNodeOperations::pushback(int val) {
    if (!head) {
        head = new ListNode(val);
        return;
    }
    ListNode* curr = head;
    while (curr->next) {
        curr = curr->next;
    }
    curr->next = new ListNode(val);
}

void ListNodeOperations::popback() {
    if (!head) {
        return;
    }
    if (!head->next) {
        delete head;
        head = nullptr;
        return;
    }
    ListNode* curr = head;
    while (curr->next->next) {
        curr = curr->next;
    }
    delete curr->next;
    curr->next = nullptr;
}

void ListNodeOperations::connect(int val) {
    if (!head) {
        head = new ListNode(val);
        return;
    }
    ListNode* curr = head;
    while (curr->next) {
        curr = curr->next;
    }
    curr->next = head; 
}

void ListNodeOperations::swap(int index1, int index2) {
    if (index1 < 0 || index2 < 0 || index1 == index2) {
        return;
    }

    ListNode* prev1 = nullptr;
    ListNode* curr1 = head;
    for (int i = 0; i < index1 && curr1; i++) {
        prev1 = curr1;
        curr1 = curr1->next;
    }

    ListNode* prev2 = nullptr;
    ListNode* curr2 = head;
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
        ListNode* temp = curr2->next;
        curr2->next = curr1->next;
        curr1->next = temp;
    }
}

void ListNodeOperations::removeElements(int target) {
    while (head && head->val == target) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }

    ListNode* curr = head;
    while (curr && curr->next) {
        if (curr->next->val == target) {
            ListNode* temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
        } else {
            curr = curr->next;
        }
    }
}

void ListNodeOperations::reverse() {
    ListNode* prev = nullptr;
    ListNode* current1 = head;
    ListNode* siguiente = nullptr;

    while (current1 != nullptr) {
        siguiente = current1->next;
        current1->next = prev;
        prev = current1;
        current1 = siguiente;
    }
    head = prev;
}

void ListNodeOperations::clear() {
    if (!head) {
        return;
    }
    ListNode* curr1 = head;
    while (curr1) {
        ListNode* curr2 = curr1->next; 
        delete curr1;                   
        curr1 = curr2;                  
    }
    head = nullptr;
}

void ListNodeOperations::display() {
    ListNode* curr = head;
    while (curr) {
        cout << curr->val;
        if (curr->next) {
            cout << ", ";
        }
        curr = curr->next;
    }
    cout << endl;
}

//
void ListNodeOperations::selectionSort() {
    if (!head || !head->next) return;

    ListNode* curr = head;
    while (curr) {
        ListNode* minNode = curr;
        ListNode* nextNode = curr->next;

        while (nextNode) {
            if (nextNode->val < minNode->val) {
                minNode = nextNode;
            }
            nextNode = nextNode->next;
        }

        // Intercambia los valores
        swap(curr->val, minNode->val);
        curr = curr->next;
    }
}

// Acceso
int ListNodeOperations::size() {
    ListNode* curr = head;
    int size = 0;
    while (curr) {
        curr = curr->next;
        size++;
    }
    return size;
}

int ListNodeOperations::front() {
    if (!head) {
        throw runtime_error("La lista está vacía");
    }
    return head->val;
}

int ListNodeOperations::back() {
    if (!head) {
        throw runtime_error("La lista está vacía");
    }
    ListNode* curr = head;
    while (curr->next) {
        curr = curr->next;
    }
    return curr->val;
}

int& ListNodeOperations::operator[](int index) {
    if (index < 0) {
        throw out_of_range("Índice no válido");
    }

    ListNode* current = head;
    int currentIndex = 0;

    while (current != nullptr && currentIndex < index) {
        current = current->next;
        currentIndex++;
    }

    if (current == nullptr) {
        throw out_of_range("Índice fuera de rango");
    }

    return current->val;
}

ListNode* ListNodeOperations::getHead() {
    return head;
}

// Utilidades y operaciones adicionales
bool ListNodeOperations::isCycle() {
    if (!head || !head->next) {
        return false;
    }
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

bool ListNodeOperations::empty() {
    return head == nullptr;
}

int ListNodeOperations::howmanyonloop() {
    if (!isCycle()) {
        return 0;
    }

    ListNode* slow = head;
    ListNode* fast = head;

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
    ListNode* current = slow->next;
    while (current != slow) {
        count++;
        current = current->next;
    }

    return count;
}

ListNode* ListNodeOperations::addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* dummyHead = new ListNode(0);
    ListNode* curr = dummyHead;
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
        curr->next = new ListNode(sum % 10);
        curr = curr->next;
    }

    ListNode* result = dummyHead->next;
    delete dummyHead;
    return result;
}

ListNode* ListNodeOperations::removeNthFromEnd(ListNode* head, int n) {
    if (!head) return nullptr;
    ListNode* dummy = new ListNode(0, head);
    ListNode* curr = dummy;
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
    ListNode* temp = curr->next;
    curr->next = curr->next->next;
    delete temp;

    ListNode* newHead = dummy->next;
    delete dummy;

    return newHead;
}

ListNode* ListNodeOperations::mergeTwoLists(ListNode* list1, ListNode* list2) {
    if (!list1) {
        return list2;
    }
    if (!list2) {
        return list1;
    }

    ListNode* dummy = new ListNode();
    ListNode* curr = dummy;

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

    ListNode* mergedList = dummy->next;
    delete dummy; 
    return mergedList;
}

int ListNodeOperations::GCD(int val1, int val2) {
    if(val2 > val1){
        return GCD(val2, val1);
    }
    if(val1*val2==0){
        return 0;
    }
    while (val2 != 0) {
        int temp = val2;
        val2 = val1 % val2;
        val1 = temp;
    }
    return val1;
}

ListNode* ListNodeOperations::insertGreatestCommonDivisors() {
    if (!head) {
        return nullptr;
    }
    ListNode* curr = head;
    while (curr && curr->next) {
        int val1 = curr->val;
        int val2 = curr->next->val;
        int gcd = GCD(val1, val2);
        ListNode* temp = new ListNode(gcd);
        temp->next = curr->next;
        curr->next = temp;
        curr = temp->next;
    }
    return head;
}

ListNode* ListNodeOperations::swapPairs() {
    if (!head || !head->next) {
        return head;
    }
    
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* prev = dummy;
    
    while (head && head->next) {
        ListNode* first = head;
        ListNode* second = head->next;
        
        prev->next = second;
        first->next = second->next;
        second->next = first;
        
        prev = first;
        head = first->next;
    }
    
    ListNode* newHead = dummy->next;
    delete dummy;
    return newHead;
}

ListNode* ListNodeOperations::deleteDuplicates() {
    if (!head) return nullptr;
    
    ListNode* curr = head;
    while (curr && curr->next) {
        if (curr->val == curr->next->val) {
            ListNode* temp = curr->next;
            curr->next = temp->next;
            delete temp;
        } else {
            curr = curr->next;
        }
    }
    return head;
}

ListNode* ListNodeOperations::rotateRight(ListNode* head, int k) {
    if (!head) {
        return head;
    }

    ListNode* curr = head;
    int length = 1;
    while (curr->next) {
        curr = curr->next;
        length++;
    }

    k = k % length;
    if (k == 0) {
        return head; 
    }

    ListNode* tail = head;
    for (int i = 1; i < length - k; i++) {
        tail = tail->next;
    }

    ListNode* newHead = tail->next; 
    tail->next = nullptr; 
    curr->next = head; 

    return newHead;

}
ListNode* ListNodeOperations::deleteDuplicates2(ListNode* head) {
    if (!head || !head->next) return head;

    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* prev = dummy;

    while (prev->next) {
        ListNode* curr = prev->next;
        bool isDuplicate = false;

        while (curr->next && curr->val == curr->next->val) {
            ListNode* temp = curr->next;
            curr->next = curr->next->next;  
            delete temp; 
            isDuplicate = true;
        }

        if (isDuplicate) {
            prev->next = curr->next;
            delete curr;
        } else {
            prev = prev->next;
        }
    }

    ListNode* newHead = dummy->next;
    delete dummy;  
    return newHead;
}

ListNode* ListNodeOperations::partition(ListNode* head, int x) {
    if (!head || !head->next) return head;

    ListNode* lessHead = new ListNode(0); 
    ListNode* greaterHead = new ListNode(0); 
    ListNode* less = lessHead; 
    ListNode* greater = greaterHead; 

    ListNode* curr = head;
    while (curr) {
        if (curr->val < x) {
            less->next = curr;
            less = less->next;
        } else {
            greater->next = curr;
            greater = greater->next;
        }
        curr = curr->next; 
    }

    greater->next = nullptr; 
    less->next = greaterHead->next; 

    ListNode* newHead = lessHead->next; 
    delete lessHead; 
    delete greaterHead; 

    return newHead;
}



int main() {
    ListNodeOperations list;

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

    list.reverse();
    cout << "List after reverse operation: ";
    list.display();

    list.removeElements(5);
    cout << "List after removeElements operation (removing 5): ";
    list.display();

    // Insert GCD values
    list.insertGreatestCommonDivisors();
    cout << "List after insertGreatestCommonDivisors operation: ";
    list.display();

    // Test swapPairs
    ListNode* swappedPairsList = list.swapPairs();
    cout << "List after swapPairs operation: ";
    while (swappedPairsList) {
        cout << swappedPairsList->val << " ";
        swappedPairsList = swappedPairsList->next;
    }
    cout << endl;

    // Test deleteDuplicates
    ListNode* l1 = new ListNode(1, new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(3)))));
    ListNode* uniqueList = list.deleteDuplicates();
    cout << "Result of deleteDuplicates: ";
    while (uniqueList) {
        cout << uniqueList->val << " ";
        uniqueList = uniqueList->next;
    }
    cout << endl;

    // Clean up
    list.clear();

    // Test removeNthFromEnd
    ListNode* l2 = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    ListNodeOperations ops;
    ListNode* result = ops.removeNthFromEnd(l2, 2);
    cout << "List after removeNthFromEnd operation (removing 2nd from end): ";
    while (result) {
        cout << result->val << " ";
        result = result->next;
    }
    cout << endl;

    // Test rotateRight
    ListNode* l3 = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    ListNode* rotated = ops.rotateRight(l3, 2);
    cout << "List after rotateRight operation (rotate by 2): ";
    while (rotated) {
        cout << rotated->val << " ";
        rotated = rotated->next;
    }
    cout << endl;

    // Clean up
    list.clear();
    return 0;
}

