f :: t -> [t] -> [t]
f n [] = []
f n [x] = [x]
f n (x:xs) = x:n:f n xs

f' (x:xs) [y] = [y]
f' (x:xs) (y:ys) = y:[x]++xs ++(f' (x:xs) ys)

