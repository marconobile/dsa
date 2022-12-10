#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

// g++ -std=c++14 -o  bt_ordering.out treeReconstrictionWithOrderings.cpp

class Node {
    public:
        std::unique_ptr<Node> left, right;
        int data;

        Node(int data): data(data), left(nullptr), right(nullptr) {}
};

// Function to slice a given vector from range X to Y
std::vector<int> slicing(std::vector<int>& arr, int X, int Y){

    // Starting and Ending iterators
    auto start = arr.begin() + X;
    auto end = arr.begin() + Y + 1;

    // To store the sliced vector
    std::vector<int> result(Y - X + 1);

    // Copy vector using copy function()
    copy(start, end, result.begin());

    // Return the final sliced vector
    return result;
}

std::unique_ptr<Node> buildTreeFromInOrderAndPreOrder(int& idx, std::vector<int> inOrderTraversal, std::vector<int> preOrderTraversal) {
    // keys must be unique

    int current_node_data = preOrderTraversal[idx];
    std::unique_ptr<Node> n = std::make_unique<Node>(current_node_data);
    // preOrderTraversal.erase(std::remove(preOrderTraversal.begin(), preOrderTraversal.end(), current_node_data), preOrderTraversal.end());

    if (inOrderTraversal.size() == 1) {
        idx++;
        return n;
    }

    std::vector<int>::iterator it = std::find(inOrderTraversal.begin(), inOrderTraversal.end(), current_node_data);
    int index = std::distance(inOrderTraversal.begin(), it);

    std::vector<int> left_nodes = {};
    std::vector<int> right_nodes = {};

    if (index == 0) {
        right_nodes = slicing(inOrderTraversal, index+1, inOrderTraversal.size()-1);
    } else if (index == inOrderTraversal.size()-1) {
        left_nodes = slicing(inOrderTraversal, 0, index-1);
    } else {
        left_nodes = slicing(inOrderTraversal, 0, index-1);
        right_nodes = slicing(inOrderTraversal, index+1, inOrderTraversal.size()-1);
    }

    idx++;
    if (left_nodes.size() != 0){
        n.get() -> left = buildTreeFromInOrderAndPreOrder(idx, left_nodes, preOrderTraversal);
    }
    if (right_nodes.size() != 0){
        n.get() -> right = buildTreeFromInOrderAndPreOrder(idx, right_nodes, preOrderTraversal);
    }

    return n;
}

std::unique_ptr<Node> buildTreeFromInOrderAndPostOrder(int& idx, std::vector<int> inOrderTraversal, std::vector<int> preOrderTraversal) {
    // keys must be unique

    int current_node_data = preOrderTraversal[idx];
    std::unique_ptr<Node> n = std::make_unique<Node>(current_node_data);
    // preOrderTraversal.erase(std::remove(preOrderTraversal.begin(), preOrderTraversal.end(), current_node_data), preOrderTraversal.end());

    if (inOrderTraversal.size() == 1) {
        idx--;
        return n;
    }

    std::vector<int>::iterator it = std::find(inOrderTraversal.begin(), inOrderTraversal.end(), current_node_data);
    int index = std::distance(inOrderTraversal.begin(), it);

    std::vector<int> left_nodes = {};
    std::vector<int> right_nodes = {};

    if (index == 0) {
        right_nodes = slicing(inOrderTraversal, index+1, inOrderTraversal.size()-1);
    } else if (index == inOrderTraversal.size()-1) {
        left_nodes = slicing(inOrderTraversal, 0, index-1);
    } else {
        left_nodes = slicing(inOrderTraversal, 0, index-1);
        right_nodes = slicing(inOrderTraversal, index+1, inOrderTraversal.size()-1);
    }

    idx--;
    if (right_nodes.size() != 0){
        n.get() -> right = buildTreeFromInOrderAndPostOrder(idx, right_nodes, preOrderTraversal);
    }
    if (left_nodes.size() != 0){
        n.get() -> left = buildTreeFromInOrderAndPostOrder(idx, left_nodes, preOrderTraversal);
    }

    return n;
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

// printPreorder: root left right
void printPreorder(Node *node) {

    std::cout << " " << node->data << " ";

    if (node -> left.get() == nullptr && node -> right.get() == nullptr) {
        return;
    }

    if (node -> left.get() != nullptr) {
        printPreorder((node -> left).get());
    }

    if (node -> right.get() != nullptr) {
        printPreorder((node -> right).get());
    }

}

int main() {
    std::vector<int> inOrderTraversalA = {8,4,10,9,11,2,5,1,6,3,7}; // Left Root Right
    std::vector<int> preOrderTraversalA = {1,2,4,8,9,10,11,5,3,6,7};  // Root Left Right

    std::vector<int> postOrderTraversalB = {9,1,2,12,7,5,3,11,4,8};
    std::vector<int> inOrderTraversalB = {9,5,1,7,2,12,8,4,3,11}; // Left Right Root

    int start_idx = 0;
    std::unique_ptr<Node> rootA = buildTreeFromInOrderAndPreOrder(start_idx, inOrderTraversalA, preOrderTraversalA);
    std::cout << "InorderA:\n";
    printInorder(rootA.get());
    std::cout << std::endl;

    start_idx = postOrderTraversalB.size() -1;
    std::unique_ptr<Node> rootB = buildTreeFromInOrderAndPostOrder(start_idx, inOrderTraversalB, postOrderTraversalB);
    std::cout << "InorderB:\n";
    printInorder(rootB.get());
    std::cout << std::endl;

    std::cout << "PreOrderB:\n";
    printPreorder(rootB.get()); // correct { 8 , 5 , 9 , 7 , 1 , 12 , 2 , 4 , 11 , 3 }
    std::cout << std::endl;

    /* Test on treeB with preorder+inorder*/
    start_idx = 0;
    std::vector<int> preOrderTraversalB = { 8 , 5 , 9 , 7 , 1 , 12 , 2 , 4 , 11 , 3 };
    std::unique_ptr<Node> rootBB = buildTreeFromInOrderAndPreOrder(start_idx, inOrderTraversalB, preOrderTraversalB);
    std::cout << "InorderB:\n";
    printInorder(rootBB.get());
    std::cout << std::endl;







}