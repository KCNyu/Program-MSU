#define MUTEX_ENABLED

#define N 20

byte count = 0;
byte mutex = 1;

inline lock() {
  atomic { mutex > 0 -> mutex-- }
}

inline unlock() {
  mutex++
}

active [N] proctype P() {
  NCS: printf("NCS\n");
  SET:
#ifdef MUTEX_ENABLED
       lock();
#endif
  CRS: count++;
       printf("CRS\n");
  RST: count--;
#ifdef MUTEX_ENABLED
       unlock();
#endif
       goto NCS;
}

ltl MutualExclusion {
  [](count <= 1)
}
