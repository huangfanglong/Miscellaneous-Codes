import java.util.Scanner;

public class TimesAndInstructors 
{
	public static void main(String[] args) 
    {
		Scanner input = new Scanner(System.in);
		
		// Set up 2 dimensional array
		String[][] courses = 
			{
	            {"CIS101", "Mon 9 am", "Farrell"},
	            {"CIS210", "Mon 11 am", "Patel"},
	            {"MKT100", "Tues 8:30 am", "Wong"},
	            {"ACC150", "Tues 6 pm", "Deitrich"},
	            {"CIS101", "Fri 1 pm", "Lenno"}
			};
		
		System.out.print("Enter a course: ");
        String courseName = input.nextLine();
        courseName = courseName.toUpperCase();
        System.out.println();
        
        // Loop through the array to find the course and display its info
        boolean found = false;
        for (int i = 0; i < courses.length; i++) 
        {
        	if (courses[i][0].equals(courseName)) 
        	{
                System.out.println("Course: " + courses[i][0]);
                System.out.println("Time: " + courses[i][1]);
                System.out.println("Instructor: " + courses[i][2]);
                System.out.println();
                found = true;
            }
        }

        // if input course not found
        if (!found) {
            System.out.println("Entered course is not found");
        }
		
		input.close();
    }
}
