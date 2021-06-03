#include <stdio.h>
#include <stdlib.h>
// binary tree

typedef struct tNode *tree;
typedef int elemtype;
typedef struct tNode
{
    elemtype elem;
    tree left;
    tree right;
} tNode;

int count(tree t) //
{
    if(t == NULL)
        return 0;
    return 1+count(t -> left)+count(t->right);
}

int find_max(tree t)
{
    if(t->left==NULL && t->right==NULL)
        return t->elem;
    int left_max=t->elem,right_max=t->elem;
    if(t->left!=NULL)
        left_max=find_max(t->left);
    if(t->right!=NULL)
        right_max=find_max(t->right);
    return (t->elem>left_max)?
          (t->elem>right_max)?t->elem:right_max:
           left_max>right_max?left_max:right_max;
}
tree create_tree(char *s)
{
    static char*p;
    tree t;
    p=s;
    if(*p=='<')
        p++;
    else
    {
        fprintf(stderr,"wrong format");
        return NULL;
    }
    if(*p=='>')
    {
        p++;
        return NULL;
    }
    t=(tree)malloc(sizeof(tNode));
    t->elem=*p;
    p++;
    t->left=create_tree(p);
    t->right=create_tree(p);
    if(*p!='>')
    {
        fprintf(stderr,"wrong format");
        return NULL;
    }
    else
    {
        p++;
        return t;
    }
}

void pre_order(tree t)
{
    if(t==NULL)
        return;
    else
    {
        printf("%c ",t->elem);
        pre_order(t->left);
        pre_order(t->right);
    }
}

void in_order(tree t)
{
    if(t==NULL)
        return;
    else
    {
        in_order(t->left);
        printf("%c ",t->elem);
        in_order(t->right);
    }
}

void post_order(tree t)
{
    if(t==NULL)
        return;
    else
    {
        post_order(t->left);
        post_order(t->right);
        printf("%c ",t->elem);
    }
}

int eval(tree t){
    if(t->left==NULL&&t->right==NULL)
        return t->elem-'0';
    int l=eval(t->left);
    int r=eval(t->right);
    if(t->elem=='+') return l+r;
    if(t->elem=='-') return l-r;
    if(t->elem=='*') return l*r;
    if(t->elem=='/') return l/r;
    else return 0;
}
// stack for binary trees

typedef  struct Node *link; /*  pointer to stack node */
typedef  tree stackelemtype; /*  stack item type */
typedef struct Node { /* stack node type */
    stackelemtype elem; /*    item */
    link next; /*  pointer to the next node */
}
node;

typedef link stack; /*  stack type (pointer to the top) */


void push(stack *pl, stackelemtype el){ /* put item on stack */
    link tmp = (link)malloc(sizeof(node));
    tmp->elem = el;
    tmp->next = *pl;
    *pl = tmp;
}

stackelemtype pop(stack *pl){
    stackelemtype tmp;
    link p = *pl;
    if (*pl == NULL){
        fprintf(stderr, "Error: empty stack\n");
        exit(1);
    }
    tmp = p->elem;
    *pl = p->next;
    free(p);
    return tmp;
}


int empty (stack p){
    return p==NULL;
}


void KLP(tree t) // pre_oder non-recursive
{
    stack s=NULL;
    if(t == NULL) return;
    else push(&s, NULL);
    while(t != NULL){
        putchar(t->elem); putchar(' ');
        if (t->right!=NULL) push(&s,t->right);
        if (t->left!=NULL) t=t->left;
        else t=pop(&s);
    }
    putchar ('\n');
}
void LKP(tree t){
    stack s = NULL;
    if(t == NULL) return;
    else push(&s,NULL);
    while(t != NULL || s->elem != NULL){
        if(t != NULL){
            push(&s,t);
            t = t->left;
        }
        else{
            t = pop(&s);
            printf("%c ",t->elem);
            t = t->right;
        }
    }
    putchar ('\n');
}
void LPK(tree t){
    stack s = NULL;
    if(t == NULL) return;
    else push(&s,NULL);
    tree tCur = t;
    tree tPre = NULL;
    while(tCur != NULL){
        push(&s,tCur);
        tCur = tCur->left;
    }
    while(s->elem != NULL){
        tCur = pop(&s);
        if(tCur->right == NULL || tCur->right == tPre){
            printf("%c ",tCur->elem);
            tPre = tCur;
        }
        else{
            push(&s,tCur);
            tCur = tCur->right;
            while(tCur != NULL){
                push(&s,tCur);
                tCur = tCur->left;
            }
        }
    }
    putchar('\n');
}


typedef int listelemtype;
typedef struct Node_list{
    listelemtype elem;
    struct Node_list* next;
}Node_list;
typedef struct Node_list* stack_int;

listelemtype Pop(stack_int *p){
    listelemtype tmp;
    stack_int p_tmp = *p;
    if(*p == NULL){
        fprintf(stderr,"Error:empty stack\n!");
        exit(1);
    }
    tmp = p_tmp->elem;
    *p = p_tmp->next;
    free(p_tmp);
    return tmp;
}
void Push(stack_int *p, listelemtype el){
    stack_int tmp = (stack_int)malloc(sizeof(Node_list));
    tmp->elem = el;
    tmp->next = *p;
    *p = tmp;
}
int eval_nor(tree t){
    if(t->left == NULL && t->right == NULL)
        return t->elem - '0';
    stack s = NULL;
    if(t == NULL) return 0;
    else push(&s,NULL);
    tree tCur = t;
    tree tPre = NULL;
    stack_int eval = NULL;

    while(tCur != NULL){
        push(&s,tCur);
        tCur = tCur->left;
    }
    while(s->elem != NULL){
        tCur = pop(&s);
        if(tCur->right == NULL || tCur->right == tPre){
            char c = tCur->elem;
            if('0' <= c && c <= '9')
                Push(&eval,c-'0');
            else if(c == '+')
                Push(&eval,Pop(&eval)+Pop(&eval));
            else if(c == '*')
                Push(&eval,Pop(&eval)*Pop(&eval));
            else if(c == '-'){
                int digit = Pop(&eval);
                Push(&eval,Pop(&eval)-digit);
            }
            else if(c == '/'){
                int digit = Pop(&eval);
                Push(&eval,Pop(&eval)/digit);
            }
                tPre = tCur;
        }
        else{
            push(&s,tCur);
            tCur = tCur->right;
            while(tCur != NULL){
                push(&s,tCur);
                tCur = tCur->left;
            }
        }
    }
    return Pop(&eval);
}


int Depth(tree t){
    if(t == NULL) return -1;
    int left = Depth(t->left);
    int right = Depth(t->right);
    return 1 + (left > right ? left : right);
}
int Height(tree t){
    if(t == NULL) return 0;
    int left = Height(t->left);
    int right = Height(t->right);
    return 1 + (left > right ? left : right);
}
int main()
{
    char *s="<*<+<1<><>><3<><>>><-<5<><>><6<><>>>>";
    //              *
    //            /  \
    //           +    -
    //          / \  / \
    //         1  3 5   6
    tree t = create_tree(s);

    pre_order(t);
    putchar('\n');
    in_order(t);
    putchar('\n');
    post_order(t);
    printf("\nanswer = %d\n",eval(t));
    printf("Depth = %d\n", Depth(t));
    printf("Height = %d\n", Height(t));

    KLP(t);
    LKP(t);
    LPK(t);
    printf("answer = %d\n",eval_nor(t));
    return 0;
}
