
// FILENAME: BigNum.h
// This is the definition of BigNum class.

// CONSTRUCTORS and DESTRUCTORS for BigNum class
//   BigNum() : Default constructor for BigNum class. A positive BigNum with default value 0
//      is created after this constructor.
//   BigNum(int num) : A BigNum with the same value and sign as num is created after this function.
//   BigNum(const char string[]) : A BigNum with the corresponding interger value of string[] is
//      created after this function.
//    ~BigNum() : Dynamic memory allocated for the BigNum is released after this function.
//
// PUBLIC MEMBER FUNCTIONS of BigNum class:
//    BigNum& operator=(const BigNum &anotherBigNum) : The BigNum has been assigned the same value
//       with anotherBigNum after this function is executed.
//
//    BigNum& operator+=(const BigNum &addend) : Addend has been added to this BigNum after this
//       function is executed.
//
//    BigNum& operator-=(const BigNum &subtractand) : Subtractand has been subtracted from this 
//       BigNum after this function is executed.
//
//    BigNum& operator*=(const BigNum &multiplicand) : This BigNum has been multiplied by multiplicand 
//       and the result is stored in this BigNum after this function  is executed.
//
//    BigNum& operator/=(const BigNum &divisor) : This BigNum has been dividied by divisor and the
//       result has been stored in this BigNum after this function is executed.
//
//    BigNum& operator%=(const BigNum &divisor) : This BigNum has been taken modulus by divisor and 
//       the result has been stored in this BigNum after this function is executed.
//    
//    BigNum& operator++() : This BigNum has been incremented by 1 after this function is executed.
//
//    BigNum& operator--() : This BigNum has been decremented by 1 after this function is executed.
//
//    BigNum operator+(const BigNum &addend) : The result of the addition of this BigNum and addend
//       has be returned after this function is executed and neither this BigNum nor addend has been
//       changed.
//
//    BigNum operator-(const BigNum &subtractand) : This BigNum has been subtracted by subtractand and 
//       neither this BigNum nor subtratcand has been changed and the result has been returned after 
//       this function is executed. 
//
//    BigNum operator*(const BigNum &multiplicand) : This BigNum has been multilpied by multiplicand and
//       neither this BigNum nor multipilcand has been changed and the result has been returned after 
//       this function is executed.
//
//    BigNum operator/(const BigNum &divisor) : This BigNum has been divided by divisor and neither this
//       BigNum nor divisor has been changed and the result has been returned after this function 
//       is executed.
//   
//    BigNum operator%(const BigNum &divisor) : This BigNum has been taken modulus by divisor and neither
//       this BigNum nor divisor has been changed and the result has been returned after this function
//       is executed.
//
//    bool operator>(const BigNum &anotherBigNum) : True will be returned if this BigNum is bigger than
//       anotherBigNum, otherwise false will be returned.
//
//    bool operator>=(const BigNum &anotherBigNum) : True will be returned if this BigNum is bigger than
//       or equal to anotherBigNum, otherwise false will be returned.
//
//    bool operator<(const BigNum &anotherBigNum) :  True will be returned if this BigNum is smaller than
//       anotherBigNum, otherwise false will be returned.
//
//    bool operator<=(const BigNum &anotherBigNum) :  True will be returned if this BigNum is smaller than
//       or equal to anotherBigNum, otherwise false will be returned.
//
//    bool operator==(const BigNum &anotherBigNum) :  True will be returned if this BigNum is equal to 
//       anotherBigNum, otherwise false will be returned.
//
//    bool operator!=(const BigNum &anotherBigNum) : True will be returned if this BigNum is not equal to
//       anotherBigNum, otherwise false will be returned.
//
//    BigNum factorial() : Factorial of this BigNum has been returned after this function is executed.
//
//    size_t get_used() const : Length of this BigNum has been returned after this function is executed.
//
//    size_t get_capacity() const : Size of the memory allocated for this BigNum has been returned after this 
//       function is executed.
//    
// Private MEMBER FUNCTIONS of BigNum class:
//    void  resize(size_t n) : Size of the memory allocated for this BigNum has been changed to n
//      after this function is executed. If n is smaller than the length of this BigNum, this BigNum
//      will not be resized.
//           
//    BigNum  diff(const BigNum &subtractand) : Precondition is that both this BigNum 
//      and subtractand are positive, and also that this BigNum >= subtractand. The result of subtraction has been retuned after this function 
//      is executed.
//
//    BigNum sum(const BigNum &addend) :  Precondition is that both this BigNum
//      and addend are positive. The result of addition has been retuned after this function is executed.
//
//  FERIEND FUNCTIONS of BigNum class:
//    friend std::ostream& operator<<(std::ostream &os, const BigNum &bignum) : This bignum has been
//      output to the console after this function is executed.
//
//    friend std::istream& operator>>(std::istream &is, BigNum &bignum) : This BigNum entered from the
//      console has been stored in bignum after this function is executed.
//



#ifndef HW2_BIGNUM_H
#define HW2_BIGNUM_H
#include <cstdlib>  // Provides size_t
#include <iostream> // Provides istream and ostream

namespace csci2270_hw2
{
    class BigNum 
    {
    public:
	
	// CONSTRUCTORS and DESTRUCTORS
	BigNum();                            
	BigNum(int num);                         
	BigNum(const char strin[]);
	BigNum(const BigNum& anotherBigNum);  
	~BigNum();
	
	// MEMBER FUNCTIONS
	size_t get_digit(size_t index) const;
	void set_digit(size_t digit, size_t index);
	void set_used(size_t new_used);
	size_t get_used() const;
	size_t get_capacity() const;
	bool get_positive() const;
	void set_positive(bool pos_or_neg);
	
	BigNum& operator=(const BigNum &anotherBigNum);
	BigNum& operator+=(const BigNum &addend);
	BigNum& operator-=(const BigNum &subtractand);
	BigNum& operator*=(const BigNum &multiplicand);
	BigNum& operator/=(const BigNum &divisor);
	BigNum& operator%=(const BigNum &divisor);
	BigNum& operator++();  // overload prefix increment
	BigNum& operator--();  // overload prefix decrement
	
	
        BigNum operator+(const BigNum &addend) const;
	BigNum operator-(const BigNum &subtractand) const;
	BigNum operator*(const BigNum &multiplicand) const;
	BigNum operator/(const BigNum &divisor) const;
	BigNum operator%(const BigNum &divisor) const;
	bool operator>(const BigNum &anotherBigNum) const;
	bool operator>=(const BigNum &anotherBigNum) const;
	bool operator<(const BigNum &anotherBigNum) const;
	bool operator<=(const BigNum &anotherBigNum) const;
	bool operator==(const BigNum &anotherBigNum) const;
	bool operator!=(const BigNum &anotherBigNum) const;
	BigNum factorial() const;
	
	// FRIEND FUNCTIONS
	friend std::ostream& operator<<(std::ostream &os, const BigNum &bignum);
	friend std::istream& operator>>(std::istream &is, BigNum &bignum);
  private:
	size_t *digits;         // Pointer to the array of BigNum digits 
	bool positive;             // Indicates the sign of BigNum (true for positive, false for negative)
	size_t used;           // Length of the array for BigNum Digits  
	size_t capacity;        // Size of the memory allocated for tis BigNum 
	void          resize(size_t n);  
	BigNum        diff(const BigNum &subtractand) const;
	BigNum        sum(const BigNum &addend) const;
	static const size_t DEFAULT_CAPACITY = 20;
    };
}
#endif

