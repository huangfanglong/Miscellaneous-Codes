import java.util.Scanner;

public class BillingMain 
{
	public static void main(String[] args) 
	{
		Billing exampleBilling = new Billing();
		
		double price = 8.99;
		int quantity = 5;
		double couponValue = 0.99;
		
		System.out.printf("Price = $%.2f%n", price);
		System.out.printf("Quantity = %d%n", quantity);
		System.out.printf("Coupon Value = $%.2f%n%n", couponValue);
		
		System.out.printf("First example (price): $%.2f%n", exampleBilling.computeBill(price));
		System.out.printf("Second example (price & quantity): $%.2f%n", exampleBilling.computeBill(price, quantity));
		System.out.printf("Third example (price, quantity & couponValue): $%.2f%n", exampleBilling.computeBill(price, quantity, couponValue));
	}

}
