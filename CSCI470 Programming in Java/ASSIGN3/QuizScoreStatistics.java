import java.util.Scanner;

public class QuizScoreStatistics 
{
	public static void main(String[] args) 
	{
		Scanner in = new Scanner(System.in);
		
		int count = 0;
		int sum = 0;
		int score;
		int max = 0;
		int min = 0;
		
		System.out.println("Enter student quiz score (enter 99 to stop):");
		score = in.nextInt();
		if(score >= 0 && score <= 10)
		{
			min = score;
			max = score;
		}
		
		while(score != 99)
		{
			if(score < 0 || score > 10)
			{
				System.out.println("Invalid. Discarded.");
			}
			
			else
			{
				count++;
				sum = sum + score;
				if(score > max)
				{
					max = score;
				}
				if(score < min)
				{
					min = score;
				}
			}
			
			System.out.println("Enter student quiz score (enter 99 to stop):");
			score = in.nextInt();
		}
		
		double average = sum / count;
		
		System.out.printf("Number of scores entered: %d%n", count);
        System.out.printf("Highest score: %d%n", max);
        System.out.printf("Lowest score: %d%n", min);
        System.out.printf("Average score: %.2f%n", average);
	}
}
