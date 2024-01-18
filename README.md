# Fibonacci Heap Implementation in C++

This project implements a Fibonacci Heap data structure using C++ classes. Fibonacci Heaps are a type of heap data structure that supports efficient decrease key and merge operations compared to other types of heaps.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Usage](#usage)
- [Classes](#classes)
- [Example](#example)
- [Contributing](#contributing)
- [License](#license)

## Introduction

The Fibonacci Heap is a type of heap data structure that provides efficient implementations of decrease key and merge operations. It consists of a collection of trees with specific properties that allow for constant amortized time complexity for these operations.

## Features

- **Node Structure:** The `Node` structure represents a node in the Fibonacci Heap, containing information such as value, degree, marking, and pointers to parent, child, left, and right nodes.

- **FibonacciHeap Class:** The `FibonacciHeap` class encapsulates the Fibonacci Heap data structure, providing methods for insertion, finding the minimum element, extracting the minimum element, decreasing key, and more.

## Usage

1. **Include the Header File:**
```cpp
#include "FibonacciHeap.h"
```

2. **Create an instance of FibonacciHeap**
```cpp
FibonacciHeap heap
```

3. Enjoy the class methods.

## Classes

### Node Structure

The `Node` structure represents a node in the Fibonacci Heap.

- `value`: The value stored in the node.
- `degree`: The degree of the node.
- `marked`: A boolean indicating whether the node is marked.
- `left`, `right`: Pointers to the left and right siblings.
- `parent`: Pointer to the parent node.
- `child`: Pointer to the child node.

### FibonacciHeap Class

The `FibonacciHeap` class encapsulates the Fibonacci Heap data structure.

- `minNode`: Pointer to the minimum node in the heap.
- `numberOfNodes`: The total number of nodes in the heap.
- `nodeList`: A vector storing pointers to all nodes in the heap.

## Example

```cpp
#include "FibonacciHeap.h"

int main() {
    FibonacciHeap fibonacciHeap;

    // Perform operations on the Fibonacci Heap

    return 0;
}
