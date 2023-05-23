import java.util.Scanner;

public class MorgansBonuses 
{
	public static void main(String[] args) 
    {
		Scanner input = new Scanner(System.in);
		
		// Set up 2 dimensional array
		Double[][] bonuses = 
			{
				{5.00,9.00,16.00,22.00,30.00},
				{10.00,12.00,18.00,24.00,36.00},
				{20.00,25.00,32.00,42.00,53.00},
				{32.00,38.00,45.00,55.00,68.00},
				{46.00,54.00,65.00,77.00,90.00},
				{60.00,72.00,84.00,96.00,120.00},
				{85.00,100.00,120.00,140.00,175.00}
			};
		
		System.out.print("(Enter 0 if you want to stop.)");
		System.out.println();
		
		int weeksWorked = -1;
		
		while(weeksWorked != 0)
		{
			System.out.print("Enter weeks worked: ");
        	weeksWorked = input.nextInt();
        	while(weeksWorked < 0)
        	{
        		System.out.print("Invalid entry.\n");
        		System.out.print("Enter weeks worked: ");
            	weeksWorked = input.nextInt();
        	}
        	
        	if(weeksWorked >= 6)
        	{
        		weeksWorked = 6;
        	}
        	
        	if(weeksWorked == 0)
        	{
        		break;
        	}
        
        	System.out.print("Enter online positive reviews received: ");
        	int positiveReviews = input.nextInt();
        	while(positiveReviews < 0)
        	{
        		System.out.print("Invalid entry.\n");
        		System.out.print("Enter online positive reviews received: ");
        		positiveReviews = input.nextInt();
        	}
        	if(positiveReviews >= 4)
        	{
        		positiveReviews = 4;
        	}
        
        	System.out.println("Bonus is: $" + bonuses[weeksWorked][positiveReviews]);
        	System.out.println();
		}
		input.close();
    }
}
