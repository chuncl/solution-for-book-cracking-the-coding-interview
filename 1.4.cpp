// Write a method to replace all spaces in a string with '%20'. 
// You may assume that the string has sufficient space at the end of the string to hold the additional characters, 
// and that you are given the "true" length of the string. (Note: if implementing in Java, please use a character array so that you can perform this operation in place.)

#include <iostream>
#include <string>

void replaceSpace(std::string& str)
{
	size_t sz = str.length();
	if (sz == 0)
		return;

	size_t spaceCount = 0;
	for (size_t i = 0; i < sz; ++i) {
		if (str[i] == ' ')
			spaceCount++;
	}

	size_t newsz = sz + spaceCount * 2;
	str.resize(newsz);

	// starting from end for inplace replacement
	// as the destination array is bigger
	size_t d = newsz - 1;

	// note:  use int i instead of size_t i when looping from back, 
	// as for size_t i, --i will get it to big positive number
	for (int i = sz-1; i >= 0; --i) {
		if (str[i] == ' ') {
			str[d] = '%';
			str[d - 1] = '2';
			str[d - 2] = '0';
			d = d - 3;				
		}
		else {
			str[d] = str[i];
			d--;
		}
	}
}

int main()
{
	std::string s1("abdc ef g");
	std::string s2("abdc");
	std::string s3("");
	std::string s4("abc ");
	std::string s5("abcd  ef g");

	replaceSpace(s1);
	replaceSpace(s2);
	replaceSpace(s3);
	replaceSpace(s4);
	replaceSpace(s5);

	std::cout << s1 << " "
		<< s2 << " "
		<< s3 << " "
		<< s4 << " "
		<< s5 << std::endl;
}