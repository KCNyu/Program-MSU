# Apple
# yearly

require(quantmod)

getSymbols("AAPL",src="yahoo")
a1=AAPL["2020-04-01/"]
#plot.xts(AAPL)

# plot.xts(a1)

apRy= periodReturn(AAPL,period="yearly",type="log")

plot.xts(apRy)
chartSeries(apRy,name="годовая доходность")
hist(apRy)


dsd=density(apRy) #ядерная оценка плотности доходностей
yl=c(min(dsd$y),max(dsd$y)) #определения нижних и верних границ
plot(dsd,main=NULL,ylim=yl)
# ##график нормальной плотности среднее и дисперсия  apRy
a=seq(min(apRy),max(apRy),0.001)
points(a,dnorm(a,mean(apRy),sd(apRy)), type="l",lty=2)

mean(apRy)
sd(apRy)

