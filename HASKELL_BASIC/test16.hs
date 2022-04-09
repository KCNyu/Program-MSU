maxmin :: Ord a => [a] -> [a]
mainmin [] = []
maxmin [x] = [x,x]
maxmin [x, y] = if x>y then [x,y] else [y,x]
maxmin (x:y:z:xs) = maxmin(max_min++xs)
    where
        max_min = maxmin' x y z

maxmin' x y z
    | x >= y && y >= z = [x,z]
    | x >= z && z >= y = [x,y]
    | y >= x && x >= z = [y,z]
    | y >= z && z >= x = [y,x]
    | z >= x && x >= y = [z,y]
    | z >= y && y >= x = [z,x]