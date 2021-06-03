#
#вычисление выпуклости
#convexity

# —праведлива€ стоимость - 
bondconv_i <- function(p, cr, ttm, y) {
  cf <- c(rep(p * cr, times=ttm - 1), p * (1 + cr))
  cf <- data.frame(cf)
  cf$t <- as.numeric(rownames(cf))
  cf$pv_factor <- 1/(1+y)^cf$t
  cf$pv <- cf$cf * cf$pv_factor*cf$t*(cf$t+1)
  conv<-sum(cf$pv)/p
  conv_mac<-sum(cf$pv)/bondprc(p, cr, ttm, y)
  conv_mod<-conv_mac/(1+y)^2
  c(conv,conv_mac, conv_mod)
}

i=0.05
r1<-i
c1<-bondconv_i(100, 0.05, 5, y=r1)
c1
#[1] 26.38943 26.38943 23.93599
