m<-0
sigma<-1

# exp2 <- function (x) {
#   (2*pi)^(-0.5)*exp(-(x-m)^2/(2*sigma^2))
# }

exp2 <- function(x) {
  (1/((2*pi)^(0.5)*sigma))*exp(-(x-m)^2/(2*sigma^2))
}
curve(exp2, -3, 3)
plot(exp2, -10, 10)

int_exp2<-integrate(function(x) exp2(x), lower = -10, upper = 10)
int_exp2$value
