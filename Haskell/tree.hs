

data Tree a = EmptyTree | Node a (Tree a) (Tree a) deriving (Show)

singleton x = Node x EmptyTree EmptyTree

treeInsert x EmptyTree = singleton x
treeInsert x (Node a left right)
	| x == a = Node x left right
	| x < a  = Node a (treeInsert x left) right
	| x > a  = Node a left (treeInsert x right)

treeElem x EmptyTree = False
treeElem x (Node a left right) 
	| x == a = True
	| x < a  = treeElem x left
	| x > a  = treeElem x right

nums = [8,6,4,1,7,3,5]
numsTree = foldr treeInsert EmptyTree nums

tree1 = Node 5 
			(Node 3 
				(Node 1 EmptyTree EmptyTree) 
				(Node 4 EmptyTree EmptyTree)
			) 
			(Node 7 
				(Node 6 EmptyTree EmptyTree) 
				(Node 8 EmptyTree EmptyTree)
			)