#include "FibonacciHeap.h"

int main()
{
    FibonacciHeap a;
    a.insert(2);
    a.insert(1);
    a.insert(3);
    a.insert(4);
    a.insert(6);
    a.extractMin();
    //    a.printNodeList();
    a.insert(1);
    a.insert(2);
    a.insert(10);
    a.insert(1);
    a.insert(16);
    a.insert(20);
    a.extractMin();
    a.extractMin();
    a.printNodeList();
    a.decreaseKey(a.getNode(0), 1);
    std::cout << a;
    //    std::cout << a.getNode(5)->value;
}