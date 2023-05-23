import java.util.Scanner;

public class CarCareChoice 
{
	public static void main(String[] args) 
    {
		Scanner input = new Scanner(System.in);
		String[] services = {"oil change", "tire rotation", "battery check", "brake inspection"};
		int[] prices = {25, 22, 15, 5};
	
		String serviceInput = "a";
		while(serviceInput.length() < 3)
		{
			System.out.println("Services available: oil change, tire rotation, battery check, and brake inspection");
			System.out.println("Enter a service (at least 3 letters): ");
			serviceInput = input.nextLine();
			
			if(serviceInput.length() < 3)
			{
				System.out.println("Invalid input. Please enter at least 3 letters. ");
			}
		}
		
		// Map the price to the corresponding selected service
        int price = 0;
        for (int i = 0; i < services.length; i++) 
        {
        	// Check if user's input string starts with a specified prefix.
            if (services[i].startsWith(serviceInput.substring(0, 3))) 
            {
            	serviceInput = services[i];
                price = prices[i];
                break;
            }
        }
        
        // Display
        if (price != 0) 
        {
            System.out.println("The price for " + serviceInput + " is $" + price);
        } 
        
        else 
        {
            System.out.println("Invalid service choice.");
        }	
		input.close();
    }
}
