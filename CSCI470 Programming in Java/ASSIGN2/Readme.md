CSCI 470
Assignment#2
Due 02/26/2023 by 11:59 pm
100 Points

Exercise 1. (20 Points)
Create a class named Billing that includes three overloaded computeBill() methods for a photo book store.
•	When computeBill() receives a single parameter, it represents the price of one photo book ordered. Add 8% tax, and return the total due.
•	When computeBill() receives two parameters, they represent the price of a photo book and the quantity ordered. Multiply the two values, add 8% tax, and return the total due.
•	When computeBill() receives three parameters, they represent the price of a photo book, the quantity ordered, and a coupon value. Multiply the quantity and price, reduce the result by the coupon value, and then add 8% tax and return the total due.
Write a main( ) method that tests all three overload methods.  Save the application as Billing.java.
RUBRIC:
computeBill() with a single parameter (5 points)
computeBill() with a single parameter (5 points)
computeBill() with a single parameter (5 points)
main( ) method that tests all three overload methods (5 points)

Exercise 2. (20 Points)
Create a class named BloodData that includes fields that hold a blood type (the four blood types are O, A, B, and AB) and an Rh factor (the factors are + and –). Create a default constructor that sets the fields to O and +, and an overloaded constructor that requires values for both fields. Include get and set methods for each field. Save this file as BloodData.java. Create an application named TestBloodData that demonstrates each method works correctly. Save the application as TestBloodData.java.
RUBRIC:
BloodData.java (10 Points)
TestBloodData.java (10 Points)

Exercise 3. (20 Points)
Write an application for the Shady Rest Hotel; the program determines the price of a room. Ask the user to choose 1 for a queen bed, 2 for a king, or 3 for a king and a pullout couch. The output echoes the input and displays the price of the room: $125 for queen, $139 for king, and $165 for suite with king bed and a pullout couch. If the user enters an invalid code, display an appropriate message and set the price to 0. Save the file as ShadyRestRoom.java.
RUBRIC:
5 points for each choice of 1, 2, and 3.  5 points for handling invalid input code.	


Exercise 4. (20 Points)
Write a program for Horizon Phones, a provider of cellular phone service. Prompt a user for maximum monthly values for talk minutes used, text messages sent, and gigabytes of data used, and then recommend the best plan for the customer’s needs. A customer who needs fewer than 500 minutes of talk and no text or data should accept Plan A at $49 per month. A customer who needs fewer than 500 minutes of talk and any text messages should accept Plan B at $55 per month. A customer who needs 500 or more minutes of talk and no data should accept either Plan C for up to 100 text messages at $61 per month or Plan D for 100 text messages or more at $70 per month. A customer who needs any data should accept Plan E for up to 3 gigabytes at $79 or Plan F for 3 gigabytes or more at $87. Save the file as CellPhoneService.java.
RUBRIC:
3 points for each correctly coded plan.  2 points for the rest of the code.

	Mins	            Text	          data
A	Less than 500	    0	              0
B	Less than 500	    More than 0	    0
C	500 or more	      Less than 100	  0
D	500 or more	      100 or more	    0
E	Any	              Any	            Up to 3 GB
F	Any	              Any	            More than 3 GB

Exercise 5. (20 Points)
Acme Parts runs a small factory and employs workers who are paid one of three hourly rates depending on their shift: first shift, $17 per hour; second shift, $18.50 per hour; third shift, $22 per hour. Each factory worker might work any number of hours per week; any hours greater than 40 are paid at one and one-half times the usual rate. In addition, second- and third-shift workers can elect to participate in the retirement plan for which 3% of the worker’s gross pay is deducted from the paychecks. Write a program that prompts the user for hours worked and shift, and, if the shift is 2 or 3, whether the worker elects the retirement. Display: 
1.	the hours worked,
2.	the shift,
3.	the hourly pay rate,
4.	the regular pay,
5.	overtime pay,
6.	the total of regular and overtime pay, and
7.	the retirement deduction, if any, and
8.	the net pay. Save the file as AcmePay.java.
RUBRIC:
5 points for each correctly coded shift and 5 points for the rest of the code.

