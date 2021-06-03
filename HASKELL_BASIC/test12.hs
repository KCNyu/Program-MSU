dup_1 :: Eq a => [a] -> Bool
dup_1 []         = False
dup_1 [x]        = False
dup_1 (x1:x2:xs) = x1 == x2 || dup_1(x1:xs)

dup_l :: Eq a => [a] -> Bool
dup_l []     = False
dup_l [x]    = False
dup_l (x:xs) = dup_1(x:xs) || dup_l(xs)
{--
detMat [[x]] = x
detMat [[a,b],[c,d]] = a*d - b*c
detMat ([]:xss) = 0
detMat ((x:xs):xss)
--}
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
    let elemI = xs !! i
        elemJ = xs !! j
        left = take i xs
        middle = take (j-i-1) (drop (i+1) xs)
        right = drop (j+1) xs
    in left ++ [elemJ] ++ middle ++ [elemI] ++ right
obratno :: Fractional t => [[t]] -> [[t]]
obratno [] = error "Empty Error"
obratno [[x]] = [[1/x]]
obratno (x:xs) = obratno_part(x:xs) ++ obratno_part(swaps 0 1(x:xs))
    where
        det = dety(x:xs)
        i = [i | i<-[1..(length(x)-1)]]
        obratno_part (x:xs) = [[(-1)^(j+1)*(dety(deletesty j xs))/det | j <-[1..(length x)]]]
--obratno_part  i (x:xs) = [[(-1)^(j+1)*(dety(deletesty j s))/det | j <-[1..(length x)]]]
--    where
--        s = if i <= (length(x)-1)
--            then drop(1 swaps(0 i (x:xs)))
--            else xs
