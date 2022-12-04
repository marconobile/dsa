#include <cstddef>
#include <iostream>
#include <string>
#include <memory>


class Node {
    public:
        int data;
        Node* left, *right;

        static std::shared_ptr<Node> createNode() {
            std::cout << "Insert INT data for node: ";
            std::string x;
            getline(std::cin, x);
            if (x.empty()) {
                return nullptr;
            }

            std::shared_ptr<Node>  newNode = std::make_shared<Node>(std::stoi(x));
            newNode -> left = createNode().get();
            newNode -> right = createNode().get();
            return newNode;
        }

        Node(int data): data(data), left(nullptr), right(nullptr) {}
};





// implement recursive creation of bt

int main() {
    std::shared_ptr<Node> root = Node::createNode();
}