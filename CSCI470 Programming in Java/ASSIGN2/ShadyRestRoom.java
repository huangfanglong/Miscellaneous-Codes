import java.util.Scanner;

public class ShadyRestRoom {

	public static void main(String[] args) 
	{
		Scanner in = new Scanner(System.in);
		
		int price;
		
		System.out.println("Enter 1 for a Queen Bed, 2 for a King, or 3 for a King and a Pullout Couch");
		int userInput = in.nextInt();
		
		if (userInput == 1 || userInput == 2 || userInput == 3)
		{
			if (userInput == 1)
			{
				System.out.printf("Input: %d for a Queen Bed%n", userInput);
				price = 125;
				System.out.printf("Price: $%d", price);
			}
			if (userInput == 2)
			{
				System.out.printf("Input: %d for a King Bed%n", userInput);
				price = 139;
				System.out.printf("Price: $%d", price);
			}
			if (userInput == 3)
			{
				System.out.printf("Input: %d for a King and a Pullout Couch suite%n", userInput);
				price = 165;
				System.out.printf("Price: $%d", price);
			}
		}
		
		else
		{
			System.out.println("Invalid input. Please enter 1 for a Queen Bed, 2 for a King, or 3 for a King and a Pullout Couch. Try again.");
			price = 0;
		}
	}
}
