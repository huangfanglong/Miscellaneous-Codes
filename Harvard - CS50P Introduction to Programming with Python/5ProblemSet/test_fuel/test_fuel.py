"""
In a file called fuel.py, reimplement Fuel Gauge from Problem Set 3, restructuring your code per the below, wherein:

convert expects a str in X/Y format as input, wherein each of X and Y is an integer, and returns that fraction as a percentage rounded to the nearest int between 0 and 100, inclusive. 
If X and/or Y is not an integer, or if X is greater than Y, then convert should raise a ValueError. If Y is 0, then convert should raise a ZeroDivisionError.
gauge expects an int and returns a str that is:
"E" if that int is less than or equal to 1,
"F" if that int is greater than or equal to 99,
and "Z%" otherwise, wherein Z is that same int.
"""
import fuel

def test_convert():
    assert(fuel.convert("1/4") == 25)
    assert(fuel.convert("3/4") == 75)
    assert(fuel.convert("5/10") == 50)
    assert(fuel.convert("6/74") == 8)

def test_gauge():
    assert(fuel.gauge(25) == "25%")
    assert(fuel.gauge(75) == "75%")
    assert(fuel.gauge(50) == "50%")
    assert(fuel.gauge(8) == "8%")
    assert(fuel.gauge(1) == "E")
    assert(fuel.gauge(99) == "F")