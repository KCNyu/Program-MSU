last' :: [a] -> a
last' [] = error "empty list"
last' [x] = x
last' (x:xs) = last' xs

init' :: [a] -> [a]
init' [] = error "empty list"
init' [x] = []
init' (x:xs) = x:init'(xs)

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
