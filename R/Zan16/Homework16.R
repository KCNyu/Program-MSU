# ARIMA -модель .
library("ggplot2") # графики
library("forecast") # прогнозирование временных рядов: ARMA 
library("xts") # операции с временными рядами
set.seed(16)
y <- arima.sim(n = 100, list(order = c(1,0,0),ar = 0.7))
ggtsdisplay(y)
set.seed(16)
y1 <- arima.sim(list(order = c(1,0,0), ar = 0.7), n = 100 )
ts.plot(y1)
set.seed(16)
y2 <- arima.sim(list(order = c(1,0,0), ar = 0.7), n = 100, sd =12 )
ts.plot(y2)