import java.util.Scanner;

public class ApartmentMain 
{
	public static void main(String[] args) 
	{
		Scanner in = new Scanner(System.in);
				
		Apartment apt1 = new Apartment(101, 2, 1, 725);
		Apartment apt2 = new Apartment(102, 2, 1.5, 775);
		Apartment apt3 = new Apartment(103, 3, 2, 870);
		Apartment apt4 = new Apartment(104, 3, 2.5, 960);
		Apartment apt5 = new Apartment(105, 3, 3, 1100);

		
		int minBed;
		double minBath;
		double maxRent;
		
		System.out.println("Enter minimum number of bedrooms:");
		minBed = in.nextInt();
		System.out.println("Enter minimum number of bathrooms:");
		minBath = in.nextDouble();
		System.out.println("Enter maximum amount of rent payment:");
		maxRent = in.nextDouble();
		
		if(apt1.getBedrooms() >= minBed && apt1.getBaths() >= minBath && apt1.getRent() <= maxRent)
		{
			System.out.println("Apartment: " + apt1.getApartmentNum() + " Bedrooms: " + apt1.getBedrooms() + " Baths: " + apt1.getBaths() + " Rent: " + apt1.getRent());
		}
		if(apt2.getBedrooms() >= minBed && apt2.getBaths() >= minBath && apt2.getRent() <= maxRent)
		{
			System.out.println("Apartment: " + apt2.getApartmentNum() + " Bedrooms: " + apt2.getBedrooms() + " Baths: " + apt2.getBaths() + " Rent: " + apt2.getRent());
		}
		if(apt3.getBedrooms() >= minBed && apt3.getBaths() >= minBath && apt3.getRent() <= maxRent)
		{
			System.out.println("Apartment: " + apt3.getApartmentNum() + " Bedrooms: " + apt3.getBedrooms() + " Baths: " + apt3.getBaths() + " Rent: " + apt3.getRent());
		}
		if(apt4.getBedrooms() >= minBed && apt4.getBaths() >= minBath && apt4.getRent() <= maxRent)
		{
			System.out.println("Apartment: " + apt4.getApartmentNum() + " Bedrooms: " + apt4.getBedrooms() + " Baths: " + apt4.getBaths() + " Rent: " + apt4.getRent());
		}
		if(apt5.getBedrooms() >= minBed && apt5.getBaths() >= minBath && apt5.getRent() <= maxRent)
		{
			System.out.println("Apartment: " + apt5.getApartmentNum() + " Bedrooms: " + apt5.getBedrooms() + " Baths: " + apt5.getBaths() + " Rent: " + apt5.getRent());
		}
		
		else
		{
			System.out.println("No match.");
		}
	}
}
