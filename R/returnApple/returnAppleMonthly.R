# Apple
# monthly

require(quantmod)

getSymbols("AAPL",src="yahoo")
a1=AAPL["2020-04-01/"]
#plot.xts(AAPL)

# plot.xts(a1)

apRm= periodReturn(AAPL,period="monthly",type="log")

plot.xts(apRm)
chartSeries(apRm,name="месячная доходность")
hist(apRm)


dsd=density(apRm) #ядерная оценка плотности доходностей
yl=c(min(dsd$y),max(dsd$y)) #определения нижних и верних границ
plot(dsd,main=NULL,ylim=yl)
# ##график нормальной плотности среднее и дисперсия  apRm
a=seq(min(apRm),max(apRm),0.001)
points(a,dnorm(a,mean(apRm),sd(apRm)), type="l",lty=2)

mean(apRm)
sd(apRm)
