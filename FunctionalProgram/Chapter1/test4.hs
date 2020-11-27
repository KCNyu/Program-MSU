{--
myhead :: [a] -> a
myhead [] = error "empty list"
myhead [x,y] = y
myhead (x:y:cxd) = myhead [x,y]
mylast :: [a] -> a
mylast [] = error "empty list"
mylast [x] = x
mylast (x:xs) = mylast xs
mylast :: [a] -> a
mylast [] = error "empty list"
mylast [x,y] = x
mylast (x:xs) = mylast xs
--}
{--
del_last :: [a] -> [a]
del_last [] = error "empty"
del_last [x] = []
del_last (x:xs) = [x] ++ del_last xs

change :: [a] -> [a]
change [] = error "empty list"
change [x] = [x]
change xs = mylast(xs):del xs
--}
{
mylast :: [a] -> a
mylast [] = error "empty list"
mylast [x] = x
mylast (x:xs) = mylast xs

del_last :: [a] -> [a]
del_last [] = error "empty"
del_last [x] = []
del_last (x:xs) = [x] ++ del_last xs
--init xs
change :: [a] -> [a]
change [] = error "empty list"
change [x] = [x]
change [x,y] = [y,x]
change (x:xs) = [mylast xs] ++ del_last xs ++ [x]
--change (x:xs) =  xs++[x]

del :: (a->Bool)->[a]->[a]
del x [] = []
del p (x:xs)
    | p x = x : del p xs
    | otherwise = del p xs
--}
--del :: a->[a]->[a]
del :: (Eq)a=>a->[a]->[a]
del cxd [] = []
del cxd (x:xs)
    | cxd == x = del cxd xs
    | otherwise = x : del cxd xs
