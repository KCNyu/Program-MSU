# Create cash flow vector
cf <- c(-95.79, 5, 5, 5, 5, 105)

# Create bond valuation function
bval <- function(i, cf,
                 t=seq(along = cf))
  sum(cf / (1 + i)^t)

# Create ytm() function using uniroot
ytm <- function(cf) {
  uniroot(bval, c(0, 1), cf = cf)$root
}

# Use ytm() function to find yield
ytm(cf)
## [1] 0.05999552
