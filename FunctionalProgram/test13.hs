dely :: Int-> [a] -> [a]
dely 1 (x:xs) = xs
dely k (x:xs) = [x] ++ dely (k-1) xs

deletesty::(Num a) => Int -> [[a]] -> [[a]]
deletesty k x = [c |c<- [ dely k q | q<-x ]]

dety :: Num a => [[a]] -> a
dety [] = error "Empty Error"
dety [[x]] = x
dety (x:xs) =
 sum [(-1)^(j+1)* (head [x])!!(j-1)
  * dety(deletesty j xs) | j
 <-
 [1..(length x) ]]

swaps :: Int -> Int -> [a] -> [a]
swaps i j xs =
    let elemI  = xs !! i
        elemJ  = xs !! j
        left   = take i xs
        middle = take (j-i-1) (drop (i+1) xs)
        right  = drop (j+1) xs
    in left ++ [elemJ] ++ middle ++ [elemI] ++ right

obratno :: Fractional t => [[t]] -> [[t]]
obratno [] = error "Empty Error"
obratno [[x]] = [[1/x]]
obratno (x:xs) = transpose([obratno_part(x:xs)]++[obratno_part_swap(swaps 0 i (x:xs))| i <-[1..(length(x)-1)]])
    where
        det = dety(x:xs)
        obratno_part (x:xs) = [(-1)^(j+1)*(dety(deletesty j xs))/det | j <-[1..(length x)]]
        obratno_part_swap (x:xs) = [(-1)^(j)*(dety(deletesty j xs))/det | j <-[1..(length x)]]

transpose :: [[a]] -> [[a]]
transpose ([]:_) = []
transpose xs     = mymap myhead xs : transpose(mymap mytail xs)

mymap :: (a -> b) -> [a] -> [b]
mymap _[]      = []
mymap f (x:xs) = f x:mymap f xs

myhead :: [a] -> a
myhead []    = error "empty list"
myhead (x:_) = x

mytail :: [a] -> [a]
mytail []     = error "empty list"
mytail (_:xs) = xs
