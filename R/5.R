bondprc_dur <- function(p, r, ttm, y) {
  cf <- c(rep(p * r, times=ttm - 1), p * (1 + r))
  cf <- data.frame(cf)
  cf$t <- as.numeric(rownames(cf))
  cf$pv_factor <- 1 / (1 + y)^cf$t
  cf$pv <- cf$cf * cf$pv_factor
  cf$discont<-cf$pv*cf$t
  bpv=sum(cf$pv)
  tbpv=sum(cf$discont)/p
  tbpv_mac=sum(cf$discont)/bpv
  tbpv_mod=tbpv_mac*(1 / (1 + y))
  c(bpv,tbpv_mac)
}
ap1<-bondprc_dur(100, 0.05, 1, 0.07)
ap1
ap2<-bondprc_dur(100, 0.05, 2, 0.07)
ap2
ap3<-bondprc_dur(100, 0.055, 3, 0.07)
ap3
ap5<-bondprc_dur(100, 0.055, 5, 0.07)
ap5
bp1<-bondprc_dur(100, 0.05, 1, 0.02)
bp1
bp2<-bondprc_dur(100, 0.05, 1, 0.05)
bp2
bp3<-bondprc_dur(100, 0.05, 1, 0.06)
bp3
bp5<-bondprc_dur(100, 0.05, 1, 0.085)
bp5