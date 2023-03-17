int nSteps = 0;

byte empty_pos[2];
byte stack[10];

// 0 0 0 0 1 2 3 efs
  // 0 2     

//((((   (   (   ((nSteps<10) && (stack[0]==2))    && (stack[1]==2))     &&(stack[2]==2))    &&(stack[3]==1))&&(stack[4]==1))&&(stack[5]==1)))

inline CanMove(i) {
    !(stack[i] == 0 || stack[i + 1] == 0)
}

inline Move(i, j) {
    atomic {
        printf("(%d, %d) -> (%d, %d)\n", i, i+1, empty_pos[j], empty_pos[j] + 1);
        printf("%d\n", nSteps);
        stack[empty_pos[j]] = stack[i];
        stack[empty_pos[j]+1] = stack[i+1];
        stack[i] = 0;
        stack[i + 1] = 0;
        empty_pos[j] = i;
        nSteps = nSteps + 1;
    }
}

inline Step(i, j) {
    CanMove(i) -> Move(i, j)
}

/*
proctype main2() {
    Step(5, 1);
    Step(8, 1);
    Step(6, 0);
    Step(4, 1);

    printf("\n")
    byte i;
    for (i : 0..9) {
        printf("%d\n", stack[i])
    }
    printf("\n")
}


proctype main() {
    do
    :: Step(5, 1);
    :: Step(8, 1);
    :: Step(6, 0);
    :: Step(0, 0)
    :: Step(0, 1)
    :: Step(1, 0)
    :: Step(1, 1)
    :: Step(2, 0)
    :: Step(2, 1)
    :: Step(3, 0)
    :: Step(3, 1)
    :: Step(4, 0)
    :: Step(4, 1)
    :: Step(5, 0)
    :: Step(5, 1)
    :: Step(6, 0)
    :: Step(6, 1)
    :: Step(7, 0)
    :: Step(7, 1)
    :: Step(8, 0)
    :: Step(8, 1)
    od
} */

proctype main3() {
    do
    :: (nSteps <= 3) -> Step(0, 0)
    :: (nSteps <= 3) -> Step(0, 1)
    :: (nSteps <= 3) -> Step(1, 0)
    :: (nSteps <= 3) -> Step(1, 1)
    :: (nSteps <= 3) -> Step(2, 0)
    :: (nSteps <= 3) -> Step(2, 1)
    :: (nSteps <= 3) -> Step(3, 0)
    :: (nSteps <= 3) -> Step(3, 1)
    :: (nSteps <= 3) -> Step(4, 0)
    :: (nSteps <= 3) -> Step(4, 1)
    :: (nSteps <= 3) -> Step(5, 0)
    :: (nSteps <= 3) -> Step(5, 1)
    :: (nSteps <= 3) -> Step(6, 0)
    :: (nSteps <= 3) -> Step(6, 1)
    :: (nSteps <= 3) -> Step(7, 0)
    :: (nSteps <= 3) -> Step(7, 1)
    :: (nSteps <= 3) -> Step(8, 0)
    :: (nSteps <= 3) -> Step(8, 1)
    od
}


init {
    stack[0] = 0
    stack[1] = 0
    stack[2] = 0
    stack[3] = 0
    stack[4] = 1
    stack[5] = 2
    stack[6] = 1
    stack[7] = 2
    stack[8] = 1
    stack[9] = 2

    empty_pos[0] = 0
    empty_pos[1] = 2
    
    run main3();
}

ltl GoalNeverReached {
    !<>(nSteps == 3 && stack[0] == 2 && stack[1] == 2 && stack[2] == 2 && 
            stack[3] == 1 && stack[4] == 1 && stack[5] == 1
        )
}
