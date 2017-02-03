// given an expression with 1, 0, |, &, ^, given a bool result, find number of the ways of parenthesising the epression such that the epression will be evaluate to the result

#include <iostream>
#include <string>
#include <unordered_map>
#include <cassert>
using namespace std;

/*
1. treat each operator as the first operator to be parenthesed
2. reduce problem to sub-problem:
f(expl | exp2 | true) = f(expl, true) * f(exp2, true) + f(expl, true) * f(exp2, false) + f(expl, false) * f(exp2, true) 
f(expl & exp2, true) = f(expl, true) * f(exp2, true) 
f(expl ^ exp2, true) = f(expl, true) * f(exp2, false) + f(explj false) * f(exp2, true)
3. base:
When string is 1 or 0
4. use memorization, note build key based on the distinct input arguments' combination
*/
typedef unordered_map<string, int> MAP;
int countParenBoolExpressR(bool result, const string& expr, int start, int end, MAP& mem) {
	//  base: When string is 1 or 0
	if (start == end) {
		if (result && (expr[start] == '1'))
			return 1;
		else if (!result && (expr[start] == '0'))
			return 1;
		else
			return 0;
	}

	string key = to_string(result) + to_string(start) + to_string(end);
	if (mem.find(key) != mem.end())
		return mem[key];

	int count = 0;
	if (result) {
		// treat each operator as the first operator to be parenthesed
		for (int i = start + 1; i <= end; i+=2) {
			char op = expr[i];
			//  reduce problem to sub-problem
			switch (op) {
			case '|': {
				count += countParenBoolExpressR(true, expr, start, i - 1, mem)*countParenBoolExpressR(true, expr, i + 1, end, mem);
				count += countParenBoolExpressR(true, expr, start, i - 1, mem)*countParenBoolExpressR(false, expr, i + 1, end, mem);
				count += countParenBoolExpressR(false, expr, start, i - 1, mem)*countParenBoolExpressR(true, expr, i + 1, end, mem);
				break;
			}
			case '&': {
				count += countParenBoolExpressR(true, expr, start, i - 1, mem)*countParenBoolExpressR(true, expr, i + 1, end, mem);
				break;

			} default: {
				assert(op == '^');
				count += countParenBoolExpressR(true, expr, start, i - 1, mem)*countParenBoolExpressR(false, expr, i + 1, end, mem);
				count += countParenBoolExpressR(false, expr, start, i - 1, mem)*countParenBoolExpressR(true, expr, i + 1, end, mem);
				break;

			}
			}
		}
	}
	else {
		// treat each operator as the first operator to be parenthesed
		for (int i = start + 1; i <= end; i+=2) {
			char op = expr[i];
			//  reduce problem to sub-problem
			switch (op) {
			case '|': {
				count += countParenBoolExpressR(false, expr, start, i - 1, mem)*countParenBoolExpressR(false, expr, i + 1, end, mem);
				break;
			} 
			case '&': {
				count += countParenBoolExpressR(false, expr, start, i - 1, mem)*countParenBoolExpressR(false, expr, i + 1, end, mem);
				count += countParenBoolExpressR(true, expr, start, i - 1, mem)*countParenBoolExpressR(false, expr, i + 1, end, mem);
				count += countParenBoolExpressR(false, expr, start, i - 1, mem)*countParenBoolExpressR(true, expr, i + 1, end, mem);
				break;					 
			} 
			default: {
				assert(op == '^');
				count += countParenBoolExpressR(true, expr, start, i - 1, mem)*countParenBoolExpressR(true, expr, i + 1, end, mem);
				count += countParenBoolExpressR(false, expr, start, i - 1, mem)*countParenBoolExpressR(false, expr, i + 1, end, mem);
				break;
			}

			}
		}

	}

	mem[key] = count; 
	return count;
}

int countParenBoolExpress(bool result, const string& expr) {
	if (expr.empty())
		return 0;

	int s = 0;
	int e = expr.length() - 1;
	MAP m;
	return countParenBoolExpressR(result, expr, s, e, m);
}

/*
Similarily as above, but use catlan number to get total ways of parenthesing n operators.
f(exp = true) = total (exp) - f(exp = false) for operator "|"
==>optimized 
 - "|" case 
 - overall case, just compute true case is fine, use total number minus true case result if needed
*/
typedef long long LL;
LL factorial(int n) {
	if (n == 0)
		return 1;

	int result = n;
	for (int i = 1; i < n; i++) {
		result *= n - i;
	}
	return result;
}

LL catlanNum(int n) {	
	return factorial(2 * n) / (factorial(n) * factorial(n + 1));
}


int countParenBoolExpressR2(bool result, const string& expr, int start, int end, MAP& mem) {
	if (start == end) {
		if (result && (expr[start] == '1'))
			return 1;
		else if (!result && (expr[start] == '0'))
			return 1;
		else
			return 0;
	}

	string key = to_string(result) + to_string(start) + to_string(end);
	if (mem.find(key) != mem.end())
		return mem[key];

	int trueCount = 0, count = 0;
	for (int i = start + 1; i <= end; i += 2) {
		char op = expr[i];
		switch (op) {
		case '|': {
			int totalCount = int(catlanNum((i - 1 - start) / 2)*catlanNum((end - i - 1) / 2));
			int falseCount = countParenBoolExpressR2(false, expr, start, i - 1, mem)*countParenBoolExpressR2(false, expr, i + 1, end, mem);
			trueCount = totalCount - falseCount;
			break;
		}
		case '&': {
			trueCount += countParenBoolExpressR2(true, expr, start, i - 1, mem)*countParenBoolExpressR2(true, expr, i + 1, end, mem);
			break;

		} default: {
			assert(op == '^');
			trueCount += countParenBoolExpressR2(true, expr, start, i - 1, mem)*countParenBoolExpressR2(false, expr, i + 1, end, mem);
			trueCount += countParenBoolExpressR2(false, expr, start, i - 1, mem)*countParenBoolExpressR2(true, expr, i + 1, end, mem);
			break;

		}
		}
	}

	if (result)
		count = trueCount;
	else
		count = int(catlanNum((end - start) / 2)) - trueCount;
	mem[key] = count;
	return count;
}

int countParenBoolExpress2(bool result, const string& expr) {
	if (expr.empty())
		return 0;

	int s = 0;
	int e = expr.length() - 1;
	MAP m;
	return countParenBoolExpressR2(result, expr, s, e, m);
}

int main() {
	string e = "1^0";
	//cout << countParenBoolExpress(true, e) << endl;
	//cout << countParenBoolExpress(false, e) << endl;

	//e = "1^0|0&1";
	//cout << countParenBoolExpress(true, e) << endl;
	//cout << countParenBoolExpress(false, e) << endl;

	//e = "1^0|0|1";
	//cout << countParenBoolExpress(true, e) << endl;
	//cout << countParenBoolExpress(false, e) << endl;

	//cout << "2nd catlan number approach" << endl;
	//e = "1^0";
	//cout << countParenBoolExpress2(true, e) << endl;
	//cout << countParenBoolExpress2(false, e) << endl;

	e = "1^0|0&1";
	cout << countParenBoolExpress2(true, e) << endl;
	cout << countParenBoolExpress2(false, e) << endl;

	//e = "1^0|0|1";
	//cout << countParenBoolExpress2(true, e) << endl;
	//cout << countParenBoolExpress2(false, e) << endl;


	return 0;
}