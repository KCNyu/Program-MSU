library('quantmod')
library('xts')

getSymbols("^NY", src = "yahoo")
ny<-NY$NY.Close
head(NY)
plot.xts(ny)
chartSeries(NY,name=" Nyse US 100 in $USD",theme=chartTheme('white'))

NYd= periodReturn(NY,period="daily",type="log")

plot.xts(NYd)
chartSeries(NYd,name="дневная доходность",theme=chartTheme('white'))
hist(NYd, col="lightgray",border="white")
dsd=density(NYd) #ядерная оценка плотности доходностей
yl=c(min(dsd$y),max(dsd$y)) #определения нижних и верних границ
plot(dsd,main=NULL,ylim=yl)

LogR = diff(log(NY))
plot(LogR)

mean(NYd)
sd(NYd)