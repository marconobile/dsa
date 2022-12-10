#include <cstddef>
#include <iostream>
#include <string>
#include <memory>

// g++ -std=c++11 -o  bt.out binaryTree.cpp

class Node {
    public:
        int data;
        std::shared_ptr<Node> left, right;

        static std::shared_ptr<Node> createNode() {
            // recursive creation of bt
            // makes root, then left child then right child
            std::cout << "Insert INT data for node: ";
            std::string x;
            getline(std::cin, x);
            if (x.empty()) { // base case
                return nullptr;
            }

            std::shared_ptr<Node> newNode = std::make_shared<Node>(std::stoi(x));
            newNode -> left = Node::createNode();
            newNode -> right = Node::createNode();
            return newNode;
        }

        Node(int data): data(data), left(nullptr), right(nullptr) {}
};

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

// printPostorder: left right root
void printPostorder(Node *node) {
    if (node -> left == nullptr) {
        std::cout << " " << node->data << " ";
        return;
    }
    if (node -> left.get() != nullptr) {
        printPostorder((node -> left).get());
    }

    if (node -> right.get() != nullptr) {
        printPostorder((node -> right).get());
    }

    std::cout << node -> data;
}

void createTreeAndPrint() {
    Node root = Node(25);

    root.left = std::make_shared<Node> (15);
    root.right = std::make_shared<Node> (50);

    root.left.get() -> left = std::make_shared<Node>(10);
    root.left.get() -> right = std::make_shared<Node>(22);

    root.right.get() -> left = std::make_shared<Node>(35);
    root.right.get() -> right = std::make_shared<Node>(70);

    root.left.get() -> left.get() ->left = std::make_shared<Node>(4);
    root.left.get() -> left.get() ->right = std::make_shared<Node>(12);

    root.left.get() -> right.get() ->left = std::make_shared<Node>(18);
    root.left.get() -> right.get() ->right = std::make_shared<Node>(24);

    root.right.get() -> left.get() ->left = std::make_shared<Node>(31);
    root.right.get() -> left.get() ->right = std::make_shared<Node>(44);

    root.right.get() -> right.get() ->left = std::make_shared<Node>(66);
    root.right.get() -> right.get() ->right = std::make_shared<Node>(90);

    printInorder(&root);
    std::cout << std::endl;
    printPreorder(&root);
    std::cout << std::endl;
    printPostorder(&root);
    std::cout << std::endl;
}


int main(int argc, char **argv) {
    if (argc != 1 && std::string(argv[1]) == "recursive") {
        std::shared_ptr<Node> root = Node::createNode();
        printInorder(root.get());
    } else {
        createTreeAndPrint();
    }
}

/*
Out:
 4 10 12 15 18 22 24 25 31 35 44 50 66 70 90
 25  15  10  4  12  22  18  24  50  35  31  44  70  66  90
 4  12 10 18  24 22 15 31 44 35 66  90 70 50 25

 tree taken from: https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
*/