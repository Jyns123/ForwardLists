#include <iostream>
using namespace std;
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
    Node(): prev(nullptr), val(0), next(nullptr){}
    Node(int _val): val(_val), prev(nullptr), next(nullptr){}
    Node(Node* _prev ,int _val): val(_val), prev(_prev), next(nullptr){}
    Node(int _val, Node* _next): val(_val), prev(nullptr), next(nullptr){}
    Node(Node* _prev,int _val, Node* _next): val(_val), prev(_prev), next(_next){}

};
class ListNodeOperations {
private:
    Node* head;
    Node* tail;


public:
    ListNodeOperations(): head(nullptr), tail(nullptr){};
    int front();
    int back();
    void push_front(int val);
    void push_back(int val);
    void pop_front();
    void pop_back();
    void insert(int val, int index);
    void remove(int index);
    int& operator[](int index);
    bool empty();
    int size();
    void clear();
    void reverse();
    ListNodeOperations& operator=(const ListNodeOperations& other);
 


};

int ListNodeOperations::front() {
    if (head != nullptr) {
        return head->val;
    }
    throw out_of_range("La lista está vacía");
}


int ListNodeOperations::back() {
    if (tail != nullptr) {
        return tail->val;
    }
    throw out_of_range("La lista está vacía");
}


void ListNodeOperations::push_front(int val){
    if(!head){
        head = tail = new Node(val);
    }
    else{
        Node* NewHead = new Node(val, head);
        head -> prev = NewHead;
        head = NewHead;
    }
}
void ListNodeOperations::push_back(int val){
    if(!head){
        head = tail = new Node(val);
    }
    else{
        Node* NewTail = new Node(tail, val);
        tail -> next = NewTail;
        tail = NewTail;
    }
}
void ListNodeOperations::pop_front(){
    if(!head){
        return;
    }
    else{
        Node* temp = head;
        head = head -> next;
        if (head) {
            head->prev = nullptr;
        }
        else{
            tail = nullptr;       
        }
        delete temp;
    }
}
void ListNodeOperations::pop_back(){
    if(!head){
        return;
    }
    else{
        Node* temp = tail;
        tail = tail -> prev;
        if (tail) {
            tail->next = nullptr;
        }
        else{
            head = nullptr;       
        }
        delete temp;
    }

}
void ListNodeOperations::insert(int val, int index) {
    if (index < 0 || index > size()) { 
        return;
    }
    if (index == 0) {
        push_front(val);
        return;
    }
    if (index == size()) {
        push_back(val);
        return;
    }

    Node* curr = head;
    int count = 0;
    while (count < index) {
        curr = curr->next;
        count++;
    }

    Node* NewNode = new Node(curr->prev, val, curr);
    curr->prev->next = NewNode;
    curr->prev = NewNode;
}



void ListNodeOperations::remove(int index) {
    if (index < 0 || index >= size()) {
        return;
    }

    if (index == 0) {
        pop_front();
        return;
    }
    if (index == size() - 1) {
        pop_back();
        return;
    }

    Node* curr = head;
    int count = 0;
    while (count < index) {
        curr = curr->next;
        count++;
    }

    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    delete curr;
}

int& ListNodeOperations::operator[](int index){
    if (index < 0) {
        throw out_of_range("Índice no válido");
    }

    Node* current = head;
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

bool ListNodeOperations::empty(){
    return head==nullptr;
}

int ListNodeOperations::size(){
    int count{};
    Node* curr = head;
        while(curr){
            curr = curr -> next;
            count++; 
        }
    return count;
}

void ListNodeOperations::clear() {
    while (!empty()) {
        pop_front();
    }
    head = tail = nullptr;
}

void ListNodeOperations::reverse() {
    if (!head) {
        return;
    }

    Node* curr = head;
    Node* temp = nullptr;

    while (curr) {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;

        curr = curr->prev; 
    }

    temp = head;
    head = tail;
    tail = temp;
}



/*

class Solution {
public:
    Node* flatten(Node* head) {
        if (!head) return nullptr;
        
        Node* curr = head;
        Node* tail = head;
        
        while (curr) {
            if (curr->child) {
                Node* child = curr->child;
                Node* childTail = child;
                
                while (childTail->next) {
                    childTail = childTail->next;
                }

                Node* nextcurNode = curr -> next;
                curr -> next = child;
                child -> prev = curr;
                curr -> child = nullptr;
                childTail->next = nextcurNode;

                if (nextcurNode != nullptr) {
                    nextcurNode->prev = childTail;
                }
            }
                

            curr = curr->next;
    }
        
        return head;
    }
};
*/


/*
struct Node {
    int key;
    int value;
    Node* prev;
    Node* next;
    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    int capacity;
    Node* head;
    Node* tail;

    void moveToFront(Node* node) {
        if (node == head) return;  
        if (node->prev) node->prev->next = node->next;
        if (node->next) node->next->prev = node->prev;

        if (node == tail) tail = node->prev;  
        node->next = head;
        node->prev = nullptr;
        if (head) head->prev = node;
        head = node;

        if (!tail) tail = head; 
    }

    void removeTail() {
        if (!tail) return;
        if (tail->prev) tail->prev->next = nullptr;
        Node* oldTail = tail;
        tail = tail->prev;
        if (!tail) head = nullptr;  
        delete oldTail;
    }

    Node* findNode(int key) {
        Node* current = head;
        while (current) {
            if (current->key == key) return current;
            current = current->next;
        }
        return nullptr; 
    }

public:
    LRUCache(int capacity) : capacity(capacity), head(nullptr), tail(nullptr) {}

    int get(int key) {
        Node* node = findNode(key);
        if (!node) return -1;  
        moveToFront(node);  
        return node->value;
    }

    void put(int key, int value) {
        Node* node = findNode(key);
        if (node) {
            node->value = value;
            moveToFront(node);
        } else {
            Node* newNode = new Node(key, value);
            if (capacity == 0) {
                removeTail();  
                capacity++;
            }
            if (head) {
                head->prev = newNode;
                newNode->next = head;
            } else {
                tail = newNode; 
            head = newNode;
            capacity--;
        }
    }
};*/

/*
#include <unordered_map>

struct Node {
    int key;
    int value;
    Node* prev;
    Node* next;
    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    int capacity;
    unordered_map<int, Node*> cache;  
    Node* head;  
    Node* tail;  

    void moveToFront(Node* node) {
        if (node == head) return;  

        if (node->prev) node->prev->next = node->next;
        if (node->next) node->next->prev = node->prev;
        
        if (node == tail) tail = node->prev;

        node->next = head;
        node->prev = nullptr;
        if (head) head->prev = node;
        head = node;

        if (!tail) tail = head;
    }

    void removeTail() {
        if (!tail) return;  
        cache.erase(tail->key);

        if (tail->prev) tail->prev->next = nullptr;
        Node* oldTail = tail;
        tail = tail->prev;
        
        if (!tail) head = nullptr;  
        
        delete oldTail;
    }

    void addToFront(Node* node) {
        node->next = head;
        node->prev = nullptr;

        if (head) head->prev = node;
        head = node;

        if (!tail) tail = head;  
    }

public:
    LRUCache(int capacity) : capacity(capacity), head(nullptr), tail(nullptr) {}

    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1; 
        }

        Node* node = cache[key];
        moveToFront(node);  
        return node->value;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            node->value = value;
            moveToFront(node);
        } else {
            Node* newNode = new Node(key, value);
            cache[key] = newNode; 
            addToFront(newNode);   

            if (cache.size() > capacity) {
                removeTail();
            }
        }
    }
};

*/

/*
struct Node {
    string url;
    Node* prev;
    Node* next;
    
    Node(string urls) : url(urls), prev(nullptr), next(nullptr) {}
};

class BrowserHistory {
private:
    Node* current; 
    
public:
    BrowserHistory(string homepage) {
        current = new Node(homepage); 
    }
    
    void visit(string url) {
        Node* newNode = new Node(url);
        current->next = newNode;   
        newNode->prev = current;  
        current = newNode;         
    }
    
    string back(int steps) {
        while (steps > 0 && current->prev != nullptr) {
            current = current->prev;
            steps--;
        }
        return current->url;
    }
    
    string forward(int steps) {
        while (steps > 0 && current->next != nullptr) {
            current = current->next;
            steps--;
        }
        return current->url;
    }
};*/

