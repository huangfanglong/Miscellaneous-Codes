public class Purchase 
{
    private int invoiceNum;
    private double salesTax;
    private double salesAmount;

    public void setinvoiceNum(int invoiceNum) 
    {
        this.invoiceNum = invoiceNum;
    }

    public void setsalesAmount(double salesAmount) 
    {
        this.salesAmount = salesAmount;
        this.salesTax = 0.05 * salesAmount;
    }

    public void display() 
    {
        System.out.printf("Invoice Number: $%d%n", invoiceNum);
        System.out.printf("Sale Amount: $%.2f%n", salesAmount);
        System.out.printf("Sales Tax: $%.2f%n", salesTax);
    }
    
    public int getInvoiceNumber() 
    {
        return invoiceNum;
    }

    public double getSaleAmount() 
    {
        return salesAmount;
    }

    public double getSalesTax() 
    {
        return salesTax;
    }
}