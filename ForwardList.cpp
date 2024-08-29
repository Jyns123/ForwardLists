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
    ListNode* swapPairs(ListNode* head);
    ListNode* deleteDuplicates(ListNode* head);

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
    if (index1 < 0 || index2 < 0) {
        return;
    }

    ListNode* curr1 = head;
    ListNode* curr2 = head;

    for (int i = 0; i < index1 && curr1; i++) {
        curr1 = curr1->next;
    }

    for (int i = 0; i < index2 && curr2; i++) {
        curr2 = curr2->next;
    }

    if (curr1 && curr2) {
        int temp = curr1->val;
        curr1->val = curr2->val;
        curr2->val = temp;
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

    while(current1 != nullptr) {
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
        throw out_of_range("no negativo");
    }

    ListNode* current = head;
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

int ListNodeOperations::GCD(int val1, int val2) { // 40 55 
    if(val2 > val1){
        return GCD(val2, val1);
    }
    if(val1*val2==0){
        return 0;
    }
//55 40
    while (val2 != 0) {
        int temp = val2;// temp = 40                //temp = 15         //temp = 10      //temp=5
        val2 = val1 % val2; // 55%40, val2 = 15     //val2 = 40%15= 10  //val2 = 15%10=5 //val2 = 10%5 = 0
        val1 = temp;//val1,55 = 40                  //val1 =15          //val1 = 10      //val1 = 5  
    }
    return val1;
}

ListNode* ListNodeOperations::insertGreatestCommonDivisors() {
    if (!head) {
        return nullptr;
    }
    ListNode* dummy = head;
    ListNode* curr = head;
    while (curr && curr->next) {
        int val1 = curr->val;
        int val2 = curr->next->val;
        while (val2 != 0) {
            int temp = val2;
            val2 = val1 % val2;
            val1 = temp;
        }
        ListNode* temp = new ListNode(val1);
        temp->next = curr->next;
        curr->next = temp;
        curr = temp->next;
    }
    return dummy;
}

ListNode* ListNodeOperations::swapPairs(ListNode* head){
    if(!head){
        return nullptr;
    }
    ListNode* dummy = head;
    ListNode* curr = head;
    while (curr && curr->next) {
        swap(curr->val, curr->next->val);
        curr = curr->next->next;
    }
    return dummy;
}

ListNode* ListNodeOperations::deleteDuplicates(ListNode* head){
    if(!head){
        return nullptr;
    }
    if(!head->next){
        return head;
    }
    ListNode* curr = head;
    ListNode* dummy = head;

    while(curr->next){
        if(curr->val==curr->next->val){
            ListNode* temp = curr -> next;
            curr -> next = temp -> next;
            delete temp;
            curr = curr -> next;
        }
    }
    return dummy;
}


// Pruebas en main
int main() {
    ListNode* l1 = new ListNode(1, new ListNode(1, new ListNode(1, new ListNode(2))));
    ListNode* result = list.deleteDuplicates(l1);
    cout << "Result of deleteDuplicates: ";
    while (result) {
        cout << result->val << " ";
        result = result->next;
    }
    cout << endl;



/*
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
    ListNode* l1 = new ListNode(2, new ListNode(4, new ListNode(3)));
    ListNode* l2 = new ListNode(5, new ListNode(6, new ListNode(4)));
    ListNode* result = list.addTwoNumbers(l1, l2);
    cout << "Result of addTwoNumbers: ";
    while (result) {
        cout << result->val << " ";
        result = result->next;
    }
    cout << endl;

    // Test mergeTwoLists
    ListNode* list1 = new ListNode(1, new ListNode(3, new ListNode(5)));
    ListNode* list2 = new ListNode(2, new ListNode(4, new ListNode(6)));
    ListNode* merged = list.mergeTwoLists(list1, list2);
    cout << "Merged list: ";
    while (merged) {
        cout << merged->val << " ";
        merged = merged->next;
    }
    cout << endl;

    // Test removeNthFromEnd
    ListNode* listToRemove = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    ListNode* newHead = list.removeNthFromEnd(listToRemove, 2);
    cout << "List after removing 2nd from end: ";
    while (newHead) {
        cout << newHead->val << " ";
        newHead = newHead->next;
    }
    cout << endl;

    // Clean up
    list.clear();
*/
    return 0;
}
