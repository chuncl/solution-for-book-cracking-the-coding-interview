// generate nth fibonacci number
// f(1) = f(2) =1;
// f(n) = f(n-1) + f(n-2) n > 2

#include <iostream>
#include <unordered_map>

using namespace std;

typedef long long ll;

/* recursion
if not using memorization, it is O(2^n)
*/
typedef unordered_map<int, ll> MAP;
ll fibonacciR(int n, MAP& hash) {
	if (n < 1)
		return -1;
	else if (n == 1 || n == 2)
		return 1;
	else if (hash.find(n) != hash.end())
		return hash[n];
	else {
		ll ret = fibonacciR(n-1, hash) + fibonacciR(n-2, hash);
		hash[n] = ret;
		return ret;
	}
}
ll fibonacci1(int n) {
	MAP h;
	return fibonacciR(n, h);
}

/*
iteration 
O(n)
*/
ll fibnocci2(int n) {
	if (n < 1)
		return -1;	
	else {
		ll a = 1, b = 1, ret = 1;
		for (int i = 3; i <=n; i++) {
			ret = a+b;
			a = b;
			b = ret;
		}
		return ret;
	}
}

/*
fast method O(logn)
*/
// state equation:
//[fn ] = [1 1] [fn-1] = ... [1 1]^n-2 [f2]
// fn-1    1 0   fn-2         1 0       f1
// caculate matrix power

// O(n)
ll pow(int m, size_t n) {
	ll ret = 1;
	for (size_t i = 1; i <= n; i++) {
		ret *= m;
	}
	return ret;
}

// fast power
// O(logn)
ll powFast(int m, size_t n) {
	ll ret = 1;	
	while (n > 0) {
		if (n & 1)			
			ret *= m;
		m *= m;
		n >>= 1;	
	}
	return ret;
}

// fast power matrix
void mul(ll c[2][2], ll a[2][2], ll b[2][2]) {
	ll t[4];
    t[0] = a[0][0]*b[0][0] + a[0][1]*b[1][0];
    t[1] = a[0][0]*b[0][1] + a[0][1]*b[1][1];
    t[2] = a[1][0]*b[0][0] + a[1][1]*b[1][0];
    t[3] = a[1][0]*b[0][1] + a[1][1]*b[1][1];
    c[0][0] = t[0];
    c[0][1] = t[1];
    c[1][0] = t[2];
    c[1][1] = t[3];
}

void powFast(ll ans[2][2], ll m[2][2], ll n) {
	while(n > 0) {
		if (n & 1) 
			mul(ans, ans, m);
		mul(m, m, m);
		n >>= 1;
	}
}

// O(logn)
ll fibnocci3(int n) {
	if (n < 1)
		return -1;	
	else if (n == 1 || n == 2)
		return 1;
	else {
		ll m[2][2] = { {1, 1}, {1, 0}};
		ll s[2][2] = { {1,0}, {0, 1} };
		powFast(s, m, n-2);
		return s[0][0]+ s[0][1];
	}
}

int main(){
    for(int i=1; i<20; ++i)
        cout<<fibonacci1(i)<<" ";
    cout<<endl;
    for(int i=1; i<20; ++i)
        cout<<fibnocci2(i)<<" ";
    cout<<endl;
    for(int i=1; i<20; ++i)
        cout<<fibnocci3(i)<<" ";
    cout<<endl;
    return 0;
}