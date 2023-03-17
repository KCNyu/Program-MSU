#define N 16

chan c = [1] of {byte /* PID */, int /* DATA */};

active [2] proctype P() {
  int i;

  if
  :: (_pid == 0) -> c!0,0
  :: else
  fi

  do
  :: c?eval(1 - _pid),i -> atomic {
                             c!_pid,(i + 1) % N;
                             printf("%d: %d\n", _pid, i);
                           }
  od
}

active proctype WatchDog() {
  do
  :: timeout -> assert(false)
  od
}

