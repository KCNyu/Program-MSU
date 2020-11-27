divid :: [a]->[[a]]
divid xs = [[xs!!k|k<-[0..length(xs)`div`2-1]],[xs!!k|k<-[length(xs)`div`2..length(xs)-1]]]

divid_reverse :: [a]->[[a]]
divid_reverse xs = [[xs!!k|k<-[length(xs)`div`2-1,length(xs)`div`2-2..0]],[xs!!k|k<-[length(xs)-1,length(xs)-2..length(xs)`div`2]]]
--divid xs = [reverse (take (length(xs)`div`2) xs),reverse (drop (length(xs)`div`2) xs)]
