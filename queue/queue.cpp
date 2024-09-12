#include <queue>
#include <string>

using namespace std;


class MyQueue {
private:
    queue<int> q;  
public:
    void push(int x) {
        q.push(x);
    }

    int pop() {
        if (!q.empty()) {
            int frontElement = q.front();
            q.pop();
            return frontElement;
        }
        return -1; 
    }

    int peek() {
        if (!q.empty()) {
            return q.front();
        }
        return -1; 
    }

    bool empty() {
        return q.empty();
    }


    int firstUniqChar(string s) {
        int frecuencias[26] = {0};

        for (char c : s) {
            frecuencias[c - 'a']++;
        }
        
        for (int i = 0; i < s.length(); ++i) {
            if (frecuencias[s[i] - 'a'] == 1) {
                return i; 
            }
        }
        
        return -1;
    }

};
