byte father[2] = {0, 1}
byte mother[2] = {0, 2}
byte son[2] = {0, 4}
byte daughter[2] = {0, 5}
byte light = 0

byte min = 0

active proctype main() {
    do
    :: (father[0] == light && min + father[1] <= 12) -> atomic{ printf("father\n"); light = 1 - light; father[0] = 1 - father[0];  min = min + father[1]}
    :: (mother[0] == light  && min + mother[1] <= 12) -> atomic{ printf("mother\n"); light = 1 - light; mother[0] = 1 - mother[0];  min = min + mother[1]}
    :: (son[0] == light  && min + son[1] <= 12) -> atomic{ printf("son\n"); light = 1 - light; son[0] = 1 - son[0];  min = min + son[1]}
    :: (daughter[0] == light  && min + daughter[1] <=12) -> atomic{ printf("daughter\n"); light = 1 - light; daughter[0] = 1 - daughter[0];  min = min + daughter[1]}
    :: (father[0] == light && mother[0] == light  && min + mother[1] <= 12) -> atomic { printf("father and mother\n"); light = 1 - light; father[0] = 1 - father[0]; mother[0] = 1 - mother[0]; min = min + mother[1]}
    :: (father[0] == light && son[0] == light  && min + son[1] <= 12) -> atomic { printf("father and son\n"); light = 1 - light; father[0] = 1 - father[0]; son[0] = 1 - son[0]; min = min + son[1]}
    :: (father[0] == light && daughter[0] == light  && min + daughter[1] <=12) -> atomic { printf("father and daughter\n"); light = 1 - light; father[0] = 1 - father[0]; daughter[0] = 1 - daughter[0]; min = min + daughter[1]}
    :: (mother[0] == light && son[0] == light  && min + son[1] <= 12) -> atomic { printf("mother and son\n"); light = 1 - light; mother[0] = 1 - mother[0]; son[0] = 1 - son[0]; min = min + son[1]}
    :: (mother[0] == light && daughter[0] == light  && min + daughter[1] <=12) -> atomic { printf("mother and daughter\n"); light = 1 - light; mother[0] = 1 - mother[0]; daughter[0] = 1 - daughter[0]; min = min + daughter[1]}
    :: (son[0] == light && daughter[0] == light  && min + daughter[1] <=12) -> atomic { printf("son and daughter\n"); light = 1 - light; son[0] = 1 - son[0]; daughter[0] = 1 - daughter[0]; min = min + daughter[1]}
    od
}

ltl GoalNeverReached {
  !(<>(father[0] == 1 && mother[0] == 1 && son[0] == 1 && daughter[0] == 1))
}