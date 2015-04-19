
/* QUESTION 1 - 0 credit */

/* We will build a general fraction class using templates provide code for all methods listed as TODO*/

#ifndef hw4_fraction_h
#define hw4_fraction_h

#include <iostream>

template<typename T>
class Fraction {
private:
	T numerator;
	T denominator;

	void update(T num, T den) {
		if(num == 0 && den == 0) throw 0;
		else { denominator = den; numerator = num; }
		if(num == 0) denominator = 1;
		if(den == 0) numerator = 1;
	}
public:
	Fraction(T num, T den): numerator{num}, denominator{den} {
		update(num, den);
	}
	Fraction(T num) : numerator{num}, denominator{1} {}
	Fraction(const Fraction &f) : numerator{f.numerator}, denominator{f.denominator} { }

	//-- returns the numerator
	T getNumerator() const{
		return numerator;
	}

	//-- returns the denominator
	T getDenominator() const{
		return denominator;
	}

	//-- inverts the fraction: swaps denominator and numerator
	Fraction &invert() {
		int temp;
		temp = this->numerator;
		numerator = this->denominator;
		this->denominator = temp;
		return this;

	}

	//-- adds the fraction f to the current fraction a/b + c/d = (a*d + b*c) / (b*d) (don't simplify!)
	Fraction &operator+=(const Fraction &f) {
		if(this->denominator == f.denominator){
			this->numerator+= f.numerator;
			return this;
		}
		else{

			int tempNum,tempDenum;
			tempNum = this->numerator;
			this->numerator = this->numerator * f.denominator;
			tempDenum = this->denominator;
			this->denominator = this->denominator * f.numerator;

			this->numerator += (f.numerator*tempNum);
			this->denominator += (f.denominator*tempDenum);

			return this;
		}
	}

	//-- adds the fraction f to the current fraction a/b + c/d = (a*d + b*c) / (b*d) (don't simplify!)
	Fraction operator+(const Fraction &f) const {
		Fraction result;
		if(this->denominator == f.denominator){
			result.numerator = this->numerator + f.numerator;
			return result;
		}
		else{
			int tempNum,tempDenum;
			tempNum = this->numerator;
			tempDenum = this->denominator;
			this->numerator = this->numerator * f.denominator;
			this->denominator = this->denominator * f.numerator;
			f.numerator = tempNum * f.numerator;
			f.denominator = tempDenum * f.denominator;

			result.numerator = f.numerator + this->numerator;
			result.denominator = this->denominator;

			return result;

		}


	}

	//-- subtracts the fraction f from the current fraction a/b - c/d = (a*d - b*c) / (b*d) (don't simplify!)
	Fraction &operator-=(const Fraction &f) {
		if(this->denominator == f.denominator){
			this->numerator-= f.numerator;
			return this;
		}
		else{

			int tempNum,tempDenum;
			tempNum = this->numerator;
			this->numerator = this->numerator * f.denominator;
			tempDenum = this->denominator;
			this->denominator = this->denominator * f.numerator;

			this->numerator -= (f.numerator*tempNum);
			this->denominator -= (f.denominator*tempDenum);

			return this;
		}
	}

	//-- subtracts the fraction f from the current fraction a/b - c/d = (a*d - b*c) / (b*d) (don't simplify!)
	Fraction operator-(const Fraction &f) const {

		Fraction result(f);

		if(this->denominator == f.denominator){
			result.numerator = this->numerator - f.numerator;
			return result;
		}
		else{
			result.numerator = (numerator * f.denominator) - (denominator * f.numerator);
			result.denominator = denominator * f.numerator;
		}

		return result;
	}

	//-- multiplies the fraction f to the current fraction a/b * c/d = (a*c) / (b*d) (don't simplify!)
	Fraction operator*(const Fraction &f) const {

		Fraction result(f);

		result.numerator = numerator * f.numerator;
		result.denominator = denominator * f.denominator;

		return result;

	}

	//-- divides the current fraction by f: (a/b) / (c/d) = (a*d) / (b*c) (don't simplify!)
	Fraction operator/(const Fraction &f) const {
			Fraction result(f);

			result.numerator = numerator * f.denominator;
			result.denominator = denominator * f.numerator;

			return result;

	}

	//-- compares the current fraction to f.
	// * If both denominators are 0, return true (they are both infinity)
	bool operator==(const Fraction &f) const {
		if(f.denominator == denominator && f.numerator == f.numerator){
			return true;
		}

		if((f.numerator/f.denominator) == (numerator/denominator)){
			return true;
		}

		return false;
	}

	//-- compares the current fraction to f for inequality.  use == above!!
	bool operator!=(const Fraction &f) const {
		return !( *this == f);
	}

	T quotient() const {
		if (denominator == 0 ) throw 1;
		return numerator / denominator;
	}

	void simplify() {
		if( numerator == denominator) {
			numerator = denominator = 1;
			return;
		}

		T &smaller = ( numerator < denominator ) ? numerator : denominator;
		// try all possible factors and simplify as long as possible
		for(T factor = 2; factor <= smaller; (factor == 2) ? factor++ : factor += 2) {
			while(numerator % factor == 0 && denominator % factor == 0) {
				numerator /= factor;
				denominator /= factor;
			}
		}
	}

	friend std::ostream& operator<<( std::ostream& os, const Fraction& f ) {
		os << "(" << f.numerator << "/" << f.denominator << ")";
		return os;
	}
};


#endif
