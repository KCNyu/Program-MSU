duration<-function (i, cupon, n, t)
{
  t_f<-seq(from = 1, to = n)
  d=1/(1+i)
  
  d_f=d^t_f;
  c_f=seq(1,1,n)
  c_f=cupon*c_f
  cur_val=sum(d_f*c_f)+1*d^n
  
  return(cur_val)
}


plot(sin, -pi, 2*pi) # see ?plot.function

sincosexp <- function(x) sin(cos(x)*exp(-x/2))
curve(sincosexp, 4, 17, n = 200)
plot (sincosexp, -17, -4, n = 200)

duration(0.1,0.1,10,1)
