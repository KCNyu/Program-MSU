#график 2 мерной плотности распределения случайного вектора
 function.draw <- function(f, low=-1, hi=1, n=30){
   r <- seq(low, hi, length=n)
   z <- outer (r, r, f)
   persp(r, r, z, xlab="X", ylab="Y", zlab="Z")}
 
 #f3 <- function(x, y) {ifelse(x >= y, 8*x*y, 0)}
 m<-0
 sgm<-1
 
 f3 <- function(x, y) {(2*pi*sgm^2)*exp((-((x-m)^2+(y-m)^2))/(2*sgm^2))}
 
 
 function.draw(f3,-3,3,25)
 
 