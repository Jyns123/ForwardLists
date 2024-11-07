/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* balanceBST(TreeNode* root) {
        vector<int> inorderesult;
        inorden(root, inorderesult);
        TreeNode* result = construir(inorderesult, 0, inorderesult.size() - 1);
        return result;
    }
    
    TreeNode* construir(vector<int>& mitad, int inicio, int fin) {
        if (inicio > fin) {
            return nullptr; 
        }
        int medio = inicio + (fin - inicio) / 2;

        TreeNode* nodo = new TreeNode(mitad[medio]);

        nodo -> left = construir(mitad, inicio, medio - 1);
        nodo -> right = construir(mitad, medio + 1, fin);
        
        return nodo;
    }
    void inorden(TreeNode* nodo, vector<int>& resultado) {
        if(nodo == nullptr){
            return;
        }
        inorden(nodo -> left, resultado);       
        resultado.push_back(nodo->val);       
        inorden(nodo -> right, resultado);      
    }
};