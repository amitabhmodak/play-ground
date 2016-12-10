#pragma once

#include<iostream>
using namespace std;


class PayLoad
{
public:
	int value = 0;

	PayLoad() = default;

	PayLoad(int val) {
		value = val;
	}
	~PayLoad() = default;// { cout << "PayLoad with value " << value << " deleted\n"; }

	ostream &operator<<(ostream &output) {
		output << value << " ";
		return output;
	}
	operator int() { return value; }
};

