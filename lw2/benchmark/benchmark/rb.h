#ifndef RBT_H
#define RBT_H

#include <cstring>
#include <iostream>
#include <fstream>
#include "stdio.h"

struct TRBTree {
    struct TRBNode {
        TRBNode() = default;// indeed to compile
        TRBNode(bool, unsigned long long int, char *); // initialization

        TRBNode *left;         /* left child */
        TRBNode *right;        /* right child */
        TRBNode *parent;       /* parent */
        bool color;

        char *key;
        unsigned long long int value;

        ~TRBNode();
    };

    TRBTree();

    ~TRBTree() = default;

    void InsertNode(TRBNode &);

    void InsertWParents(TRBNode *);

    void SubTreeRelocate(TRBNode *, TRBNode *);

    TRBNode *FindMin(TRBNode *);

    void Delete(TRBNode *);

    void DeleteWParents(TRBNode *);

    bool Search(const char *); //return pointer on node
    TRBTree::TRBNode *NodeSearch(const char *);

    int Save(const char *);

    void SaveStream(std::ofstream &, TRBNode *);  //output
    int Load(const char *);

    void LoadStream(std::ifstream &, TRBNode *&);  //input

    void LeftRotate(TRBNode &);
    void RightRotate(TRBNode &);

    static const bool BLACK = false;
    static const bool RED = true;
    TRBNode *root;
    TRBNode *nil;
};

void TreeDelete(TRBTree::TRBNode* n, TRBTree* t);

#endif