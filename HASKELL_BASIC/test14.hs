-- Формирует строку транспонированной матрицы
--frstrow :: [[Float]] -> [Float]
frstrow []     = []
frstrow (x:xs) = head x : frstrow xs

--Вспомогательная для вычеркивания столбца (удаляет выбранный элемент из строки)
--minstolbvs :: [Float] -> Int -> [Float]
minstolbvs (x:xs) y = if y==1 then xs else x : minstolbvs xs (y-1)

-- Вычеркивание выбранного столбца
--minstolb :: [[Float]] -> Int -> [[Float]]
minstolb [] _     = []
minstolb (x:xs) y = minstolbvs x y : minstolb xs y

-- Основная функция транспанирования
transp :: [[Float]] -> [[Float]]
transp [[]] = [[]]
transp (x:xs) = if (tail x == []) then [frstrow (x:xs)]
else  frstrow (x:xs) : transp(minstolb (x:xs) 1)


--Убирает выбранную строку
minrow :: [[Float]] -> Int -> [[Float]]
minrow (x:xs) y = if y==1 then xs else x:minrow xs (y-1)

--Определитель
dety :: [[Float]] ->Float
dety [[x]] = x
dety (x:xs) = sum [(-1)^(1+j) * x!!(j-1) * dety (minstolb xs j) | j<- [1..length x]]

-- Вспомогательная функция к основной
-- (Считает дополнения ко всей строке и делит на детерминант)
rematrx1 ::[[Float]] -> Int -> [Float]
rematrx1 x y=  [((-1)^(y+j) * dety (minrow (minstolb x j) y))/ dety x | j<-[1..length x]]

--Основная функция обратной матрицы
rematrx :: [[Float]] -> [[Float]]
rematrx x = transp ([c | c <- [rematrx1 x y | y<-[1..length x]]])

{--------------------------------------------------------------------}

getrow :: (Eq t, Num t) => [[t1]] -> t -> [t1]
getrow [] y     = []
getrow (x:xs) y = if y == 1 then x else getrow xs (y-1)

getcol :: [[t]] -> Int -> [t]
getcol [] y     = []
getcol (x:xs) y =  [x !! (y-1)] ++ getcol xs y

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

{--------------------------------------------------------------------}

minus_row :: (Num t) => [t] -> [t] -> [t]
minus_row [] [] = []
minus_row (x:xs) (y:ys) = x-y:minus_row xs ys

mult_const_vector n [] = []
mult_const_vector n (x:xs) = (n*x):mult_const_vector n xs

minus_row_const xs ys n = minus_row xs (mult_const_vector n ys)

minus_system xs i j = minus_row_const row_i row_j n
    where
        row_i = getrow xs i
        row_j = getrow xs j
        elem_i = row_i !! (j-1)
        elem_j = row_j !! (j-1)
        n = elem_i/elem_j

change xs elem i = left ++ [elem] ++ right
    where
        left = take (i-1) xs
        right = drop i xs

solve1 xs i j = change xs elem i
    where elem = minus_system xs i j
solve2 xs i j = if(i <= length xs) then solve2 solved (i+1) j else xs
    where solved = solve1 xs i j
solve3 xs j = if(j <= length xs -1) then solve3 solved (j+1) else xs
    where solved = solve2 xs (j+1) j

change_diag' xs i = if(i <= length xs) then change_diag' changed (i+1) else xs
    where
        diag_elem = xs !! (i-1) !! (i-1)
        row = map (\x -> x/diag_elem) (xs!!(i-1))
        changed = change xs row i

change_diag xs = change_diag' xs 1

solve_system xs = change_diag xs'
    where xs' = solve3 xs 1

getelem xs i j = xs !! (i-1) !! (j-1)

solve4 xs i j = if(i <= j-1) then solve4 solved (i+1) j else xs
    where
        solved = change xs elem i
        elem = minus_row_const row_i row_j elem_ij
        row_i = getrow xs i
        row_j = getrow xs j
        elem_ij = getelem xs i j
solve5 xs j = if(j >= 2) then solve5 solved (j-1) else xs
    where solved = solve4 xs 1 j
final_solve xs = result
    where
        len = length xs
        xs1 = solve_system xs
        xs2 = solve5 xs1 len
        result = getcol xs2 (len+1)

