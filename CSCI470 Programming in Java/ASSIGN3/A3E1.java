import java.util.Scanner;

public class A3E1 
{
	public static void main(String[] args)
	{
		Scanner in = new Scanner(System.in);
		int integerInput = 0;
		int max = 0;
		int min = 0;
		
		System.out.println("Enter an integer (-99 to stop):");
		integerInput = in.nextInt();
		min = integerInput;
		max = integerInput;
	
		while(integerInput != -99)
		{
			System.out.println("Enter an integer (-99 to stop):");
			integerInput = in.nextInt();
		
			if(integerInput > max)
			{
				max = integerInput;
			}
		
			if(integerInput < min && integerInput != -99)
			{
				min = integerInput;
			}
		}
		
		if(min != -99 || max != -99)
		{
			System.out.printf("The smallest number was: %d%n", min);
			System.out.printf("The largest number was: %d%n", max);
		}
		else
		{
			System.out.println("No input intered.");
		}
	}
}
