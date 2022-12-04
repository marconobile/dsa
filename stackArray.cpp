#include <iostream>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <stdexcept>
#include <memory>
#include <variant>

/*Key-insights:
    - keep a running idx (here int top_idx) to perform operations quickly, initialize it at 1 step before the first element (-1)
    - maximum n of elements contained in stack = (size -1)
    - use std::stack in your application
    - use preconditions
    - the isEmpty(), isFull() correctness and usage is crucial
*/

/*
To compile:
g++ -o stack_exe.exe .\stack.cpp

arr size fixed, for dyanmic mememory use std::vector
initial top_idx pointing at -1

|idx N-1|
|_ ... _|
|_ ... _|
| idx 2 |
| idx 1 |
| idx 0 |

Example usages:
- balancing of symbols in parsers (e.g. scope checker)
- redo/undo in editors
- forward/backward in browser

*/

// TODO:
//  - Split in .cpp and .h
//  - It should be defined copy-ctor, operator=, move-ctor and move=  (for copies use shared_ptr  instead of unique_ptr)
//  - const and non cost versions of members

class Stack {
    private:
        int top_idx;
        const int stack_size;
        const int max_n_els = stack_size - 1;
        std::unique_ptr<std::variant<int, std::string> []> parr;
        bool isIdxValid(int idx) { return (idx >= 0 && idx <= max_n_els); }

    public:
        Stack(int size): top_idx(-1), stack_size(size) {
            parr = std::make_unique<std::variant<int, std::string> []>(stack_size);
            std::fill_n(parr.get(), stack_size, "Empty");
        }

        bool isEmpty() { return (top_idx==-1) ? true : false; }
        bool isFull() { return (top_idx==(max_n_els)) ? true : false; }
        int count() { return top_idx+1; }

        void push(int value) {
            if(isFull()){ throw std::overflow_error("Stack overflow! Cannot push value in the stack\n"); }
            parr[++top_idx] = value;
        }

        int pop() {
            if (isEmpty()){ throw std::underflow_error("Stack underflow! No value to pop the stack\n"); }
            int poppedValue = std::get<int>(parr[top_idx]);
            parr[top_idx--] = "Empty";
            return poppedValue;
        }

        int peek(int idx_to_peek) {
            if (isEmpty()) { throw std::underflow_error("Stack underflow! No value to pop the stack\n"); }
            if (!isIdxValid(idx_to_peek)) { throw std::range_error("Peeked idx not valid\n"); }
            return std::get<int>(parr[idx_to_peek]);
        }

        void change_value(int idx_to_change, int new_value) {
            if (!isIdxValid(idx_to_change)) { throw std::range_error("Change idx not valid\n"); }
            parr[idx_to_change] = new_value;
        }

        void display() {
            std::cout << "Values in the stack:\n";
            for (int i = max_n_els; i >= 0 ; i--) {
                std::visit([](const auto &elem) { std::cout << elem << '\n'; }, parr[i]);
            }
        }
};


int main(){
    std::cout << "Enter desired size of the array:\n";
    int size;
    std::cin >> size;
    Stack s(size);
    int option_selected, pos, value;

    do {
        std::cout << "What option do you want to perform? Select option number, enter 0 to exit.\n";
        std::cout << "1. push()\n";
        std::cout << "2. pop()\n";
        std::cout << "3. isEmpty()\n";
        std::cout << "4. isFull()\n";
        std::cout << "5. peek()\n";
        std::cout << "6. count()\n";
        std::cout << "7. change()\n";
        std::cout << "8. display()\n";
        std::cout << "9. clear screen\n";
        std::cin >> option_selected;

        switch(option_selected){
            case 0:
                break;
            case 1:
                std::cout << "Enter value to be pushed onto the stack: ";
                std::cin >> value;
                try {
                    s.push(value);
                    std::cout << "Value pushed on top of the stack succesfully.\n";
                } catch (std::overflow_error const& ex) {
                    std::cout << ex.what();
                }
                break;
            case 2:
                try {
                    s.pop();
                    std::cout << "Popped value on top of the stack.\n";
                } catch (std::underflow_error const& ex) {
                    std::cout << ex.what();
                }
                break;
            case 3:
                std::cout << "Is stack empty? " << (s.isEmpty() ? "True" : "False") << std::endl;
                break;
            case 4:
                std::cout << "Is stack full? " << (s.isFull() ? "True" : "False") << std::endl;
                break;
            case 5:
                std::cout << "Enter index to peek: ";
                std::cin >> pos;
                try {
                    std::cout << "Peek out: " << s.peek(pos) << std::endl;
                } catch (std::underflow_error const& ex) {
                    std::cout << ex.what();
                } catch (std::range_error const& ex) {
                    std::cout << ex.what();
                }
                break;
            case 6:
                std::cout << "Number of elements in the stack: " << s.count() << std::endl;
                break;
            case 7:
                std::cout << "Enter index to change: ";
                std::cin >> pos;
                std::cout << std::endl;
                std::cout << "Enter value to be changed at idx [" << pos << "]: ";
                std::cin >> value;
                std::cout << std::endl;
                try {
                    s.change_value(pos, value);
                } catch (std::range_error const& ex) {
                    std::cout << ex.what();
                }
                break;
            case 8:
                s.display();
                break;
            case 9:
                system("CLS");
                break;
            default:
                std::cout << "Enter proper option number\n";
        }
    } while (option_selected != 0);

    return 0;
}