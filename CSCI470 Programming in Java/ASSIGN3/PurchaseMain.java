import java.util.Scanner;

public class PurchaseMain 
{
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        
        Purchase purchase = new Purchase();
        
        int invoiceNumber = 0;
        
        System.out.print("Enter invoice number (between 1000 - 8000): ");
        invoiceNumber = in.nextInt();
        if(invoiceNumber < 1000 || invoiceNumber > 8000)
        {
        	System.out.println("Invalid Invoice Number. Enter again.");
        	while (invoiceNumber < 1000 || invoiceNumber > 8000) 
            {
        		System.out.print("Enter invoice number (between 1000 - 8000): ");
                invoiceNumber = in.nextInt();
            }
        }
        
        purchase.setinvoiceNum(invoiceNumber);
        
        double saleAmount = 0;
        
        System.out.print("Enter sale amount: $");
        saleAmount = in.nextDouble();
        
        if(saleAmount < 0)
        {
            System.out.println("Invalid sales amount. Enter again.");
            while (saleAmount < 0) 
            {
               System.out.print("Enter sale amount: $");
               saleAmount = in.nextDouble();
            }
        }
        
        purchase.setsalesAmount(saleAmount);

        System.out.println("Purchase details:");
        
        System.out.printf("Invoice number: &%d%n", purchase.getInvoiceNumber());
        
        System.out.printf("Sale amount: $%.2f%n", purchase.getSaleAmount());
        
        System.out.printf("Sales tax: $%.2f%n", purchase.getSalesTax());
    }
}
