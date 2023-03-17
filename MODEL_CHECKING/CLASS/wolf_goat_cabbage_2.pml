bit boat = 0;
bit wolf = 0;
bit goat = 0;
bit cabb = 0;

active proctype main() {
  do
  :: (wolf != goat) && (goat != cabb) ->
         atomic { printf("boat\n"); boat = 1 - boat; }
  :: (wolf == boat) && (goat != cabb) ->
         atomic { printf("wolf\n"); boat = 1 - boat; wolf = boat; }
  :: (goat == boat) ->
         atomic { printf("goat\n"); boat = 1 - boat; goat = boat; }
  :: (cabb == boat) && (wolf != goat) ->
         atomic { printf("cabb\n"); boat = 1 - boat; cabb = boat; }
  od
}

ltl GoalNeverReached {
  !(<>(boat && wolf && goat && cabb))
}

