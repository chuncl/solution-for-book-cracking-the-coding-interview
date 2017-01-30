// compute all permutations of a string

#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;
typedef vector<string> vs;
typedef set<string> ss;

/*
a1a2a3..an
Recursion:
1. get first charater (e.g., a1) first. get permutation for a2a3..an, then, insert a1 into all places between characters(including before a2 and after an) 
2. base case: empty string, insert "" and return
*/
vs permu(const string& str) {
	vs ret;
	// base case: empty string, insert ""
	// it is needed to get following cases for permuation, such as one charater
	if (str.empty()) {
		ret.push_back("");
		return ret;
	}
	
	// get first charater (e.g., a1) first. get permutation for a2a3..an 	
	string c = str.substr(0, 1);
	string remain = str.substr(1);
	vs remainRet = permu(remain);
	// for all resulted string, insert a1 into all places between characters(including before a2 and after an)
	for (size_t i = 0; i < remainRet.size(); i++) {
		string t = remainRet[i];
		for (size_t j = 0; j <= t.length(); j++) {
			// NOTE: don't insert into t directly, as it is used in the loop, e.g., t.length()
			string u = t;
			u.insert(j, c);
			ret.push_back(u);
		}
	}

	return ret;
}

/*
Another getting recusion method
1. for each character in string, use that as leading character, and getting permuation for the rest, adding leading character to the results
2. same base condiditon
*/

vs permu2(const string& str) {
	vs ret;
	// base case: empty string, insert ""
	if (str.empty()) {
		ret.push_back("");
		return ret;
	}

	// for each character in string, use that as leading character
	for (size_t i = 0; i < str.size(); i++) {
		string c = str.substr(i, 1);
		string remain = str;
		remain.erase(i, 1);
		// getting permuation for the rest
		vs remainRet = permu(remain);
		// adding leading character to the results
		for (size_t j = 0; j < remainRet.size(); j++) {
			string t = remainRet[j];
			ret.push_back(c + t);
		}
	}

	return ret;
}

/*
when consider duplicate charater cases, use set here, the rest is the same
*/
ss permu3(const string& str) {
	ss ret;
	if (str.empty()) {
		ret.insert("");
		return ret;
	}

	string c = str.substr(0, 1);
	string remain = str.substr(1);
	ss remainRet = permu3(remain);
	for (ss::const_iterator it = remainRet.begin(); it != remainRet.end(); it++) {
		string t = *it;
		for (size_t i = 0; i <= t.length(); i++) {
			string u = t;
			u.insert(i, c);
			ret.insert(u);
		}
	}
	
	return ret;
}

void print(const vs& input) {
	for (size_t i = 0; i < input.size(); i++) {
		cout << input[i] << " ";
	}
	cout << endl;
}

void print(const ss& input) {
	for (auto& s:input) {
		cout << s << " ";
	}
	cout << endl;
}


int main() {
	string a = "abc";
	
	vs ret = permu(a);
	print(ret);	
	
	ret = permu2(a);
	print(ret);

	a = "aaa";
	ss sret = permu3(a);
	print(sret);

	a = "aab";
	sret = permu3(a);
	print(sret);

	return 0;
}