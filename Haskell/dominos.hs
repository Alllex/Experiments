{-
dominos = reverse [(x, y) | x <- [0..6], y <- [0..6], x <= y]

sumValue = fromIntegral 6
cols = fromIntegral 4
rows = fromIntegral 2

lastn n [] = []
lastn n x@(_:xs) = if n == 0 then x else lastn (n - 1) xs
groupn _ [] = []
groupn n x = (take (fromIntegral n) x) : (groupn n $ lastn n x)

sum' = foldl (\(x,y) (a,b) -> (x+a,y+b)) (0,0)

overflow n r = (l < n && (s1 > sumValue || s2 > sumValue)) || (l == n && (s1 < sumValue || s2 < sumValue))
    where s = sum' r
          l = length r
          s1 = fst s
          s2 = snd s

accept n r = length r == n && (s == (sumValue,sumValue)) where s = sum' r

rotate ([]:_) = []
rotate a = (foldl (\x c -> if c == [] then x else head c : x) [] a) 
    : (rotate $ map (\x -> if x == [] then x else tail x) a)

d1 a = sum [fst $ a !! 0, snd $ a !! 1, fst $ a !! 8, snd $ a !! 9, fst $ a !! 14, snd $ a !! 17]
d2 a = sum [fst $ a !! 5, snd $ a !! 4, fst $ a !! 9, snd $ a !! 8, fst $ a !! 13, snd $ a !! 12]

precheck a = (foldr1 (&&) $ map (not.overflow (fromIntegral cols)) ga) -- && (foldr1 (&&) $ map (not.overflow (fromIntegral rows)) $ rotate ga)
    where ga = groupn cols a
check a = (fromIntegral $ length a) == cols * rows && (foldr1 (&&) $ map (accept (fromIntegral cols)) $ groupn cols a) -- && d1 a == sumValue && d2 a == sumValue

next _ _ _ [] = Nothing
next acc left c@(d1,d2) right@(r:rs) =
    if precheck new && result /= Nothing then result 
    else if precheck newRev && resultRev /= Nothing then resultRev
         else next acc (left ++ [c]) r rs
            where new = acc ++ [c]
                  newRev = acc ++ [(d2,d1)]
                  result = bruteforce new (left ++ right)
                  resultRev = bruteforce newRev (left ++ right)
        
bruteforce acc rest = 
    if (fromIntegral $ length acc) > cols * rows then Nothing 
    else if check acc then Just acc 
         else next acc [] (head rest) (tail rest)

solve = bruteforce [] dominos

----------------------------------------------------------------------------------------------
-}

solve = bruteforce [] dominos
dominos = reverse [(x, y) | x <- [0..6], y <- [0..6], x <= y]

sum' = foldl (\(x,y) (a,b) -> (x+a,y+b)) (0,0)
precheck a = length a <= 6 && s1 <= 13 && s2 <= 13
    if l <= 6 then s1 <= 13 && s2 <= 13
    where s = sum' a
          l = length a
          s1 = fst s
          s2 = snd s

check a = length a == 18 && (sum' a) == (3*13,3*13)

next _ _ _ [] = Nothing
next acc left c@(d1,d2) right@(r:rs) =
    if precheck new && result /= Nothing then result 
    else if precheck newRev && resultRev /= Nothing then resultRev
         else next acc (c:left) r rs
            where new = c:acc
                  newRev = (d2,d1):acc
                  result = bruteforce new (left ++ right)
                  resultRev = bruteforce newRev (left ++ right)
        
bruteforce acc rest = 
    if length acc > 6 then Nothing 
    else if check acc then Just acc
         else next acc [] (head rest) (tail rest)