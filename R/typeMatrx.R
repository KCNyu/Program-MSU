ma <-matrix(letters[1:12], nrow =4, 
            dimnames =list(c('row1', 'row2', 'row3','row4'),
                           c('c1', 'c2', 'c3')))
ma

mrb <-rbind(c(3, 5, 7), c(4, 6, 8))
mrb

mrb <-cbind(c(3, 5, 7), c(4, 6, 8))
mrb
