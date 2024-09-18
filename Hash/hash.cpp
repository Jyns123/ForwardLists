#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
  
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> numandindex;
        vector<int> sol(2);  
        for(int i = 0; i < nums.size(); i++) {
            int resta = target - nums[i];
            if (numandindex.find(resta) != numandindex.end()) {
                sol[0] = numandindex[resta];
                sol[1] = i;
                return sol; 
            }
            numandindex[nums[i]] = i;
        }
        return {}; 
    }

    int romanToInt(string s) {
        unordered_map<char, int> romanandnormal = {{'I', 1},{'V', 5}, {'X', 10},
        {'L', 50}, {'C', 100}, {'D', 500},{'M', 1000}
        };
        auto sol = 0;
        for(auto i = 0; i < s.size(); i++){
            if(romanandnormal[s[i]]>=romanandnormal[s[i+1]]){
                sol += romanandnormal[s[i]];
            }
            else{
                sol -= romanandnormal[s[i]];
            }
        }
        return sol;

    }

    bool hasCycle(ListNode *head) {
        if(!head){
            return false;
        }
        map<ListNode*, bool> ListMap;
        ListNode* curr = head;
        while(curr){
            if(ListMap[curr] == true){
                return true;
            }
            ListMap[curr] = true;
            curr = curr -> next;
        }
        return false;
    }

};