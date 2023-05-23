import java.util.Scanner;

public class BirthdayReminder 
{
  
	public static void main(String[] args) 
	{
		Scanner input = new Scanner(System.in);
		String[] names = new String[10];
		String[] dates = new String[10];
		int count = 0;
		
		while(count < 10) 
		{
			System.out.print("Enter a name (or enter ZZZ to stop): ");
			String name = input.nextLine();
			if (name.equals("ZZZ") || name.equals("zzz")) 
			{
				break;
			}
			names[count] = name;
			System.out.print("Enter " + name + "'s birthdate: ");
			String date = input.nextLine();
			dates[count] = date;
			count++;
		}
    
		System.out.println("You entered " + count + " name(s).");
		for (int i = 0; i < count; i++) 
		{
			System.out.println(names[i]);
		}
		
		if(count != 0)
		{
			// While loop to ask user to input a name matching in one of the array to display their corresponding birthdates
			while (true) 
			{
				System.out.println("Enter a name for their birthdate (or enter ZZZ to quit): ");
				String name = input.nextLine();
				boolean found = false;
				if (name.equals("ZZZ") || name.equals("zzz")) 
				{
					break;
				}		
			
				for (int i = 0; i < count; i++) 
				{
					if (name.equals(names[i])) 
					{
						System.out.println(name + "'s birthdate: " + dates[i]);
						found = true;
						break;
					}
				}
				if (!found)
				{
					System.out.println("Name spelling invalid or not previously entered.");
				}
			}
		}
		input.close();
	}
}