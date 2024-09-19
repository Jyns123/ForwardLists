#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>
#include <sstream>
#include <map>
#include <string>
#include <list>
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

    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(!headA || !headB) {
            return nullptr;
        }

        map<ListNode*, bool> ListMap;

        ListNode* curr1 = headA;
        while (curr1) {
            ListMap[curr1] = true;
            curr1 = curr1->next;
        }

        ListNode* curr2 = headB;
        while (curr2) {
            if (ListMap[curr2]) {
                return curr2;  
            }
            curr2 = curr2->next;
        }

        return nullptr;
    }

    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> countMap;
        for(auto i = 0; i < nums.size(); i++) {
            countMap[nums[i]]++; 
            if(countMap[nums[i]] > nums.size() / 2) {
                return nums[i];  
            }
        }
        return {}; 
    }

    bool isHappy(int n) {
        map<int, bool> ListMap;  

        while (n != 1) {
            if (ListMap.find(n) != ListMap.end()) {
                return false;
            }

            ListMap[n] = true;  

            vector<int> digitos;
            while (n > 0) {
                int digit = n % 10;  
                digitos.push_back(digit);  
                n /= 10;  
            }

            n = 0;  
            for (int digit : digitos) {
                n += digit * digit;
            }
        }

        return true; 
    }

    bool isIsomorphic(string s, string t) {
        if (s.length() != t.length()) {
            return false;
        }

        map<char, char> SandT; 
        map<char, char> TandS; 

        for (int i = 0; i < s.length(); i++) {
            char s_char = s[i];
            char t_char = t[i];

            if (SandT.find(s_char) != SandT.end()) {
                if (SandT[s_char] != t_char) {
                    return false;
                }
            } else {
                SandT[s_char] = t_char;
            }

            if (TandS.find(t_char) != TandS.end()) {
                if (TandS[t_char] != s_char) {
                    return false;
                }
            } else {
                TandS[t_char] = s_char;
            }
        }

        return true;  
    }

    bool containsDuplicate(vector<int>& nums) {

        unordered_map<int, bool> Rep;

        for(int i = 0; i < nums.size(); i++) {
            if(Rep.find(nums[i]) != Rep.end()) {
                return true;  
            }
            Rep[nums[i]] = true;
        }

        return false;

    }

    bool containsNearbyDuplicate(std::vector<int>& nums, int k) {
        unordered_map<int, int> lastindex;  

        for (int i = 0; i < nums.size(); i++) {
            int num = nums[i];

            if (lastindex.find(num) != lastindex.end() && i - lastindex[num] <= k) {
                return true;  
            }

            lastindex[num] = i;
        }

        return false;  
    }

    bool isAnagram(string s, string t) {
        if(s.size()!=t.size()){
            return false;
        }
        int size = s.size();
        unordered_map<char, int> letterscount;
        unordered_map<char, int> letterscount2;

        for (int i = 0; i < size; i++) {
            if (letterscount.find(s[i]) == letterscount.end()) {
                letterscount[s[i]] = 0;
            }
            letterscount[s[i]]++;
        }

        for (int i = 0; i < size; i++) {
            if (letterscount2.find(t[i]) == letterscount2.end()) {
                letterscount2[t[i]] = 0;
            }
            letterscount2[t[i]]++;
        }

        if(letterscount==letterscount2){
            return true;
        } 
        return false;
    }

    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, bool> numMap;

        for (int num : nums) {
            numMap[num] = true;
        }

        for (int i = 0; i <= n; ++i) {
            if (numMap.find(i) == numMap.end()) {
                return i;
            }
        }

        return {};
    }

    bool wordPattern(string pattern, string s) {
        map<char, string> charToWord;
        map<string, char> wordToChar;
        vector<string> sepwords;
        istringstream iss(s);
        string word;

        while (iss >> word) {
            sepwords.push_back(word);
        }

        if (sepwords.size() != pattern.size()) {
            return false;
        }

        for (int i = 0; i < pattern.size(); i++) {
            char pChar = pattern[i];
            string wWord = sepwords[i];

            if (charToWord.find(pChar) != charToWord.end()) {
                if (charToWord[pChar] != wWord) {
                    return false;
                }
            } else {
                charToWord[pChar] = wWord;
            }

            if (wordToChar.find(wWord) != wordToChar.end()) {
                if (wordToChar[wWord] != pChar) {
                    return false;
                }
            } else {
                wordToChar[wWord] = pChar;
            }
        }

        return true;
    }

    ListNode *detectCycle(ListNode *head) {
        if(!head){
            return nullptr;
        }
        ListNode *curr = head;
        unordered_map <ListNode*, bool> detCyc;
        while(curr){
            if(detCyc.find(curr)!=detCyc.end()){
                return curr;
            }
            detCyc[curr]=true;
            curr = curr->next;
        }
        return nullptr;
    }

    int lengthOfLongestSubstring(string s) {
        int maxLength = 0; 

        for (int i = 0; i < s.size(); i++) {
            unordered_map<char, bool> isRepeated; 
            int currentLength = 0; 

            for (int j = i; j < s.size(); j++) {
                char c = s[j];
                
                if (isRepeated[c]) {
                    break;
                }
                
                isRepeated[c] = true;
                currentLength++;
            }

            maxLength = max(maxLength, currentLength);
        }

        return maxLength;
    }
};

class LRUCache {
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }

    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1;
        }

        usage.erase(cache[key].second);
        usage.push_front(key);

        cache[key].second = usage.begin();

        return cache[key].first;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            usage.erase(cache[key].second);
        } else {
            if (cache.size() >= capacity) {
                int lruKey = usage.back(); 
                usage.pop_back();          
                cache.erase(lruKey);        
            }
        }

        usage.push_front(key);
        cache[key] = {value, usage.begin()};
    }

private:
    int capacity; 
    list<int> usage; 
    unordered_map<int, pair<int, list<int>::iterator>> cache; 
};
