CSCI 470
Assignment#5 
Due 05/07/2023 by 11:59 pm
100 Points

Exercise 1. (30 Points)
Create a class named Horse that contains the following data fields:
•	name - of type String
•	color - of type String
•	birthYear - of type int
Include get and set methods for these fields.
Next, create a subclass named RaceHorse, which contains an additional field, races (of type int), that holds the number of races in which the horse has competed and additional methods to get and set the new field.
Write an application that demonstrates using objects of each class. An example of the DemoHorses program is shown below:
Old Paint is brown and was born in 2009.
Champion is black and was born in 2011.
Champion has been in 4 races.

Save the files as Horse.java, RaceHorse.java, and DemoHorses.java.


RUBRIC:
Horse Class with all items required. (10 Points)
Race Horse class with all items required. (10 Points)
DemoHorses class with a nice demo. (10 Points)

Exercise 2. (30 Points)
Mick’s Wicks makes candles in various sizes. Create a class for the business named Candle that contains the following data fields:
•	color - of type String
•	height - of type int
•	price - of type double
Create get methods for all three fields. Create set methods for color and height, but not for price. Instead, when height is set, determine the price as $2 per inch.
Create a child class named ScentedCandle that contains an additional data field named scent (of type String) and methods to get and set it. In the child class, override the parent’s setHeight() method to set the price of a ScentedCandle object at $3 per inch.
Write an application that instantiates an object of each type and displays the details.  An example of the DemoCandles program is shown below:
The 6 inch pink candle costs $12.0
The 6 inch gardenia white candle costs $18.0

Save the files as Candle.java, ScentedCandle.java, and DemoCandles.java.


RUBRIC:
Candle Class with all items required. (10 Points)
ScentedCande class with all items required. (10 Points)
DemoCandles class with a nice demo. (10 Points)

Exercise 3. (40 Points)
Create an abstract Student class for Parker University. The class contains fields for student ID number, last name, and annual tuition. Include a constructor that requires parameters for the ID number and name. Include get and set methods for each field; the setTuition() method is abstract. 

Create three Student subclasses named UndergraduateStudent, GraduateStudent, and StudentAtLarge, each with a unique setTuition() method. Tuition for an UndergraduateStudent is $4,000 per semester, tuition for a GraduateStudent is $6,000 per semester, and tuition for a StudentAtLarge is $2,000 per semester. 

Write an application that creates an array of at least six objects to demonstrate how the methods work for objects for each Student type.  An example of the StudentDemo program is shown below:
Student # 111 Name: Lambert  Tuition: 4000.0 per year

Student # 122 Name: Lembeck  Tuition: 4000.0 per year

Student # 233 Name: Miller  Tuition: 6000.0 per year

Student # 256 Name: Marmon  Tuition: 6000.0 per year

Student # 312 Name: Nichols  Tuition: 2000.0 per year

Student # 376 Name: Nussbaum  Tuition: 2000.0 per year

Save the files as Student.java, UndergraduateStudent.java, GraduateStudent.java, StudentAtLarge.java, and StudentDemo.java.


RUBRIC:
Student.java with all items required. (10 Points)
UndergraduateStudent.java with all items required. (10 Points)
GraduateStudent.java with all items required. (10 Points)
StudentAtLarge.java with all items required. (5 Points)
StudentDemo.java with all items required. (5 Points)

