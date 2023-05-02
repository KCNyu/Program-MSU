/*@ 
  @ requires a >= 0;
  @ requires b > 0;
  @ requires \valid(d);
  @ requires \valid(r);
  @ requires (\base_addr(d) == \base_addr(r)) ==> (d != r);
  @ assigns *d, *r;
  @ ensures a == *d * b + *r;
  @ ensures 0 <= *r < b;
*/

void div(int a, int b, int *d, int *r) {
    int d_p = 0;
    /*@
      @ loop invariant a >= 0;
      @ loop invariant \at(a, Pre) == d_p * b + a;
      @ loop variant a;
    */
    while (a >= b) {
        a = a - b;
        d_p++;
    }
    *d = d_p;
    *r = a;
}

int main(void) {
    int pp[3];
    pp[2] = 42;
    div(10, 2, pp, pp + 1);
    //@ assert (pp[0] == 5) && (pp[1] == 0);
    //@ assert pp[2] == 42;
}