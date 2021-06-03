minimum' :: (Ord a) => [a] -> a
minimum' [x] = x
minimum' (x:xs) = min x (minimum' xs)

foldr1' :: (a -> a -> a) -> [a] -> a
foldr1' f [x]     =  x
foldr1' f (x:xs)  =  f x (foldr1' f xs)

foldl11 :: (a -> a -> a) -> [a] -> a
foldl11 f [x]         =  x
foldl11 f (x:(y:ys))  =  foldl11 f (f x y : ys)

foldr':: (a -> b -> b) -> b -> [a] -> b
foldr' f x0 []      =  x0
foldr' f x0 (x:xs)  =  f x (foldr' f x0 xs)

foldl' :: (b -> a -> b) -> b -> [a] -> b
foldl' f x0 []      =  x0
foldl' f x0 (x:xs)  =  foldl' f (f x0 x) xs

sum1 :: (Num a) => [a] -> a
sum1      =  foldl (+) 0

product1 :: (Num a) => [a] -> a
product1 xs =  foldr (*) 1 xs

concat1 :: [[a]] -> [a]
concat1  =  foldr (++) []

mysum :: (Num a) => [a] -> a
mysum [] = 0
mysum [x] = x
mysum (x:xs) = (x) + (last' xs) + (mysum(init' xs))

last' :: [a] -> a
last' [] = error "empty list"
last' [x] = x
last' (x:xs) = last' xs

init' :: [a] -> [a]
init' [] = error "empty list"
init' [x] = []
init' (x:xs) = x:init'(xs)

mySort :: (Ord a)=> [a] -> [a]
mySort [] = []
mySort (x:xs) =
    let leftSort = mySort [a|a<-xs,a<=x]
        rightSort = mySort [a|a<-xs,a>x]
     in leftSort++[x]++rightSort

sort2 :: Ord a => [a] -> [a]
sort2 [] = []
sort2 [x] = [x]
sort2 (x1:x2:xs)
    | (x1<x2) = let (a:as) = sort2(x1:xs) in a : sort2(x2:as)
    | otherwise = let (a:as) = sort2(x2:xs) in a : sort2(x1:as)

swaps :: Ord a => [a] -> [a]
swaps [] = []
swaps [x] = [x]
swaps (x1:x2:xs)
    | x1 > x2 = x2 : swaps(x1:xs)
    | otherwise = x1 : swaps(x2:xs)

bubblesort :: Ord a => [a] -> [a]
bubblesort [] = []
bubblesort [x] = [x]
bubblesort xs = bubblesort(init' tmp) ++ [last' tmp]
    where
        tmp = swaps xs
