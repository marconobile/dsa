#include <cstddef>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>

// g++ -std=c++17 -o  bt.out binarySearchTree.cpp

class Node {
    public:
        int data;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;

        Node(int data): data(data), left(nullptr), right(nullptr) {};
};

// void insertNode(Node* node, int value) { // insert version that works with left, right as unique ptrs
//     if (value < node -> data) {
//         if (node -> left == nullptr) {
//             node -> left = std::make_unique<Node> (value);
//         } else {
//             insertNode(node -> left.get(), value);
//         }
//     } else if (value > node -> data) {
//         if (node -> right == nullptr) {
//             node -> right = std::make_unique<Node> (value);
//         } else {
//             insertNode(node -> right.get(), value);
//         }
//     }
// }

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
    std::cout << " " << node->data << " ";

    if (node->right.get()) {
        printInorder((node->right).get());
    }
}

std::shared_ptr<Node> insert_v2(int value, std::shared_ptr<Node> node) {
    if (node == nullptr) { // base case: if we fall off the tree, then the node needs to be created
        node = std::make_shared<Node>(value);
    } else if (value < node->data) { // binary search logic
        node -> left = insert_v2(value, node -> left); // recursively return the in-place modified sub-tree
    } else if (value > node->data) { // binary search logic
        node -> right = insert_v2(value, node -> right); // recursively return the in-place modified sub-tree
    }
    return node;
}



int main() {
    std::vector<int> values_to_insert = {11, 6, 8, 19, 4, 10, 5, 17, 43, 49, 31};
    std::shared_ptr<Node> root = nullptr;

    for (int i = 0; i <= values_to_insert.size()-1; i++)
        root = insert_v2(values_to_insert[i], root);

    printInorder(root.get());
    std::cout << std::endl;

    // deleteNode(&root, 5);
    // printInorder(&root);
    // std::cout << std::endl;

}