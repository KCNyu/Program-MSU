import Control.Exception
import Data.List
import Data.Char

code :: Int -> String ->String
code p mess = map (\c -> chr $ ord c + p) mess

decode :: Int->String->String
--decode p mess = code (negate p) mess
decode p mess = code (-p) mess

{--
main :: IO ()
main = do
putStrLn "Input your text, please:"
lineFromUser <- getLine
putStrLn $ "Not bad: " ++ lineFromUser

obtainTwoTextsFromUser :: IO String
obtainTwoTextsFromUser = do
    putStrLn "Enter your text, please: "
    firstText <- getLine
    putStrLn "One more, please: "
    secondText <- getLine
    return $ "'" ++ firstText ++ "' and '" ++ secondText ++ "'" -- простая строка??
--}
main :: IO ()
main = do

    result <- try $ readFile path :: IO (Either IOException String)
    case result of

      Left exception -> putStrLn $ "Fault: " ++ show exception

      Right cotent -> putStrLn cotent
      where path = "test17.hs"
--main :: IO ()
--main = do
--
--result <- try $ evaluate $ 2 `div` 0 :: IO (Either SomeException Integer)
--case result of
--
--    Left exception -> putStrLn $ "Fault: " ++ show exception
--
--    Right value -> print value
