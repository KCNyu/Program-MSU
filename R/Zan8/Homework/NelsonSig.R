library(YieldCurve)
data(FedYieldCurve)
rate.Fed = first(FedYieldCurve,'5 month')

maturity.Fed <- c(1/12, 0.5, 1,2,3,5,8,13)
NSParameters <- Nelson.Siegel( rate= rate.Fed, maturity=maturity.Fed )
y <- NSrates(NSParameters[5,], maturity.Fed)
plot(maturity.Fed,rate.Fed[5,],main="Fitting Nelson-Siegel yield curve", type="o")
lines(maturity.Fed,y, col=2)
legend("topleft",legend=c("observed yield curve","fitted yield curve"),
       col=c(1,2),lty=1)

