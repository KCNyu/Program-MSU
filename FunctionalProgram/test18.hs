dup :: (t1 -> t -> t1) -> t1 -> [t] -> [t1]
dup f t [] = []
dup f t (x:xs) = res:dup f res xs
    where res = f t x

newfold :: Eq t1 => (t1 -> t1 -> t1) -> [t1] -> [t1]
newfold f (x:xs) = x : (dup f x xs)
