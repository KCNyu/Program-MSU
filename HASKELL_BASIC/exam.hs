import Test.HUnit (assertEqual)
import Test.HUnit.Base
import Test.HUnit.Text
{- 
1.An integer array A of N elements is given. 
check if it has elements equal to zero. if there is, 
find the number of the first of them, i.e., the smallest i for which the element ai = 0.
-}
findZeroIndex :: [Int] -> Int
findZeroIndex [] = 0
findZeroIndex (x:xs)
    | x == 0 = 1
    | otherwise = findZeroIndex xs + 1

{-
2. An array of N natural numbers is given. 
find the arithmetic mean and geometric mean of odd numbers.
-}
findArtihmeticAndGeometricMean :: [Int] -> (Double, Double)
findArtihmeticAndGeometricMean [] = (0, 0)
findArtihmeticAndGeometricMean (x:xs)
    | odd x = (arithmeticMean, geometricMean)
    | otherwise = findArtihmeticAndGeometricMean xs
    where arithmeticMean = fromIntegral (sum (x:xs)) / fromIntegral (length (x:xs))
          geometricMean = fromIntegral (product (x:xs)) ** (1 / fromIntegral (length (x:xs)))


{-
5. Replace by one the minimum absolute value element of the given array X = (x1, x2, ..., xn). 
if there is more than one minimum component, replace them all.
-}
replaceMinAbsoluteValueWithOne :: [Int] -> [Int]
replaceMinAbsoluteValueWithOne [] = []
replaceMinAbsoluteValueWithOne xs = replaceMinAbsoluteValueWithOne' xs (minimum xs)

replaceMinAbsoluteValueWithOne' :: [Int] -> Int -> [Int]
replaceMinAbsoluteValueWithOne' [] _ = []
replaceMinAbsoluteValueWithOne' (x:xs) min
    | x == min = 1 : replaceMinAbsoluteValueWithOne' xs min
    | otherwise = x : replaceMinAbsoluteValueWithOne' xs min


{-
30. Given a sequence of 100 integers. 
determine the number of numbers in the longest subsequence of consecutive zeros.
-}
findLongestSequenceOfConsecutiveZeros :: [Int] -> Int
findLongestSequenceOfConsecutiveZeros [] = 0
findLongestSequenceOfConsecutiveZeros xs = findLongestSequenceOfConsecutiveZeros' xs 0 0

findLongestSequenceOfConsecutiveZeros' :: [Int] -> Int -> Int -> Int
findLongestSequenceOfConsecutiveZeros' [] count maxCount = maxCount
findLongestSequenceOfConsecutiveZeros' (x:xs) count maxCount
    | x == 0 = findLongestSequenceOfConsecutiveZeros' xs (count + 1) maxCount
    | otherwise = findLongestSequenceOfConsecutiveZeros' xs 0 (max maxCount count)

{-
17. Given integers a, x1, x2, ..., xn. 
determine what is the number of the term equal to a in the sequence x1, x2, ..., xn. 
if there is no such member, then the number 0 should be the answer.
-}
findNumberOfTermEqualToA :: [Int] -> Int -> Int
findNumberOfTermEqualToA [] _ = 0
findNumberOfTermEqualToA (x:xs) a
    | x == a = 1 + findNumberOfTermEqualToA xs a
    | otherwise = findNumberOfTermEqualToA xs a

-- Test cases
test1 = TestCase (assertEqual "findZeroIndex" 4 (findZeroIndex [1, 2, 3, 0, 4, 5, 6, 0, 7, 8, 9, 0]))
test2 = TestCase (assertEqual "findArtihmeticAndGeometricMean" (5.5,4.528728688116765) (findArtihmeticAndGeometricMean [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]))
test3 = TestCase (assertEqual "replaceMinAbsoluteValueWithOne" [1,2,3,4,1,6,7,8,1,10] (replaceMinAbsoluteValueWithOne [0, 2, 3, 4, 0, 6, 7, 8, 0, 10]))
test4 = TestCase (assertEqual "findLongestSequenceOfConsecutiveZeros" 3 (findLongestSequenceOfConsecutiveZeros [1, 2, 3, 0, 0, 5, 6, 0, 0, 0, 9, 0]))
test5 = TestCase (assertEqual "findNumberOfTermEqualToA" 4 (findNumberOfTermEqualToA [1, 2, 3, 0, 5, 0, 0, 8, 0, 10] 0))
tests = TestList [TestLabel "test1" test1, TestLabel "test2" test2, TestLabel "test3" test3, TestLabel "test4" test4, TestLabel "test5" test5]

main = do
    runTestTT tests
