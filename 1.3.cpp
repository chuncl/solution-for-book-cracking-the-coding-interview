// given 2 string, write a function to check if they are permutation of the other

#include <iostream>
#include <map>
#include <unordered_map>

bool isPermutation1(const std::string& a, const std::string& b)
{
	if (a.length() != b.length())
		return false;
	
	std::map<char, int> hash;
	for (size_t i = 0; i < a.length(); ++i) {
		hash[a[i]]++;
		hash[b[i]]--;
	}

	for (auto it = hash.begin(); it != hash.end(); it++)	{
		if (it->second != 0)
			return false;
	}

	return true;
}

bool isPermutation2(const char*a, const char*b)
{
	if ((a == nullptr) || (b == nullptr)) {
		if ((a == nullptr) && (b == nullptr))
			return true;
		else
			return false;
	}

	if (strlen(a) != strlen(b))
		return false;

	std::unordered_map<char, int>hash;
	while (*a) {
		hash[*a++]++;
		hash[*b++]--;
	}

	for (auto it = hash.begin(); it != hash.end(); it++) {
		if (it->second != 0)
			return false;
	}

	return true;
}

bool isPermutation3(const std::string& a, const std::string& b)
{
	if (a.length() != b.length())
		return false;
	std::vector<int> hash(256, 0);

	for (auto sit1 = a.begin(), sit2 = b.begin(); sit1 < a.end(); ++sit1,++sit2) {
		size_t idx1 = static_cast<size_t>(*sit1);
		hash[idx1]++;
		size_t idx2 = static_cast<size_t>(*sit2);
		hash[idx2]--;
	}

	for (auto it = hash.begin(); it != hash.end(); it++) {
		if (*it != 0)
			return false;
	}

	return true;
}

int main()
{
	std::string a("abcde");
	std::string b("deabc");
	std::string na("abczde");
	std::string nb("deawbc");
	std::cout << isPermutation1(a, b) << std::endl;	
	std::cout << isPermutation1(na, nb) << std::endl;
		
	std::cout << isPermutation2(a.c_str(), b.c_str()) << std::endl;
	std::cout << isPermutation2(na.c_str(), nb.c_str()) << std::endl;
	
	std::cout << isPermutation3(a, b) << std::endl;
	std::cout << isPermutation3(na, nb) << std::endl;

	return 0;
}