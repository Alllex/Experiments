
import Data.List
import Control.Parallel

chunk n xs | length(xs) > n = take n xs : chunk n (drop n xs)
           | otherwise = [xs]

-- check vertical
ch s n xs = all id [s == sm fst && s == sm snd | ys <- chunk n xs, let sm f = sum $ map f ys]

-- check horizontal
cv s n xs = all id [s == sp ys | ys <- transpose $ chunk n xs] where sp = foldl (\acc (a, b) -> acc + a + b) 0

diag _ [] = []
diag n ((x, _):(_, y):xs) = x:y:diag n (drop n xs)

diag' n xs = diag n $ concat $ map reverse $ chunk n xs

-- check diagonal
cd s n xs = eq (diag n xs) && eq (diag' n xs) where eq = (s==) . sum 


isMagisSquare s n xs = all id $ map (\f -> f s n xs) [ch, cv, cd]

--flips :: [(a, a)] -> [[(a, a)]]
flips [] = [[]]
flips ((a, b):xs) = let acc = flips xs in map ((a, b):) acc ++ map ((b, a):) acc

subs n xs = concat $ map flips $ concat [ permutations ys | ys <- subsequences xs, length ys == n]


dominos = reverse [(a, b) | a <- [0..6], b <- [0..6], a <= b]

eights = subs 8 dominos

ones = replicate 16 (1,1)
pairs = concat $ replicate 4 [(2,1), (1, 2)] 
line = map (\x -> (x, x)) [1..8]


checker = isMagisSquare 6 4
check cond = filter checker cond

solutions [] = []
solutions xs = fpart `par` (fpart ++ solutions rest) where
    (part, rest) = splitAt 100 xs
    fpart = check part


main = do
    print "hi"
    print $ take 1 $ solutions eights