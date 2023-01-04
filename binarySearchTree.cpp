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

std::shared_ptr<Node> insert(int value, std::shared_ptr<Node> root) {
    if (root == nullptr) { // base case: if we fall off the tree, then the node needs to be created
        root = std::make_shared<Node>(value);
    } else if (value < root->data) { // recursive case: binary search logic
        root -> left = insert(value, root -> left); // recursively return the in-place modified sub-tree
    } else if (value > root->data) {
        root -> right = insert(value, root -> right);
    }
    return root;
}


// find biggest node in left-sub-tree (i.e. the right-most)
std::shared_ptr<Node> findReplacement(std::shared_ptr<Node> node) {
    std::shared_ptr<Node> r = node -> left;
    while (r -> right != nullptr) {
        r = r ->right;
    }
    return r;

}

std::shared_ptr<Node> deleteNode(int value, std::shared_ptr<Node> root) {
    if (root.get() == nullptr) {
        throw;
    } else {
        if (root -> data < value) {
            root -> right = deleteNode(value, root -> right);
        } else if (root -> data > value) {
            root -> left = deleteNode(value, root -> left);
        } else if (root -> left == nullptr || root -> right == nullptr) {
            if (root -> left == nullptr) {
                root = root -> right;
            } else {
                root = root -> left;
            }
        } else {
            std::shared_ptr<Node> r = findReplacement(root);
            root -> data = r ->data;
            root -> left = deleteNode(r -> data, root -> left);
        }
    }
    return root;
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
    std::cout << " " << node->data << " ";

    if (node->right.get()) {
        printInorder((node->right).get());
    }
}


int main() {
    std::vector<int> values_to_insert = {11, 6, 8, 19, 4, 10, 5, 17, 43, 49, 31};
    std::shared_ptr<Node> root = nullptr;

    for (int i = 0; i <= values_to_insert.size()-1; i++)
        root = insert(values_to_insert[i], root);

    printInorder(root.get());
    std::cout << std::endl;

    std::cout << "Without 5\n";
    deleteNode(5, root);
    printInorder(root.get());
    std::cout << std::endl;

    std::cout << "Without 8\n";
    deleteNode(8, root);
    printInorder(root.get());
    std::cout << std::endl;

    std::cout << "Without 43\n";
    deleteNode(43, root);
    printInorder(root.get());
    std::cout << std::endl;

}