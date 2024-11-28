#include <stdio.h>

// What makes up a Huffman tree node
struct minHeapNode
{};

// What makes up a collection of Huffman tree nodes
struct minHeap
{};

// Allocates a new Huffamn tree node with a given character and frequency
struct minHeapNode* newNode(char data, unsigned freq)
{}; 

// Creates a Huffman tree of given capacity
struct minHeap* createMinHeap(unsigned capacity)
{};

// Swaps two Huffman tree nodes
void swapMinHeapNode(struct minHeapNode** a, struct minHeapNode** b)
{}

// Heapify's the Huffman tree
void minHeapify(struct minHeap* minHeap, int index)
{}

// Checks if a heap is of size 1
bool isSizeOne(struct minHeap* minHeap)
{}

// Extracts min-node from Huffman tree
struct minHeapNode* extractMin(struct minHeap* minHeap)
{}

// Inserts a new node to the Huffman tree
void insertMinHeap(struct minHeap* minHeap, struct minHeapNode* minHeapNode)
{}

// Builds Huffman tree
void buildMinHeap(struct minHeap* minHeap)
{}

// Prints an array of given size
void printArr(int arr[], int arraySize)
{}

// Checks if a given node is a leaf node
bool isLeaf(struct minHeapNode* root)
{}

// Creates a Huffman tree of capacity equal to size and 
// inserts all characters of data[] into the Huffman tree.
// Initially, the size of the Huffman tree is equal to the capacity
struct minHeap* createAndBuildMinHeap(char data[], int freq[], int size)
{}

// The main function to build the Huffman tree
struct minHeapNode* buildHuffmanTree(char data[], int freq[], int size)
{}

// Prints Huffman codes from the root of the Huffman tree
// Uses arr[] to store codes
void printCodes(struct minHeapNode* root, int arr[], int top)
{}

// Builds a Huffman Treeand prints codes by traversing the built Huffman tree
void huffmanCodes(char data[], int freq[], int size)
{}

int main()
{
    
}