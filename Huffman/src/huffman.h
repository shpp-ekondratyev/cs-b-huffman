/*
 * File: huffman.h
 * ---------------------------
 *
 */

#ifndef HAFFMAN_H
#define HAFFMAN_H

class Node{
public:
    int count;
    char symbol;
    Node *left, *right;

    Node(){left=right=NULL;}

    Node (Node *L, Node *R){
        left = L;
        right = R;
        count = L->count + R->count;
    }
    ~Node(){
        delete left;
        delete right;
    }
};

struct MyCompare{
    bool operator()(Node* l,Node* r) {
        return l->count < r->count;
    }
};

#endif
