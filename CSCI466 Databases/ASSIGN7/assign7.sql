# LONG HUANG
# Z1942308
# 20222-CSCI-466-----1 Spring
# Assignment 7

#1 Select the BabyName database
USE BabyName;

#2 Show all of the tables in the database
SHOW TABLES;

#3 Show all of the names from your birth year. Each name must be shown only once
SELECT DISTINCT name FROM BabyName WHERE year = '1999' LIMIT 50;

#4 Show all of the columns and their types for each table in the database
DESCRIBE BabyName;

#5 Show all of the years (once only) where your first name appears
SELECT DISTINCT year,name FROM BabyName WHERE name = 'Long';

#6 List how many different names there are for each place
SELECT place, COUNT(DISTINCT name) FROM BabyName GROUP BY place LIMIT 50;

#7 Display the most popular male and female names from the year 1983
(SELECT name,gender,MAX(count) AS popularity FROM BabyName WHERE year = '1983' AND gender = 'M' GROUP BY name,gender ORDER BY popularity DESC LIMIT 1)
UNION
(SELECT name,gender,MAX(count) AS popularity FROM BabyName WHERE year = '1983' AND gender = 'F' GROUP BY name,gender ORDER BY popularity DESC LIMIT 1);

#8 Show all the information available about names similar to your name (or the one you adopted from above), 
# sorted in alphabetical order by name, then, within that, by count, and, finally, by the year
SELECT DISTINCT name FROM BabyName WHERE name LIKE 'Long%' ORDER BY name,count,year;

#9 Show how many rows there are in the table.
SELECT COUNT(*) FROM BabyName;

#10 Show how many names are in the table for each sex from the year 1972
SELECT gender,COUNT(DISTINCT name) FROM BabyName WHERE year = '1972' GROUP BY gender;

#11 Show how many names there were in the year 1974.
SELECT year,COUNT(DISTINCT name) FROM BabyName WHERE year = '1974';