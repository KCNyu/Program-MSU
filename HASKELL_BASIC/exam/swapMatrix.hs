import Data.List
-- 2. Given an N×M matrix consisting of natural numbers. Select the smallest leftmost elements in the rows and put them in the first column.

minListIndex xs = minListIndex' xs  (head xs) 0 0

minListIndex' [] min_elem min_index cur_index = min_index
minListIndex' xs min_elem min_index cur_index = minListIndex' (tail xs) (min min_elem (head xs)) (if (head xs) < min_elem then cur_index else min_index) (cur_index + 1)

swapElementsAt :: Int -> Int -> [a] -> [a]
swapElementsAt i j xs = let elemI = xs !! i
                            elemJ = xs !! j
                            left = take i xs
                            middle = take (j - i - 1) (drop (i + 1) xs)
                            right = drop (j + 1) xs
                    in  left ++ [elemJ] ++ middle ++ [elemI] ++ right

changeSmallestElements :: [[Int]] -> [[Int]]
changeSmallestElements [] = []
changeSmallestElements (x:xs) = let min_index = minListIndex x
                                    new_row = swapElementsAt 0 min_index x
                                in  new_row : changeSmallestElements xs