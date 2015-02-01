class Grade
{
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

    public static void main(String[] args)
    {
        try
        {
            double acc = 0;
            double mark;
            for(int i=0; i<args.length; i++)
            {
                if(args[i].matches("^[0-9]+\\.?[0-9]$")
                {
                    mark = Double.parseDouble(args[i]);
                    if (mark < 0 || mark > 100) throw new NotMarkException("Not in the range from 0 to 100.");
                    else acc += mark;
                }
                else throw new NotMarkException("Not a number with one decimal place in the range 0 to 100.");            
            }
            System.out.println(getGrade((int)Math.ceil((double)acc/args.length)));
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
