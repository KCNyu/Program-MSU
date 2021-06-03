subStr:: [Int] -> Int -> Int -> [Int]
subStr x i j
    | i < 0 || j >= length(x) || j < i = error "skip"
    |otherwise = subStr1 x i j
    where
        subStr1 (x:xs) 0 0 = [x]
        subStr1 (x:xs) 0 j = x:subStr1 xs 0 (j - 1)
        subStr1 (x:xs) i j  = subStr1 xs (i - 1) (j - 1)

 
helpMumu::[Int] -> [Int] -> Int -> Int -> [Int]
helpMumu a b i j
    |j >=  length(b) && i < length(b)= (b!!i):helpMumu a b (i + 1) (j + 1)
    |i >= length(b) = []
    |a == (subStr b i j)  = helpMumu a b (i + length(a)) (j + length(a))
    |otherwise = (b!!i):helpMumu a b (i + 1) (j + 1)
        
        
mumu418:: [Int] -> [Int] -> [Int]
mumu418 [] b = b
mumu418 a b
    | length(a) > length(b) = b
    | otherwise = helpMumu a b 0 (length(a)-1)
    
mumu1:: [Int] -> [Int] -> [Int]
mumu1 a b
    | c == b = c 
    | otherwise = mumu1 a c
    where c = mumu418 a b
