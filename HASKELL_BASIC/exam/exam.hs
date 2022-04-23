import Data.List
import Main (sortMatrixbyDiagonal)
{--
1. Given a word.Determine how many different letters it contains.
--}
wordLetterCount :: String -> Int
wordLetterCount word = length $ nub word

{--
2. Given a natural number n and integers a1,a2,…,an.Find the number of numbers ai(i=1,2,...,n) that are perfect squares. (Define a function that allows you to recognize full squares.)
--}
perfectSquares :: Int -> [Int] -> Int
perfectSquares n xs = length $ filter (\x -> isSquare x) xs
    where isSquare x = (round $ sqrt $ fromIntegral x) ^ 2 == x

{--
1. Text is given. Determine how many words it contains.
--}
wordCount :: String -> Int
wordCount text = length $ words text

{--
2. The word is given. Swap its m-th and n-th letters.
--}
swapLetters :: String -> Int -> Int -> String
swapLetters word m n = take m word ++ [word !! n] ++ drop (n+1) word ++ [word !! m] ++ drop (m+1) word

{--
1. Determine if there is at least one triple of neighboring numbers in the list, in which the middle element is greater than its "neighbors", i.e. the previous and the next. In case of a positive answer, determine the numbers of the elements of the first of these triples.
--}

indexTripleNeighbors :: Ord a => [a] -> Int
indexTripleNeighbors xs = length $ filter (\x -> (xs !! (x-1)) < (xs !! x) && (xs !! (x+1)) < (xs !! x)) [1..(length xs - 1)]

{--
2. Determine if the list is sorted in ascending order. If the answer is negative, determine the number of the first element that violates this order.
--}
--indexUnSorted :: Ord a => [a] -> Int
indexUnSorted xs = indexUnSorted' xs 0
    where indexUnSorted' [] _ = -1
          indexUnSorted' (x:xs) i = if x > head xs then i else indexUnSorted' xs (i+1)


-- 1. Given a matrix containing n rows and n columns. Matrix elements are integers. Sort the matrix in ascending diagonal order by permuting rows and columns.

swapsMatrixElement :: [[Int]] -> Int -> Int -> [[Int]]
swapsMatrixElement matrix n m = swaps 