#include "rb.h"

TRBTree::TRBNode::TRBNode(bool newColor, unsigned long long int newValue, char* newKey) {
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    value = newValue;
    color = newColor;
    key = newKey;
}

TRBTree::TRBTree() {
    nil = new TRBNode(BLACK, 0, nullptr);
    nil->right = nullptr;
    nil->left = nullptr;
    root = nil;
}

void TreeDelete(TRBTree::TRBNode* n, TRBTree* t) {
    if (n->left) {
        TreeDelete(n->left, t);
    }

    if (n->right) {
        TreeDelete(n->right, t);
    }
    if(n != t->nil) delete n;
}

TRBTree::TRBNode::~TRBNode() {
    delete[] key;
    key = nullptr;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

void TRBTree::SubTreeRelocate(TRBNode* old_node, TRBNode* new_node) {
    if(old_node->parent == this->nil) {
        this->root = new_node;
    } else if(old_node == old_node->parent->left) {
        old_node->parent->left = new_node;
    } else {
        old_node->parent->right = new_node;
    }
    new_node->parent = old_node->parent;
}

void TRBTree::LeftRotate(TRBNode& curNode) {
    TRBNode* y = curNode.right;
    curNode.right = y->left;
    if(y->left != this->nil) {
        y->left->parent = &curNode;
    }
    y->parent = curNode.parent;
    if(curNode.parent == this->nil) {
        this->root = y;
    } else if(&curNode == curNode.parent->left) {
        curNode.parent->left = y;
    } else {
        curNode.parent->right = y;
    }
    y->left = &curNode;
    curNode.parent = y;
}

void TRBTree::RightRotate(TRBNode& curNode) {
    TRBNode* y = curNode.left;
    curNode.left = y->right;
    if(y->right != this->nil) {
        y->right->parent = &curNode;
    }
    y->parent = curNode.parent;

    if(curNode.parent == this->nil) {
        this->root = y;
    } else if(&curNode == curNode.parent->right) {
        curNode.parent->right = y;
    } else {
        curNode.parent->left = y;
    }
    y->right = &curNode;
    curNode.parent = y;
}

bool TRBTree::Search(const char* pattern) {
    TRBNode* tmp = this->root;
    while(tmp != this->nil) {
        if(!strcmp(tmp->key, pattern)) {
            return true;
        } else if(0 > strcmp(tmp->key, pattern)) {
            tmp = tmp->right;
        } else {
            tmp = tmp->left;
        }
    }
    return false;
}

TRBTree::TRBNode* TRBTree::NodeSearch(const char* pattern) {
    TRBNode* tmp = this->root;
    while(tmp != this->nil) {
        if(!strcmp(tmp->key, pattern)) {
            return tmp;
        } else if(0 > strcmp(tmp->key, pattern)) {
            tmp = tmp->right;
        } else {
            tmp = tmp->left;
        }
    }
    return nullptr;
}

TRBTree::TRBNode* TRBTree::FindMin(TRBNode* curNode) {
    if (curNode == nullptr) return nullptr;
    while(curNode->left != this->nil) {
        curNode = curNode->left;
    }
    return curNode;
}

void TRBTree::InsertNode(TRBNode &newNode) {

    TRBNode* prevNode = this->nil;
    TRBNode* curNode = this->root;
    while(curNode != this->nil) {
        prevNode = curNode;
        if (0 <= strcmp(newNode.key, curNode->key)) {
            curNode = curNode->right;
        } else {
            curNode = curNode->left;
        }
    }
    newNode.parent = prevNode;
    if(prevNode == this->nil) {
        this->root = &newNode;
    } else if (0 <= strcmp(newNode.key, prevNode->key)) {
        prevNode->right = &newNode;
    } else {
        prevNode->left = &newNode;
    }
    newNode.right = this->nil;
    newNode.left = this->nil;
    newNode.color = RED;
    InsertFixup(&newNode);
}

void TRBTree::InsertFixup(TRBNode* curNode) {
    while(curNode->parent->color ) { //RED
        if(curNode->parent == curNode->parent->parent->left) {
            TRBNode* y = curNode->parent->parent->right;
            if (y->color) {
                curNode->parent->color = BLACK;
                y->color = BLACK;
                curNode->parent->parent->color = RED;
                curNode = curNode->parent->parent;
            } else {
                if (curNode == curNode->parent->right) {
                    curNode = curNode->parent;
                    LeftRotate(*curNode);
                }
                curNode->parent->color = BLACK;
                curNode->parent->parent->color = RED;
                RightRotate(*(curNode->parent->parent));
            }
        } else {
            TRBNode* y = curNode->parent->parent->left;
            if (!y->color) {
                if (curNode == curNode->parent->left) {
                    curNode = curNode->parent;
                    RightRotate(*curNode);
                }
                curNode->parent->color = BLACK;
                curNode->parent->parent->color = RED;
                LeftRotate(*(curNode->parent->parent));
            } else {
                curNode->parent->color = BLACK;
                y->color = BLACK;
                curNode->parent->parent->color = RED;
                curNode = curNode->parent->parent;
            }
        }
    }
    this->root->color = BLACK;
}

void TRBTree::Delete(TRBNode* curNode) {
    TRBNode* transNode = curNode;
    TRBNode* childOfTrans = nullptr;
    bool orig_color = transNode->color;
    if(curNode->left == this->nil) {
        childOfTrans = curNode->right;
        SubTreeRelocate(curNode, curNode->right);
    } else if(curNode->right == this->nil) {
        childOfTrans = curNode->left;
        SubTreeRelocate(curNode, curNode->left);
    } else {
        transNode = FindMin(curNode->right);
        orig_color = transNode->color;
        childOfTrans = transNode->right;
        if(transNode->parent == curNode) {
            childOfTrans->parent = transNode;
        } else {
            SubTreeRelocate(transNode, transNode->right);
            transNode->right = curNode->right;
            transNode->right->parent = transNode;
        }
        SubTreeRelocate(curNode, transNode);
        transNode->left = curNode->left;
        transNode->left->parent = transNode;
        transNode->color = curNode->color;
    }
    if(!orig_color) { //BLACK
        DeleteFixup(childOfTrans);
    }
    delete curNode;
}

void TRBTree::DeleteFixup(TRBNode *curNode) {
    while(curNode != this->root && !curNode->color) {
        if(curNode == curNode->parent->left) {
            TRBNode* right_brother = curNode->parent->right;
            if(right_brother->color) { //RED
                right_brother->color = BLACK;
                curNode->parent->color = RED;
                LeftRotate(*(curNode->parent));
                right_brother = curNode->parent->right;
            }
            if(!right_brother->left->color && !right_brother->right->color) {
                right_brother->color = RED;
                curNode = curNode->parent;
            } else {
                if(!right_brother->right->color) {
                    right_brother->left->color = BLACK;
                    right_brother->color = RED;
                    RightRotate(*right_brother);
                    right_brother = curNode->parent->right;
                }
                right_brother->color = curNode->parent->color;
                curNode->parent->color = BLACK;
                right_brother->right->color = BLACK;
                LeftRotate(*(curNode->parent));
                curNode = this->root;
            }
        } else {
            TRBNode* left_brother = curNode->parent->left;
            if(left_brother->color) {
                left_brother->color = BLACK;
                curNode->parent->color = RED;
                RightRotate(*(curNode->parent));
                left_brother = curNode->parent->left;
            }
            if(!left_brother->right->color && !left_brother->left->color) {
                left_brother->color = RED;
                curNode = curNode->parent;
            } else {
                if(!left_brother->left->color) {
                    left_brother->right->color = BLACK;
                    left_brother->color = RED;
                    LeftRotate(*left_brother);
                    left_brother = curNode->parent->left;
                }
                left_brother->color = curNode->parent->color;
                curNode->parent->color = BLACK;
                left_brother->left->color = BLACK;
                RightRotate(*(curNode->parent));
                curNode = this->root;
            }
        }
    }
    curNode->color = BLACK;
}

int TRBTree::Save(const char* buffer) {
    std::ofstream output(buffer);
    if(output.is_open()) {
        SaveStream(output, this->root); // рекурсивно заносить данные
        //std::cout << "OK\n";
        printf("OK\n");
        output.close();
        return 1;
    } else {
        //std::cout << "ERROR: Couldn't create file\n";
        printf("ERROR: Couldn't create file\n");
        output.close();
        return 0;
    }
}

void TRBTree::SaveStream(std::ofstream& output, TRBNode* root) {
    if(root == this->nil) {
        output << -1 << " ";
        return;
    }
    output << root->key << " " << root-> value << " " << root->color << " ";
    SaveStream(output, root->left);
    SaveStream(output, root->right);
}

int TRBTree::Load(const char* buffer) {
    std::ifstream input(buffer);
    if(input.is_open()) {
        this->root = this->nil;
        this->nil->parent = nullptr;
        this->nil->left = nullptr;
        this->nil->right = nullptr;
        this->nil->value = 0;
        this->nil->color = BLACK;
        this->nil->key = nullptr;
        LoadStream(input, this->root);
        //std::cout << "OK\n";
        printf("OK\n");
        root->parent = this->nil;
        input.close();
        return 1;

    } else {
        //std::cout << "ERROR: Couldn't load file\n";
        printf("ERROR: Couldn't load file\n");
        //root = new TRBNode(RED, 0, nullptr);
        root->parent = this->nil;
        input.close();
        return 0;

    }
}

void TRBTree::LoadStream(std::ifstream& input, TRBNode*& root) {
    char buffer[512];
    unsigned long long int value = 0;
    bool color = RED;
    if(input.peek() == EOF || (input >> buffer && !strcmp(buffer, "-1"))) { //peek to next elem
        return;
    }

    input >> value >> color;
    char* tmpKey = new char[strlen(buffer) + 1]; // '\0'
    strcpy(tmpKey, buffer);

    root = new TRBNode(color, value, tmpKey);
    root->left = this->nil;
    root->right = this->nil;
    LoadStream(input, root->left);
    LoadStream(input, root->right);
    root->left->parent = root;
    root->right->parent = root;
}
