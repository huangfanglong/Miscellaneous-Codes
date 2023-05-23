import java.util.Scanner;

public class BloodDataTest 
{
	public static void main(String[] args) 
	{
		//ex1
		BloodData example = new BloodData();
		System.out.printf("First example default constructor.%nBlood Type: %s%c%n%n", example.getBloodType(), example.getRhFactor());
		
		//ex2
		example.setBloodType("B");
		example.setRhFactor('+');
		System.out.printf("Second example default constructor and using set method.%nBlood Type: %s%c%n%n", example.getBloodType(), example.getRhFactor());
		
		//ex3
		BloodData example2 = new BloodData("A", '-');
		System.out.printf("Third example overloaded constructor.%nBlood Type: %s%c%n%n", example2.getBloodType(), example2.getRhFactor());
	}

}
