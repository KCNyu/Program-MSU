import Data.List
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