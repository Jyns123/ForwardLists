#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if(nums.empty()){
            return nullptr;
        }

        int mid = nums.size()/2;
        TreeNode* root = new TreeNode(nums[mid]);

        vector<int> leftSubarray(nums.begin(), nums.begin()+mid);
        root -> left = sortedArrayToBST(leftSubarray);

        vector<int> rightSubarray(nums.begin()+mid+1, nums.end());
        root -> right = sortedArrayToBST(rightSubarray);

        return root;
    }

/*
inordertransversal(Treenode* root, vector<int> arr){
    if (root!= nullptr){
        inordertransversal(root->left,arr);
        arr.push_back(root->val);
        inordertransversal(root->right, arr);
    }
}
*/
    //-----------------------------------------------------------------------------------------

    bool isValidBST(TreeNode* root) {
        return validate(root, nullptr, nullptr);
    }

    bool validate(TreeNode* node, TreeNode* minNode, TreeNode* maxNode) {
        if(node == nullptr){
            return true;
        }
        
        if(minNode != nullptr && node->val <= minNode->val){
            return false;
        }

        if(maxNode != nullptr && node->val >= maxNode->val){
            return false;
        }

        return validate(node -> left, minNode, node) && 
               validate(node -> right, node, maxNode);
    }
    //-----------------------------------------------------------------------------------------

    bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {
        vector<int> parent(n, 0);

        for (int i = 0; i < n; i++) {
            if(leftChild[i] != -1) {
                parent[leftChild[i]]++;

                if(parent[leftChild[i]] > 1) {
                    return false;  
                }
            }
        }

        for (int i = 0; i < n; i++) {
            if(rightChild[i] != -1) {
                parent[rightChild[i]]++;
                
                if (parent[rightChild[i]] > 1){ 
                    return false;
                } 
            }
        }

        int root = -1;
        for (int i = 0; i < n; i++) {
            if(parent[i] == 0) {
                if (root == -1) {
                    root = i; 
                } else {
                    return false;  
                }
            }
        }

        if (root == -1){
            return false;
        }

        vector<bool> visited(n, false);
        stack<int> dfs;
        dfs.push(root);

        int visitedCount{};
        while (!dfs.empty()) {
            int node = dfs.top();
            dfs.pop();

            if(visited[node]){
                return false;
            }

            visited[node] = true;
            visitedCount++;

            if(leftChild[node] != -1){ 
                dfs.push(leftChild[node]);
            }
            if(rightChild[node] != -1){
                dfs.push(rightChild[node]);
            }
        }

        return visitedCount == n;
    }


//-----------------------------------------------------------------------------------------
    vector<int> arr;
    void inorderTraversal(TreeNode* root) {
        if(root == nullptr){
            return;
        }

        inorderTraversal(root -> left);
        arr.push_back(root -> val);  
        inorderTraversal(root -> right);

    }

    void modifyTree(TreeNode* root, int a, int b) {

        if(root == nullptr){
            return;
        }

        modifyTree(root -> left, a, b);

        if(root -> val == a){
            root -> val = b;
        }
        else if(root -> val == b){
            root -> val = a;
        }

        modifyTree(root -> right, a, b);
    }

    void recoverTree(TreeNode* root) {
        inorderTraversal(root);  

        vector<int> temp = arr;
        sort(temp.begin(), temp.end());

        int a = -1;
        int b = -1;

        for (int i = 0; i < arr.size(); i++) {
            if(arr[i] != temp[i]) {
                if(a == -1){
                    a = arr[i];
                }
                else
                b = arr[i];          
            }
        }

        modifyTree(root, a, b);
    }

//-----------------------------------------------------------------------------------------

    void preorden(TreeNode* nodo, vector<int>& resultado) {
        if(nodo == nullptr)
            return;
        resultado.push_back(nodo -> val);       
        preorden(nodo -> left, resultado);      
        preorden(nodo -> right, resultado);     
    }

    void inorden(TreeNode* nodo, vector<int>& resultado) {
        if(nodo == nullptr)
            return;
        inorden(nodo -> left, resultado);       
        resultado.push_back(nodo->val);       
        inorden(nodo -> right, resultado);      
    }


    void postorden(TreeNode* nodo, vector<int>& resultado) {
        if (nodo == nullptr)
            return;
        postorden(nodo -> left, resultado);    
        postorden(nodo -> right, resultado);    
        resultado.push_back(nodo->val);       
    }

    void imprimirVector(const vector<int>& v) {
        for (int valor : v) {
            cout << valor << " ";
        }
        cout << endl;
    }
//-----------------------------------------------------------------------------------------


    void preorden1(TreeNode* nodo, vector<int>& resultado) {
        if (nodo == nullptr)
            return;
        resultado.push_back(nodo->val);       
        preorden1(nodo -> left, resultado);      
        preorden1(nodo -> right, resultado);     
    }

    int kthSmallest(TreeNode* root, int k) {
        vector<int> preordenv;
        preorden1(root, preordenv);         
        sort(preordenv.begin(), preordenv.end()); 
        return preordenv[k - 1];             
    }


//-----------------------------------------------------------------------------------------





};