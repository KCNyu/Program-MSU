filter1 :: (a -> Bool) -> [a] -> [a]
filter1 _[]=[]
filter1 b (x:xs)
    | b x  = x : filter1 b xs
    | otherwise = filter1 b xs

mapmy :: (a -> b) -> [a] -> [b]
mapmy _[] = []
mapmy f (x:xs) = f x:mapmy f xs

--reverse_f x f1 f2 = f2(f1 x)
reverse_f x f1 f2 = f2$f1$x
