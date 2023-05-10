#include "queue.h"
#include <stdio.h>

int test_is_empty() {
    struct Queue *obj = q_init(2);

    if (obj == 0) {
        return 1;
    }

    if (q_is_empty(obj)) {
        q_clear(obj);
        return 0;
    } else {
        q_clear(obj);
        return -1;
    }
}

int test_not_is_empty() {
    struct Queue *obj = q_init(2);

    if (obj == 0) {
        return 1;
    }

    int add1_res = q_add(obj, 1);

    if (add1_res != 0) {
        q_clear(obj);
        return 1;
    }

    if (!(q_is_empty(obj))) {
        q_clear(obj);
        return 0;
    } else {
        q_clear(obj);
        return -1;
    }
}

int test_is_empty_after_use() {
    struct Queue *obj = q_init(2);

    if (obj == 0) {
        return 1;
    }

    int add1_res = q_add(obj, 1);
    int rem1_res = q_remove(obj, 0);

    if (!(add1_res == 0 && rem1_res == 0)) {
        q_clear(obj);
        return 1;
    }

    if (q_is_empty(obj)) {
        q_clear(obj);
        return 0;
    } else {
        q_clear(obj);
        return -1;
    }
}

int test_underflow() {
    struct Queue *obj = q_init(2);

    if (obj == 0) {
        return 1;
    }

    int res1 = q_remove(obj, 0);

    q_clear(obj);

    if (res1 != 0) {
        return 0;
    } else {
        return 1;
    }
}

int test_overflow() {
    struct Queue *obj = q_init(2);

    if (obj == 0) {
        return 1;
    }

    int add1_res = q_add(obj, 1);
    int add2_res = q_add(obj, 2);
    int add3_res = q_add(obj, 3);

    q_clear(obj);

    if (!(add1_res = 0 && add2_res == 0)) {
        return 1;
    }

    if (add3_res != 0) {
        return 0;
    } else {
        return -1;
    }
}

int test_remove() {
    struct Queue *obj = q_init(2);

    if (obj == 0) {
        return 1;
    }

    int add1_res = q_add(obj, 1);

    if (add1_res != 0) {
        q_clear(obj);
        return 1;
    }

    int res1;
    int rem1_res = q_remove(obj, &res1);

    q_clear(obj);

    if (rem1_res != 0) {
        return 1;
    } else if (res1 == 1) {
        return 0;
    } else {
        return -1;
    }
}

int test_fifo() {
    struct Queue *obj = q_init(2);

    if (obj == 0) {
        return 1;
    }

    int add1_res = q_add(obj, 1);
    int add2_res = q_add(obj, 2);

    if (!(add1_res == 0 && add2_res == 0)) {
        q_clear(obj);
        return 1;
    }

    int res1, res2;

    int rem1_res = q_remove(obj, &res1);
    int rem2_res = q_remove(obj, &res2);

    if (!(rem1_res == 0 && rem2_res == 0)) {
        q_clear(obj);
        return 1;
    }

    q_clear(obj);

    if (res1 == 1 && res2 == 2) {
        return 0;
    } else {
        return -1;
    }
}

int main(void) {
    int e_t = test_is_empty();
    int n_t = test_not_is_empty();
    int ae_t = test_is_empty_after_use();
    int u_t = test_underflow();
    int o_t = test_overflow();
    int r_t = test_remove();
    int f_t = test_fifo();

    printf("%d %d %d %d %d %d %d\n", e_t, n_t, ae_t, u_t, o_t, r_t, f_t);
}