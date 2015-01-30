rep::Int->String->String
rep 0 s = ""
rep n s
    | m == 0 = let y = s ++ s in rep d y
    | otherwise = let y = rep (n-1) s in s ++ y
    where (d,m) = divMod n 2

allIn::Eq a => [a]->[a]->Bool
allIn [] _ = True
allIn (x:xs) ys
    | elem x ys == False = False
    | otherwise          = allIn xs ys 

csh::Int->String->String
csh n s = 
    let l = length s
        a = l - (n `mod` l)
	(q,r) = splitAt a s 
    in r ++ q

--A quicksort function
qsort :: Ord a => [a] -> [a]
qsort [] = []
qsort (x:xs) = (qsort ls) ++ [x] ++ (qsort gs)
    where
        ls = [y | y<-xs, y<=x]
        gs = [y | y<-xs, y>x]

dup :: [String] -> [String]
dup s = aux s [[]]
    where
        aux :: [String] -> [String] -> [String]
        aux [] l = l --Why can I pattern match [] to [String]?
        aux (x:xs) l
            | x `elem` xs = aux xs (x:l)
            | otherwise   = aux xs l

prm::String->String->Bool
prm s t
    | s == t             = False
    | qsort s == qsort t = True
    | otherwise          = False

--Don't think this function will be useful.
comp :: String -> String -> String -> String -> String
comp [] _ acc long
    | length acc > length long = acc
    | otherwise = long 
comp _ [] acc long
    | length acc > length long = acc
    | otherwise = long
comp (x:xs) (y:ys) acc long
    | x == y                     = comp xs ys (acc ++ [x]) long
    | length acc > length long   = comp xs ys [] acc
    | otherwise                  = comp xs ys [] long

--This returns the powerset, not substrings
ps :: String -> [String]
ps [] = [[]]
ps (x:xs) = subxs ++ (map (x:) subxs)
    where subxs = ps xs

--Returns all the substrings of a string (or other types).
subs :: String -> [String]
subs [] = []
subs s = breakup s ++ subs (init s)
    where
	breakup :: String -> [String]
        breakup [] = []
        breakup (x:xs) = [(x:xs)] ++ (breakup xs)

--Longest Repeated Substring
lrs :: String -> String
lrs [] = []
lrs s = aux (dup (subs s)) 0 [] --Added extra length argument to prevent repeated computation of length. 
    where
        aux [] l cur = cur
        aux (x:xs) l cur
            | length x > l = aux xs (length x) x 
            | otherwise    = aux xs l cur


-- *************************** Pascal's Triangle ********************

npas :: Int -> [Integer]
npas m 
    | n >= 0        = [choose n k | k <- [0..n]] 
    | otherwise     = []
    where 
        choose n 0  = 1
        choose 0 k  = 0
        choose n k  = choose (n-1) (k-1) * n `div` k
        n           = toInteger m

nodot :: Int -> String
nodot n = rep n "."

lastline :: Int -> String
lastline n = mergelist (npas n) (npas (n-1))
    where
        mergelist [] (b:bs)     = (nodot . length . show) b --list A gets selected first
        mergelist (a:as) []     = show a
        mergelist (a:as) (b:bs) = show a ++ (nodot . length . show) b ++ mergelist as bs
        
nextline :: String -> [Integer] -> String
nextline below above = nlworker below above ""

nlworker :: String -> [Integer] -> String -> String
nlworker [] _ _             = []
nlworker (a:as) [] []       = '.':nlworker as [] []
nlworker (a:as) (b:bs) []
    | a == '.'              = '.':nlworker as (b:bs) []
    | otherwise             = '.':nlworker as bs (show b)
nlworker (a:as) b (c:cs)
    | a == '.'              = c:nlworker as b cs
    | otherwise             = '.':nlworker as b (c:cs)

pasloop :: Int -> String -> [Integer] -> String
pasloop 0 below above = below
pasloop n below above = pasloop (n-1) (nextline below above) (npas (n-2)) ++ "\n" ++ below

pas :: Int -> String
pas n = pasloop n (lastline n) (npas (n-1)) ++ "\n"

-- *************************** Ant ********************
type Point      = (Int, Int)
type Box        = (Point, Point)
type Grid       = [Point]

data Direction  = N | E | S | W
    deriving (Read, Show)
data Ant        = Ant {dir :: Direction,
                       pos :: Point}
    deriving (Read, Show)

left :: Direction -> Direction
left d = case d of
    N -> W
    E -> N
    S -> E
    W -> S
    
right :: Direction -> Direction
right d = case d of
    N -> E
    E -> S
    S -> W
    W -> N
    
forward :: Direction -> Point -> Point
forward d (x,y) = case d of
    N -> (x,y+1)
    E -> (x+1,y)
    S -> (x,y-1)
    W -> (x-1,y)

newBox :: Ant -> Box -> Box
newBox a ((x1,y1),(x2,y2)) = let (ax,ay) = pos a in ((min x1 ax , min y1 ay),(max x2 ax , max y2 ay))


-- A function that combines a turn and a forward movement. 
move :: (Direction -> Direction) -> Ant -> Ant
move turn a = let newdir = turn (dir a) in Ant newdir (forward newdir (pos a))

-- Computes the next grid and ant when given the previous ones.
nextState :: Ant -> Grid -> (Ant, Grid)
nextState a g
    | pos a `elem` g = ((move left a), [ x | x <- g, x /= (pos a)]) -- Ant on black square. Return new ant and grid with square removed.
    | otherwise      = ((move right a), ((pos a):g)) -- Ant on white square. Return new ant and grid with square added.

antLoop :: Ant -> Grid -> Box -> Int -> (Ant, Grid, Box)
antLoop a g b 0 = (a,g,b)
antLoop a g b n = let (na, ng) = nextState a g in antLoop na ng (newBox na b) (n-1)

split :: Int -> String -> String -- From image.hs
split n s
    | n <= 0            = error "n must be greater than or equal to 1"
    | s == ""           = ""
    | length(b) >= n    = a ++ "\n" ++ split n b
    | otherwise         = a ++ "\n" ++ b
    where (a,b)         = splitAt n s

render :: (Ant, Grid, Box) -> String -- Adapted from image.hs
render (ant, grid, ((xmin,ymin),(xmax,ymax))) = split (xmax - xmin + 1) [convert (x,y)| y <- [ymax, ymax-1..ymin], x <- [xmin..xmax]]
    where
        convert p
            | p == (pos ant)        = if p `elem` grid then '*' else '+'
            | otherwise             = if p `elem` grid then 'x' else '.'
            
ant :: Grid -> Int -> String
ant g n = render (antLoop (Ant W (0,0)) g ((0,0),(0,0)) n)

