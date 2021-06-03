divid :: [a]->[[a]]
divid xs = [[xs!!k|k<-[0..length(xs)`div`2-1]],[xs!!k|k<-[length(xs)`div`2..length(xs)-1]]]

--divid_reverse :: [a]->[a]
--divid_reverse xs = [xs!!k|k<-[length(xs)`div`2-1,length(xs)`div`2-2..0]]++[xs!!k|k<-[length(xs)-1,length(xs)-2..length(xs)`div`2]]
--divid xs = [reverse (take (length(xs)`div`2) xs),reverse (drop (length(xs)`div`2) xs)]
mygates :: [a] -> [a]
mygates [] = []
mygates x = let n = mylistlength x
                reversedx = myreverse x
                a = myreverse (mytakefirstnchildren (if (n `mod` 2 == 1)
                then  (n `div` 2 + 1) else (n `div` 2)) x)
                b = mytakefirstnchildren (n `div` 2) reversedx
                in a ++ b
                where myreverse []     = []
                      myreverse [x]    = [x]
                      myreverse (x:xs) = myreverse xs ++ [x]
                      mytakefirstnchildren 0 x = []
                      mytakefirstnchildren 1 (x:xs) = [x]
                      mytakefirstnchildren n (x:xs) = x:(mytakefirstnchildren (n-1) xs)
                      mylistlength []     = 0
                      mylistlength [x]    = 1
                      mylistlength (x:xs) = mylistlength(xs) + 1
myhometask :: [a] -> [a]
myhometask [] = []
myhometask [x] = [x]
myhometask (x:xs) = let len = mylen (x:xs)
                        half = (len + 1) `div` 2
                        (l,r) = mysplit half (x:xs)
                    in myreverse(l)++myreverse(r)
                    where mylen []     = 0
                          mylen [x]    = 1
                          mylen (x:xs) = 1 + mylen xs
                          mysplit 1 (x:xs) = ([x],xs)
                          mysplit n (x:xs) = let (l,r) = mysplit (n - 1) xs
                                             in (x:l,r)
                          myreverse [x]    = [x]
                          myreverse (x:xs) = myreverse(xs)++[x]
middleSplitThenFlip :: [a] -> [a]
middleSplitThenFlip [] = []
middleSplitThenFlip zs = list
    where
        list = (rev beg) ++ mid ++ (rev end)

        (beg, mid, end) = go zs zs
        go (x:xs) (_:_:ys) =
            let
                (beg, mid, end) = go xs ys
            in
                (x:beg, mid, end)
        go (x:xs) [_] = ([], [x], xs)
        go (x:xs) []  = ([], [], x:xs)

        rev []     = []
        rev [x]    = [x]
        rev (x:xs) = rev xs ++ [x]
