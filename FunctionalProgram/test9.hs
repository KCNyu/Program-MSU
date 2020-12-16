isPrefix::Eq a => [a] -> [a] -> Bool
isPrefix [] _ = True
isPrefix _ [] = False
isPrefix (x:xs) (y:ys) = x == y && isPrefix xs ys

del :: Eq a => [a] -> [a] -> [a]
del [] ys = ys
del _ [] = []
del xs (y:ys)
--    | isPrefix xs (y:ys) = mydrop (length xs) (y:ys)
    | isPrefix xs (y:ys) = del xs (mydrop (length xs) (y:ys))
    | otherwise = y:del xs ys

mydrop :: Int->[a]->[a]
mydrop n xs | n<=0 = xs
mydrop _ [] = []
mydrop n (_:xs) = mydrop (n-1) xs

isSame [] [] = True
isSame xs [] = False
isSame [] ys = False
isSame (x:xs) (y:ys) = x == y && (isSame xs ys)

del' [] ys = ys
del' _ [] = []
del' xs (y:ys) = if(isSame (y:ys) res) then y:ys else del' xs res
    where res = del xs (y:ys)




