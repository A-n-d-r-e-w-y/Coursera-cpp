#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <sstream>
#include <algorithm>


using namespace std;


int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}


class Rational {
public:
	Rational();
	Rational(int numerator, int denominator);

	int Numerator() const;
	int Denominator() const;

	void SetNumDen(int numerator, int denominator);

private:
	int p;
	int q;
};


Rational::Rational()
{
	p = 0;
	q = 1;
}


Rational::Rational(int numerator, int denominator)
{
	SetNumDen(numerator, denominator);
}


int Rational::Numerator() const
{
	return p;
}

int Rational::Denominator() const
{
	return q;
}

void Rational::SetNumDen(int numerator, int denominator)
{
	if (denominator == 0)
	{
		throw invalid_argument("Invalid argument");
	}
	else
	{
		if (numerator == 0)
		{
			p = 0;
			q = 1;
		}
		else
		{
			int d = gcd(abs(numerator), abs(denominator));
			p = numerator / d;
			q = denominator / d;
			if (q < 0)
			{
				p = -p;
				q = -q;
			}
		}
	}
}


bool operator == (const Rational& lhs, const Rational& rhs)
{
	return (lhs.Numerator() == rhs.Numerator()) && (lhs.Denominator() == rhs.Denominator());
}


Rational operator + (const Rational& lhs, const Rational& rhs)
{
	return Rational(lhs.Numerator() * rhs.Denominator() + lhs.Denominator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator - (const Rational& lhs, const Rational& rhs)
{
	return Rational(lhs.Numerator() * rhs.Denominator() - lhs.Denominator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator * (const Rational& lhs, const Rational& rhs)
{
	return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator / (const Rational& lhs, const Rational& rhs)
{
	if (rhs.Numerator() == 0)
		throw domain_error("Division by zero");
	return Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator());
}


istream& operator >> (istream& stream, Rational& r)
{
	int numerator;
	int denominator;
	char c;
	stream >> numerator >> c >> denominator;
	if (stream && c == '/')
		r.SetNumDen(numerator, denominator);
	else
		throw invalid_argument("Invalid argument");
	return stream;;
}


ostream& operator << (ostream& stream, const Rational& r)
{
	stream << r.Numerator() << "/" << r.Denominator();
	return stream;
}


bool operator < (const Rational& lhs, const Rational& rhs)
{
	return lhs.Numerator() * rhs.Denominator() < lhs.Denominator() * rhs.Numerator();
}



int main() {

	try {
		Rational r1;
		cin >> r1;

		char operation;
		cin >> operation;

		Rational r2;
		cin >> r2;

		switch (operation)
		{
			case '+':
				cout << r1 + r2;
				break;
			case '-':
				cout << r1 - r2;
				break;
			case '*':
				cout << r1 * r2;
				break;
			case '/':
				cout << r1 / r2;
				break;
		}
	}
	catch (exception& ex) {
		cout << ex.what();
	}


	return 0;
}

