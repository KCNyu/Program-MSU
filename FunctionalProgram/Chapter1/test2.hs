{--
test1 :: Float->Float
test1 x = x + x
test2 :: Float->Float->Float
test2 x y = test1 x + test1 y
--}

{--
max1 :: (Ord) a => a -> a -> a -> a
max1 x y z
    | x >= y && x >= z = x
    | y >= x && y >= z = y
--    | z >= x && z >= y = z
    | otherwise = x
--}

max1 :: (Ord) a => a -> a -> a -> a
max1 x y z
    | x == max2 x y && x == max2 x z = x
    | y == max2 x y && y == max2 y z = y
    | z == max2 x z && z == max2 y z = z

max2 :: (Ord) a => a -> a -> a
max2 x y
    | x <= y = y
    | otherwise = x
