# генерация 100 равномерно распределнных СВ
set.seed(16)
N<-1000000
a<-3
b<-4
data <- runif(N, a, b)
#plot(data,type='l')
#
# среднее значение
#
sr_data<-mean(data)
dis_data<-var(data)
# 4/3
#[1] 1.333333
# ожидание (b+a)/2
# дисперсия (b-a)^2/12
