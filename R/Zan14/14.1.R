m<-7
sgm<-3
exp22 <- function(x) {(2*pi*sgm^2)^(-0.5)*exp(-(x-m)^2/(2*sgm^2))}
curve(exp22, -2, 16, n = 100)

int_exp22<-integrate(function(x) exp22(x), lower = 7.1, upper = +Inf)
int_exp22 # P(X > 7.1)

p<-0.8
k<-qnorm(p, mean=m, sd=sgm)
k # P(X < k) = 0.8