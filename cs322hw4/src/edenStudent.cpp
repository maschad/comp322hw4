#include "eden.h"

#include <stack>


/* Question 2 : getting an approximation using the new Fraction class */

Fraction<cf_int> ContinuedFraction::getApproximation(unsigned int k) const {
	Fraction <cf_int> toRet(1,0);
	stack<cf_int> ints;

	if(k==0){
		throw k;
	}

	Iterator *it = getIterator();
	while (!it->isDone() && k != 0) {
		ints.push(it->next());
		k--;
	}

	// do the math for adding an integer to a partial solution:
	// x + 1 / (n / d) = x + d / n = (x*n + d) / n
	while (!ints.empty()) {
		Fraction<cf_int> toAdd(ints.top() , 1);
		toRet.invert();
		toRet += toAdd;
		ints.pop();
	}

	return toRet;
}


/* Question 3 : Building a rational cf using the new Fraction class*/

RationalCF::RationalCF(Fraction<cf_int> f) {

	if(f.getDenominator() == 0){
		int toThrow = 0;
		throw toThrow;
	}
	cf_int t,t1;
	cf_int b = f.getDenominator();
	cf_int a = f.getNumerator();

	while( b != 0)
	{
		t = a/b;
		a-= t*b;
		t1 = a;
		a = b;
		b = t1;
		fixedPart.push_back(t);
	}
}

/* Question 4 : PeriodicCF iterator*/

Iterator *PeriodicCF::getIterator() const{
	return new PeriodicCFIterator(*this);
}

cf_int PeriodicCFIterator::next() {

	if(isDone()){
		throw -1;
	}

	auto iteratorPosition = it; //save previous position
	it++; // increment previous position
	if (iteratorPosition < cf.fixedPart.size()) { // if still in the fixed part
		return cf.fixedPart[iteratorPosition];
	}else { // if in the periodic part
		auto positionInPeriodic = (iteratorPosition - cf.fixedPart.size()) % cf.periodicPart.size();
		return cf.periodicPart[positionInPeriodic];
	}

}

bool PeriodicCFIterator::isDone() const {
	return cf.periodicPart.empty() && it >= cf.fixedPart.size(); // and done with the fixed part

}


/* Question 5 : MagicBoxCF iterator */

Iterator *MagicBoxCF::getIterator() const {
	return new MagicBoxCFIterator(boxedFraction->getIterator(),a,b);
}

cf_int MagicBoxCFIterator::next() {
	if(isDone()){
		double toThrow = -1;
		throw toThrow;
	}

	 cf_int q = i / k;
	    cf_int  ii = k,
	            jj = l,
	            kk = i - k * q,
	            ll = j - l * q;
	    i = ii;
	    j = jj;
	    k = kk;
	    l = ll;

	updateIndeces();
	return q;

}

bool MagicBoxCFIterator::isDone() const {
	return (boxedIterator->next() == NULL);
}


/* Question 6 : Euler squared */

Iterator *EulerSquared::getIterator() const {
	return new EulerSquaredIterator();

}


cf_int EulerSquaredIterator::next() {
	// [7 ; 2, 1, 1, 3, 18, 5, 1, 1, 6, 30, 8, 1, 1, 9, 42, 11, 1, 1 ...];
	if(index == 0){
		index++;
		return 7; // first item
	}
	if(index == 1) {
		index++;
		return 2; // second item
	}
	if(index % 5 == 2 || index%5 == 3) {
		index++;
		return 1; // all the 1s
	}
	if(index % 5 == 4){

		auto toRet = index/5 * 3 + 3; //3,6,9,12...etc
		index++;
		return toRet;
	}
	if(index % 5 == 0){

		auto toRet = index/5 * 12 + 6; // 18, 30, 42, etc...
		index++;
		return toRet;
	}
	auto toRet = index/5 * 3 + 2; // 5,8,11,14 etc....
	index++;
	return toRet;
}

bool EulerSquaredIterator::isDone() const {
	return false;// never done
}




