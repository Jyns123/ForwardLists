#include <iostream>
#include <stack> 
#include <string>
#include <vector>
#include <queue>

using namespace std;

#define MAX 100

class MyQueue {
public:
    MyQueue() {
    }
    
    void push(int x) {
        stack1.push(x);
    }
    
    int pop() {
        moveStack1ToStack2();
        int top = stack2.top();
        stack2.pop();
        return top;
    }
    
    int peek() {
        moveStack1ToStack2();
        return stack2.top();
    }
    
    bool empty() {
        return stack1.empty() && stack2.empty();
    }

private:
    stack<int> stack1; 
    stack<int> stack2; 
    
    void moveStack1ToStack2() {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
    }
};


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class MyStack {
    
private:
    queue<int> q1; 
    queue<int> q2; 

public:
    MyStack() {}
    void push(int x) {
        q2.push(x);
        
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        
        swap(q1, q2);
    }
    
    int pop() {
        if (q1.empty()) {
        }
        int top = q1.front();
        q1.pop();
        return top;
    }
    
    int top() {
        if (q1.empty()) {return -1;}
        return q1.front();
    }
    
    bool empty() {
        return q1.empty();
    }
};

class MinStack {
private:
    ::stack<int> stack;       
    ::stack<int> minStack;    
    
public:
    MinStack() {
    }
    
    void push(int val) {
        stack.push(val);
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val);
        }
    }
    
    void pop() {
        if (stack.empty()) {
            return;
        }
        int topValue = stack.top();
        stack.pop();
        if (topValue == minStack.top()) {
            minStack.pop();
        }
    }
    
    int top() {
        if (stack.empty()) {
            return -1;  
        }
        return stack.top();
    }
    
    int getMin() {
        if (minStack.empty()) {
            return -1;  
        }
        return minStack.top();
    }
};

template <typename T>
class Stack {
private:
    T stack[MAX];  
    int topIndex;  

public:
    Stack() {
        topIndex = -1;
    }

    void push(T value) {
        if (topIndex >= MAX - 1) {
            std::cout << "Stack overflow. Cannot push " << value << std::endl;
        } else {
            stack[++topIndex] = value;
        }
    }

    void pop() {
        if (topIndex < 0) {
            std::cout << "Stack underflow. No elements to pop." << std::endl;
        } else {
            topIndex--;
        }
    }

    T top() {
        if (topIndex < 0) {
            std::cout << "Stack is empty." << std::endl;
            return T(); 
        } else {
            return stack[topIndex];
        }
    }

    bool empty() {
        return (topIndex < 0);
    }

    bool isValid(string s) {
        Stack<char> ss; 
        for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
            char curr = *it;

            if (curr == '(' || curr == '{' || curr == '[') {
                ss.push(curr);
            } 
            else {
                if (ss.empty()) return false;

                if (ss.top() == '(' && curr != ')') return false;
                if (ss.top() == '{' && curr != '}') return false;
                if (ss.top() == '[' && curr != ']') return false;

                ss.pop();
            }
        }
        return ss.empty();
    }
    
    int longestValidParentheses(const string s) {
        Stack<int> ss;
        int lenght = 0; 
        int invIndex = -1; 

        for (int i = 0; i < s.size(); ++i) {
            char curr = s[i];

            if (curr == '(') {
                ss.push(i);
            } else {
                if (ss.empty()) {
                    invIndex = i;
                } else {
                    ss.pop();
                    if (ss.empty()) {
                        lenght = max(lenght, i - invIndex);
                    } else {
                        lenght = max(lenght, i - ss.top());
                    }
                }
            }
        }
        return lenght;
    }

    string simplifyPath(string path) {
        stack<string> directorios;
        string caracteres;
        string resultado;

        for (char c : path) {
            if (c == '/') {
                if (!caracteres.empty()) {
                    if (caracteres == "..") {
                        if (!directorios.empty()) {
                            directorios.pop();
                        }
                    } else if (caracteres != "." && !caracteres.empty()) {
                        directorios.push(caracteres);
                    }
                    caracteres.clear();
                }
            } else {
                caracteres += c;
            }
        }

        if (!caracteres.empty()) {
            if (caracteres == "..") {
                if (!directorios.empty()) {
                    directorios.pop();
                }
            } else if (caracteres != "." && !caracteres.empty()) {
                directorios.push(caracteres);
            }
        }

        while (!directorios.empty()) {
            resultado = "/" + directorios.top() + resultado;
            directorios.pop();
        }

        return resultado.empty() ? "/" : resultado;
    }
    
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> resultado;
        stack<TreeNode*> pila;
        TreeNode* nodoActual = root;
        
        while (nodoActual != nullptr || !pila.empty()) {
            while (nodoActual != nullptr) {
                pila.push(nodoActual);
                nodoActual = nodoActual->left;
            }
            
            nodoActual = pila.top();
            pila.pop();
            resultado.push_back(nodoActual->val);
            
            nodoActual = nodoActual->right;
        }
        
        return resultado;
    }

    void flatten(TreeNode* root) {
        if (root == nullptr) return;
        flatten(root->left);
        flatten(root->right);
        
        if (root->left) {
            TreeNode* derecho = root->right;
            TreeNode* izquierdo = root->left;
            
            while (izquierdo->right) {
                izquierdo = izquierdo->right;
            }
            
            izquierdo->right = derecho; 
            root->right = root->left;   
            root->left = nullptr;      
        }
    }

    void mergeLists(ListNode* first, ListNode* second) {
        ListNode* temp1;
        ListNode* temp2;

        while (second != nullptr) {
            temp1 = first->next;
            temp2 = second->next;

            first->next = second;
            second->next = temp1;

            first = temp1;
            second = temp2;
        }
    }

    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        ListNode* next = nullptr;

        while (curr != nullptr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        return prev;
    }

    ListNode* findMiddle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return;
        }

        ListNode* mid = findMiddle(head);
        ListNode* secondHalf = mid->next;
        mid->next = nullptr; 

        secondHalf = reverseList(secondHalf);

        mergeLists(head, secondHalf);
    }

    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        if (!root) return result;
        
        stack<TreeNode*> s;
        s.push(root);
        
        while (!s.empty()) {
            TreeNode* node = s.top();
            s.pop();
            result.push_back(node->val);
            
            if (node->right != nullptr) {
                s.push(node->right);
            }
            if (node->left != nullptr) {
                s.push(node->left);
            }
        }
        
        return result;
    }

    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        if (!root) return result;
        
        stack<TreeNode*> s;
        TreeNode* ult = nullptr;
        TreeNode* current = root;
        
        while (current != nullptr || !s.empty()) {
            if (current != nullptr) {
                s.push(current);
                current = current->left;
            } else {
                TreeNode* topNode = s.top();
                if (topNode->right != nullptr && topNode->right != ult) {
                    current = topNode->right;
                } else {
                    result.push_back(topNode->val);
                    ult = topNode;
                    s.pop();
                }
            }
        }
        
        return result;
    }

    int performOperation(int num1, int num2, const string& op) {
        if (op == "+") return num1 + num2;
        if (op == "-") return num1 - num2;
        if (op == "*") return num1 * num2;
        if (op == "/") return num1 / num2; 
        return -1;
    }
    bool isOperator(const string& token) {
        return token == "+" || token == "-" || token == "*" || token == "/";
    }
    int evalRPN(vector<string>& tokens) {
        stack<int> stackint; 
        
        for (const string& token : tokens) {
            if (isOperator(token)) {
                int num2 = stackint.top(); stackint.pop();
                int num1 = stackint.top(); stackint.pop();
                
                int result = performOperation(num1, num2, token);
                stackint.push(result);
            } else {
                stackint.push(stoi(token));
            }
        }
        
        return stackint.top();
    }

    bool isPalindrome(ListNode* head) {
        stack<int> st;
        ListNode* temp = head;
        
        while (temp) {
            st.push(temp->val);
            temp = temp->next;
        }
        
        temp = head;
        while (temp) {
            if (st.top() != temp->val) {
                return false;  
            }
            st.pop();
            temp = temp->next;
        }
        
        return true; 
    }


    int calculate(string s) {
        stack<int> valores;     
        stack<char> operadores; 
        int numeroActual = 0;   
        bool construyendoNumero = false; 

        auto precedencia = [](char op) {
            if (op == '+' || op == '-') return 1;
            if (op == '*' || op == '/') return 2;
            return 0;
        };

        auto evaluar = [](int num1, int num2, char op) {
            if (op == '+') return num1 + num2;
            if (op == '-') return num1 - num2;
            if (op == '*') return num1 * num2;
            if (op == '/') return num1 / num2;
            return 0;
        };

        for (char ch : s) {
            if (ch >= '0' && ch <= '9') {
                numeroActual = numeroActual * 10 + (ch - '0');
                construyendoNumero = true;
            } else {
                if (construyendoNumero) {
                    valores.push(numeroActual);
                    numeroActual = 0;
                    construyendoNumero = false;
                }

                if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                    
                    while (!operadores.empty() && precedencia(operadores.top()) >= precedencia(ch)) {
                        int num2 = valores.top(); valores.pop();
                        int num1 = valores.top(); valores.pop();
                        char op = operadores.top(); operadores.pop();
                        valores.push(evaluar(num1, num2, op));
                    }
                    operadores.push(ch);
                }
            }
        }

        if (construyendoNumero) {
            valores.push(numeroActual);
        }

        while (!operadores.empty()) {
            int num2 = valores.top(); valores.pop();
            int num1 = valores.top(); valores.pop();
            char op = operadores.top(); operadores.pop();
            valores.push(evaluar(num1, num2, op));
        }

        return valores.top();
    }


    string removeKdigits(string num, int k) {
        string resultado = "";          
        for (char digito : num) {
            while (!resultado.empty() && k > 0 && resultado.back() > digito) {
                resultado.pop_back(); 
                k--;  
            }
            if (!resultado.empty() || digito != '0') {
                resultado.push_back(digito);
            }
        }
        
        while (k > 0 && !resultado.empty()) {
            resultado.pop_back();
            k--;
        }
        
        if (resultado.empty()) {
            return "0";
        }
        
        return resultado;
    }



};

int main() {
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);

    cout << "Top element is: " << s.top() << endl;

    s.pop();
    cout << "Top element after pop is: " << s.top() << endl;

    Stack<char> sc;
    string input = "{[()]}}";
    if (sc.isValid(input)) {
        cout << "La cadena es válida." << endl;
    } else {
        cout << "La cadena no es válida." << endl;
    }

    return 0;
}
