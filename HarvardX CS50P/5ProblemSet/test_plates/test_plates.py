"""
In a file called plates.py, reimplement Vanity Plates from Problem Set 2, restructuring your code per the below, wherein is_valid still expects a str as input and returns True if that str meets all requirements and False if it does not, 
but main is only called if the value of __name__ is "__main__"

Then, in a file called test_plates.py, implement four or more functions that collectively test your implementation of is_valid thoroughly, each of whose names should begin with test_ so that you can execute your tests with:

pytest test_plates.py
"""

import plates

def test_is_valid():
    assert(plates.is_valid("CS50") == True)
    assert(plates.is_valid("CS05") == False)
    assert(plates.is_valid("CS50P") == False)
    assert(plates.is_valid("PI3.14") == False)
    assert(plates.is_valid("H") == False)
    assert(plates.is_valid("OUTATIME") == False)

def test_is_minimum_two_characters():
    assert(plates.is_minimum_two_characters("CS50") == True)
    assert(plates.is_minimum_two_characters("C") == False)
    assert(plates.is_minimum_two_characters("AB") == True)
    assert(plates.is_minimum_two_characters("1") == False)

def test_is_first_number_a_zero():
    assert(plates.is_first_number_a_zero("CS50") == False)
    assert(plates.is_first_number_a_zero("CS05") == True)
    assert(plates.is_first_number_a_zero("ABCD1325") == False)
    assert(plates.is_first_number_a_zero("ABCD0325") == True)

def test_is_number_in_middle():
    assert(plates.is_number_in_middle("A56C13E") == True)
    assert(plates.is_number_in_middle("ABCD50E") == True)
    assert(plates.is_number_in_middle("ABCD500") == False)
    assert(plates.is_number_in_middle("ABCDEF0") == False)

def test_is_special_character():
    assert(plates.is_special_character("AB@E512") == True)
    assert(plates.is_special_character("ABE#51!") == True)
    assert(plates.is_special_character("AB2E512") == False)
    assert(plates.is_special_character("ABE3511") == False)