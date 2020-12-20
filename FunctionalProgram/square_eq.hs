solve :: (Eq a, Floating a) => (a, a, a) -> (a, a)
solve (a, b, c) = if(a == 0) then throw NoneResult else (x1, x2)
                where 
                  d   = b * b - 4 * a * c
                  sqD = sqrt d
                  a2  = 2 * a
                  x1  = (-b + sqD) / a2
                  x2  = (-b - sqD) / a2

solveInR e = solve (e :: (Float, Float, Float))
solveInC e = solve (e :: ((Complex Float), (Complex Float), (Complex Float)))

main :: IO()
main = do
    putStr "Input a: "
    s_a <- getLine
    putStr "Input b: "
    s_b <- getLine
    putStr "Input c: "
    s_c <- getLine
    let a = (fromRational (toRational (read s_a :: Double)))
        b = (fromRational (toRational (read s_b :: Double)))
        c = (fromRational (toRational (read s_c :: Double)))
    print a
    print b
    print c
    result <- try $ evaluate $ solveInC (a, b, c) :: IO (Either IOException (Complex Float, Complex Float))
    case result of
        Left exception -> putStrLn $ "Fault: " ++ show exception
        Right content -> print content

