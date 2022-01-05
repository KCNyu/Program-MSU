# 并行计算研究Brocard问题

###### *CPU: Intel(R) Core(TM) i5-8300H CPU @ 2.30GHz (Cores 4 Threads 8)*

### 0、问题简介

**Brocard问题**是一个数学问题，要求找到n和m的整数值，其中
$$
n! + 1 = m^2
$$
它是由亨利·布罗卡德（Henri Brocard）在1876年和1885年的两篇文章中提出的，并于1913年由斯里尼瓦萨·拉马努金（Srinivasa Ramanujan）独立提出。

解决布罗卡德问题的数字（n，m）对称为布朗数。 截至2021年5月，只有三对已知的布朗数字：
$$
(4,5)、(5,11)、(7,11)
$$
Paul Erdős推测没有其他解决方案存在。Overholt（1993）表明，只要abc猜想是正确的，就只有有限多的解决方案。Berndt & Galway（2000）对n进行了高达109的计算，但没有发现进一步的解决方案。Matson（2017）将这一数字扩大了三个数量级，达到一万亿。



###### *本文将在不使用任何第三方库的情况下，从简单算法层面进行该问题的尝试性解决。*



### 1、问题剖析



#### I) 计算大数阶乘

##### 

##### 1) 核心BigInteger类

*一个int储存八位数字，极大扩展内存上限。*

```c++
class BigInteger {
private:
    static const int BASE = 100000000;
    static const int WIDTH = 8;
    // Each vector contains eight digits
    bool sign;
    // false means negative
    size_t length;
    // length of digits
    std::vector<int> num;
    // reverse storage
```



##### 2) 快速阶乘

*使用Eratosthenes筛法进行快速阶乘计算*

```c++
BigInteger Factorial(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    if (n == 1 || n == 2) return n;
    std::vector<bool> u(n + 1, false);
    std::vector<std::pair<int, int>> p; // 质因数及其对应幂阶
    for (int i = 2; i <= n; ++i) {

        if (!u[i]) // i为质数
        {
            // 计算因数及其幂阶
            int k = n / i;
            int c = 0;
            while (k > 0)
            {
                c += k;
                k /= i;
            }
            // 将因数及其对应幂阶储存
            p.push_back(std::pair<int, int>(i, c));
            // 筛选合数
            int j = 2;
            while (i * j <= n)
            {
                u[i * j] = true;
                ++j;
            }
        }
    }
```

*并行计算部分*

*辅以C++17并行计算策略**std::execution::par_unseq**提高计算速度*

```c++
    // 并行计算阶乘
    std::vector<BigInteger> bis;
 
    bis.resize(p.size());
    transform(std::execution::par_unseq,
        p.begin(), p.end(), bis.begin(),
        [&bis](pair<int, int>& elem) { return BigInteger(elem.first).pow(elem.second); }
    );

    BigInteger r = reduce(std::execution::par_unseq, bis.begin() + 1, bis.end(), bis[0], [](auto fir, auto sec) { return fir * sec; });
    return r;
```



##### 3) 运行结果

***非并行版本***

```
.\debug.exe
Testing with 50000!
Serial: Len: 213237 Time: 6794.138900ms
Serial: Len: 213237 Time: 6783.730000ms
Serial: Len: 213237 Time: 6793.402900ms
Serial: Len: 213237 Time: 6777.779000ms
Serial: Len: 213237 Time: 6782.529600ms

.\release.exe
Testing with 50000!
Serial: Len: 213237 Time: 815.084900ms
Serial: Len: 213237 Time: 801.489600ms
Serial: Len: 213237 Time: 760.321900ms
Serial: Len: 213237 Time: 749.938200ms
Serial: Len: 213237 Time: 744.722700ms
```

***并行版本***

```
.\debug.exe
Testing with 50000!
Parallel: Len: 213237 Time: 5145.338300ms
Parallel: Len: 213237 Time: 5075.909400ms
Parallel: Len: 213237 Time: 5027.378600ms
Parallel: Len: 213237 Time: 5017.485700ms
Parallel: Len: 213237 Time: 5022.266800ms

.\release.exe
Testing with 50000!
Parallel: Len: 213237 Time: 455.566500ms
Parallel: Len: 213237 Time: 467.521100ms
Parallel: Len: 213237 Time: 456.891900ms
Parallel: Len: 213237 Time: 458.666400ms
Parallel: Len: 213237 Time: 484.469900ms
```

由于手头这块CPU性能拉跨，但是依旧清晰可见效率提升还是非常明显的~



#### II) 使用数论方法优化问题校验策略



##### 1) 勒让德符号

勒让德符号
$$
{(\frac{a}{p})}
$$
有下列定义：

设 a 为整数，p 为 2 以外的素数。勒让德符号 (𝑎 / 𝑃) 定义如下：
$$
({\tfrac {a}{p}}) = 0\qquad如果 a 可以被 p 整除\\
({\tfrac {a}{p}}) = 1\quad如果 a 是二次残差模 p\\
\quad({\tfrac {a}{p}}) = -1\quad如果 a 是二次非残差模 p\\
$$
欧拉准则：
$$
{\displaystyle \left({\frac {a}{p}}\right)=\pm 1\equiv a^{\frac {p-1}{2}}{\pmod {p}}.}
$$
如果(a|p) = 1，a 便称为二次剩余(mod p)；如果(a|p) = −1，则 a 称为二次非剩余(mod p)。通常把零视为一种特殊的情况。



##### 2) 数论优化详解

由于这里的P值很大，所以使用了求幂和蒙哥马利模数。乘法被用来有效地计算勒让德符号。对于给定的一对整数，勒让德符号为 -1 的概率几乎为 50%，因此给出了证明 n 的关键！ + 1 不是一个完美的平方 - 它是一个具有足够素数的检查，因此必须为其中一个找到勒让德符号 -1 的结果。例如，如果对 40 个素数进行测试，则给定的 n 通过所有 40 个测试的概率大约为 2 ^ 40 分之一，或大约为万亿分之一。请注意，如果应该找到这样的 n，这并不意味着这个 Brocard 问题的解决方案是必要条件，但不是充分条件。



##### 3) 蒙哥马利模数

```c++
BigInteger PowModule(BigInteger base, long long a, const long long md) {
    BigInteger ans = 1;
    while (a != 0) {
        if (a & 1) ans = ans * base % md;
        base = base * base % md;
        a >>= 1;
    }
    return ans;
}
```



##### 4) 核心判断函数

***__builtin_expect***进行分支预测

```c++
void Judge(int n, int size) {
    BigInteger a = Factorial(n)+1;
    vector<bool> res;
    res.resize(size);
    transform(std::execution::par_unseq,
        Primes.begin(), Primes.end(), res.begin(),
        [&a,&res](auto& p) { 
            BigInteger tmp = a % p;
            BigInteger res = PowModule(tmp, (p - 1) / 2, p);
            if (__builtin_expect(res == 0 || res == 1),0) return 1;
            else return 0;
        }
    );
    for (auto i : res) {
        if (i == 0) return;
    }
    printf("The possible solution is %d\n", n);
}
```



#### 2、结果分析

```
Testing with 10000!
The possible solution is 4
The possible solution is 5
The possible solution is 7
Time: 35436.774900ms
```

半分钟内进行了一万内的检验，效果看上去还算不错，但实际上从BigInteger的设计等各个方面都有大量可优化的地方，只做一次尝试性探索。

