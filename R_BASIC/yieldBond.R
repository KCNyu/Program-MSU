# Вектор денежного потока cash flow vector
cf <- c(-95.79, 5, 5, 5, 5, 105)

# короткая программа для оценки приведенной стоимости valuation function
bval <- function(i, cf,
                 t=seq(along = cf))
  sum(cf / (1 + i)^t)

# Находим доходность к погашению ytm() function using uniroot
ytm <- function(cf) {
  uniroot(bval, c(0, 1), cf = cf)$root
}

#  ytm() - доходность к погашению
ytm(cf)
## [1] 0.05999552
