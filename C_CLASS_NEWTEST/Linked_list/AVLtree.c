/*================================================================
* Filename:AVLtree.c
* Author: KCN_yu
* Createtime:Thu 06 Feb 2020 03:22:13 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>

typedef int Type;

typedef struct AVLtreeNode{
    Type key;
    int height;
    struct AVLtreeNode *left;
    struct AVLtreeNode *right;
}Node, *AVLTree;

static Node* avltree_create_node(Type key, Node* left, Node *right){
    Node* p;
    if((p = (Node*)malloc(sizeof(Node))) == NULL)
        return NULL;
    p->key = key;
    p->height = 0;
    p->left = left;
    p->right = right;

    return p;
}

#define HEIGHT(p) ((p == NULL) ? 0 : ((Node*)(p))->height)
#define MAX(a,b) ((a) > (b) ? (a) : (b))

static Node* left_left_rotation(AVLTree k2){
    AVLTree k1;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = MAX(HEIGHT(k2->left),HEIGHT(k2->right)) + 1;
    k1->height = MAX(HEIGHT(k1->left),k2->height) + 1;

    return k1;
}

