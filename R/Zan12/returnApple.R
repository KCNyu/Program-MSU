# вычисление доходности и построение гистограммы
#install.packages('quantmod')
library('quantmod')
#install.packages('forecast')
library('forecast')
library('xts')

#library(quantmod); library(xts)

Sys.setlocale("LC_TIME","C")


getSymbols("AAPL",src="yahoo")
ap1<-AAPL['2021-01-01/']
pr.close<-AAPL$AAPL.Close['2021-01-01/']
head(ap1)
plot.xts(pr.close)
chartSeries(ap1,name="APPLE in $USD")
barChart(ap1)
