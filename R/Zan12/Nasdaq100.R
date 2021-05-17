library('quantmod')
library('xts')

getSymbols("^NDX", src = "yahoo")
NDX<-nasdaq$NDX
ndx<-NDX$NDX.Close
head(NDX)
plot.xts(ndx.close)
chartSeries(NDX,name=" Nasdaq 100 in $USD",theme=chartTheme('white'))

NDXd= periodReturn(NDX,period="daily",type="log")

plot.xts(NDXd)
chartSeries(NDXd,name="дневная доходность",theme=chartTheme('white'))
hist(NDXd, col="lightgray",border="white")
dsd=density(NDXd) #ядерная оценка плотности доходностей
yl=c(min(dsd$y),max(dsd$y)) #определения нижних и верних границ
plot(dsd,main=NULL,ylim=yl)

LogR = diff(log(NDX))
plot(LogR)

mean(NDXd)
sd(NDXd)