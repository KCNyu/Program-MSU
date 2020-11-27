del :: (Eq)a=>a->[a]->[a]
del cxd [] = []
del cxd (x:xs)
    | cxd == x = del cxd xs
    | otherwise = x : del cxd xs
del_dup :: (Eq)t=>[t]->[t]
del_dup [] = []
del_dup (x:xs) = x:del_dup (del x xs)

del_dup_t :: (Eq)t=>[t]->[t]
del_dup_t [] = []
del_dup_t (x:xs)
    | del x xs == xs = x:del_dup_t xs
    | otherwise  = del_dup_t (del x xs)
