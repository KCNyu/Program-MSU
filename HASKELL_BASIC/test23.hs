sub :: Eq t => [t] -> Int -> [t] -> Int -> [t]
sub [] i ys j = []
sub xs i [] j = []
sub xs i ys j
    | elem_i == elem_j = elem_i:(sub xs' (i-1) ys' (j-1))
    | otherwise = if(len_sub_xs >= len_sub_ys) then sub_xs else sub_ys
    where
        xs' = take (len_xs-1) xs
        ys' = take (len_ys-1) ys
        elem_i = xs !! (i-1)
        elem_j = ys !! (j-1)
        sub_xs = sub xs' (i-1) ys j
        sub_ys = sub xs i ys' (j-1)
        len_xs = length xs
        len_ys = length ys
        len_sub_xs = length sub_xs
        len_sub_ys = length sub_ys

sub_final :: Eq t => [t] -> [t]
sub_final xs = sub xs len rev len
    where
        rev = reverse xs
        len = length xs
