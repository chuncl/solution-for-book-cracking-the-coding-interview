// print all combinations of valid n-pair parentheses 

#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

typedef set<string> ss;
typedef vector<string> vs;

/*
Insert a pair of parentheses into every existing pair of parentheses and before the first parenthesis
NOTE: it could result into duplicate, so using set to deal with that
*/
ss paren(int n) {
	ss strs;
	if (n == 0) {		
		strs.insert("");		
	}
	else {
		// insert a pair of parentheses into every existing pair of parentheses
		ss prev = paren(n - 1);
		for (auto& s : prev) {
			for (size_t i = 0; i < s.length(); i++) {
				if (s[i] == '(') {
					string t = s.substr(0, i + 1);
					string r = s.substr(i + 1);
					string u = t + "()" + r;
					strs.insert(u);
				}
			}
			// and before the first parenthesis
			strs.insert("()" + s);
		}
	}
	return strs;
}

/*
build string from scratch, do NOT need set to deal with duplicate ==> more optimal

left: keep adding left parenthsis as long as it is not used up
right: add right parenthsis as long as valid syntax
==> right remaining parenthesis is not larger than remaining left parenthesis
*/
void paren2(int l, int r, string str, vs& strs) {	
	// invalid case
	if (l < 0 || r < l)
		return;
	// base case, put built string into results
	if (l == 0 && r == 0) {
		strs.push_back(str);
	}
	
	// adding adding left parenthsis
	// "as long as it is not used up " will be checked above in recursion
	paren2(l - 1, r, str+"(", strs);

	// add right parenthsis as long as valid syntax
	// "as long as valid syntax & avaibility" will be checked above in recursion
	paren2(l, r - 1, str + ")", strs);
}

void print(ss ret) {
	for (auto s : ret) {
		cout << s << " ";
	}
	cout << endl;
}

void print(vs ret) {
	for (auto s : ret) {
		cout << s << " ";
	}
	cout << endl;
}

int main() {
	ss s = paren(3);
	print(s);

	int n = 3;
	string a;
	vs strs;
	paren2(n, n, a, strs);
	print(strs);

	return 0;
}
