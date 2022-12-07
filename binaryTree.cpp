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
void printInorder(Node *node) {
    if (node -> left == nullptr) {
        std::cout << node -> data << std::endl;
        return;
    }
    printInorder((node -> left).get());
    std::cout << node -> data << std::endl;
    printInorder((node -> right).get());
}

// printPreorder: root left right
void printPreorder(Node *node) {
    std::cout << node -> data << std::endl;
    if (node -> left == nullptr) {
        return;
    }
    printPreorder((node -> left).get());
    printPreorder((node -> right).get());
}

// printPostorder: left right root
void printPostorder(Node *node) {
    if (node -> left == nullptr) {
        std::cout << node -> data << std::endl;
        return;
    }
    printPostorder((node -> left).get());
    printPostorder((node -> right).get());
    std::cout << node -> data << std::endl;
}

void createTreeAndPrint() {
    Node root = Node(25);

    Node a1 = Node(15);
    Node a2 = Node(50);

    root.left = std::make_shared<Node> (a1); //std::make_shared<Node> (15)
    root.right = std::make_shared<Node> (a2);

    Node b1 = Node(10);
    Node b2 = Node(22);
    a1.left = std::make_shared<Node>(b1);
    a1.right = std::make_shared<Node>(b2); 

    Node b3 = Node(35);
    Node b4 = Node(70);
    a2.left = std::make_shared<Node>(b3);
    a2.right = std::make_shared<Node>(b4); 

    Node c1 = Node(4);
    Node c2 = Node(12);
    b1.left = std::make_shared<Node>(c1);
    b1.right = std::make_shared<Node>(c2);

    Node c3 = Node(18);
    Node c4 = Node(24);
    b2.left = std::make_shared<Node>(c3);
    b2.right = std::make_shared<Node>(c4);

    Node c5 = Node(31);
    Node c6 = Node(44);
    b3.left = std::make_shared<Node>(c5);
    b3.right = std::make_shared<Node>(c6);

    Node c7 = Node(66); 
    Node c8 = Node(90);
    b4.left = std::make_shared<Node>(c7);
    b4.right = std::make_shared<Node>(c8);

    printInorder(&root);
    printPreorder(&root);
    printPostorder(&root);
}


int main(int argc, char **argv) {
    if (argc != 1 && std::string(argv[1]) == "recursive") {
        std::shared_ptr<Node> root = Node::createNode();
        printInorder(root.get());
    } else {
        createTreeAndPrint();
    }
}