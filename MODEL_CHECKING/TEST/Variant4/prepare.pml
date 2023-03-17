byte nSteps = 0;

byte stack[10]; // 0 -- empty 1 -- black  2 -- white

#define EMPTY(i) (stack[i] == 0)
#define NOEMPTY(i) !EMPTY(i)

#define EMPTY_P(i) (EMPTY(i) && EMPTY(i+1))
#define NOEMPTY_P(i) (NOEMPTY(i) && NOEMPTY(i+1))


inline CanMove(src, dst) {
    EMPTY_P(dst) && NOEMPTY_P(src)
}

inline Move(i, j) {
    atomic {
        assert(nSteps <= 3);
        printf("(%d, %d) -> (%d, %d)\n", i, i + 1, j, j + 1);
        stack[j] = stack[i];
        stack[j+1] = stack[i+1];
        stack[i] = 0;
        stack[i + 1] = 0;
        nSteps = nSteps + 1;
    }
}

inline Step(i, j) {
    CanMove(i, j) -> Move(i, j)
}

proctype main() {
    // Step(5, 2)
    // Step(8, 5)
    // Step(6, 0)
    do
    :: Step(5, 2)
    :: Step(8, 5)
    :: Step(6, 0)
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
    
    run main();
}

ltl GoalNeverReached {
    !<>(nSteps == 3 && stack[0] == 2 && stack[1] == 2 && stack[2] == 2 && 
            stack[3] == 1 && stack[4] == 1 && stack[5] == 1 &&
            stack[6] == 0 && stack[7] == 0 && stack[8] == 0 && stack[9] == 0
        )
}

