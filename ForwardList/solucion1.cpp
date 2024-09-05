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
    ListNode* sol1(ListNode* head, int val);

};

ListNode* ListNodeOperations::sol1(ListNode* head, int val){
    while (head && head->val == val) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }

    ListNode* curr = head;
    while (curr && curr->next) {
        if (curr->next->val == val) {
            ListNode* temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
        } else {
            curr = curr->next;
        }
    }
    
    return head;
}

int main(){
    ListNode* l1 = new ListNode(7, new ListNode(7, new ListNode(7, new ListNode(7))));
    ListNodeOperations ops;

    ListNode* list = ops.sol1(l1, 7);
    cout << "sol1: ";
    while (list) {
        cout << list->val << " ";
        list = list->next;
    }
    cout << endl;
    return 0;
}