#define N 2

bool flag[N] = 0;
byte turn = 0;

active [N] proctype P() {
  byte i = _pid;
  assert(0 <= i && i <= 1);
  NCS: printf("NCS%d\n", i);
  SET: flag[i] = 1; turn = i;
  TST: !((flag[1-i] == 1) && (turn == i));
  CRS: printf("CRS%d\n", i);
  RST: flag[i] = 0; goto NCS;
}

ltl safety {
  [](!(P[0]@CRS && P[1]@CRS))
}

ltl liveness {
  [](P[0]@SET -> <>(P[0]@CRS))
}
