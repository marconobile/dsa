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
	bool isFull();
	bool isEmpty();
	void push(StackNode *new_node);
	char pop();
	void display() const;
	void peek(int pos) const;
	void show_top() const;

};

void Stack::show_top() const { std::cout << "Top element: " << top->data << std::endl; }
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

int main()
{

	Stack stack = Stack(5);

	StackNode n0 = StackNode(0);
	StackNode n1 = StackNode(1);
	StackNode n2 = StackNode(2);
	StackNode n3 = StackNode(3);
	StackNode n4 = StackNode(4);
	StackNode n5 = StackNode(5);

	stack.push(&n0);
	stack.push(&n1);
	stack.push(&n2);
	stack.push(&n3);
	stack.push(&n4);
	stack.push(&n5);

	std::cout << "Is stack full: " << stack.isFull() << std::endl;
	std::cout << "Is stack empty: " << stack.isEmpty() << std::endl;

	stack.show_top();

	std::cout << "Full list\n";
	stack.display();
	stack.pop();
	stack.pop();
	stack.pop();

	std::cout << "After pop\n";
	stack.display();

	std::cout << "Showing full list with peek\n";
	stack.peek(0);
	stack.peek(1);
	std::cout << "Indeed showtop returns: \n";
	stack.show_top();

	std::cout << "Then emptying stack: \n";

	try
	{
		stack.pop();
		stack.pop();
		stack.pop();
		stack.pop();
	}
	catch (std::string &e)
	{
		std::cout << e << std::endl;
	}
	stack.push(&n5);
	stack.show_top();
}