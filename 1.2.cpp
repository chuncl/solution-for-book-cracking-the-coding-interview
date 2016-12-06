//implement void reverse(char* str) to reverse non a null-terminate string

#include <iostream>

void reverse1(char *str)
{
	if (str == nullptr)
		return;

	char *end = str;
	char tmp;
	while (*end) {
		end++;
	}
	end--;

	while (str < end) {
		tmp = *str;
		*str++ = *end;
		*end-- = tmp;

	}
}

void swap(char& a, char&b)
{
	a = a^b;
	b = a^b;
	a = a^b;
}

void reverse2(char* str)
{
	if (str == nullptr)
		return;
	char *end = str;
	while (*end) {
		end++;
	}
	end--;
	while (str < end) {
		swap(*str++, *end--);
	}
}

void reverse3(char*str)
{
	if (str = nullptr)
		return;

	int sz = strlen(str);
	for (int i = 0; i < sz / 2; ++i) {
		swap(str[i], str[sz-i-1]);
	}

}

int main()
{
	char s[] = "12345678";
	reverse1(s);
	std::cout << s << std::endl;
	char s2[] = "12345678";
	reverse2(s2);
	std::cout << s2 << std::endl;
	char s3[] = "12345678";
	reverse2(s3);
	std::cout << s3 << std::endl;
	return 0;
}



