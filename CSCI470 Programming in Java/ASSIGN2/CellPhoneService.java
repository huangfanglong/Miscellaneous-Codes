import java.util.Scanner;

public class CellPhoneService 
{
	public static void main(String[] args) 
	{
		Scanner in = new Scanner(System.in);
		
		System.out.println("What is your estimated maximum talk minutes per month? (e.g: 100, 250, 500, etc; whole number only)");
		int talkMinutes = in.nextInt();
		
		System.out.println("What is your estimated maximum number of texts per month? (e.g: 100, 250, 500, 0, etc; whole number only)");
		int texts = in.nextInt();
		
		System.out.println("What is your estimated maximum Gigabytes of data used per month? (e.g: 1, 2, 3, or 0; whole number only)");
		int data = in.nextInt();
		
		if(talkMinutes < 500 && texts == 0 && data == 0)
		{
			System.out.println("Plan A (500 minutes of talk | no texts | no data) - $49/month");
		}
		
		if(talkMinutes < 500 && texts > 0 && data == 0)
		{
			System.out.println("Plan B (500 minutes of talk | Unlimited texts | no data) - $55/month");
		}
		
		if(talkMinutes >= 500 && data == 0)
		{
			System.out.println("Plan C (Unlimited talk | Up to 100 texts | no data) - $61/month");
			System.out.println("Plan D (Unlimited talk | Unlimited texts | no data) - $70/month");
		}
		
		if(data > 0)
		{
			System.out.println("Plan E (Unlimited talk | Unlimited texts | 3 GBs) - $79/month");
			System.out.println("Plan F (Unlimited talk | Unlimited texts | Unlimited data) - $87/month");
		}
	}

}
