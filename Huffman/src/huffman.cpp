/*
 * File: huffman.cpp
 * ---------------------------
 * Huffman coding is a compression technique used to
 * reduce the number of bits needed to send or store a message.
 */

#include <iostream>
#include "huffman.h"
#include "console.h"
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string.h>

using namespace std;

/* Function prototypes */
void compress(string sourceFileName, string archiveFileName);
void decompress(string archiveFileName, string outputFileName);
void buildTable(Node *root1);

/* Global variables */
vector<bool> symbolCode; // vector of zeros and ones for buildTable(); function
map<char, vector<bool> > table;// association table for symbols and codes
Node *root; // pointer to the root of the binary tree
char sourceFileName[100] = "input.txt";
char archiveFileName[100] = "archive.hzip";
char outputFileName[100] = "decompressed-";

int main ()
{
    int command;
    cout << "Huffman coding is a compression technique used to reduce" << endl;
    cout << "the number of bits needed to send or store a message." << endl;
    cout << "Put it in the 'res' folder file and check the algorithm." << endl;
    cout << "Or use the default file - 'input.txt'." << endl;
    cout << endl << "Use next commands:" << endl;
    cout << "1 - to compress the file" << endl;
    cout << "2 - to decompress the file" << endl;
    cout << "3 - to end program \n";
    while (true){
        cout << endl << "Type your command: ";
        cin >> command;
        switch (command) {
            case 1:
                cout << "Enter file name: ";
                cin >> sourceFileName;
                strcpy(archiveFileName, sourceFileName);
                strcat(archiveFileName, ".hzip");
                compress(sourceFileName, archiveFileName);
                cout << "\nCompression completed. \nFile was saved with name: " << archiveFileName << endl;
                break;
            case 2:
                strcat(outputFileName, sourceFileName);
                decompress(archiveFileName, outputFileName);
                cout << "\nDecompression completed. \nFile was saved with name: " << outputFileName << endl;
                break;
            case 3:
                cout << "Program closed." << endl;
                return(0);
            default:
                cout << "\nYou made a wrong choice! \n" <<endl;
                cout << "Program ended." << endl;
                exit(1);
        }
    }
    return 0;
}

/*
* Function: buildTable
* Usage: buildTable(Node *root1);
* ---------------------------------------
* Function creates a table of correspondences between characters and their codes
*/
void buildTable(Node *root1){
    if (root1->left!=NULL){
        symbolCode.push_back(0);
        buildTable(root1->left);
    }
    if (root1->right!= NULL){
        symbolCode.push_back(1);
        buildTable(root1->right);
    }
    if(root1->left==NULL && root1->right==NULL){
        table[root1->symbol]=symbolCode;
    }
        symbolCode.pop_back();
}

/*
* Function: compress
* Usage: compress();
* ---------------------------------------
* Compress the input.txt file.
*/
void compress(string sourceFileName, string archiveFileName){

    ifstream tozipStream(sourceFileName, ios::in | ios::binary); // create a stream from the source file

    map <char, int> charsCounts; // for counting characters in source file

    while(!tozipStream.eof()){
        char c = tozipStream.get();
        charsCounts[c]++;
    }

    list <Node*> nodePointers;

    map <char,int>::iterator iter;
    for (iter = charsCounts.begin(); iter != charsCounts.end(); ++iter){
        Node *p = new Node;
        p->symbol = iter->first;
        p->count = iter->second;
        nodePointers.push_back(p);
    }

    while (nodePointers.size()!=1){
        nodePointers.sort(MyCompare());

        Node *SonL = nodePointers.front();
        nodePointers.pop_front();
        Node *SonR = nodePointers.front();
        nodePointers.pop_front();

        Node *parent = new Node(SonL, SonR);
        nodePointers.push_back(parent);
    }

    root = nodePointers.front();

    buildTable(root);

    tozipStream.clear(); tozipStream.seekg(0);

    ofstream hzipStream(archiveFileName, ios::out | ios::binary);
    int counter = 0;
    char buffer = 0;
    while(!tozipStream.eof()){
        char c = tozipStream.get();
        vector<bool> x = table[c];
        for (int n=0; n < x.size(); n++){
            buffer = buffer | x[n] << (7-counter);
            counter++;
            if(counter==8){
                counter = 0;
                hzipStream << buffer;
                buffer=0;
            }
        }
    }

    tozipStream.close();
    hzipStream.close();

}

/*
* Function: decompress
* Usage: decompress();
* ---------------------------------------
* Decompress the input.txt.hzip file.
*/
void decompress(string archiveFileName, string outputFileName){

    ifstream hzipStream(archiveFileName, ios::in | ios::binary);
    ofstream unzipStream(outputFileName, ios::out | ios::binary);
    Node *p = root;
    int counter=0;
    char byte;
    byte = hzipStream.get();
    while(!hzipStream.eof()){
        bool b = byte & (1 << (7-counter));
        if (b) p=p->right; else p=p->left;
        if(p->left==NULL && p->right==NULL){
            unzipStream<<(p->symbol);
            p = root;            
        }
        counter++;
        if (counter==8){
            counter=0;
            byte = hzipStream.get();
        }
    }

    hzipStream.close();
    unzipStream.close();

}
