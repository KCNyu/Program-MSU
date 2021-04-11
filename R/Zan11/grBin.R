par(mfrow=c(1,2), pty="m") #задает параметры для графиков 1, 2 квадратные
plot(0:8, dbinom(0:8,8,0.3), type="h", xlab="x", ylab="P(X=x)", xlim=c(-1,9))
 title("PDF for X~Bin(8, 0.3)")

plot(0:8, pbinom(0:8,8,0.3), type="n", xlab="x", ylab="F(x)",
      xlim=c(-1,9), ylim=c(0,1))
#segments(-1,0,0,0)
#segments(0:8, pbinom(0:8,8,.3), 1:9, pbinom(0:8,8,.3))
lines(0:7, pbinom(0:7,8,.3), type="p", pch=16)
segments(-1,1,9,1, lty=2)
title("CDF for X~Bin(8, 0.3)")