library('quantmod')
library('xts')
Sys.setlocale("LC_TIME","C")
getSymbols("AAPL", src = "yahoo")
getSymbols("^DJI", src = "yahoo")

indxAP.close<-AAPL$AAPL.Close['2021-01-01/']
indxAP.F<-AAPL$AAPL.Close['2021-01-04/2021-01-04']
ifisrt<-as.numeric(indxAP.F)
iAP<-indxAP.close/ifisrt
plot.xts(iAP)
dAP<-data.frame(iAP)
write.table(dAP, file = "iAP.csv", sep = ",", col.names = NA,
            qmethod = "double")

indxDJ.close<-DJI$DJI.Close['2021-01-01/']
indxDJ.F<-DJI$DJI.Close['2021-01-04/2021-01-04']
ifisrt<-as.numeric(indxDJ.F)
iDJ<-indxDJ.close/ifisrt
plot.xts(iDJ)
dDJ<-data.frame(iDJ)
write.table(dDJ, file = "iDJ.csv", sep = ",", col.names = NA,
            qmethod = "double")