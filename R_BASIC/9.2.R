set.seed(16)
N<-100
data<-runif(N, -2, 2)
plot(data, type = 'l')

sr_data<-mean(data) #E[X]
dis_data<-var(data) #D[X]

