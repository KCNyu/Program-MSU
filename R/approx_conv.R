#
#оценка выпуклости
#  с помощью 2 разности функции стоимости облигации 

r<-0.05
r1<-r

px=bondprc(100, 0.05, 5, y=r1)
px
#px
#[1] 100

dr=0.01
dr
r1=r+dr
px_up=bondprc(100, 0.05, 5, y=r1)
px_up
#[1] 95.78764

r1=r-dr
px_down=bondprc(100, 0.05, 5, y=r1)
px_down
#[1] 104.4518
# 
#


convexity <- (px_up + px_down - 2 * px) / (px * (dr^2))


convexity
#[1] 23.94585
