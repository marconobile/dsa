#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

// g++ -std=c++11 -o  bt_ordering2.out constructBTFromPreAndPostOrder.cpp

// Note: it is possible to build an unique binary tree from pre+post orderings iff the tree is full (each node has either 0 or 2 nodes)
// if the bt is not full then with pre+post orderings it is not possible to define uniquely a bt

class Node {
    public:
        std::shared_ptr<Node> left, right;
        char data;

        Node(char data): data(data), left(nullptr), right(nullptr) {}
};

// Function to slice a given vector from range X to Y
std::vector<char> slicing(std::vector<char>& arr, int X, int Y){

    // Starting and Ending iterators
    auto start = arr.begin() + X;
    auto end = arr.begin() + Y + 1;

    // To store the sliced vector
    std::vector<char> result(Y - X + 1);

    // Copy vector using copy function()
    copy(start, end, result.begin());

    // Return the final sliced vector
    return result;
}

// inorder: left root right
void printInorder(Node *node)
{
    if (node->left.get() == nullptr && node->right.get() == nullptr)
    {
        std::cout << " " << node->data << " ";
        return;
    }

    if (node->left.get()) {
        printInorder((node->left).get());
    }
    std::cout << node->data;

    if (node->right.get()) {
        printInorder((node->right).get());
    }

}

std::shared_ptr<Node> buildTreeFromPrePostOrderings(std::vector<char> preOrder, std::vector<char> postOrder) {

    char outmost_el = preOrder[0];
    preOrder.erase(std::remove(preOrder.begin(), preOrder.end(), outmost_el), preOrder.end());
    postOrder.erase(std::remove(postOrder.begin(), postOrder.end(), outmost_el), postOrder.end());
    std::shared_ptr<Node> n = std::make_shared<Node> (outmost_el);

    // define base case
    if (preOrder.size() == 0) {
        return n;
    }

    //
    std::vector<char>::iterator it = std::find(postOrder.begin(), postOrder.end(), preOrder[0]);
    int index = std::distance(postOrder.begin(), it);

    std::vector<char> left_nodes_pre = {};
    std::vector<char> left_nodes_post = {};

    left_nodes_pre = slicing(preOrder, 0, index);
    left_nodes_post = slicing(postOrder, 0, index);

    std::vector<char> right_nodes_pre = {};
    std::vector<char> right_nodes_post = {};

    right_nodes_pre = slicing(preOrder, index+1, preOrder.size()-1);
    right_nodes_post = slicing(postOrder, index+1, postOrder.size()-1);

    if (left_nodes_pre.size() != 0 && left_nodes_post.size() != 0){
        n.get() -> left = buildTreeFromPrePostOrderings(left_nodes_pre, left_nodes_post);
    }
    if (right_nodes_pre.size() != 0 && right_nodes_post.size() != 0){
        n.get() -> right = buildTreeFromPrePostOrderings(right_nodes_pre, right_nodes_post);
    }

    return n;

}

int get_index(char ch, std::vector<char> postOrder) {
    std::vector<char>::iterator it = std::find(postOrder.begin(), postOrder.end(), ch);
    return std::distance(postOrder.begin(), it);
}


std::shared_ptr<Node> buildTreeFromPrePostOrderings2(std::vector<char> preOrder, std::vector<char> postOrder) {

    std::vector<std::shared_ptr<Node>> nodeList;
    for (int i = 0; i <= preOrder.size()-1; i++) {
        char ch = preOrder[i];
        std::shared_ptr<Node> n = std::make_shared<Node> (ch);
        if (i == 0) {
            nodeList.push_back(n);
            continue;
        }

        int j = 0;
        while(true) {
            if(get_index(ch, postOrder) < get_index(nodeList[j].get() ->data, postOrder) ) {
                if (nodeList[j].get() -> left == nullptr){
                    nodeList[j].get() -> left = n;
                    nodeList.insert(nodeList.begin(), n);
                    break;
                } else {
                    nodeList[j].get() -> right = n;
                    nodeList.insert(nodeList.begin(), n);
                    break;
                }
            }
            j++;
        }
    }

    return nodeList.back();
}


int main(){
    std::vector<char> preOrder = {'F', 'B', 'A', 'D', 'C', 'E', 'G', 'I', 'H'};
    std::vector<char> postOrder = {'A', 'C', 'E', 'D', 'B', 'H', 'I', 'G', 'F'};

    std::shared_ptr<Node> root = buildTreeFromPrePostOrderings(preOrder, postOrder);
    printInorder(root.get());
    std::cout << std::endl;

    std::shared_ptr<Node> root2 = buildTreeFromPrePostOrderings2(preOrder, postOrder);
    printInorder(root2.get());
    std::cout << std::endl;





}