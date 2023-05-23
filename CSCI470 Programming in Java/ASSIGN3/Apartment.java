public class Apartment 
{
	private int numBedrooms;
	private double numBaths;
	private int ApartmentNum;
	private double rentAmount;
	
	// Default constructor
	public Apartment(int ApartmentNum, int bedrooms, double baths, double rent)
	{
		this.ApartmentNum = ApartmentNum;
		numBedrooms = bedrooms;
		numBaths = baths;
		rentAmount = rent;
	}
	
	public int getBedrooms()
	{
		return numBedrooms;
	}
	
	public double getBaths()
	{
		return numBaths;
	}
	
	public double getRent()
	{
		return rentAmount;
	}
	
	public int getApartmentNum()
	{
		return ApartmentNum;
	}
}
