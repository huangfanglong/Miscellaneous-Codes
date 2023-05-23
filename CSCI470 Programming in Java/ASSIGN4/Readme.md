CSCI 470
Assignment#4 
Due 04/16/2023 by 11:59 pm
100 Points
C:\Users\ccrun\IdeaProjects\Assign4\src
Exercise 1. (20 Points)
Write an application that stores nine integers in an array. Display the integers from first to last, and then display the integers from last to first. Save the file as NineInts.java.

RUBRIC:
Display the integers from first to last. (10 Points)
Display the integers from last to first. (10 Points) 

Exercise 2. (20 Points)
Write an application that allows a user to enter the names and birthdates of up to 10 friends. Continue to prompt the user for names and birthdates until the user enters the sentinel value ZZZ for a name or has entered 10 names, whichever comes first. When the user is finished entering names, produce a count of how many names were entered, and then display the names. In a loop, continuously ask the user to type one of the names and display the corresponding birthdate or an error message if the name has not been previously entered. The loop continues until the user enters ZZZ for a name. Save the application as BirthdayReminder.java.




RUBRIC:
Allows the user to enter names and birthdays. (5 Points)
Uses the sentinel value or 10 to control the loop. (5 Points)
Display the count and the names. (5 Points)
Asks the user for a name and display the birthday continuously until user wants to stop.             (5 Points)









Exercise 3. (20 Points)
a)	Write an application for Cody’s Car Care Shop that shows a user a list of available services: oil change, tire rotation, battery check, or brake inspection. Allow the user to enter a string that corresponds to one of the options, and display the option and its price as $25, $22, $15, or $5, accordingly. Display an error message if the user enters an invalid item. Save the file as CarCareChoice.java.
b)	It might not be reasonable to expect users to type long entries such as “oil change” accurately. Modify the CarCareChoice class so that as long as the user enters the first three characters of a service, the choice is considered valid. Save the file as CarCareChoice2.java.





CarCareChoice2 Ouput



RUBRIC:
Shows the services available. (5 Points)
Asks for user input.  Display the option with price. (5 Points)
Displays an error message for invalid input. (5 Points)
Modified the code for b. (5 Points)

Exercise 4. (20 Points)
Write an application that stores at least five different college courses (such as CIS101), the time it first meets in the week (such as Mon 9 am), and the instructor (such as Johnson) in a two-dimensional array. Allow the user to enter a course name and display the corresponding time and instructor. If the course exists twice, display details for both sessions. If the course does not exist, display an error message. Save the file as TimesAndInstructors.java.
Use the following values:
Course	Time	Instructor
CIS101	Mon 9 am	Farrell
CIS210	Mon 11 am	Patel
MKT100	Tues 8:30 am	Wong
ACC150	Tues 6 pm	Deitrich
CIS101	Fri 1 pm	Lenno

Sample Output 1:
Enter a course:
MKT100
Course: MKT100 Time: Tues 8:30 am Instructor: Wong

Sample Output 2:
Enter a course:
CIS101
Course: CIS101 Time: Mon 9 am Instructor: Farrell
Course: CIS101 Time: Fri 1 pm Instructor: Lennon


RUBRIC:
Setup the table values in array. (10 Points)
Allow the user to enter the course and display the information. (10 Points)






Exercise 5. (20 Points)
Morgan’s Department Store distributes bonuses to its salespeople after the holiday rush. Table below shows the bonuses, which are based on full weeks worked during the season and the number of positive online customer reviews. Write a program that allows a user to continuously enter values for the two bonus-determining factors and displays the appropriate bonus. Save the file as MorgansBonuses.java.
Morgan’s Department Store bonuses
	Positive Reviews Received
Full Weeks Worked	0	1	2	3	4 or More
0	5.00	9.00	16.00	22.00	30.00
1	10.00	12.00	18.00	24.00	36.00
2	20.00	25.00	32.00	42.00	53.00
3	32.00	38.00	45.00	55.00	68.00
4	46.00	54.00	65.00	77.00	90.00
5	60.00	72.00	84.00	96.00	120.00
6 or more	85.00	100.00	120.00	140.00	175.00

RUBRIC:
Setup the table values in array. (10 Points)
Allow the user to enter the criteria and display the bonus. (10 Points)






