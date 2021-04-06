#install.packages('quantmod')
library('quantmod')
#install.packages('forecast')
library('forecast')
library('xts')

#library(quantmod); library(xts)

Sys.setlocale("LC_TIME","C")


getSymbols("AAPL",src="yahoo")
ap1<-AAPL['2021-01-01/']
chartSeries(ap1,name="APPLE in $USD")
#barChart(AAPL)
getSymbols("XPT/USD",src="oanda")
chartSeries(XPTUSD,name="Platinum (.oz) in $USD")