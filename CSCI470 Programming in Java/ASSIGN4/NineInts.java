public class NineInts 
{
	public static void main(String[] args) 
	{
		int[] array = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		
		System.out.println("First to last:");
		for (int i = 0; i < array.length; i++) 
		{
			System.out.print(array[i] + " ");
		}
		
		System.out.println("\n");
		    
		System.out.println("Last to first:");
		for (int i = array.length - 1; i >= 0; i--) 
		{
			System.out.print(array[i] + " ");
		}
	}

}
