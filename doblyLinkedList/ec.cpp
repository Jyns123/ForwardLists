//LRU Cache Implementación (Lista Doble Simple)
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
};

//LRU Cache Implementación (Con unordered_map)
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

//
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
};

//LFU Cache Implementación (Con unordered_map y list)
#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

// Node structure for each entry in the cache
struct Node {
    int key, value, freq;
    Node(int k, int v) : key(k), value(v), freq(1) {}
};

// Doubly Linked List for maintaining nodes of same frequency
class DLL {
public:
    list<Node*> nodes;
    
    // Add a node to the front of the list (most recently used for that frequency)
    void addNode(Node* node) {
        nodes.push_front(node);
    }
    
    // Remove a node from the list
    void removeNode(Node* node) {
        nodes.remove(node);
    }
    
    // Check if the list is empty
    bool isEmpty() const {
        return nodes.empty();
    }
    
    // Return the least recently used node (at the back)
    Node* getLRU() {
        return nodes.back();
    }
};

class LFUCache {
private:
    int capacity, minFreq, size;
    unordered_map<int, Node*> keyNodeMap;  // Maps key to its node
    unordered_map<int, DLL> freqListMap;   // Maps frequency to its corresponding DLL

    // Update node's frequency and move it to the corresponding DLL
    void updateNode(Node* node) {
        int oldFreq = node->freq;
        freqListMap[oldFreq].removeNode(node);  // Remove node from the old frequency list

        // If the old frequency list becomes empty and it's the minFreq, increment minFreq
        if (freqListMap[oldFreq].isEmpty() && oldFreq == minFreq) {
            minFreq++;
        }

        // Increment node's frequency and add it to the new frequency list
        node->freq++;
        freqListMap[node->freq].addNode(node);
    }

public:
    LFUCache(int capacity) : capacity(capacity), minFreq(0), size(0) {}

    int get(int key) {
        if (capacity == 0 || keyNodeMap.find(key) == keyNodeMap.end()) {
            return -1;
        }

        Node* node = keyNodeMap[key];
        int value = node->value;
        
        // Update the node's frequency
        updateNode(node);
        return value;
    }

    void put(int key, int value) {
        if (capacity == 0) return;

        if (keyNodeMap.find(key) != keyNodeMap.end()) {
            Node* node = keyNodeMap[key];
            node->value = value;
            updateNode(node);
            return;
        }

        if (size == capacity) {
            // Get the least frequently used DLL and evict the least recently used node from it
            Node* lruNode = freqListMap[minFreq].getLRU();
            keyNodeMap.erase(lruNode->key);
            freqListMap[minFreq].removeNode(lruNode);
            size--;
            delete lruNode;  
        }

        Node* newNode = new Node(key, value);
        keyNodeMap[key] = newNode;
        minFreq = 1; 
        freqListMap[1].addNode(newNode);
        size++;
    }
};

//LFU Cache Implementación (Con DoublyLinkedList y Array de Punteros)
#include <iostream>
#include <limits.h>
using namespace std;

// Node structure for each entry in the cache
struct Node {
    int key, value, freq;
    Node* prev;
    Node* next;
    Node(int k, int v) : key(k), value(v), freq(1), prev(nullptr), next(nullptr) {}
};

// Doubly Linked List for maintaining nodes of same frequency
class DoublyLinkedList {
public:
    Node* head;
    Node* tail;

    DoublyLinkedList() {
        head = new Node(-1, -1); // Dummy head
        tail = new Node(-1, -1); // Dummy tail
        head->next = tail;
        tail->prev = head;
    }

    // Add a node to the front of the list (most recently used)
    void addNode(Node* node) {
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
        node->prev = head;
    }

    // Remove a node from the list
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    // Check if the list is empty
    bool isEmpty() {
        return head->next == tail;
    }

    // Return the least recently used node (last node before dummy tail)
    Node* getLRU() {
        return tail->prev;
    }
};

class LFUCache {
private:
    int capacity, size;
    Node** nodes;             // Array of pointers to cache nodes
    DoublyLinkedList* dll;     // Doubly Linked List to track the order of nodes

    // Find the least frequently used node (LRU in case of tie)
    Node* findLFU() {
        Node* lfu = nullptr;
        int minFreq = INT_MAX;
        Node* current = dll->head->next;
        while (current != dll->tail) {
            if (current->freq < minFreq) {
                minFreq = current->freq;
                lfu = current;
            } else if (current->freq == minFreq && lfu != nullptr) {
                // If frequencies are the same, choose least recently used
                lfu = current;
            }
            current = current->next;
        }
        return lfu;
    }

public:
    LFUCache(int capacity) : capacity(capacity), size(0) {
        nodes = new Node*[capacity];
        for (int i = 0; i < capacity; i++) {
            nodes[i] = nullptr;
        }
        dll = new DoublyLinkedList();
    }

    int get(int key) {
        // Linear search to find the key
        for (int i = 0; i < capacity; i++) {
            if (nodes[i] && nodes[i]->key == key) {
                // Increase frequency and move node to the front of the list
                nodes[i]->freq++;
                dll->removeNode(nodes[i]);
                dll->addNode(nodes[i]);
                return nodes[i]->value;
            }
        }
        return -1; // Key not found
    }

    void put(int key, int value) {
        if (capacity == 0) return;

        // Check if key already exists
        for (int i = 0; i < capacity; i++) {
            if (nodes[i] && nodes[i]->key == key) {
                nodes[i]->value = value;
                nodes[i]->freq++;
                dll->removeNode(nodes[i]);
                dll->addNode(nodes[i]);
                return;
            }
        }

        // If cache is full, remove the LFU (LRU in case of tie)
        if (size == capacity) {
            Node* lfuNode = findLFU();
            dll->removeNode(lfuNode);
            for (int i = 0; i < capacity; i++) {
                if (nodes[i] == lfuNode) {
                    delete nodes[i];
                    nodes[i] = nullptr;
                    break;
                }
            }
            size--;
        }

        // Insert new node
        Node* newNode = new Node(key, value);
        dll->addNode(newNode);
        for (int i = 0; i < capacity; i++) {
            if (nodes[i] == nullptr) {
                nodes[i] = newNode;
                break;
            }
        }
        size++;
    }
};
