# вычисление доходности и построение гистограммы
#install.packages('quantmod')
library('quantmod')
#install.packages('forecast')
library('forecast')
library('xts')

#library(quantmod); library(xts)

Sys.setlocale("LC_TIME","C")

#old.par <- par(mfrow=c(2,1))
#getSymbols("AAPL",src="yahoo")
ap1<-AAPL['2021-01-01/']
pr.close<-AAPL$AAPL.Close['2021-01-01/']
head(ap1)
plot.xts(pr.close)
chartSeries(ap1,name="APPLE in $USD",theme=chartTheme('white'))
barChart(ap1,theme=chartTheme('white'))

apRd= periodReturn(AAPL,period="monthly",type="log")

plot.xts(apRd)
chartSeries(apRd,name="месячная доходность",theme=chartTheme('white'))
hist(apRd, col="lightgray",border="white")


dsd=density(apRd) #ядерная оценка плотности доходностей
yl=c(min(dsd$y),max(dsd$y)) #определения нижних и верних границ
plot(dsd,main=NULL,ylim=yl)


##график нормальной плотности среднее и дисперсия  apRd
a=seq(min(apRd),max(apRd),0.001)
points(a,dnorm(a,mean(apRd),sd(apRd)), type="l",lty=2)
mean(apRd)
sd(apRd)
m1<-mean(apRd)
sd1<-sd(apRd)
p<-0.05
#P (X < x)=p
x<-qnorm (p, mean = m1, sd = sd1) 
x
#[1] -0.1294558
#квантиль выборочного распределения
x2<-quantile(apRd, p)
x2


dev.new()
qqnorm(apRd); qqline(apRd)
