######################################################################
#########
## gauss_pdfs.m
##
## Плотность распреления (pdf) гауссовской СВ.
######################################################################
#########
0 20 40 60 80 100 -2 -1 0 1 2 3
график y=ax+b+eps
Index
x6
## СКО
sigma = [0.5, 1, 2]; ## sigma СКО
y = linspace(-6, 6, 100); ## разбиение 
Pry(1,:) = normpdf(y, 2, sigma(1)); ## плотность для 
sigma(1).
Pry(2,:) = normpdf(y, 0, sigma(2)); ## плотность для 
sigma(2).
Pry(3,:) = normpdf(y, 0, sigma(3)); ## плотность для 
sigma(3).
Pry1(1,:) = stdnormal_cdf (y); ## плотность для sigma(1).
## Графики
figure
hold on;
plot(y, Pry(1,:), '1;0.5;','linewidth', 4); 
plot(y, Pry(2,:), '2;1.0;','linewidth', 4); 
plot(y, Pry(3,:), '3;2.0;','linewidth', 4); 
hold off
figure
plot(y, Pry1(1,:), '1;Standart N(0,1) ;','linewidth', 4); 
## Количество точек
## Индексная переменная
N=100;
i=1:N;
x=randn(1,N);
epsilon=randn(1,N);
a=2;
b=1;7
sg=0.5;
y=a*x+b+sg*epsilon;
figure
hold on
plot( i, x(1,:), '1; x = stand normal;','linewidth', 1); 
plot( i, y(1,:), '2; y = ax+b ;','linewidth', 1);