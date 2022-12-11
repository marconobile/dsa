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
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        Node(int data): data(data), left(nullptr), right(nullptr) {};
};

void insertNode(Node* node, int value) {

    if (value < node -> data) {
        if (node -> left == nullptr) {
            node -> left = std::make_unique<Node> (value);
        } else {
            insertNode(node -> left.get(), value);
        }
    } else if (value > node -> data) {
        if (node -> right == nullptr) {
            node -> right = std::make_unique<Node> (value);
        } else {
            insertNode(node -> right.get(), value);
        }
    }
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


//*************************************************************
void deleteNodeWithNoChild(Node *node) {

}

void deleteNodeWithOnceChild(Node* node) {

}

void deleteNodeWithChildren_predecessor(Node* node) {
    // using predecessor
}

void deleteNodeWithChildren_successor(Node* node) {
    // using successor
}

void deleteNode(Node* node , int val) {
    if(node -> left.get() == nullptr && node -> right.get() == nullptr) {
        deleteNodeWithNoChild(node);
        return;
    } else if (node -> left.get() != nullptr || node -> right.get() == nullptr) {
        deleteNodeWithOnceChild(node);
        return;
    } else if (node -> left.get() != nullptr || node -> right.get() == nullptr) {
        deleteNodeWithOnceChild(node);
        return;
    } else if (node -> left.get() != nullptr || node -> right.get() != nullptr) {
        deleteNodeWithChildren_predecessor(node); //deleteNodeWithChildren_successor(node);
        return;
    }
}

void traverseToDeleteNode(Node* node , int val) {

    if (node -> data == val) {
        deleteNode(node, val);
        return;
    }

    if(node -> left.get() == nullptr && node -> right.get() == nullptr) {
        return;
    }

    if(node -> left.get() != nullptr) {
        traverseToDeleteNode(node -> left.get(), val);
    }

    if(node -> right.get() != nullptr) {
        traverseToDeleteNode(node -> right.get(), val);
    }

}

int main() {
    std::vector<int> values_to_insert = {11, 6, 8, 19, 4, 10, 5, 17, 43, 49, 31};

    Node root = Node(values_to_insert[0]);

    for (int i = 1; i <= values_to_insert.size()-1; i++){
        insertNode(&root, values_to_insert[i]);
    }

    printInorder(&root);

}