fx<-1/(2-(-2))
fx

f1<-function(x) (fx*x)
Ex<-integrate(f1, lower = -2, upper = 2)
Ex$value

f2<-function(x) (fx*(x-Ex$value)^2)
Dx<-integrate(f2, lower = -2, upper = 2)
Dx$value