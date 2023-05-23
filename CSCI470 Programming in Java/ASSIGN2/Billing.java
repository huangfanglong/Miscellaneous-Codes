
public class Billing 
{
	public double computeBill(double price) 
	{
		return price + (price * 0.08);
	}
	
	public double computeBill(double price, int quantity) 
	{
		double tax = (price * quantity) * 0.08;
		return (price * quantity) + tax;
	}
	
	public double computeBill(double price, int quantity, double couponValue) 
	{
		double tax = ((price * quantity) - couponValue) * 0.08;
		return ((price * quantity) - couponValue) + tax;
	}
}
