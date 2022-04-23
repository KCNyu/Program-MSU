{--
1. Determine if there is at least one triple of neighboring numbers in the list, 
    in which the middle element is greater than its "neighbors", 
    i.e. the previous and the next. In case of a positive answer, 
    determine the numbers of the elements of the first of these triples.
--}
deternmineTriple :: [Int] -> Maybe (Int, Int)
deternmineTriple [] = Nothing
deternmineTriple (x:xs) = if (x > (head xs) && x > (last xs)) then Just (x, head xs) else deternmineTriple xs

{--
2. Determine if the list is sorted in ascending order. 
    If the answer is negative, determine the number of the first element that violates this order.
--}
isSorted [] _ = 1
isSorted (x:xs) index = if (x > (head xs)) then index else isSorted xs (index + 1)  