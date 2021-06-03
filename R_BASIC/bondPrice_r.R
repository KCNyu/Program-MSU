#
#вычисление выпуклости
#

# Справедливая стоимость - сила процента
bondprc_r <- function(p, cr, ttm, r) {
  cf <- c(rep(p * cr, times=ttm - 1), p * (1 + cr))
  cf <- data.frame(cf)
  cf$t <- as.numeric(rownames(cf))
  cf$pv_factor <- exp(-r*cf$t)
  cf$pv <- cf$cf * cf$pv_factor
  sum(cf$pv)
}

i=0.1
r1=log(1+i)

px=bondprc_r(100, 0.1, 5, r=r1)

dr=0.01
r1=r1+dr
px_up=bondprc_r(100, 0.1, 5, r=r1)

r1=r1-dr
px_down=bondprc_r(100, 0.1, 5, r=r1)


# 
convexity <- -(px_up + px_down - 2 * px) / (px * (2*dr)^2)
convexity
## [1] 116.5218
