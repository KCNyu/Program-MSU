# Справедливая стоимость + дюрация 
# - function
bondprc_dur <- function(p, r, ttm, y) {
  cf <- c(rep(p * r, times=ttm - 1), p * (1 + r))
  #  print(cf)
  cf <- data.frame(cf)
  #  cf
  cf$t <- as.numeric(rownames(cf))
  cf$pv_factor <- 1 / (1 + y)^cf$t
  cf$pv <- cf$cf * cf$pv_factor
  cf$discont<-cf$pv*cf$t
  
  bpv=sum(cf$pv) 
  
  tbpv=sum(cf$discont)/p
  
  tbpv_mac=sum(cf$discont)/bpv
 
  tbpv_mod=tbpv_mac*(1 / (1 + y))
  # стоимость, дюрация , дюрация Маколея и модфицированная дюрация
  
  c(bpv,tbpv, tbpv_mac, tbpv_mod)
}
# 20 летние
p2<-bondprc_dur(p = 100, r = 0.1, ttm = 20, y = 0.10)
p2
## 100.000000   9.364920   9.364920   8.513564