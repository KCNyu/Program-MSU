f (n,m) [] = []
f (n,m) (x:xs)
    | (n == 0 || m == 0) = f(n-1,m-1) xs
    | otherwise = x:(f (n-1,m-1) xs)

mydivid eps c h = converge eps (iterate(\x -> x*(2-c*x)) h)
mydivid' c = converge 1e-20 (iterate(\x -> x*(2-c*x)) 1e-19)

converge::(Ord a, Num a)=>a->[a]->a
converge eps (a:b:xs)
      | abs (a-b)<= eps = a
      | otherwise = converge eps (b:xs)

easydiff::Fractional a=>(a->a)->a->a->a
easydiff f x h = (f(x+h)-2*f x+f(x-h))/h/h

diff::(Ord a, Fractional a)=>a->a->(a->a)->a->a
diff h0 eps f x =converge eps $ map(easydiff f x) $ iterate(/2) h0
     where easydiff f x h = (f(x+h)-2*f x+f(x-h))/h/h
