library(MASS) 

mBonds=(read.table("LeastSquares_bonds.txt"))
 mBonds
mPrice<-read.table("LeastSquares_price.txt")
 mPrice
 #betta<-0.01
 betta<-0.3
 
 
 mReg=(read.table("Reg.txt"))
 mReg 
# mReg<-0.01*mReg
 mB<-(as.matrix(mBonds))
 mB
 mP<-(as.matrix(mPrice))
 mP
 mBT<-t(mB)
 mB<-mBT%*%mB
 mB
 mR<-(as.matrix(mReg))
 mR
 mRT<-t(mR)
 mR<-mRT%*%mR
 mR<-betta*mR
 
 mP<-mBT%*%mP
 mP
 
 
 discontFact<- ginv(mB+mR)%*%mP
 discontFact
 ir_curve<-c(rep(0,10))
for(i in (1:10)){
  ir_curve[i]=(1/discontFact[i])^(1/i)-1
  
}
  
  ir_curve
plot(ir_curve, type = 'b')
# id<-i1-ir_curve
# plot(id)

