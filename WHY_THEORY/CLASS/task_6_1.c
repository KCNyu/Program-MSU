#include <limits.h>

/*@
  @ predicate sorted (int *array, integer first, integer after_last) = \forall integer i, integer j; 
  @    (first <= i <= j < after_last) ==> (array[i] <= array[j]);
  @
  @ axiomatic CountTheory {
  @      logic integer count{L}(int *array, integer first, integer after_last, integer elem);
  @      
  @      axiom empty_count{L}: \forall integer first, after_last, elem, int *array;
  @             (first >= after_last) ==> (count(array, first, after_last, elem) == 0);
  @
  @      axiom one_count{L}: \forall integer first, after_last, elem, int *array;
  @             (first + 1 == after_last) ==> (count(array, first, after_last, elem) 
  @                     == (array[first] == elem ? 1 : 0));
  @
  @      axiom split_count{L}: \forall integer first, after_last, elem, middle, int *array;
  @             (first <= middle <= after_last) ==> 
  @                     (count(array, first, after_last, elem) == count(array, first, middle, elem) + 
  @                             count(array, middle, after_last, elem));
  @
//   @      lemma no_changes{L1, L2}:
//   @             \forall integer first, after_last, elem, int *array;
//   @                 (\forall integer k; (first <= k < after_last) ==> (\at(array[k], L1) == \at(array[k], L2)))
//   @                     ==> (\at(count(array, first, after_last, elem), L1) == \at(count(array, first, after_last, elem), L2));
  @ }
  @ 
*/

/*@
  @ requires len1 >= 0;
  @ requires len2 >= 0;
  @ requires \valid(first + (0..len1 - 1));
  @ requires \valid(second + (0..len2 - 1));
  @ requires sorted(first, 0, len1);
  @ requires sorted(second, 0, len2);
  @ requires \valid(result + (0..(len1 + len2 - 1)));
  @ requires (len1 + len2) <= INT_MAX;
  @
  @ assigns result[0..(len1 + len2 - 1)];
  @
  @ ensures sorted(result, 0, (len1 + len2));
  @ ensures \forall integer x; count(first, 0, len1, x) + count(second, 0, len2, x) 
  @    == count(result, 0, len1 + len2, x);
*/

void merge(int *first, int *second, int *result, int len1, int len2) {
    int i = 0, j = 0;
    /*@
      @ loop invariant 0 <= i <= len1;
      @ loop invariant 0 <= j <= len2;
      @ loop invariant sorted(result, 0, (i + j));
      @ loop invariant \forall integer k; (0 <= k < i + j) ==> 
      @     ((i < len1 ==> (result[k] <= first[i])) && (j < len2 ==> (result[k] <= second[j])));
      @ loop invariant  \forall integer x; count(first, 0, i, x) + count(second, 0, j, x) 
      @    == count(result, 0, i + j, x);
      @
      @ loop variant (len1 + len2) - (i + j);
    */
    while (i + j < len1 + len2) {
        Before:
        if (i == len1) {
            result[i + j] = second[j];
            j++;
            /*@ ghost
              @ int q = 0;
              @ /@ loop invariant 0 <= q <= i + j -1;
              @  @ loop invariant \forall integer w00; (0 <= w00 < i + j -1) ==> (\at(result[w00], Before) == result[w00]);
              @  @ loop invariant \forall integer x; count{Before}(result, 0, q, x) 
              @  @       == count(result, 0, q, x); 
              @  @ loop variant (i + j - 1) - q;
              @  @/
              @ while (q < i + j -1) {
              @     q++;
              @     /@ assert \forall integer x; count{Before}(result, 0, q, x)
              @      @      == count{Before}(result, 0, q - 1, x) + count{Before}(result, q - 1, q, x)
              @      @      == count{Before}(result, 0, q - 1, x) + (\at(result[\at(q - 1, Here)], Before) == x ? 1 : 0)
              @      @      == count(result, 0, q - 1, x) + (\at(result[\at(q - 1, Here)], Before) == x ? 1 : 0)
              @      @      == count(result, 0, q - 1, x) + count(result, q - 1, q, x)
              @      @      == count(result, 0, q, x); 
              @      @/
              @ }
            */
            /*@
              @ assert  \forall integer x; count{Before}(result, 0, i + j - 1, x) 
              @    == count(result, 0, i + j - 1, x);
            */
            /*@
              @ assert \forall integer x; count(first, 0, i, x) + count(second, 0, j, x)
              @     == count(first, 0, i, x) + (count(second, 0, j - 1, x) + count(second, j - 1, j, x))
              @     == count{Before}(first, 0, i, x) + (count{Before}(second, 0, j - 1, x) + count{Before}(second, j - 1, j, x))
              @     == (count{Before}(first, 0, i, x) + count{Before}(second, 0, j - 1, x)) + count{Before}(second, j - 1, j, x)
              @     == count{Before}(result, 0, i + j - 1, x) + count{Before}(second, j - 1, j, x)
              @     == count{Before}(result, 0, i + j - 1, x) + (\at(second[\at(j - 1, Here)], Before) == x ? 1 : 0)
              @     == count{Before}(result, 0, i + j - 1, x) + (result[i + j - 1] == x ? 1 : 0)
              @     == count{Before}(result, 0, i + j - 1, x) + count(result, i + j -1, i + j, x)
              @     == count(result, 0, i + j - 1, x) + count(result, i + j -1, i + j, x)
              @     == count(result, 0, i + j, x);
            */
        } else if (j == len2) {
            result[i + j] = first[i];
            i++;
        } else if (first[i] <= second[j]) {
            result[i + j] = first[i];
            i++;
        } else {
            result[i + j] = second[j];
            j++;
        }
    }
}