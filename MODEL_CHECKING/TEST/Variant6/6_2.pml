// source(out1) — время от времени порождает маркер на выходе;
proctype source(chan out1){
    do
    :: out1 ! 1 -> atomic { printf("source\n"); }
    od
}

// sink(in1) — время от времени поглощает маркер на входе;
proctype sink(chan in1){
    do
    :: in1 ? _ -> atomic { printf("sink\n"); }
    od
}

// fork(in1; out1, out2) — по одному входному маркеру генерирует два выходных;
proctype fork(chan in1, out1, out2){
    do
    :: in1 ? _ -> atomic{out1 ! 1; out2 ! 1; printf("fork\n"); }
    od
}

// join(in1, in2; out1) — по двум входным маркерам генерирует один выходной;
proctype join(chan in1, in2, out1){
    do
    :: in1 ? _ -> in2 ? _; atomic{out1 ! 1; printf("join\n"); }
    od
}

// switch(in1; out1, out2) — перенаправляет входной маркер на один из выходов;
proctype switch(chan in1, out1, out2){
    do
    :: in1 ? _ -> atomic{out1 ! 1; printf("switch1\n"); }
    :: in1 ? _ -> atomic{out2 ! 1; printf("switch2\n"); }
    od
}

// merge(in1, in2; out1) — перенаправляет один из входных маркеров на выход;
proctype merge(chan in1, in2, out1){
    do
    :: in1 ? _ -> atomic{out1 ! 1; printf("merge1\n"); }
    :: in2 ? _ -> atomic{out1 ! 1; printf("merge2\n"); }
    od
}

// queue[N](in1; out1) — добавляет в буфер емкости N маркер со входа, выдает из буфера маркер на выход.
proctype enqueue(chan in1, buf){
    do
    :: in1 ? _ -> atomic{buf ! 1; printf("enqueue\n"); }
    od
}

proctype dequeue(chan out1, buf){
    do
    :: buf ? _ -> atomic{out1 ! 1; printf("dequeue\n"); }
    od
}

proctype queue(chan in1, out1, buf){
    run enqueue(in1, buf);
    run dequeue(out1, buf);
}

active proctype WatchDog() {
    do
    :: timeout -> assert(false)
    od
}

chan a = [0] of {bit};
chan b = [0] of {bit};
chan c = [0] of {bit};
chan d = [0] of {bit};
chan e = [0] of {bit};
chan f = [0] of {bit};
chan g = [0] of {bit};
chan h = [0] of {bit};
chan i = [0] of {bit};
chan j = [0] of {bit};
chan k = [0] of {bit};
chan l = [0] of {bit};


chan buf2 = [2] of {bit};
chan buf3 = [3] of {bit};

init {
    atomic{
        run sink(a);
        run sink(b);
        run switch(c, a, b); 
        run join(d, e, c);
        run queue(f, d, buf2);
        run queue(g, e, buf3);
        run merge(h, i, f);
        run merge(j, k, g);
        run source(h);
        run source(k);
        run fork(l, i, j);
        run source(l);
    }
}