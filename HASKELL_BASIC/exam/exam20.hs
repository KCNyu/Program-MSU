{--
1. 按升序对给定的数字列表进行排序，不包括负数。
--}
sortList :: [Int] -> [Int]
sortList [] = []
sortList (x:xs) = sortList [y | y <- xs, y <= x, y >= 0] ++ [x] ++ sortList [y | y <- xs, y > x, y >= 0]

{--
2. Given a matrix of size NxM ( N>2, M<10). 
The elements of the matrix are the numbers 0 and 1. 
The allowed operation is the permutation of the columns. 
Transform the matrix so that the first row has columns with one in the first row, 
then the columns with one in the second row (if any), and so on.
--}
transformMatrix 

