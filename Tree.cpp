#include <iostream>
#include <queue>
#include <vector>
#include <stack>

template <class T>
class tree{
public:
    ~tree();
    void add(const T & node);
    std::vector<T> popAll();
private:
    struct Node{
        Node(const T & node):data(node){};
        T data;
        Node* left = NULL;
        Node* right = NULL;
    };
    Node* root = NULL;
};

template  <class T>
void tree<T>::add(const T &node) {
    if(root != NULL){
        Node*  treeNode = root;
        while(true){
            if(treeNode -> data >= node){
                if(treeNode->left == NULL){
                    treeNode -> left =  new Node(node);
                    break;
                }
                treeNode = treeNode -> left;
            }else{
                if(treeNode->right == NULL){
                    treeNode -> right =  new Node(node);
                    break;
                }
                treeNode = treeNode -> right;
            }
        }
    }else{
        root = new Node(node);
    }
}

template <class T>
std::vector<T> tree<T>::popAll() {
    std::stack<Node *> result;
    std::vector<T> res;
    Node * node = root;
    while(node != NULL || !result.empty()){
        while (node != NULL){
            result.push(node);
            node = node->left;
        }
        res.push_back(result.top()->data);
        node = result.top()->right;
        result.pop();
    }
    return res;
}

template <class T>
tree<T>::~tree(){
    std::stack<Node *> tmpStack;
    Node * node = root;
    while(node != NULL || !tmpStack.empty()){
        while (node != NULL){
            tmpStack.push(node);
            node = node->left;
        }
        delete tmpStack.top();
        node = tmpStack.top()->right;
        tmpStack.pop();
    }
}

int main() {
    int count = 0;
    std::cin >> count;
    tree<int> tree;
    int elem;
    for(int i = 0; i < count; i++){
        std::cin >> elem;
        tree.add(elem);
    }
    std::vector<int> res = tree.popAll();
    for(int i = 0; i < res.size(); i++){
        std::cout << res[i] << " ";
    }
    return 0;
}
