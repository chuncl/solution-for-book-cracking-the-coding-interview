//Given a(decimal - e.g. 3.72) number that is passed in as a string, print the binary representation.If the number can not be represented accurately in binary, print “ERROR”.

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <cassert>
using namespace std;

string print_binary(double value) {
	// get string from double value
	stringstream ss;
	ss << value;
	string input = ss.str();
	size_t pos = input.find(".");
	assert(pos != string::npos);

	// get left part integer value and right part decimal value
	int leftV = atoi(input.substr(0, pos).c_str());
	double rightV = atof(input.substr(pos, input.length() - pos).c_str());

	// get int part string, by comparing LSB and move right bit by bit
	string leftStr, rightStr;
	while (leftV > 0) {
		if (leftV & 1) 
			leftStr += "1";			
		else 
			leftStr += "0";
		leftV >>= 1;
	}
	
	// get decimal part string, by mulptiply 2 and comparing with 1
	while (rightV > 0) {
		if (rightStr.length() > 32) {
			return "ERROR";
		}
		rightV *= 2;
		if (rightV >= 1) {
			rightStr += "1";
			rightV -= 1;
		}
		else
			rightStr += "0";
	}

	return leftStr + "." + rightStr;

}

string print_binary2(double value) {
	stringstream ss;
	ss << value;
	string input = ss.str();
	size_t pos = input.find(".");
	assert(pos != string::npos);
	int leftV = atoi(input.substr(0, pos).c_str());
	double rightV = atof(input.substr(pos, input.length() - pos).c_str());

	// get int part string, by take mode of 2 and then divid by 2
	string leftStr, rightStr;
	while (leftV > 0) {
		if (leftV % 2)
			leftStr += "1";
		else
			leftStr += "0";
		leftV /= 2;
	}

	// get int part string, by comparing with 0.5, 0.25..so on
	double factor = 0.5;
	while (rightV > 0) {
		if (rightStr.length() > 32) {
			return "ERROR";
		}		
		if (rightV >= factor) {
			rightStr += "1";
			rightV -= factor;
		}
		else
			rightStr += "0";

		factor /= 2;
	}

	return leftStr + "." + rightStr;

}

int main() {
	cout << print_binary(19.25) << endl;
	cout << print_binary2(19.25) << endl;
	return 0;
}