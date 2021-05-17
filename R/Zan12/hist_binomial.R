library(fBasics)
binom_gen <- function(samples, n, pi) {
  values <- sample(c(0,1), samples*n, replace=TRUE, prob=c(1-pi,pi))
  value.mat <- matrix(values, ncol=n)
  Successes <- apply(value.mat, 1, sum)
  a1 <- round((table(Successes)/samples), 3)
  b1 <- round(dbinom(0:n, n, pi), 3)
  names(b1) <- 0:n
  hist(Successes, breaks=c((-.5+0):(n+.5)), probability=TRUE,
       ylab="", main="  Теоретические значения плотности и
       Гистограмма смоделированных значений", col="lightblue")
  x <- 0:n
  fx <- dbinom(x, n, pi)
  lines(x, fx, type="h")
  lines(x, fx, type="p", pch=16)
  list(simulated.distribution=a1, theoretical.distribution=b1, vsample=value.mat)}

l_sample<-binom_gen(10, 10, 0.5)
vsample<-l_sample$vsample
vsample

colMeans(vsample)
var(vsample[,1])
sd(vsample[,1])

#basicStats(list3)
