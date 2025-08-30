/*
 * Name: Baldwin Cepeda
 * GitHub: https://github.com/BaldwinCepeda
 * Website: http://baldwincepeda.me/
 *
 * Description:
 * This program implements a stack and queue using linked lists in C++.
 * The `LLStack` class provides standard stack operations (LIFO), while
 * the `LLQueue` class implements a queue with FIFO behavior.
 *
 * Key Features:
 * - `LLStack`: Supports `push`, `pop`, and `printStack`, with a dummy node as the top.
 * - `LLQueue`: Includes `insertQ`, `deleteQ`, and `printQueue`, with indicators for
 *   `head` and `tail` positions in the queue.
 * - Demonstrates the transfer of elements from a stack to a queue, maintaining
 *   respective order for each data structure.
 *
 * The program reads input from a file, logs operations to a log file, and
 * outputs the stack and queue structures to an output file for verification.
 */
#include <iostream>
#include <fstream>
using namespace std;

class listNode
{
public:
    int data;
    listNode *next;

    listNode(int data) : data(data), next(nullptr) {}

    void printNode(ofstream &file)
    {
        file << "(" << data << ", ";
        if (next)
        {
            file << next->data;
        }
        else
        {
            file << "null"; // Indicate that there's no next node
        }
        file << ") ";
    }
};

class LLStack
{
public:
    listNode *top;

    LLStack()
    {
        top = new listNode(-1); // Dummy node
    }

    bool isEmpty()
    {
        return top->next == nullptr;
    }

    void push(int data)
    {
        listNode *newNode = new listNode(data);
        newNode->next = top->next;
        top->next = newNode;
    }

    listNode *pop()
    {
        if (isEmpty())
            return nullptr;

        listNode *tmp = top->next;
        top->next = tmp->next;
        tmp->next = nullptr;
        return tmp;
    }

    void buildStack(ifstream &inFile, ofstream &logFile)
    {
        logFile << "** Entering buildStack() **\n";

        int data;
        while (inFile >> data)
        {
            logFile << "Input data is " << data << endl;
            push(data);
            logFile << "** Printing Stack after push **\n";
            printStack(logFile);
        }

        logFile << "** Leaving buildStack() **\n";
    }

    void printStack(ofstream &file)
    {
        file << "Stack (top): ";
        listNode *current = top->next;
        while (current != nullptr)
        {
            current->printNode(file);
            current = current->next;
        }
        file << "NULL\n";
    }
};
class LLQueue
{
public:
    listNode *head; // Dummy head node
    listNode *tail; // Points to the last node of the queue

    // Constructor: Initializes the queue with a dummy node
    LLQueue()
    {
        head = new listNode(-999); // Dummy node with data -999
        tail = head;               // Initially, tail points to the head
    }

    // insertQ: Inserts a new node at the end of the queue
    void insertQ(listNode *newNode)
    {
        tail->next = newNode;    // Link current tail to new node
        tail = newNode;          // Update tail to the new node
        newNode->next = nullptr; // Ensure new node’s next is null
    }

    // deleteQ: Removes and returns the first node after the dummy node (FIFO behavior)
    listNode *deleteQ()
    {
        if (head->next == nullptr) // Queue is empty
            return nullptr;

        listNode *tmp = head->next; // First real node in the queue
        head->next = tmp->next;     // Update head to skip over tmp
        if (head->next == nullptr)  // If queue becomes empty, reset tail to head
            tail = head;

        tmp->next = nullptr; // Detach tmp from the queue
        return tmp;
    }

    // buildQueue: Pops nodes from the stack and inserts them into the queue
    void buildQueue(LLStack &stack, ofstream &logFile)
    {
        logFile << "** Entering buildQueue() **\n";

        while (!stack.isEmpty())
        {
            listNode *newNode = stack.pop(); // Pop from stack
            logFile << "** Node popped from stack: " << newNode->data << " **\n";
            logFile << "** Printing stack after pop **\n";
            stack.printStack(logFile);

            insertQ(newNode); // Insert at the end of the queue
            logFile << "** Printing Queue after insert **\n";
            printQueue(logFile);
        }

        logFile << "** Leaving buildQueue() **\n";
    }
    void printQueue(ofstream &file)
    {
        file << "Queue (head): ";
        listNode *current = head;
        while (current != nullptr)
        {
            current->printNode(file);
            if (current == tail)
            {
                file << "(tail) "; // Indicate the tail position
            }
            current = current->next;
        }
        file << "NULL\n";
    }
};

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cerr << "Usage: " << argv[0] << " <inFile> <outFile1> <logFile>\n";
        return 1;
    }

    ifstream inFile(argv[1]);
    ofstream outFile1(argv[2]);
    ofstream logFile(argv[3]);

    if (!inFile.is_open() || !outFile1.is_open() || !logFile.is_open())
    {
        cerr << "Error opening files.\n";
        return 1;
    }

    LLStack stack;
    outFile1 << "** calling buildStack() **\n";
    stack.buildStack(inFile, logFile);

    outFile1 << "** Printing the stack after buildStack **\n";
    stack.printStack(outFile1);
    // outFile1 << "** TESTING **\n";
    // stack.pop();
    // outFile1 << "** After  pop ] **\n";
    // stack.printStack(outFile1);// outFile1 << "** TESTING **\n";
    // stack.pop();
    // outFile1 << "** After  pop2 ] **\n";
    // stack.printStack(outFile1);
    LLQueue queue;
    outFile1 << "** calling buildQueue() **\n";
    queue.buildQueue(stack, logFile);

    outFile1 << "** Printing the queue after buildQueue **\n";
    queue.printQueue(outFile1);

    // outFile1 << "** TESTING **\n";
    // stack.pop();
    // outFile1 << "** After  pop3 ] **\n";
    // stack.printStack(outFile1);

    inFile.close();
    outFile1.close();
    logFile.close();

    return 0;
}