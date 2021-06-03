library(tidyverse) 
library(wbstats)

# наборы данных на сайте World Bank
# тестовая программа 
#df1_bond<-wb_search(pattern ="bond") %>% head
df1_bond<-wb_search(pattern ="bond")
df1_ed<-wb_search(pattern = "education")

df1_bond %>% head


df1_ed %>% tail