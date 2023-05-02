#define N 3

int nSteps = 0;

typedef Stack {
  byte disks[N];
  byte size;
}

Stack stacks[3];

#define SIZE(i) stacks[i].size
#define TOP(i)  stacks[i].disks[SIZE(i)-1]

inline CanMove(src, dst) {
  SIZE(src) > 0 && (SIZE(dst) == 0 || TOP(dst) > TOP(src))
}

inline Move(src, dst) {
  atomic {
    assert(src != dst);
    printf("Move %d -> %d\n", src, dst);
    SIZE(dst)++;
    TOP(dst) = TOP(src);
    SIZE(src)--;
    nSteps++;
    printf("Steps %d\n", nSteps);
  }
}

inline Step(src, dst) {
  CanMove(src, dst) -> Move(src, dst)
}

proctype main() {
  do
  :: Step(0, 1)
  :: Step(0, 2)
  :: Step(1, 0)
  :: Step(1, 2)
  :: Step(2, 0)
  :: Step(2, 1)
  od
}

init {
  byte i;

  for(i : 0 .. (N - 1)) {
    stacks[0].disks[i] = (N - i);
  }

  stacks[0].size = N;
  stacks[1].size = 0;
  stacks[2].size = 0;

  run main();
}

ltl GoalNeverReached {
  !<>(SIZE(2) == N && nSteps < 10)
}
