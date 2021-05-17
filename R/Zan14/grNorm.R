#
#нарисуем график нормального распределения N(m,sigma)
#
m<-0
sgm<-1
exp22 <- function(x) {(2*pi*sgm^2)^(-0.5)*exp(-(x-m)^2/(2*sgm^2))}
#exp3 <- function(x) 1/sigma*(2*pi)^(-0.5)*exp(-(x-m)^2/(2*sigma^2))
curve(exp22, -3, 3, n = 100)

#
# проинтегрируем -10 до p
#
int_exp22<-integrate(function(x) exp22(x), lower = -3, upper = 0)
int_exp22
#
#0.4986501 with absolute error < 5.5e-15
p<-0.5

qnorm(p, mean=m, sd=sgm)
#[1] 0
