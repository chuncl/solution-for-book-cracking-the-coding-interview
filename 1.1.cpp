// implement an algorithm to determin if a string has all unique characters? what if no additonal data structure?

#include <string>
#include <vector>
#include <iostream>

bool isUnique1(std::string str)
{
	std::vector<bool> hash(256, false);
	for (size_t i = 0; i < str.length(); i++) {
		size_t v = static_cast<size_t>(str[i]);
		if (hash[v] == true) {
			return false;
		} else {
			hash[v] = true;
		}
	}
	return true;
}

bool isUnique2(std::string str)
{
	const size_t intBits = sizeof(int)*8;
	std::vector<int> bitVec(256/intBits, 0);
	for (size_t i = 0; i < str.length(); i++) {
		size_t v = static_cast<size_t>(str[i]);
		size_t idx = v/intBits, shift = v%intBits;		
		if (bitVec[idx] & (1 << shift))
			return false;
		else
			bitVec[idx] |= (1 << shift);
	}
	return true;
}

int main() {
	std::string string1 = "tryhad";
	std::string string2 = "tryhardtryaaaa";
	std::string string3 = "aaa";
	std::cout << isUnique1(string1) << std::endl;
	std::cout << isUnique1(string2) << std::endl;

	std::cout << isUnique2(string1) << std::endl;
	std::cout << isUnique2(string2) << std::endl;
	std::cout << isUnique2(string3) << std::endl;

	return 0;
}
