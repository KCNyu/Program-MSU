-- Формирует строку транспонированной матрицы
frstrow :: [[Float]] -> [Float]
frstrow []     = []
frstrow (x:xs) = head x : frstrow xs

--Вспомогательная для вычеркивания столбца (удаляет выбранный элемент из строки)
minstolbvs :: [Float] -> Int -> [Float]
minstolbvs (x:xs) y = if y==1 then xs else x : minstolbvs xs (y-1)

-- Вычеркивание выбранного столбца
minstolb :: [[Float]] -> Int -> [[Float]]
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

mult x y i j = mult_vector row col
    where
        row = getrow x i
        col = getcol y j

mult_matrix x y = [[mult x y i j|j<-[1..len_y]]|i<-[1..len_x]]
    where
        len_x = length(x)
        len_y = length(head y)
