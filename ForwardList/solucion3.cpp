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
    ListNode* sol3(ListNode* head);

};


ListNode* ListNodeOperations::sol3(ListNode* head) {
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



int main(){

    ListNode* l1 = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4))));
    ListNodeOperations ops;

    ListNode* list = ops.sol3(l1);
    cout << "sol3: ";
    while (list) {
        cout << list->val << " ";
        list = list->next;
    }
    cout << endl;
    return 0;
}