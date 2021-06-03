substring [x] = [x]
substring [x,y] = if(y /= (x+1)) then [x] else [x,y]
substring (x:y:xs) = if(y /= (x+1)) then [x] else x:(substring (y:xs))

substr s [] = s
substr s (x:xs) = if(len_s > len_str) then (substr s xs) else (substr str xs)
    where
        len_s = length s
        len_str = length str
        str = substring (x:xs)

substr_final s = substr [] s

-----------------------------------------------------------

getrow :: (Eq t, Num t) => [[t1]] -> t -> [t1]
getrow [] y     = []
getrow (x:xs) y = if y == 1 then x else getrow xs (y-1)

getcol :: [[t]] -> Int -> [t]
getcol [] y     = []
getcol (x:xs) y =  [x !! (y-1)] ++ getcol xs y

getelem :: [[a]] -> Int -> Int -> a
getelem xs i j = xs !! (i-1) !! (j-1)

getdiag' xs n = if(n < length xs) then [getelem xs n n]++getdiag' xs (n+1) else [getelem xs n n]
getdiag'' xs n = if(n < len) then [getelem xs n (len-n+1)]++getdiag'' xs (n+1) else [getelem xs n (len-n+1)]
    where
        len = length xs

judge_row_sum x xs res = (row == res)
    where
        row = sum $ getrow xs x

judge_col_sum x xs res = (col == res)
    where
        col = sum $ getcol xs x

judge1 n xs res = if(n < length xs) then (judge_row_sum n xs res) && (judge1 (n+1) xs res) else judge_row_sum n xs res
judge2 n xs res = if(n < length xs) then (judge_col_sum n xs res) && (judge2 (n+1) xs res) else judge_col_sum n xs res
judge3 xs res = diag1 == res && diag2 == res
    where
        diag1 = sum $ getdiag' xs 1
        diag2 = sum $ getdiag'' xs 1

judge xs = judge1 1 xs res && judge2 1 xs res && judge3 xs res
    where
        res = sum $ getrow xs 1

