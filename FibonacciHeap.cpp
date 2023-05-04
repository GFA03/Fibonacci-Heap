//
// Created by gfa on 5/3/23.
//
#include <FibonacciHeap.h>
#include <cmath>

Node::Node(int value) {
    this->value = value;
    this->marked = false;
    this->left = this;
    this->right = this;
    this->parent = nullptr;
    this->child = nullptr;
    this->degree = 0;
}

void Node::appendChild(Node *newChild) {
    if(this->child == nullptr) {
        this->child = newChild;
        newChild->parent = this;
        Node::linkNodes(newChild, newChild);
    }
    else {
        newChild->parent = this;
        Node::linkNodes(this->child, newChild);
    }
}

void Node::merge(Node* node1, Node* node2) {
    if(node1->value < node2->value) {
        node1->appendChild(node2);
        node1->degree++;
    }
    else {
        node2->appendChild(node1);
        node2->degree++;
    }
}

void Node::linkNodes(Node* baseNode, Node* linkedNode) {
    linkedNode->left = baseNode;
    linkedNode->right = baseNode->right;
    baseNode->right = linkedNode;
    linkedNode->right->left = linkedNode;
}

void display(Node* node, std::ostream& out){
    Node* startingPoint = node;
    Node* currentNode = node;
    while(currentNode->right != startingPoint){
        std::cout << currentNode->value << " ";
        if(currentNode->child != nullptr)
            display(currentNode->child, out);
        currentNode = currentNode->right;
    }
    std::cout << currentNode->value << " ";
    if(currentNode->child != nullptr)
        display(currentNode->child, out);
}

std::ostream& operator<<(std::ostream& out, const FibonacciHeap& obj) {
    out << "Number of nodes: " << obj.numberOfNodes << '\n';
    out << "Minimum value: " << obj.minNode->value << '\n';
    out << "Trees:\n";
    Node* currentNode = obj.minNode;
    Node* startingPoint = currentNode;
    while(currentNode->right != startingPoint) {
        out << currentNode->value << ' ';
        if(currentNode->child != nullptr)
            display(currentNode->child, out);
        out << '\n';
        currentNode = currentNode->right;
    }
    out << currentNode->value << ' ';
    if(currentNode->child != nullptr)
        display(currentNode->child, out);
    out << '\n';
    return out;
}

int FibonacciHeap::findMin() {
    return minNode->value;
}

void FibonacciHeap::insert(int value) {
    Node* newNode = new Node(value);
    if(this->numberOfNodes > 0) {
        Node::linkNodes(this->minNode, newNode);
    }

    if(this->minNode == nullptr)
        this->minNode = newNode;
    else if(this->minNode->value > newNode->value)
        this->minNode = newNode;
    this->numberOfNodes++;
}

Node* FibonacciHeap::mergeTrees(Node *root1, Node *root2, std::vector<Node *>& degrees) {
    Node* minNodeTemp;
    Node* maxNodeTemp;
    if(root1->value < root2->value)
    {
        minNodeTemp = root1;
        maxNodeTemp = root2;
    }
    else{
        minNodeTemp = root2;
        maxNodeTemp = root1;
    }
    degrees[minNodeTemp->degree] = nullptr;
    maxNodeTemp->left->right = maxNodeTemp->right;
    maxNodeTemp->right->left = maxNodeTemp->left;
    Node::merge(minNodeTemp, maxNodeTemp);
    return minNodeTemp;
}

int FibonacciHeap::extractMin() {
    int minValue = this->minNode->value;
    if(this->numberOfNodes == 1){
        this->minNode = nullptr;
        this->numberOfNodes--;
        return minValue;
    }
    int maxDegree = (int)ceil(log2(this->numberOfNodes))+1;
    std::vector<Node*> degrees(maxDegree, nullptr);

    Node* startingPoint;
    Node* newMinNode = this->minNode->right;
    Node* currentNode = newMinNode;

    if(this->minNode->child) {
        Node* minNodeChild = this->minNode->child;
        minNodeChild->parent = nullptr;
        startingPoint = minNodeChild;
        Node::linkNodes(newMinNode, minNodeChild);
        minNodeChild = minNodeChild->right;
        while(minNodeChild != startingPoint){
            minNodeChild->parent = nullptr;
            Node::linkNodes(newMinNode, minNodeChild);
            minNodeChild = minNodeChild->right;
        }
    }

    newMinNode = this->minNode->right;
    currentNode = newMinNode;

    while(currentNode != this->minNode){
        if(currentNode->value < newMinNode->value)
            newMinNode = currentNode;
        currentNode = currentNode->right;
    }

    this->minNode->left->right = this->minNode->right;
    this->minNode->right->left = this->minNode->left;
    this->minNode = newMinNode;

    currentNode = this->minNode;
    std::unordered_map<Node*, bool> passedBy;
    degrees[currentNode->degree] = currentNode;
    passedBy[currentNode] = true;
    currentNode = currentNode->right;

    Node* minNodeTemp;
    Node* currentNodeTemp; // if currentNode goes as a child then it will stop the while (that's why is needed a temporary current node)

    while(!passedBy[currentNode]) {
        passedBy[currentNode] = true;
        currentNodeTemp = currentNode->right;
        if(degrees[currentNode->degree] != nullptr) {
            minNodeTemp = FibonacciHeap::mergeTrees(currentNode, degrees[currentNode->degree], degrees);
            while(degrees[minNodeTemp->degree] != nullptr) {
                minNodeTemp = FibonacciHeap::mergeTrees(minNodeTemp, degrees[minNodeTemp->degree], degrees);
            }
            degrees[minNodeTemp->degree] = minNodeTemp;
        }else {
            degrees[currentNode->degree] = currentNode;
        }
        currentNode = currentNodeTemp;
    }
    this->numberOfNodes--;
    return minValue;
}


int main() {
    FibonacciHeap a;
    a.insert(2);
    a.insert(1);
    a.insert(3);
    a.insert(4);
    a.insert(6);
    a.extractMin();
    a.insert(1);
    a.insert(2);
    a.insert(10);
    a.insert(1);
    a.insert(16);
    a.insert(20);
    a.extractMin();
    std::cout << a;
}