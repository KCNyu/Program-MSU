getrow :: (Eq t, Num t) => [[t1]] -> t -> [t1]
getrow [] y     = []
getrow (x:xs) y = if y == 1 then x else getrow xs (y-1)

getcol :: [[t]] -> Int -> [t]
getcol [] y     = []
getcol (x:xs) y =  [x !! (y-1)] ++ getcol xs y

getelem :: [[a]] -> Int -> Int -> a
getelem xs i j = xs !! (i-1) !! (j-1)

--------------------------------------------------------------------

minus_row :: Num t => [t] -> [t] -> [t]
minus_row [] [] = []
minus_row (x:xs) (y:ys) = x-y:minus_row xs ys

minus_row_const :: Num t => [t] -> [t] -> t -> [t]
minus_row_const xs ys n = minus_row xs (map (*n) ys)

minus_system :: (Num t, Eq t, Fractional t1) => [[t1]] -> t -> Int -> [t1]
minus_system xs i j = minus_row_const row_i row_j n
    where
        row_i = getrow xs i
        row_j = getrow xs j
        elem_i = row_i !! (j-1)
        elem_j = row_j !! (j-1)
        n = elem_i/elem_j

--------------------------------------------------------------------

change :: [a] -> a -> Int -> [a]
change xs elem i = left ++ [elem] ++ right
    where
        left = take (i-1) xs
        right = drop i xs

change_diag' :: Fractional a => [[a]] -> Int -> [[a]]
change_diag' xs i = if(i <= length xs) then change_diag' changed (i+1) else xs
    where
        diag_elem = getelem xs i i
        row = map (\x -> x/diag_elem) (xs!!(i-1))
        changed = change xs row i

change_diag :: Fractional a => [[a]] -> [[a]]
change_diag xs = change_diag' xs 1

--------------------------------------------------------------------

solve1 :: Fractional t1 => [[t1]] -> Int -> Int -> [[t1]]
solve1 xs i j = change xs elem i
    where elem = minus_system xs i j

solve2 :: Fractional t1 => [[t1]] -> Int -> Int -> [[t1]]
solve2 xs i j = if(i <= length xs) then solve2 solved (i+1) j else xs
    where solved = solve1 xs i j

solve3 :: Fractional t1 => [[t1]] -> Int -> [[t1]]
solve3 xs j = if(j <= length xs -1) then solve3 solved (j+1) else xs
    where solved = solve2 xs (j+1) j

solve_system :: Fractional a => [[a]] -> [[a]]
solve_system xs = change_diag xs'
    where xs' = solve3 xs 1

solve4 :: Num t1 => [[t1]] -> Int -> Int -> [[t1]]
solve4 xs i j = if(i <= j-1) then solve4 solved (i+1) j else xs
    where
        solved = change xs elem i
        elem = minus_row_const row_i row_j elem_ij
        row_i = getrow xs i
        row_j = getrow xs j
        elem_ij = getelem xs i j

solve5 :: Num t1 => [[t1]] -> Int -> [[t1]]
solve5 xs j = if(j >= 2) then solve5 solved (j-1) else xs
    where solved = solve4 xs 1 j

solve_final :: Fractional a => [[a]] -> [a]
solve_final xs = result
    where
        len = length xs
        xs1 = solve_system xs
        xs2 = solve5 xs1 len
        result = getcol xs2 (len+1)

--------------------------------------------------------------------

mult_vector :: Num a => [a] -> [a] -> a
mult_vector xs ys = sum[(xs!!j) * (ys!!j) | j<- [0..length xs -1]]

mult :: (Num a, Num t, Eq t) => [[a]] -> [[a]] -> t -> Int -> a
mult x y i j = mult_vector row col
    where
        row = getrow x i
        col = getcol y j

mult_matrix :: Num t => [[t]] -> [[t]] -> [[t]]
mult_matrix x y = [[mult x y i j|j<-[1..len_y]]|i<-[1..len_x]]
    where
        len_x = length(x)
        len_y = length(head y)

--------------------------------------------------------------------

rewrite :: Num t => [t] -> [[t]]
rewrite [] = [[0]]
rewrite (x:xs) = [[x]]++rewrite xs

diff :: Num a => [[a]] -> [[a]] -> a
diff xs ys = sum res
    where
        res = minus_row xs' ys'
        xs' = getcol xs (length xs + 1)
        ys' = getcol ys 1

diff_final :: Fractional a => [[a]] -> a
diff_final xs = diff xs k
    where
        res = rewrite (solve_final xs)
        k = mult_matrix xs res

