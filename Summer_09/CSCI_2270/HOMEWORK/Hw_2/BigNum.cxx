//Joe Becker
//810-07-1484
//July 20th, 2009
//CSCI 2270
//Elizableth White

#include "BigNum.h"
#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

namespace csci2270_hw2
{
	//Constructors and Destructors
	BigNum::BigNum( )
	{
		//default constructor that creates an array of Default capacity
		//(20), sets the first entry in the array to 0, puts used to 1
		//and sets positive to true. This is representive of the number
		//zero.
		capacity = DEFAULT_CAPACITY;
		digits = new size_t [capacity];
		digits[0] = 0;
		used = 1;
		positive = true;
	}
	
	BigNum::BigNum(int num)
	{
		//initalize used to zero as there is no current input	
		used = 0;
		
		//declaring and setting a temp variable to the input number 
		//("num")temp will be modified rather than modifying the acutal 
		//input number
		int temp;
		temp = num; 	
		
		//count the number of digits in "num" increase "used" for each 
		//digit
		while (temp != 0)
		{
			temp = temp / 10;
			++used;
		}
		
		//test if used is greater than the default size of array
		//if so make capacity equal to 10 more than used to be safe
		//if used is smaller than the default use the default capacity
		if (used > DEFAULT_CAPACITY) capacity = used + 10;
		else capacity = DEFAULT_CAPACITY;
	
		//declare the digits array	
		digits = new size_t [capacity];
	 
		//reset the temp variable to the absoulute of the input number
		//the sign is stored in the bool positive and isn't needed for
		//the input
		temp = abs(num); 
		
		//set the digits to the array
		for (size_t i = 0; i < used; ++i)
		{
			//set the last digit of "temp" to the array
			digits[i] = temp % 10; 
			//drop the last digit off of "temp" (temp is set to num
			//on line 48)
			temp = temp / 10;	
			
		}
		
		//this loop writes zeros to all other digits in the array to be safe
		for (size_t i = used; i < capacity; ++i)
		{
			digits[i] = 0;
		}

		//check if "num" is positive or negative and set 
		//"positive" to the correct value with zero as positive
		if (num >= 0) positive = true;
		else positive = false;

	}

	BigNum::BigNum(const char strin[])
	{
		used = strlen(strin); //set the used to the length of the string
	
		//bool to store if the string has a +/- symbol. Defaults to 
		//false.
		bool has_symbol = false;
		
		//default positive to true for the case where there is no +/-
		//symbol
		positive = true; 

		//look for a positive or negative symbol at the begining of the
		//string. If there is one set positive to refelect the symbol
		if (strin[0] == '-')
		{
			//negative symbol set to false
			positive = false;
			
			//since there is a symbol change "has_symbol" to true
			has_symbol = true;

			//remove the symbol from the used count
			used--;
		}

		if (strin[0] == '+')
		{
			//this is a bit redundent but since + symbol set 
			//positive to true
			positive = true;
			
			//since there is a symbol change "has_symbol" to true
			has_symbol = true;
			
			//remove the symbol from the used count
			used--;
		}

		//set a value for extraneous zeros in the begining of the string
		//default to zero	
		size_t zero_count = 0;
		
		if(has_symbol)
		{	
			//if there is a symbol we start looking for zeros one
			//char forward 
			for (size_t i = 1; strin[i] == '0'; ++i)
			{
				//for each zero we find we increase the 
				//zero_count by one
				zero_count++;
			}
		}else
		{	
			//for the case with no symbol we start looking for zeros
			//at the begining
			for (size_t i = 0; strin[i] == '0'; ++i)
			{
				//for each zero we find we increase the 
				//zero_count by one
				zero_count++;
			}
		}

		//remove the leading zeros from the used count	
		used -= zero_count;
			
		//test if used is greater than the default size of array
		//if so make capacity equal to 10 more than used to be safe
		//if used is smaller than the default use the default capacity
		if (used > DEFAULT_CAPACITY) capacity = used + 10;
		else capacity = DEFAULT_CAPACITY;
		
		digits = new size_t [capacity]; //declare the array
		
		if (has_symbol == true)
		{
			//for the case with a symbol we count fill the array 
			//digits backwards stopping befor the symbol
			for (int i = used - 1; i != -1; --i)
			{
				digits[i] = strin[used - i + zero_count] - '0';
			}
		}else
		{	
			//for the case w/out a symbol we fill the array normally
			//from the begining
			for (size_t i = 0; i < used; ++i)
			{	
				digits[i] = 
					strin[used - 1 - i + zero_count] - '0';	
			}	
		}
	}
	
	BigNum::BigNum(const BigNum& anotherBigNum)
	{
		capacity = 0; //set to a default capacity of zero
		digits = NULL; //prevent the = operator from trying to delete
		
		//call the '=' operator to copy 'anotherBigNum'
		*this = anotherBigNum; 

		
	}
	
	//Destructor
	BigNum::~BigNum()
	{
		delete [] digits; //delete the array "digits"
	}

	size_t BigNum::get_digit(size_t index) const
	{
		return digits[index]; //return the digit at index
	}
	
	void BigNum::set_digit(size_t digit, size_t index)
	{
		digits[index] = digit; //set the digit at index to 'digit'
	}

	void BigNum::set_used(size_t new_used)
	{
		used = new_used; //change the used
	}

	size_t BigNum::get_used() const
	{	
		return used; //return the value of 'used'
	}

	size_t BigNum::get_capacity() const
	{
		return capacity; //return the value of 'capacity'
	}

	bool BigNum::get_positive() const
	{
		return positive; //return the bool value of 'positive' 
	}

	void BigNum::set_positive(bool pos_or_neg)
	{
		//set the value of 'positive' to true or false
		positive = pos_or_neg; 
	}
	
	//The copy constructor	
	BigNum& BigNum::operator = (const BigNum& anotherBigNum)
	{
		if (this == &anotherBigNum)
		{
			return *this;
		}
		
		if (capacity < anotherBigNum.capacity)
		{
			if (digits != NULL) //don't delete a non declared digits
			{
				delete [] digits; //delete the current array
			}

			//set the capacity to "anotherBigNum" capacity
			capacity = anotherBigNum.capacity;
			digits = new size_t [capacity]; //declare a new array
	
		}
		
		//make the used equal
		used = anotherBigNum.used;

		//set the positives to be the same
		positive = anotherBigNum.positive;	


		//copy the "anotherBigNum" array into the new array
		for (size_t i = 0; i < used; ++i)
		{
			digits[i] = anotherBigNum.digits[i];			
		}
		
		//this loop writes zeros to all other digits in the array to be safe
		for (size_t i = used; i < capacity; ++i)
		{
			digits[i] = 0;
		}

		return *this; 
	}
	
	BigNum& BigNum::operator+=(const BigNum &addend)
	{
		//add the value of 'this' to the value of 'addend' and set it 
		//to 'this'. Then return 'this'
		*this = addend + *this;
		return *this;
	}

	BigNum& BigNum::operator-=(const BigNum &subtractand)
	{
		//subtract the value of 'this' to the value of 'subtractand' and set it 
		//to 'this'. Then return 'this'
		*this = *this - subtractand;
		return *this;
	}

	BigNum& BigNum::operator*=(const BigNum &multiplicand)
	{
		//multipy the value of 'this' to the value of 'multiplicand' and set it 
		//to 'this'. Then return 'this'
		*this =  *this * multiplicand;
		return *this;
	}

	BigNum& BigNum::operator/=(const BigNum &divisor)
	{
		//divide the value of 'this' to the value of 'multiplicand' and set it 
		//to 'this'. Then return 'this'
		*this = *this / divisor;
		return *this;
	}

	BigNum& BigNum::operator%=(const BigNum &divisor)
	{
		//mod the value of 'this' to the value of 'multiplicand' and set it 
		//to 'this'. Then return 'this'
		*this = *this % divisor;
		return *this;
	}

	BigNum& BigNum::BigNum::operator++()  // overload prefix increment
	{
		//add one to *this and set it to 'this'. Then return 'this'	
		*this = *this + 1;
		return *this;
	}

	BigNum& BigNum::operator--()  // overload prefix decrement
	{
		//subtract one from the total of 'this' and return 'this'
		*this = *this - 1;
		return *this;
	}
	
	BigNum BigNum::operator+(const BigNum &addend) const
	{	
		//declare a BigNum to store the sum of the added BigNums
		BigNum total; 
		
		//find which BigNum has the largest used and set 
		//it to total.used	
		if (used > addend.used) total.used = used;
		else total.used = addend.used;

		//resize the array with a capacity of total.used
		total.resize(total.used);
		
		//declare the digit_sum variable this will store the sum of 
		//the digits
		int digit_sum;
		//size_t digit_sum;
		
		//declare the carried_one variable this will store the carried
		//one if the sum of the digits is greater than 10
		size_t carried_one = 0;
		
		//test for the case where the first number is negative but the
		//2nd is not
		if ((!positive) && (addend.positive))
		{	
			//make a copy of this and make it positive
			BigNum positive_copy_this(*this);
			positive_copy_this.positive = true;
					
			//since adding a negative is the same as subtracting
			//subtract the BigNums from each other
			total = addend - positive_copy_this; 
			total.positive = false;
			return total;
		}

		//test for the case where the 2nd number is negative but the
		//first is not
		if ((positive) && (!addend.positive))
		{
			//make a copy of addend and make it positive
			BigNum positive_copy_addend(addend);
			positive_copy_addend.positive = true;
			
			//since adding a negative is the same as subtracting
			//subtract the BigNums from each other
			total = *this - positive_copy_addend; 
			total.positive = true;
			return total;
		}

		//for the case where both numbers are negative set 
		//total.positive to false but add them like normal
		if ((!positive) && (!addend.positive)) total.positive = false;	
	

		for(size_t i = 0; i < total.used; ++i)
		{
			//find the sum of the digits and the carried_one (if a
			//one is carried)
			digit_sum = digits[i] + addend.digits[i] + carried_one;

			//get the last digit of the digit_sum and set it to the
			//total array
			total.digits[i] = digit_sum % 10;
			
			//test if the digits add to more than 10. If this is the
			//case then carry one by setting the carried_one to one
			if(digit_sum >= 10)
			{
				carried_one = 1;
				
				//this line tests to see if we are on the last
				//or highest digit. If so we need to increase
				//the used to account for the extra place when
				//the sum is greater than 10
				if (i == total.used - 1) 
				{
					total.used++;
				}
				
			}	
			else carried_one = 0;
		}
	
		//return the value of the sum
		return total;
	}	

	BigNum BigNum::operator-(const BigNum &subtractand) const
	{
		//declare a BigNum that will store the difference between the
		//two BigNums
		BigNum difference;
	
		//test to see which BigNum has the largest used and set the used
		//of the difference to the larger of the 2	
		if (used > subtractand.used) difference.used = used;
		else difference.used = subtractand.used;
		

		//for the case a - (-b) = a + b
		if ((positive) && (!subtractand.positive))
		{
			//create a copy of the BigNum subtractand and make it
			//positive by setting positive equal to true
			BigNum positive_subtractand_copy(subtractand);
			positive_subtractand_copy.positive = true;
		
			//add the two BigNums and return the value	
			difference = *this + positive_subtractand_copy;
			return difference;	
		}

		//for the case (-a) - b = -(a + b)
		if ((!positive) && (subtractand.positive))
		{
			//create a copy of the BigNum *this and make it
			//positive by setting positive equal to true
			BigNum positive_this_copy(*this);
			positive_this_copy.positive = true;
			

			//add the two BigNums
			difference = positive_this_copy + subtractand;
			
			//set the difference positive to false to reflect that
			//the difference equals the NEGATIVE sum of the 
			//two BigNums
			difference.positive = false;
		
			return difference; //return BigNum difference
			
		}
		
		//test for the case where both BigNums are negative. 
		if ((!positive) && (!subtractand.positive))
		{
			if (*this < subtractand)
			{ 
				//for the case (a - b) where 
				//(+a) > (+b) or (-a) < (-b)
				//continue with normal subtraction but with
				//positive set to false
				//(-a) - (-b) = -(a - b)
				difference.positive = false;	
			}else
			{	
				//for the case of (a - b) where 
				//(+a) < (+b) or (-a) > (-b)
				//the subtraction has to be reversed because the
				//for loop that does the subraction cannot 
				//correctly borrow one unless (+a) > (+b)
				difference = subtractand - *this;
				
				//set difference.positive to true because we
				//reversed a negative making it positive
				//(-a) - (-b) = - -(b - a) = +(b - a)
				difference.positive = true;
				return difference; //return BigNum differnce
			}

		//this if statement is redundent because the cases where 
		//one BigNum is positive and the other isn't are already tested
		//for and return a BigNum difference. This if statement is just
		//for extra rigour and clarity
		}else if ((positive) && (subtractand.positive))
		{
			if (*this >= subtractand)
			{ 
				//for the case (a - b) where a is greater than b
				//and 'a' and 'b' are both positive the 
				//difference is positive
				difference.positive = true;	
			}else
			{	
				//for the case where a is less than b the 
				//variables need to be swiched due to 
				//precondition of 'a' > 'b'
				difference = subtractand - *this;
				
				//the actual difference is the negative of the
				//flipped subtraction
				difference.positive = false;
				return difference; //return BigNum difference
			}
		}
		
		//create a variable that will store the borrowed one needed for
		//subtraction. initially zero.
		size_t borrowed_one = 0;

		//declare a variable that will store the difference in the 
		//digits this is an int instead of size_t to allow the
		//digit difference to drop below 0. 
		int digit_diff;

		for(size_t i = 0; i < difference.used; ++i)
		{
			//set 'digit_diff' to the difference between the two 
			//digits taking into account for a borrowed one from the
			//previous run of the loop
			digit_diff = digits[i] - borrowed_one 
					       - subtractand.digits[i];

			//check if the digit diff is below zero or if
			//'subtractand.digits[i]' was greater than 'digits[i]'
			if (digit_diff < 0)
			{
				//borrow one from the next place up by adding 10
				//to the difference
				digit_diff += 10;

				//account for the borrowed one from the next 
				//place up this is set last so that it 
				//only affects the next loop
				borrowed_one = 1;
				
			}else
			{	
				//set the borrowed one to zero since no one was
				//borrowed. This is set last for the next loop
				//and so it doesn't affect the curent loop there
				//is no need to adjust digit_diff
				borrowed_one = 0;
			}
			
			//set the difference digit to the digit difference found
			//in the loop
			difference.digits[i] = digit_diff;
		}

		//this loop checks for leading zeros after the subtraction if it finds
		//any then it will lower 'difference.used' by one	
		for (int i = difference.used - 1; difference.digits[i] == 0; --i)
		{
			--difference.used;
		}
		
		return difference;
	}

	BigNum BigNum::operator*(const BigNum &multiplicand) const
	{
		//create a BigNum that will store the poduct of the two BigNums
		BigNum product;	
		
		//sub_product will store the single digit multiplication for
		//example abc * de 'sub_product' will store the value abc * e
		BigNum sub_product;	

		//cange the capacity of the newily declared BigNums to fit the sum of 
		//both useds
		product.resize(used + multiplicand.used);
		sub_product.resize(used + multiplicand.used);

		//set the product and sub_ product used to the sum of the two 
		//BigNum's used as the number of digits of the product will be 
		//the sum of all the digits
		product.used = used + multiplicand.used;
		sub_product.used = used + multiplicand.used;

		//for the cases where one of the BigNums is positive and the 
		//the other is negative the product is negative so set 
		//product.positive to false
		if ((!positive) && (multiplicand.positive)) 
		{
			product.positive = false;
		}
		if ((positive) && (!multiplicand.positive)) 
		{
			product.positive = false;
		}

		//for the case where both BigNums are negative the product is
		//positve so set product.positive to true
		if ((!positive) && (!multiplicand.positive)) 
		{
			product.positive = true;
		}


		//declare a variable that will store the product of the digits
		//and the carried tens
		size_t digit_product;		

		//declare a variable that will store the tens place of the digit
		//product
		size_t carried_tens = 0;

		//declare a variable that keeps track of what position of the
		//sub_product.digits array we are in
		size_t sub_counter;
		
		//this for loop runs through all the multiplicand.digits array
		for (size_t i = 0; i < multiplicand.used; ++i)
		{
			//set and reset sub_counter back to start
			sub_counter = 0; 
			
			//reset the carried tens to zero for the next digit of this
			carried_tens = 0;
	
			//for each every 'i' we increase what we are multiplying
			//by a power of 10 we account for this by moving the
			//digits up on and placing a zero in there place
			for(size_t k = 0; k < i; ++k)
			{
				//add zero to the first 'i' places in digits
				sub_product.digits[sub_counter] = 0;
				
				//move the counter up to the next place in 
				//the array 'sub_product.digits'
				sub_counter++;
			}

			//this loop multiplies one digit of multiplicand with
			//the digits of 'this'
			for (size_t j = 0; j < used; ++j)
			{
				
				//calculate digit_product by multiplying the 
				//digits together and adding any carried ten
				digit_product = digits[j] 
						* multiplicand.digits[i]
						+ carried_tens; 

				//set the sub_product.digit to the ones place
				//of digit_product
				sub_product.digits[sub_counter] 
							= digit_product % 10;
	
				//set the carried ten to the tens place of 
				//digit_product
				carried_tens = digit_product / 10;
			
				//for the last digit of the multiplication it adds the carried
				//tens to the next spot of sub_product to account for the next
				//place that wont be run in the loop
				if (j == used - 1)
				{
					sub_product.digits[sub_counter + 1] = digit_product / 10;
				}	
				//move on to the next place in 
				//sub_product.digits
				sub_counter++;
				
			}
			//add the sub_product to the overall total product	
			product += sub_product;
		}
	
		//this loop checks for leading zeros after the multiplication if it 
		//finds any then it will lower 'product.used' by one	
		for (int i = product.used - 1; product.digits[i] == 0; --i)
		{
			--product.used;
		}
	
		return product; //return the total product
	}

	BigNum BigNum::operator/(const BigNum &divisor) const
	{
		//Declare a BigNum quotient to store the value of the quotient
		//between 'this' and 'divisor'
		BigNum quotient;
		BigNum copy_this(*this);
		BigNum copy_divisor(divisor);
	
		//for the cases where one BigNum is positive and the other is
		//negative the quotient is negaitve. So 'quotient.positive = false'	
		if((positive) && (!divisor.positive)) 
		{
			quotient.positive = false;
			
			//the positive of the copy is set to true to meet the while loop's
			//precondition of both BigNums are positive. The sign is taken into
			//account
			copy_divisor.positive = true;
		}
		if((!positive) && (divisor.positive))
		{
			quotient.positive = false;
			//the positive of the copy is set to true to meet the while loop's
			//precondition of both BigNums are positive. The sign is taken into
			//account
			copy_this.positive = true;
		}
		
		//for the case where both BigNums are negative the quotient is positive
		//so set 'quotient.positive to true
		if((!positive) && (!divisor.positive)) 
		{
			quotient.positive = true;
			
			//the positive of both copies is set to true to meet the while loops
			//precondition of both BigNums are positive. The signs are taken 
			//into account
			copy_this.positive = true;
			copy_divisor.positive = true;
		}

		
		//this loop subtracts the divisor from the copy of this. For every time
		//divisor is subtracted the BigNum quotient counts up one. The loop
		//stops when the difference between the copy of this and divisor drops
		//below or equals zero
		//both BigNums must be positive
		while ((copy_this - copy_divisor) >= 0)
		{
			copy_this -= copy_divisor;
			++quotient;
		}
		
		return quotient; //return the value of quotient
	
	}

	BigNum BigNum::operator%(const BigNum &divisor) const
	{
		//declare a BigNum called remainder that is a copy of 'this'
		BigNum remainder(*this);
		//declare a copy of the BigNum divisor
		BigNum copy_divisor(divisor);
	

		//set both BigNum copies to meet the precondition of the loop	
		remainder.positive = true;
		copy_divisor.positive = true;
				
		//this loop subtracts the divisor from 'remainder' untill the difference
		//drops to or below zero. Both BigNums positive must equal true
		while ((remainder - copy_divisor) >= 0)
		{
			remainder -= copy_divisor;
		}
		
		//for the case where one this is negative and divisor is positive set
		//remainder.positive to false
		if((!positive) && (divisor.positive)) remainder.positive = false;
		
		//for the case where one this is positive and divisor is negative set
		//remainder.positive to false
		if((positive) && (!divisor.positive)) remainder.positive = true;

		//for the case where both BigNums are negative the negative carries
		//with mod so remainder.positive is set to false
		if((!positive) && (!divisor.positive)) remainder.positive = false;

		//the value of remainder after the loop runs is the value of mod so 
		//return remainders
		return remainder;
	}

	bool BigNum::operator>(const BigNum &anotherBigNum) const
	{	
		//if they equal than this is not greater than so return false
		if (*this == anotherBigNum) return false;
		
		//if 'this' is positive and anotherBigNum is not for all numbers
		// this is greater so return true
		if ((positive) && (!anotherBigNum.positive)) return true;

		//if 'this' is negative and anotherBigNum is positive for all
		//numbers this is less than so return false
		if ((!positive) && (anotherBigNum.positive)) return false;
		
		
		//for the case where both numbers are positive
		if ((positive) && (anotherBigNum.positive))
		{
			if (used == anotherBigNum.used)
			{	
				//this loop starts with the largest digit or 
				//place and goes to the smallest 
				for (int i = used - 1; i != -1; --i)
				{
					//if the largest place's value is
					//greater then this is greater
					if (digits[i] > anotherBigNum.digits[i])
					{
					return true;
					}
					//is the largest place's value is less
					//then this is less
					if (digits[i] < anotherBigNum.digits[i])
					{
					return false;
					}
				} 	
			
			//if this.used is greater than anotherBigNum.used then
			//this must be greater. The oppisite is true as well
			//for the equal case is the if to this else statement
			}else return (used > anotherBigNum.used);
		}
		
		//the algorithom is almost the same as when both are positive
		//the difference is the all the less thans become greater thans
		//and vise versa
		if ((!positive) && (!anotherBigNum.positive))
		{
			if (used == anotherBigNum.used)
			{
				//this loop starts with the largest digit or 
				//place and goes to the smallest 
				for (int i = used - 1; i != -1; --i)
				{	
					//if this' highest placed digit is 
					//SMALLER than anotherBigNum then it
					//must be greater
					if (digits[i] < anotherBigNum.digits[i])
					{
					return true;
					}

					//if this' highest placed digit is 
					//BIGGER than anotherBigNum then it
					//must be less.
					if (digits[i] > anotherBigNum.digits[i])
					{
					return false;
					}
				} 	
			
			//if this.used is less than anotherBigNum.used then
			//this must be greater (smaller negative number). 
			//The oppisite is true as well for the equal case is 
			//the if to this else statement
			}else return (used < anotherBigNum.used);
		}
			
		//there should be no way to get to this point but to be safe
		//if the program makes it here it returns false
		return false;
	}

	bool BigNum::operator>=(const BigNum &anotherBigNum) const
	{
		//if they equal than then less than equal is true
		if (*this == anotherBigNum) return true;
		
		//if they don't equal the only way it can be true is if it is
		//greater than so return greater than
		return (*this > anotherBigNum);
	}

	bool BigNum::operator<(const BigNum &anotherBigNum) const
	{
		//if they equal than this is not less than so return false
		if (*this == anotherBigNum) return false;
		
		//if they do not equal then the if this is greater than 
		//anotherBigNum then it is not less than so return the oppisite
		//of greater than
		return !(*this > anotherBigNum);
	}
	
	bool BigNum::operator<=(const BigNum &anotherBigNum) const
	{
		//if they equal than then less than equal is true
		if (*this == anotherBigNum) return true;
		
		//if they don't equal the only way it can be true is if it is
		//greater than so return greater than
		return (*this > anotherBigNum);
	}

	bool BigNum::operator==(const BigNum &anotherBigNum) const
	{
		//if one BigNum is negative and the other isnt then they do not
		//equal so return false
		if ((positive) && (!anotherBigNum.positive)) return false;
		if ((!positive) && (anotherBigNum.positive)) return false;
		
		//if the used are not the same then they are not equal
		if (used != anotherBigNum.used) return false;

		//for each digit check if the digits do not equal if they do
		//return false
		for (size_t i = 0; i < used; ++i)
		{
			if (digits[i] != anotherBigNum.digits[i]) return false;
		}
		
		//if it passes all the tests then they must be equal so return
		//true	
		return true;
	}
		
	bool BigNum::operator!=(const BigNum &anotherBigNum) const
	{	
		//this one was easy just return the oposite of the '==' operator
		return !(*this == anotherBigNum);
	}
	
	BigNum BigNum::factorial() const
	{
		//Create a big num that is equal to 1 so when it is multiplied with 
		//we are not multiplying by the default of zero
		BigNum total = 1;
		
		//create a BigNum copy of 'this'. This BigNum will be subtracted from
		
		BigNum copy_this(*this);

		//this loop is the factorial. It multiplies copy_this with 1 initaily 
		//then with just the total. Then it removes one from copy_this
		while (copy_this > 0)
		{
			total *= copy_this;
			--copy_this;
		}
		
		return total; //return the total value
	}
	
	// FRIEND FUNCTIONS
	ostream& operator << (ostream &os, const BigNum &bignum)
	{
		if (bignum.positive == false) 
			os << '-';

		//This for loop loops backwards from used -1 to 0. When i = -1
		//the loop ends leaving digits[0] as the last digit to be writen
		for (int i = bignum.used - 1; i != -1; --i)
		{
			os << bignum.digits[i];
		}
		
		return os;
	}

	istream& operator>>(istream &is, BigNum &bignum)
	{	
		
		string input; //create string input to store the user input 
		is >> input; //read input from is and write to input

		bignum = input.c_str(); //call BigNum string constructor
		
		return is; 
	}

	void BigNum::resize(size_t n)  
	{		
			//test if the input capacity is smaller than the current. If so 
			//retrun; 
			if (n <= capacity) return;
			
			//set capacity to equal n
			capacity = n;
		
			//declare a new array of size capacity which is now set to n	
			size_t * new_digits = new size_t [capacity];
		
			//copy all the digits from the array digits to the new digits array	
			for (size_t i = 0; i < used; ++i)
			{	
				new_digits[i] = digits[i];	
			}

			//write zeros to the rest of the array from used to capacity
			for (size_t i = used; i < capacity; ++i)
			{
				new_digits[i] = 0;
			}

			if (digits != NULL) //don't delete a non declared digits array
			{
				delete [] digits; //delete the current array
			}
			
			//create a new array 'digits' of size capacity
			digits = new size_t [capacity]; 
			//copy new_digits back onto digits
			digits = new_digits;
	}

	BigNum BigNum::diff(const BigNum &subtractand) const
	{
		//declare a BigNum to store the difference
		BigNum difference;
		
		//subtract the difference from this and subtractand
		difference = *this - subtractand;

		return difference; //return the difference
	}

	BigNum BigNum::sum(const BigNum &addend) const
	{
		//declare a BigNum to store the sum
		BigNum sum;

		//add this and addend
		sum = *this + addend;

		return sum; //return the value of sum
	}

}
