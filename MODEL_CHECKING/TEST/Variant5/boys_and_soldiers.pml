bit boat = 0;
bit boy1 = 0;
bit boy2 = 0;
bit soldier1 = 0;
bit soldier2 = 0;
bit soldier3 = 0;

active proctype main() {
  do
  :: (boy1 == boat && boy2 == boat) -> atomic { printf("2 Boys on the boat\n"); boat = 1 - boat; boy1 = 1 - boy1; boy2 = 1 - boy2; }
  :: (boy1 == boat) -> atomic {printf("1 Boy1 on the boat\n"); boat = 1 - boat; boy1 = 1 - boy1; }
  :: (boy2 == boat) -> atomic {printf("1 Boy2 on the boat\n"); boat = 1 - boat; boy2 = 1 - boy2; }
  :: (soldier1 == boat) -> atomic { printf("1 Soldier1 on the boat\n"); boat = 1 - boat; soldier1 = 1 - soldier1; }
  :: (soldier2 == boat) -> atomic { printf("1 Soldier2 on the boat\n"); boat = 1 - boat; soldier2 = 1 - soldier2; }
  :: (soldier3 == boat) -> atomic { printf("1 Soldier3 on the boat\n"); boat = 1 - boat; soldier3 = 1 - soldier3; }
  od
}

ltl GoalNeverReached {
  !(<>(boat && boy1 && boy2 && soldier1 && soldier2 && soldier3))
}