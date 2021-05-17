library('quantmod')
library('xts')

getSymbols("^GSPC", src = "yahoo")
gspc<-GSPC$GSPC.Close
head(GSPC)
plot.xts(gspc)
chartSeries(GSPC,name=" Gspc 500 in $USD",theme=chartTheme('white'))

GSPCd= periodReturn(GSPC,period="daily",type="log")

plot.xts(GSPCd)
chartSeries(GSPCd,name="дневная доходность",theme=chartTheme('white'))
hist(GSPCd, col="lightgray",border="white")
dsd=density(GSPCd) #ядерная оценка плотности доходностей
yl=c(min(dsd$y),max(dsd$y)) #определения нижних и верних границ
plot(dsd,main=NULL,ylim=yl)

LogR = diff(log(GSPC))
plot(LogR)

mean(GSPCd)
sd(GSPCd)