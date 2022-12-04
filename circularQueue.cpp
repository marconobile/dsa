#include <iostream>
#include <stdexcept>

/*
Array-based implementation of a circular queue.
To achieve circularity we just need to use the module operator:

0 % N = 0
1 % N = 1
2 % N = 2
....
N-1 % N = N-1
N % N = 0
N+1 % N = 1
N+2 % N = 2
....
2N % N = 0

(rear+1) % size_of_container // rear +1 -> update then% for circularity

When you struggle to catch the right formula right away, mock-up a small example with pen and paper
Be very careful with order of statements when designing an operation
*/

class CircularQueue {
    private:
        int front;
        int rear;
        static const int q_size = 5;
        const int max_n_els = q_size - 1;
        int arr[q_size];
        int itemCount;

    public:

        int getFront() const { return front; }
        int getRear() const { return rear; }

        CircularQueue(): front(-1), rear(-1), itemCount(0) {
            std::fill_n(arr, q_size, 0);
        }

        bool isEmpty() { return (rear == -1 && front == -1) ? true : false; }
        bool isFull() { return (((rear+1) % q_size ) == front) ? true : false; }

        void enqueue(int value) {
            if (isFull()){ throw std::overflow_error("Queue overflow!\n"); }
            if (isEmpty()) { front++; }
            rear = (rear+1) % q_size;
            arr[rear] = value;
            itemCount++;
        }

        int dequeue() { // always consider all reset cases
            if (isEmpty()){ throw std::underflow_error("Queue underflow!\n"); }
            int return_value;
            itemCount--;
            if (front == rear) {
                return_value = arr[front];
                arr[front] = 0;
                front = -1;
                rear = -1;
                return return_value;
            }
            return_value = arr[front];
            arr[front] = 0;
            front = (front+1) % q_size;
            return return_value;
        }

        int count() { return itemCount; }

        void display() {
            std::cout << "Front of the queue: " << getFront() << std::endl;
            std::cout << "Rear of the queue: " << getRear() << std::endl;
            for (int &el : arr)
                std::cout << el << std::endl;
        }
};


int main(){
    CircularQueue q;
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