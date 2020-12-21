substring [x] = [x]
substring [x,y] = if(y /= (x+1)) then [x] else [x,y]
substring (x:y:xs) = if(y /= (x+1)) then [x] else x:(substring (y:xs))

substr s [] = s
substr s (x:xs) = if(len_s > len_str) then (substr s xs) else (substr str xs)
    where
        len_s = length s
        len_str = length str
        str = substring (x:xs)

substr_final s = substr [] s
