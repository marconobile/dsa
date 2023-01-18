#include <iostream>
#include <string>
#include <algorithm> // for std::min
#include <vector>

// g++ -std=c++17 -o  rbt.out RedBlackTrees.cpp
// leaks --atExit -- ./rbt.out


class RBNode {
    public:
        enum Color { black, red };
        int data;
        RBNode* right, *left, *parent;
        Color color = RBNode::Color::red;

        RBNode(int data, RBNode* right, RBNode* left, RBNode* parent): data(data), right(right), left(left), parent(nullptr) {}
        RBNode(): data(0), right(this), left(this), parent(this), color(RBNode::Color::black) {}

};

RBNode nil = RBNode();

void printInorderWithColor(RBNode *node)
{
    if (node->left == &nil && node->right == &nil)
    {
        std::cout << " " << node->data << " ";
        if (node -> color == RBNode::Color::red)
            std::cout << "(red) ";
        else
            std::cout << "(black) ";
        return;
    }

    if (node->left != &nil) {
        printInorderWithColor((node->left));
    }

    std::cout << " " << node->data << " ";
    if (node -> color == RBNode::Color::red)
            std::cout << "(red) ";
        else
            std::cout << "(black) ";

    if (node->right != &nil ) {
        printInorderWithColor((node->right));
    }
}

bool isLeft(RBNode* q) {
    RBNode* p = q -> parent;
    if (p -> left == q)
        return true;
    return false;
}

RBNode* getSibling(RBNode* q) {
    if (isLeft(q))
        return q -> parent ->right;
    return q -> parent ->left;
}

void swapw_colors(RBNode* p, RBNode* q) {
    RBNode::Color p_color = p ->color;
    p ->color = q ->color;
    q ->color = p_color;
}

void flip_color(RBNode* p) {
    if (p ->color == RBNode::Color::red) {
        p ->color = RBNode::Color::black;
        return;
    }
    p ->color = RBNode::Color::red;
}

RBNode* rotate(RBNode* p) {

    // if (p -)

}


RBNode* check(RBNode* p) {
    if (p -> parent->color == RBNode::Color::black)
        return p;

    RBNode* parent_sibling = getSibling(p -> parent);
    if ( parent_sibling ->color == RBNode::Color::black || parent_sibling == &nil) {
         swapw_colors(p, p ->parent ->parent);
        // return rotate() // TODO
    } else {
        flip_color(p->parent);
        flip_color(getSibling(p->parent));
        if (p ->parent -> parent -> parent == nullptr)
            return p;
        return check(p ->parent -> parent);
    }
}

RBNode* insert(int value, RBNode* node) {

    if (node == nullptr){ // if tree is empty
        node = new RBNode(value, &nil, &nil, nullptr);
        return node;
    }

    if (node -> left == &nil && node -> right == &nil) {
        node = new RBNode(value, &nil, &nil, node);
    }

    if (node -> data < value) {
        node -> left = insert(value, node -> left);
    } else if (node -> data > value) {
        node -> right = insert(value, node -> right);
    } else {
        throw; // duplicate key found
    }

    return check(node);
}


int main(){
    std::vector<int> values_to_insert = {10, 18, 7, 15, 16, 30, 25, 40, 60, 2, 1, 70};
    RBNode* root = nullptr; //new RBNode(4, &nil, &nil);

    for(int i: values_to_insert) {
        root = insert(i, root);
    }

    printInorderWithColor(root);
    std::cout << std::endl;
}
