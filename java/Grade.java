class Grade
{
    private static String getGradeBinary(int mark) throws NotMarkException
    {
    
        int[] gb = {0, 40, 50, 60, 70, 80, 90, 100, 101};
        String[] grades =
        {
            "Fail",
            "Third Class",
            "Lower Second Class",
            "Upper Second Class",
            "First Class",
            "Above and Beyond",
            "Publishable",
            "Perfect"
        };
        //System.out.format("mark: %d\n", mark);
        return grades[bSearch(gb,mark,0,gb.length-1)];
    }
    
    private static String getGrade(int mark)
    {
        if (mark == 100) return "Perfect";
        else if (mark >= 90) return "Publishable";
        else if (mark >= 80) return "Above and Beyond";
        else if (mark >= 70) return "First Class";
        else if (mark >= 60) return "Upper Second Class";
        else if (mark >= 50) return "Lower Second Class";
        else if (mark >= 40) return "Third Class";
        else return "Fail";
    }
    
    private static int bSearch(int[] gb, int key, int min, int max) throws NotMarkException
    {
        if(max < min)
            throw new NotMarkException("Key not in array.");
        else
        {
            int mid = (min+max)/2;
            System.out.format("Split: %d\n", mid);
            if (gb[mid] > key)
                return bSearch(gb,key,min,mid-1);
            else if (gb[mid] <= key && gb[mid+1] > key)
                return mid;
            else
                return bSearch(gb,key,mid+1,max);
        }
    }

    public static void main(String[] args)
    {        
        try
        {
            double acc = 0;
            double mark;
            boolean bin = false;
            boolean flags = true;
            int argNo = 0;
            for(int i=0; i<args.length; i++)
            {
                if (flags && args[i].equals("-binary"))
                    bin = true;
                else if(args[i].matches("([1-9]\\d*|0)\\.?[0-9]?"))
                {
                    flags = false;
                    argNo++;
                    mark = Double.parseDouble(args[i]);
                    if (mark < 0 || mark > 100) throw new NotMarkException("Not in the range from 0 to 100.");
                    else acc += mark;
                }
                else throw new NotMarkException("Not a number with zero or one decimal places.");            
            }
            if (bin) System.out.println(getGradeBinary((int)Math.round(acc/argNo)));
            else System.out.println(getGrade((int)Math.round(acc/argNo)));
        } 
        catch(NotMarkException ex)
        {
            System.err.println(ex.getMessage());
            System.exit(1);
        }
        catch(NumberFormatException|ArrayIndexOutOfBoundsException ex)
        {
            System.err.println("You need to input a number between 0 and 100.");
            System.exit(1);
        }
    } 
}

class NotMarkException extends Exception
{
    public NotMarkException() { super(); }
    public NotMarkException(String message) { super(message); }
}
