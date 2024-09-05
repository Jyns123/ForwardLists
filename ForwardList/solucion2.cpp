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
    ListNode* sol2(ListNode* head);

};

int gcd(int val1, int val2) {
    if(val2 > val1){
        return gcd(val2, val1);
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

ListNode* ListNodeOperations::sol2(ListNode* head) {
    if (!head) {
        return nullptr;
    }
    ListNode* curr = head;
    while (curr && curr->next) {
        int val1 = curr->val;
        int val2 = curr->next->val;
        int GCD = gcd(val1, val2);
        ListNode* temp = new ListNode(GCD);
        temp->next = curr->next;
        curr->next = temp;
        curr = temp->next;
    }
    return head;
}



int main(){

    // ListNode* l1 = new ListNode(45, new ListNode(90, new ListNode(23, new ListNode(25, new ListNode(50)))));
    ListNode* l1 = new ListNode(18, new ListNode(6, new ListNode(10, new ListNode(3))));

    ListNodeOperations ops;

    ListNode* list = ops.sol2(l1);
    cout << "sol2: ";
    while (list) {
        cout << list->val << " ";
        list = list->next;
    }
    cout << endl;
    return 0;
}