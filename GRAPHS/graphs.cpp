#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <vector>
#include <queue>

using namespace std;

class Graph {
private:
    int n; 
    vector<int> vals;  
    vector<vector<int>> lista_de_ad;  
    
public:
    Graph(int nodes, const vector<int>& values) {
        n = nodes;
        vals = values;
        lista_de_ad.resize(n); 
    }
    
    void addEdge(int u, int v) {
        lista_de_ad[u].push_back(v);
        lista_de_ad[v].push_back(u);
    }
    
    int maxStarSum(int k) {
        int maxSum = INT_MIN;  

        for (int i = 0; i < n; ++i) {
            vector<int> neighbors;

            for (int neighbor : lista_de_ad[i]) {
                neighbors.push_back(vals[neighbor]);
            }

            sort(neighbors.rbegin(), neighbors.rend());

            int starSum = vals[i];

            for (int j = 0; j < min(k, (int)neighbors.size()); ++j) {
                if (neighbors[j] > 0) {
                    starSum += neighbors[j];  
               
                }
            }

            maxSum = max(maxSum, starSum);
        }

        return maxSum;
    }

    int findJudge(int n, vector<vector<int>>& trust) {

        vector<int> howmany_trust_pos_judge(n + 1, 0);      
        vector<int> howmany_people_each_person_trust(n + 1, 0); 

        for (auto& t : trust) {
            int a = t[0];
            int b = t[1];
            howmany_trust_pos_judge[b]++;      
            howmany_people_each_person_trust[a]++; 
        }

        for (int i = 1; i <= n; i++) {
            if (howmany_trust_pos_judge[i] == n - 1 && howmany_people_each_person_trust[i] == 0) {
                return i;
            }
        }
        return -1;
    }
    template <typename T>
    void traverse(int start, bool isBFS) {
        vector<bool> visited(n, false);
        T container; 

        container.push(start);
        visited[start] = true;

        while (!container.empty()) {
            int node = container.top();
            container.pop();

            cout << "Visited node: " << node << endl;

            for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    if (isBFS) {
                        static_cast<queue<int>&>(container).push(neighbor);
                    } else {
                        static_cast<stack<int>&>(container).push(neighbor);
                    }
                }
            }
        }
    }

    vector<vector<int>> crearListaDeAdyacencia(int n, vector<vector<int>>& edges) {
        vector<vector<int>> lista_de_ad(n);
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            lista_de_ad[u].push_back(v);
            lista_de_ad[v].push_back(u);
        }
        return lista_de_ad;
    }
    
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        if (source == destination) return true;

        vector<vector<int>> lista_de_ad = crearListaDeAdyacencia(n, edges);

        vector<bool> visited(n, false);
        queue<int> q;
        q.push(source);
        visited[source] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            if (node == destination) return true;

            for (int neighbor : lista_de_ad[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        return false;
    }
};

int main() {
    vector<int> vals1 = {1, 2, 3, 4, 10, -10, -20};
    vector<vector<int>> edges1 = {{0, 1}, {1, 2}, {1, 3}, {3, 4}, {3, 5}, {3, 6}};
    int k1 = 2;
    
    Graph graph1(vals1.size(), vals1);
    for (const auto& edge : edges1) {
        graph1.addEdge(edge[0], edge[1]);
    }
    
    cout<< graph1.maxStarSum(k1) << endl;  
    
    vector<int> vals2 = {-5};
    vector<vector<int>> edges2 = {};
    int k2 = 0;
    
    Graph graph2(vals2.size(), vals2);
    for (const auto& edge : edges2) {
        graph2.addEdge(edge[0], edge[1]);
    }
    
    cout << graph2.maxStarSum(k2) << endl;  
    return 0;
}
