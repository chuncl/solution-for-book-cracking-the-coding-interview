// assume that you have issubstr function to determine if one string is a sub-string of another. given 2 strings s1 and s2, use issubstr only once to determine if s1 is a rotation of s2
// (e.g., "waterbottLe" is a rotation of "erbottLewat").

#include<iostream>
#include<string>

bool issubstr(const std::string& s1, const std::string& s2) 
{
	auto idx = s1.find(s2);
	return idx != std::string::npos ? true : false;
}

bool isrotate(const std::string& s1, const std::string& s2)
{
	if (s1.length() != s2.length() || s2.length() == 0)
		return false;

	return issubstr(s1 + s1, s2) ? true : false;
}

int main()
{
	std::string s1("waterbottLe");
	std::string s2("erbottLewat");

	std::string s3("waterbottLe");
	std::string s4("ezbottLewat");

	std::cout << isrotate(s1, s2) << std::endl;
	std::cout << isrotate(s3, s4) << std::endl;
}

//s1 = xy, s2 = yx ==> s1+s1 = xyxy, so s2 is a substr of it

// string.find return 1st index of substr, or string::npos