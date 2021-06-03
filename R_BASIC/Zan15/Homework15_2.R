# генерация y=ax+b x-нормально распред.
set.seed(16)
N<-100
m1<-0
s1<-1
data <- rnorm(N, m1, s1)
plot(data,type='l', main = 'график y=ax+b')

#
# среднее значение
#

sr_data<-mean(data)
sr_data
dis_data<-var(data)
dis_data
#[1] 0.05958278
# [1] 1.016086

x<-data
eps1<-rnorm(N, m1, s1)

#random number a, b, sg1
a<-runif(1,-2,2)
b<-runif(1,-1,1)
sg1<-runif(1,0,1)

y<-a*x+b+sg1*eps1
plot(x,type='l', main = 'график y=ax+b+eps')
i<-1:100
i=seq(1,100)

points(i,y,type="l",lty=2)