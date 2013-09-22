-- With self-referencing data
fib1 n = fibs !! n
        where fibs = 0 : scanl (+) 1 fibs
        -- 0,1,1,2,3,5,...
 
-- Same, coded directly
fib2 n = fibs !! n
        where fibs = 0 : 1 : next fibs
              next (a : t@(b:_)) = (a+b) : next t
 
-- Similar idea, using zipWith
fib3 n = fibs !! n
        where fibs = 0 : 1 : zipWith (+) fibs (tail fibs)
 
-- Using a generator function
fib4 n = fibs (0,1) !! n
        where fibs (a,b) = a : fibs (b,a+b)

fib5 n = fib' n (0, 1) where 
    fib' n (f1, f2) 
        | n > 0 = fib' (n - 1) (f2, f1 + f2)
        | n == 0 = f1