#define INVALID    255
#define TIMEOUT(c) nfull(c)
#define BUFSIZE    4

chan d = [1] of {
  byte, // Data
  bool, // Error
  byte  // SEQ
};

chan a = [1] of {
  bool, // Error
  byte  // SEQ
};

byte sendMSG = 0;
byte sendSEQ = 0;

byte recvMSG = INVALID;
byte recvSEQ = INVALID;

active proctype P() {
  byte seq;
  do
  :: a?0,seq -> if
                :: (seq == sendSEQ) -> atomic {
                                         printf("P: recv=%d\n", seq);
			                 sendMSG = (sendMSG + 1) % BUFSIZE;
                                         sendSEQ = !sendSEQ;
				       }
                :: else -> printf("P: wrong\n");
                fi
  :: a?1,_ -> printf("P: error\n");
  :: TIMEOUT(d) -> Sending: atomic {
                     printf("P: send=%d\n", sendSEQ);
                     d!sendMSG,0,sendSEQ;
                   }
  od
}

active proctype Q() {
  byte msg, seq;
  do
  :: d?msg,0,seq -> if
                    :: (seq != recvSEQ) -> atomic {
                                             printf("Q: recv=%d\n", seq);
                                             recvMSG = msg;
                                             recvSEQ = seq;
                                           }
                                           Received: skip
                    :: else -> printf("Q: wrong\n");
                    fi
  :: d?msg,1,seq -> printf("Q: error\n");
  :: TIMEOUT(a) && (recvMSG != INVALID) -> Sending: atomic {
                                             printf("Q: send=%d\n", recvSEQ);
                                             a!0,recvSEQ
                                           }
  od
}

active proctype dmedia() {
  do
  :: true -> Normal:
             atomic {
               printf("d: normal\n");
               d?<_,0,_> -> empty(d);
             }
  :: true -> Loss:
             atomic {
               printf("d: loss\n");
               d?_,0,_;
             }
  :: true -> Corruption:
             atomic {
               printf("d: corruption\n");
               d?_,0,_;
               d!INVALID,1,INVALID;
             }
  od
}

active proctype amedia() {
  do
  :: true -> Normal:
             atomic {
               printf("a: normal\n");
               a?<0,_> -> empty(a);
             }
  :: true -> Loss:
             atomic {
               printf("a: loss\n");
               a?0,_;
             }
  :: true -> Corruption:
             atomic {
               printf("a: corruption\n");
               a?0,_;
               a!1,INVALID;
             }
  od
}

active proctype WatchDog() {
  do
  :: timeout -> assert(false)
  od
}

#define D_ALIVE ([]<>(dmedia@Normal && P@Sending))
#define A_ALIVE ([]<>(amedia@Normal && Q@Sending))

ltl ReliableDataTransmission {
  (D_ALIVE && A_ALIVE) ->
    [](P@Sending -> <>(Q@Received && (recvMSG == sendMSG)))
}

