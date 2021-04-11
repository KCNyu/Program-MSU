par(mfrow=c(1,2), pty="m") #задает параметры для графиков 1, 2 квадратные
N<-200
p<-0.8

plot(0:N, dbinom(0:N,N,p), type="h", xlab="x", ylab="P(X=x)", xlim=c(-1,N+1))
 title("PDF for X~Bin(N, p)")

plot(0:N, pbinom(0:N,N,p), type="n", xlab="x", ylab="F(x)",
      xlim=c(-1,N+1), ylim=c(0,1))
segments(-1,0,0,0)
segments(0:N, pbinom(0:N,N,p), 1:N+1, pbinom(0:N,N,p))
lines(0:N-1, pbinom(0:N-1,N,p), type="p", pch=16)
segments(-1,1,9,1, lty=2)
title("CDF for X~Bin(N, p)")