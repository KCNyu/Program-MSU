library('quantmod')
library('xts')

setSymbolLookup(SSEC=list(name="000001.SS",src='yahoo'))
getSymbols("SSEC", src = "yahoo")
ssec<-SSEC$SSEC.Close
head(SSEC)
plot.xts(ssec)
chartSeries(SSEC,name=" SSEC in CNY",theme=chartTheme('white'))

SSECd= periodReturn(SSEC,period="daily",type="log")

plot.xts(SSECd)
chartSeries(SSECd,name="дневная доходность",theme=chartTheme('white'))
hist(SSECd, col="lightgray",border="white")
dsd=density(SSECd) #ядерная оценка плотности доходностей
yl=c(min(dsd$y),max(dsd$y)) #определения нижних и верних границ
plot(dsd,main=NULL,ylim=yl)

LogR = diff(log(SSEC))
plot(LogR)

mean(SSECd)
sd(SSECd)