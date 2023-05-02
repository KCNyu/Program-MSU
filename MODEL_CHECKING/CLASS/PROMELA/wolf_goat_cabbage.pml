bit boat = 0;
bit wolf = 0;
bit goat = 0;
bit cabb = 0;

active proctype main() {
  do
  :: true           -> atomic { printf("boat\n"); boat = 1 - boat; }
  :: (wolf == boat) -> atomic { printf("wolf\n"); boat = 1 - boat; wolf = boat; }
  :: (goat == boat) -> atomic { printf("goat\n"); boat = 1 - boat; goat = boat; }
  :: (cabb == boat) -> atomic { printf("cabb\n"); boat = 1 - boat; cabb = boat; }
  od
}

#define UNSAFE ((wolf == goat) && (wolf != boat) ||\
                (goat == cabb) && (goat != boat))

#define SAFE !(UNSAFE)

ltl GoalNeverReached {
  !(SAFE U (boat && wolf && goat && cabb))
}

