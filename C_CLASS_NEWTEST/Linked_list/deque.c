#include <stdio.h>
#include <stdlib.h>

typedef int elemtype;
typedef struct dNode * link;
typedef struct dNode {
            elemtype elem;
            link prev;
            link next;
        } dnode;


typedef struct Deque {
                link front;
                link rear;
} deque;

int main()
{
    printf("Hello world!\n");
    return 0;
}
