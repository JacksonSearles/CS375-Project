#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream> 
#include <map>

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
    size_t leftNode = 2 * index + 1; // index of the left child of the current node
    size_t rightNode = 2 * index + 2; // index of the right child of the current node
    
    // If the left child exists and if leftNodes frequency is smaller, update smallest to leftNode
    if (leftNode < minHeap->size && minHeap->nodeArray[leftNode]->freq < minHeap->nodeArray[smallest]->freq)
        smallest = leftNode;
    
    // If the right child exists and if rightNodes frequency is smaller, update smallest to rightNode
    if (rightNode < minHeap->size && minHeap->nodeArray[rightNode]->freq < minHeap->nodeArray[smallest]->freq)
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

// Prints the characters frequency to terminal
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
struct minHeap* createAndBuildMinHeap(vector<char>& characters, vector<int>& freqeuncies, int size)
{
    struct minHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i) {
        minHeap->nodeArray[i] = newNode(characters[i], freqeuncies[i]); //for each item (node) in the array, maka a node with respective data
    }
    minHeap->size = size; //update size
    buildMinHeap(minHeap);

    return minHeap;
}

// The main function to build the Huffman tree
struct minHeapNode* buildHuffmanTree(vector<char>& characters, vector<int>& freqeuncies, int size)
{
    struct minHeapNode *left, *right, *top;
    //create min heap of capacity size
    struct minHeap* minHeap = createAndBuildMinHeap(characters, freqeuncies, size);

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
void printCodes(struct minHeapNode* root, int arr[], int top, vector<char>& chars, map<char, string>& huffmanCodesMap, ofstream& huffmanOutputFile)
{
    //0 is left
    if(root->leftNode) {
        arr[top] = 0;
        printCodes(root->leftNode, arr, top+1, chars, huffmanCodesMap, huffmanOutputFile);
    }
    //1 is right
    if (root->rightNode) {
        arr[top] = 1;
        printCodes(root->rightNode, arr, top + 1, chars, huffmanCodesMap, huffmanOutputFile);
    }

    // leaf node, save the Huffman code and print it
    if (isLeaf(root)) {
        string code = "";

        for (int i = 0; i < top; ++i) {
            code += to_string(arr[i]); // convert array to string
        }

        huffmanCodesMap[root->data] = code; // store the code in the map

        // print to terminal
        cout << "\t" << root->data << ": "; // print the character to terminal
        printArr(arr, top);                 // print the characters frequency to terminal
    }
}

// Builds a Huffman Tree and prints codes by traversing the built Huffman tree.
void huffmanCodes(vector<char>& uniqueCharacters, vector<int>& frequencies, int size, vector<char>& chars, ofstream& huffmanOutputFile)
{
    map<char, string> huffmanCodesMap; // for holding each character and its code

    //make tree
    struct minHeapNode* root = buildHuffmanTree(uniqueCharacters, frequencies, size);
    //print codes  using tree above
    int arr[MAX_TREE_HEIGHT], top = 0;

    cout << "DEBUGGING, GET RID OF ME:" << endl << "\tEach characters bitwise representation after huffman encoding:" << endl; // get rid of the print statement in printCodes()
        printCodes(root, arr, top, chars, huffmanCodesMap, huffmanOutputFile);
    
    // print the entire huffman code to the huffmanOutputFile
    for (char ch : chars) {
        huffmanOutputFile << huffmanCodesMap[ch]; 
    }
}

void printUnencoded(vector<char>& chars, ofstream &unencodedOutputFile)
{
    // iterate through each character in the vector    
    for (char character : chars) 
    { 
        // iterate over each bit (8 bits for a char)
        for (int i = 7; i >= 0; --i)  
        {
            // extract and print the bit at position i
            unencodedOutputFile << ((character >> i) & 1); 
        }
    }
}

void compareBits(ifstream& huffmanOutputFile, ifstream& unencodedOutputFile)
{
    int numHuffmanBits = 0;
    int numUnencodedBits = 0;

    char character;
    while (huffmanOutputFile.get(character)) {
        numHuffmanBits++;
    }
    while (unencodedOutputFile.get(character)) { 
        numUnencodedBits++;
    }

    cout << endl << "Number of bits in the original message: " << numUnencodedBits << endl;
    cout << "Number of bits in the Huffman encoded message: " << numHuffmanBits << endl;
    cout << "Huffman Coding cut out " << 100 - (static_cast<double>(numHuffmanBits)/numUnencodedBits)*100 << "% of the bits that made up the original message" << endl;
    cout << "Huffman Coding saved " << numUnencodedBits-numHuffmanBits << " bits, which is ";
    cout << ((numUnencodedBits - numHuffmanBits)/(8.0)) << " bytes";
    cout << ", or " << ((numUnencodedBits - numHuffmanBits)/(8.0*1024)) << " kilobytes" << endl;
    cout << endl;
}

int main(int argc, char* argv[])
{

    // USE:  ./huffman input.txt huffmanOut.txt unencodedOut.txt


    // create I/O file variables
    string inputFileName = argv[1];
    string huffmanOutput = argv[2];
    string unencodedOutput = argv[3];
    ifstream inputFile(inputFileName);
    ofstream huffmanOutputFile(huffmanOutput);
    ofstream unencodedOutputFile(unencodedOutput);
    // do I/O file and command line error checking
    if (argc != 4) {
        cout << endl << "\tUsage: prompt> submission inputFile.txt huffmanOutput.txt unencodedOutput.txt" << endl << endl;
        return 0;
    }
    if (!inputFile) {
        cout << endl <<"\tUnable to open input file" << endl << endl;
        return 0;
    }
    if (!huffmanOutputFile || !unencodedOutputFile) {
        cerr << endl << "\tError: Could not opening output file(s)" <<  endl << endl;
        return 0;
    }

     
    // get the input, putting the characters into the chars vector
    char character;
    vector<char> chars;
    while (inputFile.get(character)) { // read character by character
        chars.push_back(character); // put the character into the vector
    }
    inputFile.close();

    // creating the character map that will hold the characters and their corresponding frequency...
    // every char will be unique and will have a corresponding frequency 
    map<char, int> characterMap;
    // convert char vector to frequency map
    for (char ch : chars) { // iterate through each character in the vector
        characterMap[ch]++; // increment the frequency of the character, if its not in there, itll put it in
    }

    // creating the characters and frequencies vectors
    vector<char> uniqueCharacters;
    vector<int> frequencies;
    int size = characterMap.size();

    // moving the characters and frequencies from the characterMap into their respective vectors
    for (const auto& pair : characterMap) {
        uniqueCharacters.push_back(pair.first); // collecting the just the characters
    }
    for (const auto& pair : characterMap) {
        frequencies.push_back(pair.second); // collecting the just the frequncies
    }
 
    // ****** get rid of me starting here
    cout << endl << "DEBUGGING GET RID OF ME:" << endl << "\tCharacters and their corresponding frequencies: " << endl;
    for (size_t i = 0; i < uniqueCharacters.size(); i++) { 
        cout << "\t" << uniqueCharacters[i] << " : " << frequencies[i] << endl; 
    }
    cout << endl;
    // ****** get rid of me ending here

    // print out the encoded binary, and the unencoded binary to two separate files 
    huffmanCodes(uniqueCharacters, frequencies, size, chars, huffmanOutputFile); // prints out the huffman code into the huffmanOuputFile
    printUnencoded(chars, unencodedOutputFile);  // turns all of the characters from the input into binary, and outputs the binary to the output file
    
    // closing the original output files, and reopening them as input files
    huffmanOutputFile.close();
    unencodedOutputFile.close();
    ifstream huffmanInputFile(huffmanOutput);
    ifstream unencodedInputFile(unencodedOutput);
    if (!huffmanInputFile || !unencodedInputFile) {
        cerr << "\nError opening files for comparison.\n";
        return 1;
    }

    // compares the number of bits in the uncoded output file with the number of bits in the encoded file
    compareBits(huffmanInputFile, unencodedInputFile);
}

