### Нарисуем кривую доходности Европейского Центрального банка ###
data(ECBYieldCurve)

first(ECBYieldCurve,'3 day')
last(ECBYieldCurve,'3 day')

#mat.ECB <- tau <- c(3/12,6/12,1)
mat.ECB <- tau <- c(3/12,6/12,1:30)

par(mfrow=c(2,3))
#for( i in c(1,2,3,653,654,655) )
for( i in c(1,2,3) ){
  plot(mat.ECB, ECBYieldCurve[i,], type="o", xlab="Maturities structure in years", ylab="Interest rates values")
  title(main=paste("European Central Bank yield curve obeserved at",time(ECBYieldCurve[i], sep=" ") ))
  grid()
}
