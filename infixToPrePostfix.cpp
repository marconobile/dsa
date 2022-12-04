#include <iostream>

struct StackNode
{
    char data;
    StackNode *prev;
    StackNode(char data) : data(data), prev(nullptr) {}
};

class Stack
{

private:
    int size;
    int n_of_els;
    StackNode *top;

public:
    Stack(int size) : size(size), top(nullptr), n_of_els(0) {}
    StackNode *getTop() const { return top; }
    int getNofEls() const { return n_of_els; }
    bool isFull();
    bool isEmpty();
    void push(StackNode *new_node);
    char pop();
    void display() const;
    void peek(int pos) const;
    void show_top() const;
};

void Stack::show_top() const { std::cout << top->data; }
bool Stack::isFull() { return (n_of_els == size) ? true : false; }
bool Stack::isEmpty() { return (n_of_els == 0) ? true : false; }

void Stack::display() const
{
    StackNode *tmp = top;
    while (tmp != nullptr)
    {
        std::cout << tmp->data << std::endl;
        tmp = tmp->prev;
    }
}

void Stack::peek(int pos) const
{
    int counter = 0;
    StackNode *tmp = top;
    while (counter != pos)
    {
        tmp = tmp->prev;
        counter++;
    }
    std::cout << tmp->data << std::endl;
}

void Stack::push(StackNode *new_node)
{
    if (isFull())
    {
        std::cout << "stack overflow\n";
        return;
    }
    else if (top == nullptr)
    {
        top = new_node;
        n_of_els++;
        return;
    }
    new_node->prev = top;
    top = new_node;
    n_of_els++;
    return;
}

char Stack::pop()
{
    if (isEmpty() || top == nullptr)
    {
        throw std::string("stack underflow\n");
    }
    char res = top->data;
    top = top->prev;
    n_of_els--;
    return res;
}

/*************************************************************************/

#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <cassert>

bool findCharInStack(char c, const Stack &stack)
{
    StackNode *tmp = stack.getTop();
    while (tmp != nullptr)
    {
        if (tmp->data == c)
        {
            return true;
        }
        tmp = tmp->prev;
    }
    return false;
}

int assignPriority(char ch)
{
    if (ch == '+' || ch == '-')
    {
        return 0;
    }
    else if (ch == '*' || ch == '/')
    {
        return 1;
    }
    else if (ch == '^')
    {
        return 3;
    }
}

int incomingHasHigherPrecedence(char ch, char currTop)
{

    if (currTop == '(' || currTop == ')')
    {
        return 1;
    }
    int priorityCurrent = assignPriority(currTop);
    int priorityIncoming = assignPriority(ch);

    if (priorityIncoming > priorityCurrent)
    {
        return 1;
    }
    else if (priorityIncoming == priorityCurrent)
    {
        return 0;
    }
    return -1;
}

void dropParenthesisFromOut(std::string &out)
{
    out.erase(remove(out.begin(), out.end(), '('), out.end());
    out.erase(remove(out.begin(), out.end(), ')'), out.end());
}

std::string confert_infix_to_postfix(std::string s)
{
    Stack stack = Stack(s.length());
    std::vector<std::shared_ptr<StackNode>> vect;
    std::string out = "";
    char currTop;

    for (char ch : s)
    {
        if (isalpha(ch))
        {
            out += ch;
        }
        else
        {
            if (ch == ')')
            {
                while (stack.getTop()->data != '(')
                {
                    out += stack.pop();
                }
                out += stack.pop();
            }
            else if (stack.isEmpty() || findCharInStack('(', stack))
            {
                vect.push_back(std::make_shared<StackNode>(ch));
                stack.push(vect.back().get());
            }
            else if (ch == '(')
            {
                vect.push_back(std::make_shared<StackNode>(ch));
                stack.push(vect.back().get());
            }
            else
            {
                currTop = stack.getTop()->data;
                if (ch == '^')
                {
                    vect.push_back(std::make_shared<StackNode>(ch));
                    stack.push(vect.back().get());
                }
                else if (incomingHasHigherPrecedence(ch, currTop) == 1)
                {
                    vect.push_back(std::make_shared<StackNode>(ch));
                    stack.push(vect.back().get());
                }
                else if (incomingHasHigherPrecedence(ch, currTop) == -1)
                {
                    while (incomingHasHigherPrecedence(ch, currTop) == -1 || incomingHasHigherPrecedence(ch, currTop) == 0)
                    {
                        out += stack.pop();
                        if (stack.getTop())
                        {
                            currTop = stack.getTop()->data;
                        }
                        else
                        {
                            break;
                        }
                    }
                    vect.push_back(std::make_shared<StackNode>(ch));
                    stack.push(vect.back().get());
                }
                else
                { // if (incomingHasHigherPrecedence(ch, currTop) == 0)
                    out += stack.pop();
                    vect.push_back(std::make_shared<StackNode>(ch));
                    stack.push(vect.back().get());
                }
            }
        }
    }

    while (stack.getNofEls() != 0)
    {
        out += stack.pop();
    }
    dropParenthesisFromOut(out);
    return out;
}

std::string confert_infix_to_prefix(std::string s)
{
    Stack stack = Stack(s.length());
    std::vector<std::shared_ptr<StackNode>> vect;
    std::string out = "";
    char currTop;

    for (char ch : s)
    {
        if (isalpha(ch))
        {
            out += ch;
        }
        else if (stack.isEmpty())
        {
            vect.push_back(std::make_shared<StackNode>(ch));
            stack.push(vect.back().get());
        }
        else
        {
            currTop = stack.getTop()->data;
            if (ch == '(')
            {
                while (stack.getTop()->data != ')' && stack.getTop())
                { // invert bool operators
                    out += stack.pop();
                }
                out += stack.pop();
            }
            else if (incomingHasHigherPrecedence(ch, currTop) >= 0 || ch == ')')
            {
                vect.push_back(std::make_shared<StackNode>(ch));
                stack.push(vect.back().get());
            }
            else if (incomingHasHigherPrecedence(ch, currTop) < 0)
            {
                if (findCharInStack(')', stack))
                {
                    while (stack.getTop()->data != ')' && stack.getTop())
                    {
                        out += stack.pop();
                    }
                }
                else
                {
                    while (stack.getTop() && incomingHasHigherPrecedence(ch, stack.getTop()->data) != 0)
                    {
                        out += stack.pop();
                    }
                }
                vect.push_back(std::make_shared<StackNode>(ch));
                stack.push(vect.back().get());
            }
        }
    }

    while (stack.getNofEls() != 0)
    {
        out += stack.pop();
    }

    dropParenthesisFromOut(out);
    return out;
}

int main()
{
    std::string out;
    std::string s = "K+L-M*N+(O^P)*W/U/V*T+Q";
    std::cout << "Infix version: " << s << std::endl;
    out = confert_infix_to_postfix(s);
    assert(out == "KL+MN*-OP^W*U/V/T*+Q+");
    std::cout << "postfx version: " << out << std::endl;

    std::reverse(s.begin(), s.end());
    out = confert_infix_to_prefix(s);
    std::reverse(out.begin(), out.end());
    std::cout << "prefix version: " << out << std::endl;
    assert(out == "++-+KL*MN*//*^OPWUVTQ");

    s = "A-B+(M^N)*(O+P)-Q/R^S*T+Z";
    std::cout << "Infix version: " << s << std::endl;
    out = confert_infix_to_postfix(s);
    assert(out == "AB-MN^OP+*+QRS^/T*-Z+");
    std::cout << "postfx version: " << out << std::endl;

    std::reverse(s.begin(), s.end());
    out = confert_infix_to_prefix(s);
    std::reverse(out.begin(), out.end());
    assert(out == "+-+-AB*^MN+OP*/Q^RSTZ");
    std::cout << "prefix version: " << out << std::endl;

    s = "K+L-M*(N+(O^P)*W/U/V)*T+Q";
    std::cout << "Infix version: " << s << std::endl;
    std::reverse(s.begin(), s.end());
    out = confert_infix_to_prefix(s);
    std::reverse(out.begin(), out.end());
    std::cout << "prefix version: " << out << std::endl;
    assert(out == "+-+KL**M+N//*^OPWUVTQ");
}