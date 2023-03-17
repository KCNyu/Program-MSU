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

task_bond_dur_sum <- function (face_value, coupon_rate, maturity, market_yield) {

  # Calculate present value and duration of each bond
  bond_pv_dur <- matrix(0, nrow = length(maturity), ncol = 2)
  for (i in 1:length(maturity)) {
    bond_pv_dur[i,] <- bondprc_dur(face_value, coupon_rate[i], maturity[i], market_yield[maturity[i]])
  }

  # Calculate portfolio present value and duration
  portfolio_pv <- sum(bond_pv_dur[,1])
  portfolio_duration <- sum(bond_pv_dur[,2] * bond_pv_dur[,1]) / portfolio_pv

  return(list(portfolio_pv, portfolio_duration, bond_pv_dur))
}

# Define bond parameters
face_value <- 100
coupon_rate <- c(0.05, 0.05, 0.055, 0.055, 0.055)
maturity <- c(1, 2, 3, 4, 5)
market_yield_a <- c(0.07, 0.07, 0.07, 0.07, 0.07)
market_yield_b <- c(0.02, 0.05, 0.06, 0.07, 0.085)

# result
resA = task_bond_dur_sum(face_value, coupon_rate, maturity, market_yield_a)
resB = task_bond_dur_sum(face_value, coupon_rate, maturity, market_yield_b)

# Install and load the quantmod package
# install.packages("ggplot2")
# install.packages("lubridate")

library(lubridate)
library(ggplot2)
bond_data <- read.csv("")
# Convert the Date column to a date format
bond_data$Date <- as.Date(bond_data$Date, "%b %d, %Y")

bond_data_2021 <- subset(bond_data, year(Date) == 2021)

ggplot(bond_data_2021, aes(x = Date, y = Price)) +
  geom_line() +
  labs(title = "China 10-Year Bond Yield Curve (2021)", x = "Date", y = "Yield (%)") +
  scale_x_date(date_breaks = "1 month", date_labels = "%b") +
  theme_minimal()

