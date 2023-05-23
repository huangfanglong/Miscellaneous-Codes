import java.util.Scanner;

public class AcmePay 
{
	public static void main(String[] args) 
	{
		Scanner in = new Scanner(System.in);
		
		System.out.println("Hours worked this week:");
		int hoursWorked = in.nextInt();
		
		System.out.println("Shift(1, 2 or 3):");
		int shift = in.nextInt();
		
		if(shift == 2 || shift == 3)
		{
			System.out.println("Elect retirement? (y/n):");
		    String retirement = in.next();
		    
			while(!retirement.equals("y") && !retirement.equals("n"))
			{
			    System.out.println("Invalid input. Elect retirement? (y/n). Enter only a character 'y' for yes or 'n' for no");
			    retirement = in.next();
			}
			
			double grossPay = 0;
			
			if (hoursWorked > 40)
			{
				double overtimePay = 0;
				
				System.out.printf("Hours worked: %d%n", hoursWorked);
				System.out.printf("Shift: %d%n", shift);
				if(shift == 2)
				{
					System.out.println("Hourly Payrate: $18.5");
					grossPay = 40 * 18.5;
					System.out.printf("Regular Pay: $%.2f%n", grossPay);
					hoursWorked -= 40;
					overtimePay = hoursWorked * (18.5 * 1.5);
					grossPay = grossPay + (hoursWorked * (18.5 * 1.5));
					System.out.printf("Overtime Pay: $%.2f%n", overtimePay);
					System.out.printf("Total Pay: $%.2f%n", grossPay);
					if(!retirement.equals("n"))
					{
						System.out.printf("Retirement deduction: $%.2f%n", grossPay * 0.03);
						grossPay -= (grossPay * 0.03);
						System.out.printf("Net Pay: $%.2f%n", grossPay);
					}
				}
				
				if(shift == 3)
				{
					System.out.println("Hourly Payrate: $22");
					grossPay = 40 * 22;
					System.out.printf("Regular Pay: $%.2f%n", grossPay);
					hoursWorked -= 40;
					overtimePay = hoursWorked * (22 * 1.5);
					grossPay = grossPay + (hoursWorked * (22 * 1.5));
					System.out.printf("Overtime Pay: $%.2f%n", overtimePay);
					System.out.printf("Total Pay: $%.2f%n", grossPay);
					if(!retirement.equals("n"))
					{
						System.out.printf("Retirement deduction: $%.2f%n", grossPay * 0.03);
						grossPay -= (grossPay * 0.03);
						System.out.printf("Net Pay: $%.2f%n", grossPay);
					}
				}
			}
			
			else
			{
				if(shift == 2)
				{
					grossPay = hoursWorked * 18.5;
					System.out.printf("Hours worked: %d%n", hoursWorked);
					System.out.printf("Shift: %d%n", shift);
					System.out.println("Hourly Payrate: $18.5");
					System.out.printf("Regular Pay: $%.2f%n", grossPay);
					if(!retirement.equals("n"))
					{
						System.out.printf("Retirement deduction: $%.2f%n", grossPay * 0.03);
						grossPay -= (grossPay * 0.03);
						System.out.printf("Net Pay: $%.2f%n", grossPay);
					}
				}
				
				if(shift == 3)
				{
					grossPay = hoursWorked * 22;
					System.out.printf("Hours worked: %d%n", hoursWorked);
					System.out.printf("Shift: %d%n", shift);
					System.out.println("Hourly Payrate: $22");
					System.out.printf("Regular Pay: $%.2f%n", grossPay);
					if(!retirement.equals("n"))
					{
						System.out.printf("Retirement deduction: $%.2f%n", grossPay * 0.03);
						grossPay -= (grossPay * 0.03);
						System.out.printf("Net Pay: $%.2f%n", grossPay);
					}
				}
			}	
			
		}
		
		// else is first shift(1)
		else
		{
			double grossPay = 0;
			
			if (hoursWorked > 40)
			{
				double overtimePay = 0;
				
				System.out.printf("Hours worked: %d%n", hoursWorked);
				System.out.printf("Shift: %d%n", shift);
				System.out.println("Hourly Payrate: $17");
				grossPay = 40 * 17;
				System.out.printf("Regular Pay: $%.2f%n", grossPay);
				hoursWorked -= 40;
				overtimePay = hoursWorked * (17 * 1.5);
				grossPay = grossPay + (hoursWorked * (17 * 1.5));
				System.out.printf("Overtime Pay: $%.2f%n", overtimePay);
				System.out.printf("Total Pay: $%.2f%n", grossPay);
			}
			
			else
			{
				grossPay = hoursWorked * 17;
				System.out.printf("Hours worked: %d%n", hoursWorked);
				System.out.printf("Shift: %d%n", shift);
				System.out.println("Hourly Payrate: $17");
				System.out.printf("Regular Pay: $%.2f%n", grossPay);
			}
		}
	}
}
