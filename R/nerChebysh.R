x <- 0:3
px <- c(1/8,3/8,3/8,1/8)
EX <- weighted.mean(x, px)
EX2 <- weighted.mean(x^2, px)
VX <- EX2 - EX^2
sigmaX <- sqrt(VX)
c(EX, EX2, VX, sigmaX)
#[1] 1.5000000 3.0000000 0.7500000 0.8660254
