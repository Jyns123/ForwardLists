#include <queue>
#include <string>

using namespace std;

class RecentCounter {
private:
    queue<int> cola;  

public:
    RecentCounter() {
    }
    
    int ping(int t) {
        cola.push(t);
        
        while (!cola.empty() && cola.front() < t - 3000) {
            cola.pop();
        }
        
        return cola.size();
    }
};

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

    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        int count0{}, count1{};
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (*it == 0) count0++;
            else count1++;
        }

        for (auto it = sandwiches.begin(); it != sandwiches.end(); ++it) {
            if (*it == 0 && count0 == 0) {
                break;
            }
            if (*it == 1 && count1 == 0) {
                break;  
            }

            if (*it == 0) {
                count0--;  
            } else {
                count1--;  
            }
        }

        return count0 + count1;
    }

    int timeRequiredToBuy(vector<int>& tickets, int k) {
        queue<int> q;  
        int n = tickets.size(); 
        
        for (int i = 0; i < n; i++) {
            q.push(i);
        }
        
        int time = 0;  
        
        while (!q.empty()) {
            int idx = q.front();
            q.pop();
            
            tickets[idx]--;
            time++;  
            
            if (idx == k && tickets[idx] == 0) {
                break;
            }
            
            if (tickets[idx] > 0) {
                q.push(idx);
            }
        }
        
        return time;
    }

};
