#include <cstdio>
#include <cstring>

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

struct BigInteger {
	const static int MOD = 10000;
	
	int integer[128], len;
	BigInteger() {
		memset(integer, 0, sizeof(integer));
		len = 0;
	}

	void print() {
		printf("%d", integer[len]);
		for(int i = len - 1; i; --i) {
			if(integer[i] == 0) { printf("0000"); continue; }
			for(int k = 10; k * integer[i] < MOD; k *= 10)
				printf("0");
			printf("%d", integer[i]);
		}
	}
	
	void read() {
		char s[1000];
		scanf("%s", s + 1);

		int len2 = strlen(s + 1);
		int x = 0;

		while(len2 > 0) {
			for(int i = min(3, len2 - 1); i >= 0; --i) {
				x = x * 10 + (s[len2 - i] - '0');
			}
			integer[++len] = x;
			x = 0;
			len2 -= 4;
		}

		if(x > 0) {
			integer[++len] = x;
		}
	}

  bool operator == (const BigInteger &a) {
		if(a.len != len) return false;
		for(int i = len; i > 0; --i) {
			if(integer[i] != a.integer[i]) return false;
		}
		return true;
	}

	bool operator < (const BigInteger &a) {
		if(len != a.len) return (len < a.len);
		for(int i = len; i; --i)
			if(integer[i] != a.integer[i]) return (integer[i] < a.integer[i]);
		return false;
	}
};

BigInteger operator + (const BigInteger &a, const BigInteger &b) {
	BigInteger c;
	c.len = max(a.len, b.len);
	int x = 0;
	for(int i = 1; i <= c.len; ++i) {
		c.integer[i] = a.integer[i] + b.integer[i] + x;
		x = c.integer[i] / BigInteger::MOD;
		c.integer[i] %= BigInteger::MOD;
	}
	if(x > 0) c.integer[++c.len] = x;
	return c;
}

BigInteger operator - (const BigInteger &a, const BigInteger &b) {
	BigInteger c;
	c.len = a.len;
	for(int i = 1; i <= a.len; ++i) {
		c.integer[i] += a.integer[i] - b.integer[i];
		while(c.integer[i] < 0) {
			c.integer[i] += BigInteger::MOD;
			c.integer[i + 1] -= 1;
		}
	}
	while(c.len > 0 && c.integer[c.len] == 0) c.len--;
	return c;
}

BigInteger operator * (const BigInteger &a, const int &b) {
	BigInteger c;
	c.len = a.len;
	int x = 0;
	for(int i = 1; i <= c.len; ++i) {
		c.integer[i] = a.integer[i] * b + x;
		x = c.integer[i] / BigInteger::MOD;
		c.integer[i] %= BigInteger::MOD;
	}

	while(x > 0) {
		c.integer[++c.len] = x % BigInteger::MOD;
		x /= BigInteger::MOD;
	}
	return c;
}

BigInteger max(const BigInteger &a, const BigInteger &b) {
	if(a.len > b.len) return a;
	if(b.len > a.len) return b;
	for(int i = a.len; i; --i) {
		if(a.integer[i] > b.integer[i]) return a;
		else if(b.integer[i] > a.integer[i]) return b;
	}
	return a;
}
