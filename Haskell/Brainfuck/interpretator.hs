
data TapeBF = T [Int] Int [Int] deriving Show
data ExprBF = Operation Char
            | Loop [ExprBF] deriving Show

class Tape t where
    com :: t -> Int -> t
    dot :: t -> Int
    left, right, plus, minus :: t -> t
    zero :: t -> Bool

instance Tape TapeBF where
    com (T l _ r) x' = T l x' r
    dot (T _ p _) = p
    left (T (lh:l) p r) = T l lh (p:r)
    left (T [] p r) = T [] 0 (p:r)
    right (T l p (rh:r)) = T (p:l) rh r
    right (T l p []) = T (p:l) 0 []
    plus (T l p r) = T l (p + 1) r
    minus (T l p r) = T l (p - 1) r
    zero (T _ x _) = x == 0
    
empt = T [] 0 []

newtype Parser a = P (String -> [(a, String)])
empty = P (\_ -> [])
sym c = P p where p (x:xs) | x == c = [(c, xs)]
                  p _               = []
val a = P (\s -> [(a, s)])
infixl 2 |||
(P p) ||| (P q) = P $ \s -> p s ++ q s
infixl 3 ||>
(P p) ||> q = P $ \s -> concat [apply (q a) s | (a, s) <- p s] where apply (P p) = p
many a = a ||> (\ x -> many a ||> val . (x:)) ||| val []
opt a = a ||> val . Just ||| val Nothing
eof = map fst . filter ((""==) . snd)
oneOf = foldl (\ a b -> a ||| sym b) empty

instance Monad Parser where
  return = val
  (>>=) = (||>)

pp = parse pgm
  where chainChar :: Parser ExprBF
        chainChar = do  c <- oneOf ['.',',','+','-','<','>']
                        return $ Operation c

        chain :: Parser [ExprBF]
        chain = do c <- chainChar
                   s <- many chainChar
                   return (c:s)

        loop :: Parser ExprBF
        loop = do sym '['
                  l <- expr
                  sym ']'
                  return $ Loop l

        expr :: Parser [ExprBF]
        expr = do c <- chain
                  lcs <- many lc
                  ml <- opt loop
                  return $ (foldl (++) c lcs) ++ (case ml of Nothing -> []; Just l -> [l])
               where lc = do l <- loop
                             c <- chain
                             return (l:c)

        pgm :: Parser [ExprBF]
        pgm = expr

        parse :: Parser a -> String -> a
        parse (P p) s = case eof $ p s of
                            [] -> error "Cannot parse program"
                            vs -> head vs

eval [] _ = return ()
eval (curr:rest) tape = 
    case curr of
        ([], [], []) -> (eval $! rest) $! tape

        ([], [], next_op:linear_rest) -> -- just process linear block
            case next_op of
                Operation c -> eval_op' c ([], [], linear_rest) -- just perform some operation
                Loop l      -> eval_rest (l, l, linear_rest) -- now new loop wait for processing

        ([], loop@(loop_first:_), linear) -> -- check for need of looping
            do  t <- tape
                if zero t then eval_rest ([], [], linear) -- loop is end, now continue process linear block
                else eval_rest (loop, loop, linear) -- looping

        (loop_next:loop_rest, loop, linear) -> -- process loop
            case loop_next of
                Operation c -> eval_op' c (loop_rest, loop, linear) -- just perform operation from loop block
                Loop l      -> (eval  $! ((l, l, loop_rest):([], loop, linear):rest)) $! tape -- inner loop


    where eval_rest add = (eval $! (add:rest)) $! tape
          eval_op' c add = eval_op c tape (add:rest)
          eval_op c tape rest =
            case c of 
                '+' -> ret $! fmap plus tape
                '-' -> ret $! fmap minus tape
                '<' -> ret $! fmap left tape
                '>' -> ret $! fmap right tape
                '.' -> do t <- tape
                          putStrLn $ "Out: " ++ (show $! dot t)
                          ret $! tape
                ',' -> do t <- tape
                          putStr "In:  "
                          x <- getLine
                          ret $! return $! com t $! read x
            where ret x = (eval $! rest) $! x

run :: String -> IO ()
run s = eval [([], [], pp s)] (return empt) 

main = do s <- getLine
          run s
