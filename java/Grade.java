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
        int mark = Integer.parseInt(args[0]);
        if (mark < 0 || mark > 100)
        {
            System.err.println("Not in the correct range");
            System.exit(1);
        }
        else System.out.println(getGrade(mark));
    }
}
