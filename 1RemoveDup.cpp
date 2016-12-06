// remove duplicate character in a string, without using any extra buff, but additional variables are fine. write up test cases

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

// o(n)
void removeDup1(std::string& str)
{
	if (str.length() <= 1)
		return;

	int bitVar(0);
	int p = 0;
	for (size_t i = 0; i < str.length(); ++i) {
		int v = static_cast<int>(str[i] - 'a');
		if (bitVar & (1 << v)) {
			continue;
		} else {
			str[p++] = str[i];
			bitVar |= (1 << v);
		}
	}
	str.erase(p);
}

// o(n)
void removeDup2(char* str)
{
	if ((str == nullptr) || (strlen(str) < 2))
		return;

	size_t intBits = sizeof(int) * 8;
	size_t sz = 256 / intBits;
	std::vector<int> bitVec(sz, 0);

	char* src = str;
	while (*src++) {
		size_t v = static_cast<size_t>(*src);
		size_t idx = v / intBits;
		size_t shift = v % intBits;
		if ((bitVec[idx] & (1 << shift)) == 0) {			
			*str++ = *src;
			bitVec[idx] |= (1 << shift);
		}
	}

	*str = '\0';
}

// o(n^2)
void removeDup3(char *str)
{
	
	if (str == nullptr)
		return;
	size_t sz = strlen(str);
	if (sz < 2)
		return;

	size_t d = 0;
	for (size_t i = 0; i < sz; ++i) {
		if (str[i] != '\0') {
			for (size_t j = i+1; j < sz; ++j) {
				if (str[j] == str[i])
					str[j] = '\0';
			}
			str[d++] = str[i];
		}
	}
	str[d] = '\0';
}

// o(nlogn) & order changed
// use sort + unique + erase
// note unique assume vector/string is already sorted
void removeDup4(std::string& s)
{
	std::sort(s.begin(), s.end());
	s.erase(std::unique(s.begin(), s.end()), s.end());
}

// o(nlogn) & order changed
// use set<==>vector/string
void removeDup5(std::string& s)
{
	std::set<char> tmpset(s.begin(), s.end());
	s.assign(tmpset.begin(), tmpset.end());
}


int main()
{
	std::string c1("babcabcabc"); // one character
	std::string c2("a"); // one character
	std::string c3(""); // emptyer string
	std::string c4("abcbaccab");
	std::string c5("aaaaa");
	std::string c6("aaabbb");

	removeDup1(c1);
	removeDup1(c2);
	removeDup1(c3);
	removeDup1(c4);
	removeDup1(c5);
	removeDup1(c6);

	std::cout << c1 << " " << c2 << " " << c3 << " " << c4 << " " << c5 << " " << c6 << std::endl;

	char char1[] ="abcabcabc"; // one character
	char char2[] = "a"; // one character
	char char3[] =""; // emptyer string
	char char4[] ="abcbaccab";
	char char5[] = "aaaaa";
	char char6[] = "aaabbb";

	removeDup2(char1);
	removeDup2(char2);
	removeDup2(char3);
	removeDup2(char4);
	removeDup2(char5);
	removeDup2(char6);

	std::cout << char1 << " " << char2 << " " << char3 << " " << char4 << " " << char5 << " " << char6 << std::endl;

	removeDup3(char1);
	removeDup3(char2);
	removeDup3(char3);
	removeDup3(char4);
	removeDup3(char5);
	removeDup3(char6);

	std::cout << char1 << " " << char2 << " " << char3 << " " << char4 << " " << char5 << " " << char6 << std::endl;

	removeDup4(c1);
	removeDup4(c2);
	removeDup4(c3);
	removeDup4(c4);
	removeDup4(c5);
	removeDup4(c6);

	std::cout << c1 << " " << c2 << " " << c3 << " " << c4 << " " << c5 << " " << c6 << std::endl;

	removeDup5(c1);
	removeDup5(c2);
	removeDup5(c3);
	removeDup5(c4);
	removeDup5(c5);
	removeDup5(c6);

	std::cout << c1 << " " << c2 << " " << c3 << " " << c4 << " " << c5 << " " << c6 << std::endl;


}

/*
source ptr & destination ptr concept for inplace replacement, as along as the dest ptr is faster than src ptr, it works.
*/

/*
for std::string, need to use erase to get rid off left unused charaters, for char*, we can just set '\0'.
*/

/*
bit vecotr/variable, depending on charater is acii or a-z, etc.
*/

/*What is the difference between char s[] and char *s in C ?

The difference here is that:
char *s = "Hello world";
will place "Hello world" in the read - only parts of the memory, and making s a pointer to that makes any writing operation on this memory illegal.

While doing :

char s[] = "Hello world";
puts the literal string in read - only memory and copies the string to newly allocated memory on the stack.Thus making

s[0] = 'J';
legal.
*/