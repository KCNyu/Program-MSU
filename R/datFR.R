#set.seed(0)
options(digits =1)
df <-data.frame(id = LETTERS[1:6],
                age =runif(6, 24, 30),
                height =rnorm(6, 170, 2))
df
df$height
is.vector(df$height)
df$age