# Apple
# quarterly 

require(quantmod)

getSymbols("AAPL",src="yahoo")
a1=AAPL["2020-04-01/"]
#plot.xts(AAPL)

# plot.xts(a1)

apRq= periodReturn(AAPL,period="quarterly",type="log")

plot.xts(apRq)
chartSeries(apRq,name="квартальная доходность")
hist(apRq)


dsd=density(apRq) #ядерная оценка плотности доходностей
yl=c(min(dsd$y),max(dsd$y)) #определения нижних и верних границ
plot(dsd,main=NULL,ylim=yl)
# ##график нормальной плотности среднее и дисперсия  apRq
a=seq(min(apRq),max(apRq),0.001)
points(a,dnorm(a,mean(apRq),sd(apRq)), type="l",lty=2)

mean(apRq)
sd(apRq)
