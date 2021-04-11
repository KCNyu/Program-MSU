# Apple
# daily

require(quantmod)

getSymbols("AAPL",src="yahoo")
a1=AAPL["2020-04-01/"]
#plot.xts(AAPL)

# plot.xts(a1)

apRd= periodReturn(AAPL,period="daily",type="log")

plot.xts(apRd)
chartSeries(apRd,name="дневная доходность")
hist(apRd)


dsd=density(apRd) #ядерная оценка плотности доходностей
yl=c(min(dsd$y),max(dsd$y)) #определения нижних и верних границ
plot(dsd,main=NULL,ylim=yl)
# ##график нормальной плотности среднее и дисперсия  apRd
a=seq(min(apRd),max(apRd),0.001)
points(a,dnorm(a,mean(apRd),sd(apRd)), type="l",lty=2)

mean(apRd)
sd(apRd)
