{--
1. Given a matrix containing n rows and n columns. 
Matrix elements are integers. 
Sort the matrix in ascending diagonal order by permuting rows and columns.
--}
sortMatrixbyDiagonal :: [[Int]] -> [[Int]]
sortMatrixbyDiagonal [] = []
sortMatrixbyDiagonal (x:xs) = sortMatrixbyDiagonal' xs x

sortMatrixbyDiagonal' :: [[Int]] -> [Int] -> [[Int]]
sortMatrixbyDiagonal' [] y = [y]
sortMatrixbyDiagonal' (x:xs) y = sortMatrixbyDiagonal' xs (y ++ x)

{--
2. 给定一个由自然数组成的 N×M 矩阵。 
选择行中最小的最左侧元素并将它们放在第一列中。
--}
sortMatrixbyRow :: [[Int]] -> [[Int]]
sortMatrixbyRow [] = []
sortMatrixbyRow (x:xs) = sortMatrixbyRow' xs x

sortMatrixbyRow' :: [[Int]] -> [Int] -> [[Int]]
sortMatrixbyRow' [] y = [y]
sortMatrixbyRow' (x:xs) y = sortMatrixbyRow' xs (y ++ [minimum x])