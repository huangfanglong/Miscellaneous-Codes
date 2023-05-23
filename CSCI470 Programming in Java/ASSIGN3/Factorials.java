public class Factorials 
{
    public static void main(String[] args) 
    {
        for (int i = 1; i <= 10; i++) 
        {
            int factorial = 1;
            
            for (int j = 1; j <= i; j++) 
            {
                factorial = factorial * j;
            }
            System.out.printf("Factorial %d = %d%n", i, factorial);
        }
    }
}
