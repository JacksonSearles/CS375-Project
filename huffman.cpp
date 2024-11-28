#include <stdio.h>
#include <stdlib.h>

#define  MAX_TREE_HEIGHT 100

// What makes up a min heap tree node
struct minHeapNode
{
    char data; // one of the characters
    unsigned freq; // frequency of the character
    struct minHeapNode *leftNode, *rightNode; // nodes to left and right of this node
};

// What makes up a collection of min heap nodes
struct minHeap
{
    unsigned size; // current size of the min heap
    unsigned capacity; // capacity of min heap
    struct minHeapNode** nodeArray; // array of min heap node pointers, makes up the min heap
};

// Allocates a new min heap node with a given character and frequency
struct minHeapNode* newNode(char data, unsigned freq)
{
    // create a new temporary node
    struct minHeapNode* tempNode = (struct minHeapNode*)malloc(sizeof(minHeapNode));

    // set tempNodes left and rights node to NULL
    tempNode->leftNode = tempNode->rightNode = NULL;
    
    // populate data fields
    tempNode->data = data;
    tempNode->freq = freq;

    return tempNode;
}; 

// Creates a min heap of given capacity
struct minHeap* createMinHeap(unsigned capacity)
{
    // create a new min heap
    struct minHeap* minHeap = (struct minHeap*)malloc(sizeof(struct minHeap));

    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->nodeArray = (struct minHeapNode**)malloc(minHeap->capacity * sizeof(struct minHeapNode));

    return minHeap;
};

// Swaps two min heap tree nodes
void swapMinHeapNode(struct minHeapNode** a, struct minHeapNode** b)
{
    struct minHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Heapifys the min heap
void minHeapify(struct minHeap* minHeap, int index)
{
    int smallest = index; // assumes the current node at index is smallest
    int leftNode = 2 * index + 1; // index of the left child of the current node
    int rightNode = 2 * index + 2; // index of the right child of the current node
    
    // If the left child exists and if leftNodes frequency is smaller, update smallest to leftNode
    if(leftNode < minHeap->size && minHeap->nodeArray[leftNode]->freq)
        smallest = leftNode;
    
    // If the right child exists and if rightNodes frequency is smaller, update smallest to rightNode
    if(rightNode < minHeap->size && minHeap->nodeArray[rightNode]->freq)
        smallest = rightNode;

    // if the smallest isnt the current node
    if(smallest != index)
    {
        // swap the current node with smallest child usin swapMinHeapNode
        swapMinHeapNode(&minHeap->nodeArray[smallest], &minHeap->nodeArray[index]);
        // do minHeapify() to the affected subtree
        minHeapify(minHeap, smallest);
    }
}

// Checks if a heap is of size 1
bool isSizeOne(struct minHeap* minHeap)
{
    if(minHeap->size == 1)
        return true;
    else
        return false;
}

// Extracts min-node from min heap
struct minHeapNode* extractMin(struct minHeap* minHeap)
{}

// Inserts a new node to the min heap
void insertMinHeap(struct minHeap* minHeap, struct minHeapNode* minHeapNode)
{}

// Builds min heap
void buildMinHeap(struct minHeap* minHeap)
{}

// Prints an array of given size
void printArr(int arr[], int arraySize)
{}

// Checks if a given node is a leaf node
bool isLeaf(struct minHeapNode* root)
{}

// Creates a min heap of capacity equal to given size and 
// inserts all characters of data[] into the min heap.
// Initially, the size of the min heap is equal to the capacity
struct minHeap* createAndBuildMinHeap(char data[], int freq[], int size)
{}

// The main function to build the Huffman tree
struct minHeapNode* buildHuffmanTree(char data[], int freq[], int size)
{}

// Prints Huffman codes from the root of the Huffman tree.
// Uses arr[] to store codes
void printCodes(struct minHeapNode* root, int arr[], int top)
{}

// Builds a Huffman Tree and prints codes by traversing the built Huffman tree.
void huffmanCodes(char data[], int freq[], int size)
{}

int main()
{
    
}