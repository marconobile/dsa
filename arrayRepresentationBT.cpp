#include <cstddef>
#include <iostream>
#include <string>
#include <memory>
#include <cctype>

// g++ -std=c++11 -o  bt.out binaryTree.cpp

class Node
{
public:
    char data;
    int height;
    int depth;
    std::shared_ptr<Node> left, right;
    Node(char data) : data(data), height(0), depth(0), left(nullptr), right(nullptr) {}
};

// inorder: left root right
void printInorder(Node *node)
{
    if (node->left.get() == nullptr && node->right.get() == nullptr)
    {
        std::cout << node->data;
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


// inorder: left root right
void printInorderWithHeightDepth(Node *node)
{
    if (node->left == nullptr)
    {
        std::cout << node->data << ", d= " << node->depth << ", h= " << node->height << std::endl;
        return;
    }
    printInorder((node->left).get());
    std::cout << node->data << ", d= " << node->depth << ", h= " << node->height << std::endl;
    printInorder((node->right).get());
}

void assignDepth(Node *node, int d)
{
    node->depth = d;
    // base case
    if (node->left.get() == nullptr && node->right.get() == nullptr)
    {
        return;
    }

    d++;

    if (node->left.get() != nullptr)
    {
        assignDepth(node->left.get(), d);
    }
    if (node->right.get() != nullptr)
    {
        assignDepth(node->right.get(), d);
    }
}

void assignHeight(Node *node)
{

    // define base case
    // go to leftmost leaf
    // once there assign it height 0
    // retur to parent and go down right side untill leaf and assign 0
    // while moving upward increase height
    // at parent take max(left_height, right_height) +1
    // repeat untill root

    int heightLeftSubtree = 0;
    int heightRightSubtree = 0;

    if (node->left.get() == nullptr && node->right.get() == nullptr)
    {
        node->height = 0;
        return;
    }

    if (node->left.get() != nullptr)
    {
        assignHeight(node->left.get());
        heightLeftSubtree = node->left.get()->height;
    }

    if (node->right.get() != nullptr)
    {
        assignHeight(node->right.get());
        heightRightSubtree = node->right.get()->height;
    }

    node->height = (heightLeftSubtree >= heightRightSubtree) ? heightLeftSubtree : heightRightSubtree;
    node->height++;
}

int getMaxDepth(Node *node, int max_depth_so_far)
{

    if (node->left.get() == nullptr && node->right.get() == nullptr)
    {
        return (node->depth > max_depth_so_far) ? node->depth : max_depth_so_far;
    }

    if (node->left.get() != nullptr)
    {
        int dLeft = getMaxDepth(node->left.get(), max_depth_so_far);
        if (dLeft > max_depth_so_far)
        {
            max_depth_so_far = dLeft;
        }
    }

    if (node->right.get() != nullptr)
    {
        int dRight = getMaxDepth(node->right.get(), max_depth_so_far);
        if (dRight > max_depth_so_far)
        {
            max_depth_so_far = dRight;
        }
    }

    return max_depth_so_far + 1;
}


void clean_string_from_trailing_underscores(std::string &s)
{
    int i;
    for (i = s.length() - 1; i >= 0; i--)
    {
        char c = s.at(i);
        if (isalpha(c) != 0)
        {
            break;
        }
    }

    s = std::string(&s[0], &s[i + 1]);
}

void iterateTree(Node *node, int target_depth, int max_depth, std::string &output_string)
{

    if (target_depth == node->depth)
    {
        output_string = output_string + ' ' + node->data + ' ';
    }

    if (target_depth > node->depth)
    {
        if (node->left.get() == nullptr) {
            output_string = output_string + " _ ";
        }
        if (node->right.get() == nullptr) {
            output_string = output_string + " _ ";
        }
    }

    if (node->left.get() == nullptr && node->right.get() == nullptr)
    {
        return;
    }

    if (node->left.get())
    {
        iterateTree(node->left.get(), target_depth, max_depth, output_string);
    }

    if (node->right.get())
    {
        iterateTree(node->right.get(), target_depth, max_depth, output_string);
    }
}

void printBTArrayRepresentation(Node *node, int target_depth, int max_depth)
{ // ugly but works

    std::string output_string = "";
    while (target_depth != max_depth)
    {
        iterateTree(node, target_depth, max_depth, output_string);
        target_depth++;
    }

    clean_string_from_trailing_underscores(output_string);
    std::cout << output_string;
}

int main()
{

    Node root = Node('a');
    root.left = std::make_shared<Node>('b');
    root.right = std::make_shared<Node>('c');

    root.left.get()->left = std::make_shared<Node>('d');
    root.left.get()->right = std::make_shared<Node>('e');

    root.left.get()->right.get()->left = std::make_shared<Node>('h');
    root.left.get()->right.get()->right = std::make_shared<Node>('i');

    root.right.get()->left = std::make_shared<Node>('f');
    root.right.get()->right = std::make_shared<Node>('g');

    root.right.get()->right.get() -> right = std::make_shared<Node>('X');

    assignDepth(&root, 0);
    assignHeight(&root);
    printInorder(&root);

    std::cout << std::endl;

    int maxDepth = getMaxDepth(&root, 0);
    std::cout << "maxDepth " << maxDepth << std::endl;

    printBTArrayRepresentation(&root, 0, maxDepth);
    std::cout << std::endl;
}
