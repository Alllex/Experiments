
dominos = [(x, y) | x <- [0..6], y <- [0..6], x <= y]
{-
del i x = (take i x) ++ (take (length x - i - 1) . reverse $ x)

sumFst = foldr (\(a,b) acc -> acc + a) 0 
sumSnd = foldr (\(a,b) acc -> acc + b) 0

sum' (a,b) = a+b
checkRow row = length row == 6 && sumFst row == 13 && sumSnd row == 13
checkCols ([]:[]:[]) = True
checkCols ((a:as):(b:bs):(c:cs):[]) = sum' a + sum' b + sum' c == 13 && (checkCols [as, bs, cs])
checkCols _ = False

d1 (a:b:c:[]) = sum [fst $ a !! 0, snd $ a !! 1, fst $ b !! 2, snd $ b !! 3, fst $ c !! 4, snd $ c !! 5]
d2 (a:b:c:[]) = sum [fst $ a !! 5, snd $ a !! 4, fst $ b !! 3, snd $ b !! 2, fst $ c !! 1, snd $ c !! 0]
checkDiagonals t@(a:b:c:[]) = if length a == 6 && length b == 6 && length c == 6 then (d1 t == 13 && d2 t == 13) else False
check (t@(a:b:c:[])) = (checkRow a && checkRow b && checkRow c && checkCols t && checkDiagonals t)


add t@(a:b:c:[]) d = 
    if length a < 6 then (a ++ [d]):b:c:[] else 
        if length b < 6 then a:(b ++ [d]):c:[] else
            if length c < 6 then a:b:(c ++ [d]):[] else t

--rock = solve dominos [[],[],[]]
-}

lastn n [] = []
lastn n x@(_:xs) = if n == 0 then x else lastn (n - 1) xs
groupn _ [] = []
groupn n x = (take n x) : (groupn n $ lastn n x)

overflow n r = length r < n && ((fst s) > 13 || (snd s) > 13) where s = (foldl (\(x,y) (a,b) -> (x+a,y+b)) (0,0) r)
accept n r = length r == n && (s == (13,13)) where s = (foldl (\(x,y) (a,b) -> (x+a,y+b)) (0,0) r)
rotate :: [[(a, a)]] -> [[(a, a)]]
rotate a = (foldl (\x c -> head c : x) [] a) : (rotate $ map tail a)

d1 a = sum [fst $ a !! 0, snd $ a !! 1, fst $ a !! 8, snd $ a !! 9, fst $ a !! 16, snd $ a !! 17]
d2 a = sum [fst $ a !! 5, snd $ a !! 4, fst $ a !! 9, snd $ a !! 8, fst $ a !! 13, snd $ a !! 12]

--colsSumsCheck a = 


