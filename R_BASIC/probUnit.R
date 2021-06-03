# Квадратный полином x^2-9   : -3 and 3
f <- function (x) x ^ 2 - 9
curve(f, from = -5, to = 5); abline(h = 0, lty = 3)

uniroot(f, lower = -5, upper = 5)
#Error in uniroot(f, lower = -5, upper = 5) : 
#  f() значений на концевых точках не противоположного знака
#

uniroot(f, lower = -5, upper = 0)
#


uniroot(f, lower = 0, upper = 5)
