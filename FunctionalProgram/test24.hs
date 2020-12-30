dup [] = []
dup (x:xs) = if(x `mod` 2 == 1) then (2*x):dup xs else x:dup xs
