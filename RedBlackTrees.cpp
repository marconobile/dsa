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

        RBNode(int data, RBNode* right, RBNode* left, RBNode* parent, Color color): data(data), right(right), left(left), parent(parent), color(color) {}
        RBNode(): data(0), right(this), left(this), parent(this), color(RBNode::Color::black) {}

};

RBNode nil = RBNode();

RBNode* rotateLeft(RBNode* p) {
    RBNode* q = p->right;
    p->right = q->left;
    q->left = p;

    RBNode* p_parent;
    if (p ->parent == nullptr) {
        p_parent = nullptr;
    } else {
        p_parent = p ->parent;
    }

    q -> parent = p_parent;
    p->parent = q;

    return q;
}

RBNode* rotateRight(RBNode* p) {
    RBNode* q = p->left; // get the root of the left subtree
    p->left = q -> right; // move the right subtree of q to the left side of p
    q->right = p; // move p
    // : lifting q by moving its right subtree to the left side of p

    RBNode* p_parent;
    if (p ->parent == nullptr) {
        p_parent = nullptr;
    } else {
        p_parent = p ->parent;
    }
    q -> parent = p_parent;
    p->parent = q;

    return q;
}

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

bool check_if_rotation_is_needed(RBNode* q) {

    if (q->left -> color == RBNode::Color::red)
        if (q->left -> left ->color == RBNode::Color::red || q->left -> right ->color == RBNode::Color::red)
            return true;
    if (q->right -> color == RBNode::Color::red)
        if (q->right -> left ->color == RBNode::Color::red || q->right -> right ->color == RBNode::Color::red)
            return true;
     return false;

// if (q-> color == RBNode::Color::red)
//         if (q->left ->color == RBNode::Color::red || q-> right ->color == RBNode::Color::red)
//             return true;
//      return false;

}

RBNode* rotate_and_swap_colors(RBNode* q) {

    // if (q -> parent == nullptr)
    //     return q;


    if (!check_if_rotation_is_needed(q))
        return q;

    RBNode* sibling;
    if (q -> parent != nullptr)
        sibling = getSibling(q);

    if (q -> parent == nullptr || sibling ->color == RBNode::Color::black || sibling == &nil) {
        RBNode* ret, *change_color_target;
        if (q -> left != &nil && q -> left -> color == RBNode::Color::red) {
            if ( q -> left -> left -> color == RBNode::Color::red){
                change_color_target = q -> left; //-> left;
                ret = rotateRight(q);
            } else if (q ->left ->right -> color == RBNode::Color::red){
                change_color_target = q ->left ->right;
                q ->left = rotateLeft(q ->left);
                ret = rotateRight(q);
            }
        } else if ( q -> right != &nil && q ->right -> color == RBNode::Color::red) {
            if (q->right->left->color == RBNode::Color::red) {
                change_color_target = q->right->left;
                q ->right = rotateRight(q ->right);
                ret = rotateLeft(q);
            } else if (q->right->right->color == RBNode::Color::red){
                change_color_target = q->right;
                ret = rotateLeft(q);
            }
        }
        swapw_colors(q, change_color_target);
        return ret;
    }
}

RBNode* check(RBNode* p) {

    if (p ->parent == nullptr)
        return p;

    if (p -> parent->color == RBNode::Color::black)
        return p;

    if (p ->color == RBNode::Color::red && p -> parent->color == RBNode::Color::red) {
        RBNode* parent_sibling = getSibling(p -> parent);
        if (parent_sibling ->color == RBNode::Color::black || parent_sibling == &nil) {
            // swap_colors & rotate will be called later if required
            return p;
        } else {
            flip_color(p->parent);
            flip_color(getSibling(p->parent));
            if (p ->parent -> parent -> parent == nullptr)
                return p;
            flip_color(p->parent->parent);
            return p;
        }
    }
    return p;
}

RBNode* insert(int value, RBNode* node, RBNode* parent) {

    if (node == nullptr){ // if tree is empty
        return new RBNode(value, &nil, &nil, nullptr, RBNode::Color::black);
    }

    if (node == &nil) {
        RBNode* new_node = new RBNode(value, &nil, &nil, parent, RBNode::Color::red);
        if (value < parent -> data) {
            parent ->left = new_node;
        } else if (value > parent -> data) {
            parent ->right = new_node;
        }
        return rotate_and_swap_colors(check(new_node));

    } else if (value < node -> data) {
        node -> left = insert(value, node -> left, node);
    } else if (value > node -> data) {
        node -> right = insert(value, node -> right, node);
    } else {
        throw; // duplicate key found
    }

    return rotate_and_swap_colors(check(node));
}

void deleteTree(RBNode *node) {
    // follow post-order traversal criteria L-Ri-Ro to delete
    if (node -> left == &nil && node -> right == &nil) {
        delete node;
        return;
    }

    if (node -> left != &nil) {
        deleteTree(node ->left);
    }

    if (node -> right != &nil) {
        deleteTree(node ->right);
    }

    delete node;
    return;
}

int main(){
    std::vector<int> values_to_insert = {10, 18, 7, 15, 16, 30, 25, 40, 60, 2, 1, 70};
    RBNode* root = nullptr; //new RBNode(4, &nil, &nil);

    for(int i: values_to_insert) {
        root = insert(i, root, nullptr);
    }

    printInorderWithColor(root);
    std::cout << std::endl;

    deleteTree(root);
}
