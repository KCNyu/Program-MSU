import Data.List
-- 1. Given a natural number n and a sequence of integers d1 , d2 , …, dn . Consider segments of this sequence (subsequences of consecutive numbers) consisting of even numbers. Get the largest of the lengths of the considered segments.

findLongestSequenceOfEvenNumbers :: Int -> [Int] -> Int
findLongestSequenceOfEvenNumbers n ds = maximum $ map length $ filter even $ subsequences ds