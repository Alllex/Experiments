{-
data Person' = Person' { firstName   :: String
			  		   , lastName    :: String
			  		   , age         :: Int
			  		   , height	    :: Float
			  		   , phoneNumber :: String
			  		   , flavor      :: String 
			  		   } deriving (Show)
-}

data Person = Person { firstName :: String
					 , lastName :: String
					 , age :: Int
					 } deriving (Eq)			  		 

p1 = Person "a" "a" 1
p2 = Person "b" "b" 2
p3 = Person "a" "a" 1