library(MASS) 
mBonds=(read.table("Matrix_bond_2.txt"))
 mBonds
mPrice<-read.table("Matrix_price_2.txt")
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
 ir_curve<-c(rep(0,6))
for(i in (1:6)){
  ir_curve[i]=(1/discontFact[i])^(1/i)-1
  
}
  
  ir_curve
plot(ir_curve, type = 'b')
