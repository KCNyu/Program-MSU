# Apple
# weekly

require(quantmod)

getSymbols("AAPL",src="yahoo")
a1=AAPL["2020-04-01/"]
#plot.xts(AAPL)

# plot.xts(a1)

apRw= periodReturn(AAPL,period="weekly",type="log")

plot.xts(apRw)
chartSeries(apRw,name="недельная доходность")
hist(apRw)


dsd=density(apRw) #ядерная оценка плотности доходностей
yl=c(min(dsd$y),max(dsd$y)) #определения нижних и верних границ
plot(dsd,main=NULL,ylim=yl)
# ##график нормальной плотности среднее и дисперсия  apRw
a=seq(min(apRw),max(apRw),0.001)
points(a,dnorm(a,mean(apRw),sd(apRw)), type="l",lty=2)

mean(apRw)
sd(apRw)
