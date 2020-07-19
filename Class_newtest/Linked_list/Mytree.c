/*================================================================
* Filename:tree.c
* Author: KCN_yu
* Createtime:Fri 13 Dec 2019 04:30:10 PM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int elemtype;
typedef struct tNode *tree;
typedef struct tNode{
    elemtype elem;
    tree left;
    tree right;
}tNode;
int count(tree t){
    if(t == NULL)return 0;
    return 1 + count(t->left) + count(t->right);
}
int Max(tree t){
    int lmax = t->elem, rmax = t->elem;
    if(t->left != NULL) lmax = Max(t->left);
    if(t->right != NULL) rmax = Max(t->right);
    return (t->elem > lmax) ? (t->elem > rmax ? t->elem : rmax) : (lmax > rmax ? lmax : rmax);
}
int Count_n(tree t, int n){
    if(t == NULL)return 0;
    return t->elem == n ? Count_n(t->left,n)+Count_n(t->right,n)+1 : Count_n(t->left,n)+Count_n(t->right,n);
}
int Sum(tree t){
    if(t == NULL)return 0;
    return t->elem + Sum(t->left) + Sum(t->right);
}
_Bool Judge_n(tree t, int n){
    if(t == NULL)return false;
    return t->elem == n ? true : Judge_n(t->left,n)+Judge_n(t->right,n);
}
void Print_nonleave(tree t){
    if(t == NULL)return;
    if(t->left != NULL || t->right != NULL)printf("%d\n",t->elem);
    Print_nonleave(t->left);
    Print_nonleave(t->right);
}
_Bool Judge_tree(tree t1, tree t2){
    if(t1 == NULL && t2 == NULL)return true;
    if(t1 == NULL && t2 != NULL)return false;
    if(t1 != NULL && t2 == NULL)return false;
    if(t1->elem != t2->elem)return false;
    return Judge_tree(t1->left,t2->left) && Judge_tree(t1->right,t2->right);
}

tree Create_temp(){
    elemtype n;
    tree t;
    scanf("%d",&n);
    if (n != 0) {
        t = (tree)malloc(sizeof(tNode));
        t->elem = n;
        printf("input left: ");
        t->left = Creat();
        printf("input right: ");
        t->right = Creat();
    }
    else t = NULL;

    return t;
}
/*
tree Create(char *s){
    static char *p;
    tree t;
    p = s;
    if(*p == '<')p++;
    else return NULL;
    if(*p == '>')return NULL;

    t = (tree)malloc(sizeof(tNode));
    t->elem = *p;
    p++;
    t->left = Create(p);
    t->right = Create(p);
    if(*p != '>')return NULL;
    else{
        p++;
        return t;
    }
}
*/
void Print_traversal(tree t){
    if(t == NULL)return;
    printf("%d ",t->elem);
    Print_traversal(t->left);
    Print_traversal(t->right);
}
int main(int argc, char *argv[])
{

    tree t1 = (tree)malloc(sizeof(tNode));
    t1->elem = 300;
    t1->left = (tree)malloc(sizeof(tNode));
    t1->right = (tree)malloc(sizeof(tNode));
    t1->left->elem = 30;
    t1->right->elem = 300;
    t1->right->left = NULL;
    t1->right->right = NULL;
    t1->left->left = (tree)malloc(sizeof(tNode));
    t1->left->right = NULL;
    t1->left->left->elem = 3000;
    t1->left->left->left = NULL;
    t1->left->left->right = NULL;

    tree t2 = (tree)malloc(sizeof(tNode));
    t2->elem = 30;
    t2->left = (tree)malloc(sizeof(tNode));
    t2->right = (tree)malloc(sizeof(tNode));
    t2->left->elem = 30;
    t2->right->elem = 300;
    t2->right->left = NULL;
    t2->right->right = NULL;
    t2->left->left = (tree)malloc(sizeof(tNode));
    t2->left->right = NULL;
    t2->left->left->elem = 30;
    t2->left->left->left = NULL;
    t2->left->left->right = NULL;
    tree t = Create();
    Print_traversal(t1);
    printf("count = %d\n",count(t1));
    printf("max = %d\n",Max(t1));
    printf("sum = %d\n",Sum(t1));
    Print_nonleave(t1);
    printf("a total of %d\n",Count_n(t1,30));
    printf("have ? = %d\n",Judge_n(t1,3));

    printf("%d\n",Judge_tree(t1,t2));
    return 0;
}
