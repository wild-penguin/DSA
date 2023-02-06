#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <map>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <stack>
#include <queue>

#define VECTOR_EXISTS(key, vector) (std::find(vector.begin(), vector.end(), key) != vector.end())
#define VECTOR_GET_ITERATOR(key, vector) (std::find(vector.begin(), vector.end(), key))
#define ull unsigned long long int

class Node{
    public:
    ull key;
    std::vector<ull> connections;
    void* data;

    Node(ull key = 0){ this->key = key; this->data = NULL;};
};

class DirectedGraph{
    private:
    std::map<ull, Node> dictionary;
    
    public:

    bool exists(ull key){
        if (dictionary.find(key) != dictionary.end())
            return true;
        return false;
    }

    void insert(ull key){
        if (exists(key)){
            return;
        }
        dictionary[key];
    }

    void remove(ull key){
        if (exists(key)){
            for (auto &dict_elem : dictionary){
                if (VECTOR_EXISTS(key, dict_elem.second.connections))
                    dict_elem.second.connections.erase(VECTOR_GET_ITERATOR(key, dict_elem.second.connections));
            }
            dictionary.erase(key);
        }        
    }

    void connect(ull from, ull to){
        if (!exists(from) || !exists(to)){
            std::cout << "connect: one of the key doesn't exist.\n";
            return;
        }
        dictionary.at(from).connections.push_back(to);
        
    }

    void printNode(ull key){
        if(!exists(key)){
            std::cout << key << " not present inside the dictionary.\n";
            return;
        }

        std::cout << key << " -> [";
        for (const ull& key : dictionary.at(key).connections){
            std::cout << key << ", ";
        }
        std::cout << " END]" << std::endl;
    }

    void printGraphDFS(ull key){
        if (!exists(key)){
            std::cout << key << " not present inside the dictionary.\n";
            return;
        }
        
        std::vector<ull> keys;
        std::stack<ull> stack;
        std::vector<ull> visited;
        stack.push(key);

        while(stack.size()){
            ull current_key = stack.top();
            stack.pop();
            
            if (VECTOR_EXISTS(current_key, visited))
                continue;

            for(int i = dictionary.at(current_key).connections.size() - 1; i >= 0; --i)
                stack.push(dictionary.at(current_key).connections.at(i));
            
            
            if (!VECTOR_EXISTS(current_key, keys))
                keys.push_back(current_key);
            visited.push_back(current_key);
        }

        std::cout << "=== DFS print beigns ===\n";
        for (const ull& key : keys)
            std::cout << key << std::endl;
        std::cout << "=== DFS print ends ===\n";
    }

    void printGraphBFS(char key){
        if (!exists(key)){
            std::cout << key << " not present inside the dictionary.\n";
            return;
        }

        std::vector<ull> keys;
        std::queue<ull> queue;
        std::vector<ull> visited;
        queue.push(key);

        while(queue.size()){
            ull current_key = queue.front();
            queue.pop();

            if (VECTOR_EXISTS(current_key, visited))
                continue;

        for(int i = dictionary.at(current_key).connections.size() - 1; i >= 0; --i)
                queue.push(dictionary.at(current_key).connections.at(i));

        if (!VECTOR_EXISTS(current_key, keys))
                keys.push_back(current_key);
            visited.push_back(current_key);
        }

        std::cout << "=== BFS print beigns ===\n";
        for (const ull& key : keys)
            std::cout << key << std::endl;
        std::cout << "=== BFS print ends ===\n";
    }

    bool path_exists(ull from, ull to){
        if (!exists(from) || !exists(to)){
            std::cout << "path exists: one of the keys is not in the dictionary\n";
            return false;
        }

        std::vector<ull> keys;
        std::stack<ull> stack;
        std::vector<ull> visited;
        stack.push(from);

        while(stack.size()){
            ull current_key = stack.top();

            if (current_key == to)
                return true;
            
            stack.pop();
            
            if (VECTOR_EXISTS(current_key, visited))
                continue;

            for(int i = dictionary.at(current_key).connections.size() - 1; i >= 0; --i)
                stack.push(dictionary.at(current_key).connections.at(i));
            
            
            if (!VECTOR_EXISTS(current_key, keys))
                keys.push_back(current_key);
            visited.push_back(current_key);
        }
        return false;
    }
};

int main(){
    DirectedGraph dg;
    // dg.insert(1);
    // dg.insert(9);
    // dg.insert(3);
    // dg.insert(2);
    // dg.insert(6);
    // dg.insert(8);

    // dg.connect(3, 1);
    // dg.connect(3, 9);
    // dg.connect(1, 2);
    // dg.connect(6, 2);
    // dg.connect(1, 8);

    // dg.printNode(3);
    // dg.printGraphDFS(3);




}

