#include <cctype>

#include "rb.h"

void TreeDelete(TRBTree tree);

char LowerCase(char c) {
    return c >= 'A' && c <= 'Z' ? c - 'A' + 'a' : c;
}

bool IsLetter(char c) {
    return c >= 'a' && c <= 'z';
}

void TreePrint(TRBTree::TRBNode* n, TRBTree* t) {
    //std::cout << n->value << std::endl;
    printf("OK: %llu\n", n->value);
    if(n->left &&(n->left->left && n->left->right)){
        TreePrint(n->left, t);
    }
    if(n->right &&(n->right->left && n->right->right)){
        TreePrint(n->right, t);
    }
}

void Parsing(char *action, char *buffer, unsigned long long *value) { // gonna change 'em
    char ch;
    size_t i = 0;
    bool flag = true;

    ch = getchar();

    if(ch == EOF) {
        *action = 'q';
        return;
    }

    if(ch == '+' || ch == '-') {
        *action = ch;
        getchar();
        while(flag) {
            ch = LowerCase(getchar());
            if(!IsLetter(ch)) {
                flag = false;
            } else {
                buffer[i++] = ch;
            }
        }
        buffer[i] = '\0';
        if(*action == '+') {
            *value = 0;

            while ((ch = getchar()) != '\n') {
                *value = (*value) * 10 + ch - '0';
            }
        }
    } else if(ch == '!') {
        getchar();
        while((ch = getchar()) != ' ') {
            buffer[i++] = ch;
        }
        buffer[i] = '\0';
        i = 0;
        *action = buffer[0];
        while((ch = getchar()) != '\n') {
            buffer[i++] = ch;
        }
        buffer[i] = '\0';
    } else {
        *action = 'F';
        buffer[0] = LowerCase(ch);
        ++i;
        while((ch = getchar()) != '\n') {
            buffer[i++] = LowerCase(ch);
        }
        buffer[i] = '\0';
    }
}

int main(){

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    TRBTree tree;

    char buffer[257]; // + '/0'
    char action;
    unsigned long long value;

    double mrbTime, stdTime;
    clock_t start;

    start = clock();

    while (true) {

        int flag = 1;
        Parsing(&action, buffer, &value);

        auto *temp = new TRBTree::TRBNode;
        temp->key = new char[strlen(buffer) + 1]; // PROBLEM
        auto *temp_real = temp;

        if (action == 'q') {
            delete temp;
            break;
        } else {

            switch (action) {
                case '+': {
                    strcpy(temp->key, buffer);
                    temp->value = value;
                    temp->color = TRBTree::RED; // check RB theory

                    if (!tree.Search(buffer)) {
                        tree.InsertNode(*temp);
                        //std::cout << "OK\n";
                        //printf("OK\n");
                        flag = 0; // del later
                    } else {
                        //std::cout << "Exist\n";
                        //printf("Exist\n");
                    }
                    break;
                }

                case '-': {
                    temp_real = tree.NodeSearch(buffer);
                    if (temp_real) {
                        tree.Delete(temp_real);
                        //std::cout << "OK\n";
                        //printf("OK\n");
                    } else {
                        //std::cout << "NoSuchWord\n";
                        //printf("NoSuchWord\n");
                    }
                    break;
                }

                case 'S': { // Save
                    tree.Save(buffer);
                    break;
                }
                case 'L': { // Load
                    if(tree.root->left != nullptr)
                        TreeDelete(tree.root->left, &tree);
                    if(tree.root->right != nullptr)
                        TreeDelete(tree.root->right, &tree);
                    tree.Load(buffer);

                    break;
                }

                case 'F': {
                    temp_real = tree.NodeSearch(buffer);
                    if (temp_real) {
                        //std::cout << "OK: " << temp_real->value << "\n";
                        //printf("OK: %llu\n", temp_real->value);
                    } else {
                        //std::cout << "NoSuchWord\n";
                        //printf("NoSuchWord\n");
                    }
                    break;
                }

            }

            if (flag) {
                delete temp;
            }
        }
    }

    if(tree.root->left != nullptr)
        TreeDelete(tree.root->left, &tree);
    if(tree.root->right != nullptr)
        TreeDelete(tree.root->right, &tree);
    delete tree.root;
    delete tree.nil;

    mrbTime = (clock() - start) / (double)CLOCKS_PER_SEC;
    printf("My  time is: %f ms\n", mrbTime);

    return 0;
}