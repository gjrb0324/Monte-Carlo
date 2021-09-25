library(ggplot2)
library(ggpubr)
df <- read.csv("D:/Kyu/Study/2021/2021 Fall Monte Carlo/output_0.1.csv")
lsnl = c()
lsel  = c()
for(i in df$pi_val){
  lse = log(abs(i-3.1415926535),10)
  lsel = c(lsel,lse)
}
for(i in df$trial){
  lsn = log(i,10)
  lsnl = c(lsnl,lsn)
}
df_2 <- data.frame(lsnl,lsel)
ggplot(data = df_2, aes(x = lsnl, y = lsel ))+
  geom_point()+
  xlab("log scale trial") + ylab("log scale error")+
  ggtitle("Relationship between trial and error of the value of pi") +
  geom_smooth(method = "lm")+
  stat_regline_equation()
 