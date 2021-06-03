m<-3
sgm<-0.5
exp22 <- function(x) {(2*pi*sgm^2)^(-0.5)*exp(-(x-m)^2/(2*sgm^2))}
curve(exp22, 1.5, 4.5, n = 100)

int_exp22<-integrate(function(x) exp22(x), lower = 3.5, upper = +Inf)
int_exp22 # P(X > 3.5)
