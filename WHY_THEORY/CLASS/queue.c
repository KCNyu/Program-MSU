#include "queue.h"
#include <stdlib.h>

int q_init(struct Queue *self, int max_size) {

    self->array = calloc(max_size + 1, sizeof(int));
    self->capacity = max_size + 1;
    self->curr_elem = 0;
    self->empty_elem = 0;

    return 0;
}

void q_clear(struct Queue *self) {
    free(self->array);
    self->array = NULL;
}

int q_add(struct Queue *self, int elem) {
    if ((self->empty_elem + 1) % self->capacity == self->curr_elem) {
        return -1;
    }

    self->array[self->empty_elem] = elem;
    self->empty_elem = (self->empty_elem + 1) % self->capacity;

    return 0;
}

int q_remove(struct Queue *self, int *elem){
    if (q_is_empty(self)) {
        return -1;
    }

    if (elem != 0) {
        *elem = self->array[self->curr_elem];
    }

    self->curr_elem = (self->curr_elem + 1) % self->capacity;

    return 0;
}

int q_is_empty(struct Queue *self){
    return self->curr_elem == self->empty_elem;
}
