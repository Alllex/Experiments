bmiTell weight height
    | bmi <= skinny = "Under"
    | bmi <= normal = "OK"
    | bmi <= fat = "Fat"
    | otherwise = "Whale"
    where bmi = weight / height ^ 2 
          (skinny, normal, fat) = (18.5, 25.0, 30.0)

initials :: String -> String -> String
initials fstname lstname =
	[f] ++ ". " ++ [s] ++ "."
	where (f:_) = fstname
	      (s:_) = lstname

test = (let a = 100; b = 200; c = 300 in a * b * c,
	     let foo = "Hey "; bar = "there!" in foo ++ bar)

test1 :: Integer
test1 = (let (a, b, c) = (1, 2, 3) in a + b + c) * 100	

qsort' :: (Ord a) => [a] -> [a]
qsort' [] = []
qsort' (h:t) = qsort' [a|a<-t,a<=h]++[h]++qsort' [a|a<-t,a>h]

factorial n = product [1..n]

chain 1 = [1]
chain n
	| even n = n : chain (n `div` 2)
	| odd n  = n : chain (n * 3 + 1)

flip' :: (a -> b -> c) -> b -> a -> c
flip' f = \x y -> f y x

sum' :: (Num a) => [a] -> a
sum' lst = foldl (\acc x -> acc + x) 0 lst

sum2 = foldl (+) 0

map' :: (a -> b) -> [a] -> [b]
map' f = foldr (\x acc -> f x : acc) []

elem' y ys = foldl (\acc x -> if x == y then True else acc) False ys

sqrtSums = length (takeWhile (<1000) (scanl1 (+) (map sqrt [1..]))) + 1
