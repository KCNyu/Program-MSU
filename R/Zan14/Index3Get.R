# получение данных по индексам yahoo
#install.packages('quantmod')
library('quantmod')

library('xts')

Sys.setlocale("LC_TIME","C")
#c("ˆVLIC") #,"GE","KO","AAPL","MCD")
#symbols=c("^FCHI")
#^GDAXI -DAX ^FCHI-CAC
#symbols=c("000300.SS")
#symbols=c("^DJI")
symbols=c("^GDAXI") 
getSymbols(symbols,src="yahoo")



symbols=c("^GDAXI") 
getSymbols(symbols,src="yahoo")

indxDAX.close<-GDAXI$GDAXI.Close['2021-01-01/']
indxDAX.F<-GDAXI$GDAXI.Close['2021-01-04/2021-01-04']
#print(indxDAX.F)
ifisrt<-as.numeric(indxDAX.F)
iDAX<-indxDAX.close/ifisrt
plot.xts(iDAX)
dDAX<-data.frame(iDAX)
write.table(dDAX, file = "iDAX.csv", sep = ",", col.names = NA,
            qmethod = "double")



symbols=c("^DJI") 
getSymbols(symbols,src="yahoo")
indxDJ.close<-DJI$DJI.Close['2021-01-01/']
indxDJ.F<-DJI$DJI.Close['2021-01-04/2021-01-04']
ifisrt<-as.numeric(indxDJ.F)
iDJ<-indxDJ.close/ifisrt
plot.xts(iDJ)
dDJ<-data.frame(iDJ)
write.table(dDJ, file = "iDJ.csv", sep = ",", col.names = NA,
            qmethod = "double")



symbols=c("^FCHI")
getSymbols(symbols,src="yahoo")
indxSAS.close<-FCHI$FCHI.Close['2021-01-01/']
indxSAS.F<-FCHI$FCHI.Close['2021-01-04/2021-01-04']
ifisrt<-as.numeric(indxSAS.F)
iSAS<-indxSAS.close/ifisrt
plot.xts(iSAS)
dSAS<-data.frame(iSAS)


write.table(dSAS, file = "iSAS.csv", sep = ",", col.names = NA,
            qmethod = "double")




