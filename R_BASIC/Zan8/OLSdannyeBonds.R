library(MASS) 
#mBonds=(read.table("clipboard"))
 mBonds
#mPrice<-read.table("clipboard")
 # метод наименьших квадратов
 mPrice
 
 mB<-(as.matrix(mBonds))
 mB
 mP<-(as.matrix(mPrice))
 mP
 mBT<-t(mB)
 mB<-mBT%*%mB
 mB
 mP<-mBT%*%mP
 mP
 
 discontFact<- ginv(mB)%*%mP
 discontFact
 ir_curve<-c(rep(0,10))
for(i in (1:10)){
  ir_curve[i]=(1/discontFact[i])^(1/i)-1
  
}
  
  ir_curve
plot(ir_curve, type = 'b')
