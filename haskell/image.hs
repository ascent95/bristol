{-**********-}

--  define a Point as a pair of integers
type Point = (Int,Int)

--  define the point we call the origin
origin :: Point
origin = (0,0)

-- define a function for scaling a point
-- horizontally by h and vertically by v
scale :: Int -> Int -> Point -> Point
scale h v (x,y) = (h*x,v*y)

-- flip a point about the  horizontal axis (y=0)
flipH :: Point -> Point
flipH (x,y) = (x,-y)

-- flip a point about the  vertical axis (x=0)
flipV :: Point -> Point
flipV (x,y) = (-x,y)
 
-- flip a point about the diagonal line (x=y)
flipD :: Point -> Point
flipD (x,y) = (y,x)

-- quarter turn clockwise
turnC :: Point -> Point
turnC (x,y) = (y,-x)

-- half turn
turnB :: Point -> Point
turnB (x,y) = (-x,-y)
 
-- quarter turn anticlockwise
turnA :: Point -> Point
turnA (x,y) = (-y,x)

{-**********-}

-- define an Image as a list of points
type Image = [Point]

-- define a T-shaped image
t :: Image
t=[(0,1),(1,0),(1,1),(2,1)]

-- define an X-shaped image
x :: Image
x=[(1,1),(1,-1),(2,0),(3,1),(3,-1)]

-- transform an Image point by point
pointwise :: (Point->Point) -> (Image->Image)
pointwise f = \ps -> [f p | p <- ps]

-- overlay two images
overlay :: Image -> Image -> Image
overlay i j = i ++ j

-- shift a point
shift :: Int -> Int -> Point -> Point
shift h v (x,y) = (x+h, y+v)

-- bounds of an image
bounds :: Image -> (Int, Int, Int, Int)
bounds [] = error "This image has no points"
bounds ((x,y):ps)  = aux ps (x,x,y,y)
    where aux [] b = b
          aux ((x,y):ps) (xmin,xmax,ymin,ymax) = aux ps (min x xmin, max x xmax, min y ymin, max y ymax)

-- places two images side by side, sitting on the x-axis
sideBySide :: Image -> Image -> Image
sideBySide a b = overlay (pointwise (shift (-p) (-q)) a) (pointwise (shift (-r) (-s)) b)
    where (_,p,q,_) = bounds a
          (r,_,s,_) = bounds b

-- inserts a newline character every n characters
split :: Int -> String -> String
split n s
    | n <= 0            = error "n must be greater than or equal to 1"
    | length(b) >= n    = a ++ "\n" ++ split n b
    | otherwise         = a ++ "\n" ++ b
    where (a,b)         = splitAt n s

-- renders an image as a string
render :: Image -> String
render i = split d [convert (x,y)| y <- [ymax+1, ymax..ymin-1], x <- [xmin-1..xmax+1]]
    where 
        (xmin,xmax,ymin,ymax) = bounds i;
        d = xmax-xmin+3
        convert p 
            | p `elem` i = 'x'
        convert (0,0) = '+'
        convert (_,0) = '-'
        convert (0,_) = '|'
        convert (_,_) = '.' 

{-**********-}
