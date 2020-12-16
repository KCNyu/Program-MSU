import Control.Exception
import Data.List
import Data.Char

data MyException = NoneResult deriving(Show)
instance Exception MyException

solve a b c = if(derta' < 0 || a == 0) then throw NoneResult else [x1,x2]
    where
        derta = sqrt derta'
        derta' = b^2-4*a*c
        x1 = (-b+derta)/2
        x2 = (-b-derta)/2
main :: IO ()
main = do
    putStr "Input a: "
    s_a <- getLine
    putStr "Input b: "
    s_b <- getLine
    putStr "Input c: "
    s_c <- getLine
    let a = read s_a :: Double
        b = read s_b :: Double
        c = read s_c :: Double
    result <- try $ evaluate $ solve a b c :: IO (Either IOException [Double])
    case result of

      Left exception -> putStrLn $ "Fault: " ++ show exception

      Right content -> print content
