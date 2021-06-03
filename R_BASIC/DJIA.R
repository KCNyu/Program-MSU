#
#индекс Доу Джонса
# и ставка LIBOR 3 мес
require(quantmod)
getSymbols("DJIA",src="FRED") 
plot.xts(DJIA,main="DJIA")
dj<-DJIA['2020-01-01/']
chartSeries(dj,name="DJIA")
dj_ya<-getSymbols("^DJI",src="yahoo")
ns_ya<-getSymbols("^IXIC",src="yahoo")

# LIBOR 3 mnth
#USD3MTD156N
getSymbols('USD3MTD156N',src='FRED')
head(USD3MTD156N)
str(USD3MTD156N)
sample.xts=USD3MTD156N['2007-04-01/']
sample1.xts=USD3MTD156N['2020-04-01/']
plot.xts(sample.xts)
plot.xts(sample1.xts)
chartSeries(sample1.xts,name="LIBOR")
