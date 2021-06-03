#
#нарисуем график нормального распределения N(m,sigma)
#
m<-0
sigma<-1
exp2 <- function(x) (2*pi)^(-0.5)*exp(-(x-m)^2/(2*sigma^2))

curve(exp2, -3, 3, n = 200)
plot (exp2, -10, 10, n = 200)

#
# проинтергрируем -10 до 10
#
int_exp2<-integrate(function(x) exp2(x), lower = -10, upper = 10)
int_exp2
#1 with absolute error < 7.4e-05