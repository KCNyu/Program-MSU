proctype euclid(int a, b) {
  int x = a;
  int y = b;
  printf("a=%d, b=%d\n", a, b);
  assert(a > 0 && b > 0);
  do
  :: x > y -> x = x - y
  :: x < y -> y = y - x
  :: else  -> break
  od
  printf("gcd(%d,%d)=%d\n", a, b, x);
}

init {
  run euclid(25, 5);
  run euclid(33, 11);
  run euclid(19, 17);
}
