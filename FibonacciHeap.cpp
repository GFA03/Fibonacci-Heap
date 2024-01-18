//
// Created by gfa on 5/3/23.
//
#include "FibonacciHeap.h"

Node::Node(int value)
{
    this->value = value;
    this->marked = false;
    this->left = this;
    this->right = this;
    this->parent = nullptr;
    this->child = nullptr;
    this->degree = 0;
}

void Node::appendChild(Node *newChild)
{
    if (this->child == nullptr)
    {
        this->child = newChild;
        newChild->parent = this;
        Node::linkNodes(newChild, newChild);
    }
    else
    {
        newChild->parent = this;
        Node::linkNodes(this->child, newChild);
    }
}

void Node::merge(Node *node1, Node *node2)
{
    if (node1->value <= node2->value)
    {
        node1->appendChild(node2);
        node1->degree++;
    }
    else
    {
        node2->appendChild(node1);
        node2->degree++;
    }
}

void Node::linkNodes(Node *baseNode, Node *linkedNode)
{
    linkedNode->left = baseNode;
    linkedNode->right = baseNode->right;
    baseNode->right = linkedNode;
    linkedNode->right->left = linkedNode;
}

void display(Node *node, std::ostream &out)
{
    Node *startingPoint = node;
    Node *currentNode = node;
    while (currentNode->right != startingPoint)
    {
        std::cout << currentNode->value << " ";
        if (currentNode->child != nullptr)
            display(currentNode->child, out);
        currentNode = currentNode->right;
    }
    std::cout << currentNode->value << " ";
    if (currentNode->child != nullptr)
        display(currentNode->child, out);
}

std::ostream &operator<<(std::ostream &out, const FibonacciHeap &obj)
{
    out << "Number of nodes: " << obj.numberOfNodes << '\n';
    if (obj.minNode)
        out << "Minimum value: " << obj.minNode->value << '\n';
    else
    {
        out << "Nodes not found!\n";
        return out;
    }
    out << "Trees:\n";
    Node *currentNode = obj.minNode;
    Node *startingPoint = currentNode;
    while (currentNode->right != startingPoint)
    {
        out << currentNode->value << ' ';
        if (currentNode->child != nullptr)
            display(currentNode->child, out);
        out << '\n';
        currentNode = currentNode->right;
    }
    out << currentNode->value << ' ';
    if (currentNode->child != nullptr)
        display(currentNode->child, out);
    out << '\n';
    return out;
}

Node *FibonacciHeap::getNode(int index) const
{
    if (index >= 0 && index <= this->numberOfNodes)
        return this->nodeList[index];
    return nullptr;
}

void FibonacciHeap::printNodeList()
{
    for (int i = 0; i < this->nodeList.size(); ++i)
        std::cout << this->nodeList[i]->value << " ";
    std::cout << '\n';
}

int FibonacciHeap::findMin()
{
    return minNode->value;
}

void FibonacciHeap::insert(int value)
{
    Node *newNode = new Node(value);
    this->nodeList.push_back(newNode);
    if (this->numberOfNodes > 0)
    {
        Node::linkNodes(this->minNode, newNode);
    }

    if (this->minNode == nullptr)
        this->minNode = newNode;
    else if (this->minNode->value > newNode->value)
        this->minNode = newNode;
    this->numberOfNodes++;
}

Node *FibonacciHeap::mergeTrees(Node *root1, Node *root2, std::vector<Node *> &degrees)
{
    Node *minNodeTemp;
    Node *maxNodeTemp;
    if (root1->value <= root2->value)
    {
        minNodeTemp = root1;
        maxNodeTemp = root2;
    }
    else
    {
        minNodeTemp = root2;
        maxNodeTemp = root1;
    }
    degrees[minNodeTemp->degree] = nullptr;
    maxNodeTemp->left->right = maxNodeTemp->right;
    maxNodeTemp->right->left = maxNodeTemp->left;
    Node::merge(minNodeTemp, maxNodeTemp);
    return minNodeTemp;
}

int FibonacciHeap::extractMin()
{
    int minValue = this->minNode->value;
    for (int i = 0; i < this->nodeList.size(); ++i)
        if (this->nodeList[i] == this->minNode)
        {
            this->nodeList.erase(this->nodeList.begin() + i);
            break;
        }
    if (this->numberOfNodes == 1)
    {
        this->minNode = nullptr;
        this->numberOfNodes--;
        return minValue;
    }
    int maxDegree = (int)ceil(log2(this->numberOfNodes)) + 1;
    std::vector<Node *> degrees(maxDegree, nullptr);

    Node *startingPoint;
    Node *newMinNode = this->minNode->right;
    Node *currentNode = newMinNode;

    if (this->minNode->child)
    {
        Node *minNodeChild = this->minNode->child;
        Node *tempNode;
        minNodeChild->parent = nullptr;
        startingPoint = minNodeChild;
        tempNode = minNodeChild->right;
        Node::linkNodes(newMinNode, minNodeChild);
        minNodeChild = tempNode;
        while (minNodeChild != startingPoint)
        {
            minNodeChild->parent = nullptr;
            tempNode = minNodeChild->right;
            Node::linkNodes(newMinNode, minNodeChild);
            minNodeChild = tempNode;
        }
    }

    newMinNode = this->minNode->right;
    currentNode = newMinNode;

    while (currentNode != this->minNode)
    {
        if (currentNode->value < newMinNode->value)
            newMinNode = currentNode;
        currentNode = currentNode->right;
    }

    this->minNode->left->right = this->minNode->right;
    this->minNode->right->left = this->minNode->left;
    this->minNode = newMinNode;

    currentNode = this->minNode;
    std::unordered_map<Node *, bool> passedBy;
    degrees[currentNode->degree] = currentNode;
    passedBy[currentNode] = true;
    currentNode = currentNode->right;

    Node *minNodeTemp;
    Node *currentNodeTemp; // if currentNode goes as a child then it will stop the while (that's why is needed a temporary current node)

    while (!passedBy[currentNode])
    {
        passedBy[currentNode] = true;
        currentNodeTemp = currentNode->right;
        if (degrees[currentNode->degree] != nullptr)
        {
            minNodeTemp = FibonacciHeap::mergeTrees(degrees[currentNode->degree], currentNode, degrees);
            while (degrees[minNodeTemp->degree] != nullptr)
            {
                if (minNodeTemp == this->minNode)
                    minNodeTemp = FibonacciHeap::mergeTrees(minNodeTemp, degrees[minNodeTemp->degree], degrees);
                else
                    minNodeTemp = FibonacciHeap::mergeTrees(degrees[minNodeTemp->degree], minNodeTemp, degrees);
            }
            degrees[minNodeTemp->degree] = minNodeTemp;
        }
        else
        {
            degrees[currentNode->degree] = currentNode;
        }
        currentNode = currentNodeTemp;
    }
    this->numberOfNodes--;
    return minValue;
}

void FibonacciHeap::cutChild(Node *parent, Node *child)
{
    if (parent->child == child)
    {
        if (parent->degree == 1)
        {
            parent->child = nullptr;
        }
        else
        {
            parent->child = child->left;
        }
    }
    child->right->left = child->left;
    child->left->right = child->right;
    Node::linkNodes(this->minNode, child);
    parent->degree--;
    child->marked = false;
    if (child->value < this->minNode->value)
        this->minNode = child;
    if (parent->marked == true)
    {
        if (parent->parent != nullptr)
            cutChild(parent->parent, parent);
    }
    else
    {
        if (parent->parent != nullptr)
            parent->marked = true;
    }
}

void FibonacciHeap::decreaseKey(Node *node, int newValue)
{
    if (newValue >= node->value)
        return;
    if (node->parent == nullptr)
    {
        node->value = newValue;
        return;
    }
    if (newValue >= node->parent->value)
        return;
    node->value = newValue;
    if (node->parent == nullptr)
    {
        if (this->minNode->value > newValue)
            this->minNode = node;
        return;
    }
    cutChild(node->parent, node);
}