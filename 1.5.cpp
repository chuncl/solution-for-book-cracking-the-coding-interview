//Implement a method to perform basic string compression using the counts of repeated characters.For example, 
//the string aabcccccaaa would become a2blc5a3.If the "compressed" string would not become smaller than the original string, 
//your method should return the original string

#include <iostream>
#include <string>
#include <sstream>

size_t getNewsz(const std::string& s)
{
	size_t newsz(0);
	char last = s[0];
	size_t count = 1;		
	for (size_t i = 1; i < s.length(); i++) {			
		if (s[i] == last) {
			count++;
		}
		else {
			newsz += (1 + std::to_string(count).length());	
			last = s[i];
			count = 1;
		}
	}
	newsz += (1 + std::to_string(count).length());
	return newsz;
}

std::string compress(const std::string& s)
{
	size_t sz = s.length();
	if (sz == 0)
		return std::string(s);
	size_t newsz = getNewsz(s);
	if (sz <= newsz)
		return std::string(s);

	char last = s[0];
	size_t count = 1;
	std::stringstream ss;
	for (size_t i = 1; i < sz; i++) {		
		if (s[i] == last) {
			count++;
		}
		else {
			ss << last << count;			
			last = s[i];
			count = 1;
		}	
	}
	ss << last << count;	
	return ss.str();
}

int main()
{
	std::string s1("aabcccccaaa");
	std::string s2("abc");
	std::string s3("");
	std::string s4("aab");
	std::string s5("aabc");

	std::string s1R = compress(s1);
	std::string s2R = compress(s2);
	std::string s3R = compress(s3);
	std::string s4R = compress(s4);
	std::string s5R = compress(s5);

	std::cout << s1R << " "
		<< s2R << " "
		<< s3R << " " 
		<< s4R << " "
		<< s5R << " "
		<< std::endl;

	return 0;
}