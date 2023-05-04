//
// Created by gfa on 5/3/23.
//

#ifndef FIBONACCIHEAPS_FIBONACCIHEAP_H
#define FIBONACCIHEAPS_FIBONACCIHEAP_H

#include <vector>
#include <iostream>
#include <unordered_map>

struct Node{
    int value;
    int degree;
    bool marked;
    Node* left;
    Node* right;
    Node* parent;
    Node* child;

    explicit Node(int value);
    void appendChild(Node* newChild);
    static void linkNodes(Node* baseNode, Node* linkedNode);
    static void merge(Node* node1, Node* node2);
};

class FibonacciHeap{
    Node* minNode;
    int numberOfNodes;
public:
    FibonacciHeap():minNode(nullptr), numberOfNodes(0){}

    friend std::ostream& operator<<(std::ostream& out, const FibonacciHeap& obj);

    int findMin();
//    void merge(Node* root1, Node* root2);
    void insert(int value);
    static void mergeTrees(Node* root1, Node* root2, std::vector<Node*> degrees);
    int extractMin();
    void decreaseKey();
};

#endif //FIBONACCIHEAPS_FIBONACCIHEAP_H
