# -*- coding: utf-8 -*-

# 原函数
def argminf(x1, x2):
    r = 10*(x2-x1**2)**2+(1-x1)**2
    return r


# 全量计算一阶偏导的值
def deriv_x(x1, x2):
    r1 = 2*(20*x1**3-20*x1*x2+x1-1)
    r2 = 20*(x2-x1**2)
    return r1, r2

# 梯度下降算法
def gradient_decs(n):
    alpha = 0.01     # 学习率
    x1, x2 = 0, 0    # 初始值
    y1 = argminf(x1, x2)
    for i in range(n):
        deriv1, deriv2 = deriv_x(x1, x2)
        x1 = x1 - alpha * deriv1
        x2 = x2 - alpha * deriv2
        y2 = argminf(x1, x2)
        if y1 - y2 < 1e-16:
            return x1, x2, y2
        if y2 < y1:
            y1 = y2
    return x1, x2, y2
print(gradient_decs(100000))
