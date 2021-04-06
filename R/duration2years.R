#
#расчет дюрации облигации 
#

m_flow<-c(0.1,1.1)  #денежный поток
m_rate<-c(0.1, 0.1) #рыночная доходность

d_factor<-c(1/(1+m_rate[1]),1/(1+m_rate[2])^2)
m_t<-c(1,2)

d_factor

#plot(m_flow)

s1<-m_flow*d_factor
s1

pr_value<-sum(m_flow*d_factor)
print( pr_value)

#m_duration=sum(s1*m_t)
m_dur=s1*m_t
m_duration=sum(s1*m_t)
print(m_duration)
