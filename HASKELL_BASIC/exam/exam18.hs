import Data.Tuple

{--
1. Text is given. Determine how many words it contains.
--}
textCount :: String -> Int
textCount text = length $ words text

{--
2. 给定的单词。 交换第 m 个和第 n 个字母。
--}

wordSwap :: Int -> Int -> String -> String
wordSwap m n text = unwords $ swap m n $ words text