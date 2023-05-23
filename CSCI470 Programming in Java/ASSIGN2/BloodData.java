public class BloodData 
{
	private String bloodType;
	private char RhFactor;
	
	// Default constructor
	public BloodData()
	{
		bloodType = "O";
		RhFactor = '+';
	}
	
	// Overloaded Constructor
	public BloodData(String bloodType, char RhFactor)
	{
		this.bloodType = bloodType;
		this.RhFactor = RhFactor;
	}
	
	// Set and Get for Blood Type and RhFactor
	public void setBloodType(String bloodType)
	{
		this.bloodType = bloodType;
	}
	
	public void setRhFactor(char RhFactor)
	{
		this.RhFactor = RhFactor;
	}
	
	public String getBloodType()
	{
		return bloodType;
	}
	
	public char getRhFactor()
	{
		return RhFactor;
	}
}
