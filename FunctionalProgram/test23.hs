getelem xs n = xs !! (n-1)

sub [] i ys j = []
sub xs i [] j = []
sub xs i ys j
    | elem_i == elem_j = (sub xs' (i-1) ys' (j-1)) ++ [elem_i]
    | otherwise = if(len_sub_xs > len_sub_ys) then sub_xs else sub_ys
    where
        sub_xs = sub xs' (i-1) ys j
        sub_ys = sub xs i ys' (j-1)
        xs' = take (len_xs-1) xs
        ys' = take (len_ys-1) ys
        len_xs = length xs
        len_ys = length ys
        elem_i = getelem xs i
        elem_j = getelem ys j
        len_sub_xs = length sub_xs
        len_sub_ys = length sub_ys

sub_final xs = sub xs len rev len
    where
        rev = reverse xs
        len = length xs

