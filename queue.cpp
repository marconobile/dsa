#include <iostream>
#include <stdexcept>

// IMPORTANT: this is a naive immplementation of a queue based on array, not a circular queue

/*
Example usages:
- ordered scheduling/event handling
- synchronization between threads/data transfer between threads
*/


// keep 2 running idxs, initialize them at 1 step before the first element (-1). Move them in an asymmetric manner; process/use their relationship to keep track of the status of the queue
// there might be corner cases at the first insertion in the data struct
// always remember to replace when removing from ds


/*
Initial state:

rear = -1   0           1        2      3       4
            ------------------------------------
            | idx0 | idx1 | idx2 | idx3 | idx4 |
            ------------------------------------
front = -1  0       1      2      3      4

*/

class Queue {
    private:
        int front;
        int rear;
        static const int q_size = 5;
        const int max_n_els = q_size - 1;
        int arr[q_size];


    public:
        Queue(): front(-1), rear(-1) {
            std::fill_n(arr, q_size, 0);
        }

        bool isEmpty() { return (rear == -1 && front == -1) ? true : false; }
        bool isFull() { return (rear == max_n_els) ? true : false; }

        void enqueue(int value) {
            if (isFull()){ throw std::overflow_error("Queue overflow!\n"); }
            if (isEmpty()) { front++; }
            arr[++rear] = value;
        }

        int dequeue() { // always consider all reset cases
            if (isEmpty()){ throw std::underflow_error("Queue underflow!\n"); }
            int return_value;
            if (front == rear) {
                return_value = arr[front];
                arr[front] = 0;
                front = -1;
                rear = -1;
                return return_value;
            }
            return_value = arr[front];
            arr[front++] = 0;
            return return_value;
        }

        int count() { return rear - front + 1; }

        void display() {
            std::cout << "Front of the queue:\n";
            for (int &el : arr)
                std::cout << el << std::endl;
            std::cout << "Rear of the queue:\n";
        }

};


int main(){
    Queue q;
    int option_selected, value;

    do {
        std::cout << "What option do you want to perform? Select option number, enter 0 to exit.\n";
        std::cout << "1. enqueue()\n";
        std::cout << "2. dequeue()\n";
        std::cout << "3. isEmpty()\n";
        std::cout << "4. isFull()\n";
        std::cout << "5. count()\n";
        std::cout << "6. display()\n";
        std::cout << "7. clear screen\n";
        std::cin >> option_selected;

        switch(option_selected){
            case 0:
                break;
            case 1:
                std::cout << "Enter value to be inserted into the queue: ";
                std::cin >> value;
                try {
                    q.enqueue(value);
                    std::cout << "Value inserted into the queue succesfully.\n";
                } catch (std::overflow_error const& ex) {
                    std::cout << ex.what();
                }
                break;
            case 2:
                try {
                    q.dequeue();
                    std::cout << "Value dequeue from  the queue succesfully.\n";
                } catch (std::underflow_error const& ex) {
                    std::cout << ex.what();
                }
                break;
            case 3:
                std::cout << "Is queue empty? " << (q.isEmpty() ? "True" : "False") << std::endl;
                break;
            case 4:
                std::cout << "Is queue full? " << (q.isFull() ? "True" : "False") << std::endl;
                break;
            case 5:
                std::cout << "Number of elements in the stack: " << q.count() << std::endl;
                break;
            case 6:
                q.display();
                break;
            case 7:
                system("CLS");
                break;
            default:
                std::cout << "Enter proper option number\n";
        }
    } while (option_selected != 0);
}