#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

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
{
    struct minHeapNode* temp = minHeap->nodeArray[0]; //temp now minimum
    minHeap->nodeArray[0] = minHeap->nodeArray[minHeap->size -1]; //fill that spot with botton of array
    --minHeap->size; //size changed so update
    minHeapify(minHeap, 0); // minheapify
    return temp;
}

// Inserts a new node to the min heap
void insertMinHeap(struct minHeap* minHeap, struct minHeapNode* minHeapNode)
{
    ++minHeap->size; //inserting means increasing size lmao
    int i = minHeap->size - 1; //last item in array
    while (i && minHeapNode->freq < minHeap->nodeArray[(i - 1) / 2]->freq) { //while not at top and frequency is less
        minHeap->nodeArray[i] = minHeap->nodeArray[(i - 1) / 2]; //item switches with parent
        i = (i - 1) / 2; // update i to match
    }
    minHeap->nodeArray[i] = minHeapNode;
}

// Builds min heap
void buildMinHeap(struct minHeap* minHeap)
{
    int n = minHeap->size - 1; 
    for (int i = (n - 1) / 2; i >= 0; --i) {
        minHeapify(minHeap, i);
    }
}

// Prints an array of given size
void printArr(int arr[], int n)
{
    for (int i = 0; i < n; ++i) {
        cout << arr[i];
    }
    cout << "\n";
}

// Checks if a given node is a leaf node
bool isLeaf(struct minHeapNode* root)
{
    return !(root->leftNode) && !(root->rightNode); //return if node has children
}

// Creates a min heap of capacity equal to given size and 
// inserts all characters of data[] into the min heap.
// Initially, the size of the min heap is equal to the capacity
struct minHeap* createAndBuildMinHeap(char data[], int freq[], int size)
{
    struct minHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i) {
        minHeap->nodeArray[i] = newNode(data[i], freq[i]); //for each item (node) in the array, maka a node with respective data
    }
    minHeap->size = size; //update size
    buildMinHeap(minHeap);

    return minHeap;
}

// The main function to build the Huffman tree
struct minHeapNode* buildHuffmanTree(char data[], int freq[], int size)
{
    struct minHeapNode *left, *right, *top;
    //create min heap of capacity size
    struct minHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {
        //extract the two minimum freq items from heap
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        //create a new internal node with req = sum of those two children
        //add to minHeap
        //'$' used to denote this combination node
        top = newNode('$', left->freq + right->freq);

        top->leftNode = left;
        top->rightNode = right;

        insertMinHeap(minHeap, top);
    }

    //remaining node is the root and tree is finished
    return extractMin(minHeap);
    
}

// Prints Huffman codes from the root of the Huffman tree.
// Uses arr[] to store codes
void printCodes(struct minHeapNode* root, int arr[], int top)
{
    //0 is left
    if(root->leftNode) {
        arr[top] = 0;
        printCodes(root->leftNode, arr, top+1);
    }
    //1 is right
    if (root->rightNode) {
        arr[top] = 1;
        printCodes(root->rightNode, arr, top + 1);
    }

    //if leaf node than contains input chars
    if(isLeaf(root)) {
        cout << root->data << ": ";
        printArr(arr, top);
    }
}

// Builds a Huffman Tree and prints codes by traversing the built Huffman tree.
void huffmanCodes(char data[], int freq[], int size)
{
    //make tree
    struct minHeapNode* root = buildHuffmanTree(data, freq, size);
    //print codes  using tree above
    int arr[MAX_TREE_HEIGHT], top = 0;

    printCodes(root, arr, top);
    
}

int main()
{
    char testArr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int testFreq[] = { 5, 9, 12, 13, 16, 45};
    
    int size = sizeof(testArr) / sizeof(testArr[0]);

    huffmanCodes(testArr, testFreq, size);
}