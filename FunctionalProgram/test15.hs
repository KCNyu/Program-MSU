multi :: [Int] -> [[Int]] ->[Int]
multi [] [] = []
multi [] _ = error "10"
multi _ [] = error "20"
multi (x:xs) (y:ys) = x * head y : multi xs ys

reduce :: [[Int]] -> [[Int]]
reduce [] = []
reduce (x:xxs) = check ((tail x) : reduce xxs)
    where
        check [[]] = []
        check x = x
--calculate one row
firstRow :: [Int] -> [[Int]] -> [Int]
firstRow _ [] = []
firstRow [] _ = []
firstRow x y = sum (multi x y) : firstRow x (reduce y)

matrixMulti :: [[Int]] -> [[Int]] -> [[Int]]
matrixMulti [] [] = []
matrixMulti [] _ = []
matrixMulti (x:xs) y = firstRow x y : matrixMulti xs y

converge::(Ord a, Num a)=>a->[a]->a
converge eps (a:b:xs)
      | abs (a-b)<= eps = a
      | otherwise = converge eps (b:xs)

easydiff::Fractional a=>(a->a)->a->a->a
easydiff f x h = (f(x+h)-2*f x+f(x-h))/h/h

diff::(Ord a, Fractional a)=>a->a->(a->a)->a->a
diff h0 eps f x =converge eps $ map(easydiff f x) $ iterate(/2) h0
     where easydiff f x h = (f(x+h)-2*f x+f(x-h))/h/h

intgrl::(Ord a, Fractional a)=>a->a->(a->a)->a->a->a
intgrl h0 eps f a b =converge eps $ map(easyIntgrl f a b) $ iterate(*2) h0

easyIntgrl::(Eq a, Fractional a)=>(a->a)->a->a->a->a
easyIntgrl f a b h = (b - a)/h * ((f a + f b)/ 2 + cikl f a ((b - a)/h) (h - 1))

cikl::(Eq a, Fractional a)=>(a->a)->a->a->a->a
cikl f x h 0 = 0
cikl f x h i = f (x + h * i) + cikl (f) x h (i - 1)
