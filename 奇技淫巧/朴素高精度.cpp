#include <cstdio>

const int MAXN = 10005;
const int BASE = 10;

struct BigInteger{
	int a[MAXN], len;	//a[0] 表示正负, 0->正, 1->负
};

void read(BigInteger &rhs) {
	rhs.len = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') rhs.a[0] = 1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		rhs.a[++rhs.len] = ch - '0';
		ch = getchar();
	}
	int cur1 = 1, cur2 = rhs.len;
	while(cur1 < cur2) {
		int t = rhs.a[cur1];
		rhs.a[cur1] = rhs.a[cur2];
		rhs.a[cur2] = t;
		cur1++;
		cur2--;
	}
}

int BigInt_cmp(const BigInteger x, const BigInteger y) {
	if(x.a[0] == 1 && y.a[0] == 0) return -1;
	if(x.a[0] == 0 && y.a[0] == 1) return 1;
	if(x.a[0] == 0 && y.a[0] == 0) {	
		if(x.len > y.len) return 1;
		if(y.len > x.len) return -1;
		for(int i = x.len; i > 0; --i) {
			if(x.a[i] > y.a[i]) return 1;
			if(x.a[i] < y.a[i]) return -1;
		}
	}
	if(x.a[0] == 1 && y.a[0] == 1) {
		if(x.len > y.len) return -1;
		if(y.len > x.len) return 1;
		for(int i = x.len; i > 0; --i) {
			if(x.a[i] > y.a[i]) return -1;
			if(x.a[i] < y.a[i]) return 1;
		}
	}
	return 0;
}

void assign(BigInteger &x, const BigInteger y) {
	x.len = y.len;
	for(int i = 0; i <= y.len; ++i) x.a[i] = y.a[i];
}

void Print(const BigInteger x) {
	if(x.a[0] == 1) printf("-");
	printf("%d", x.a[x.len]);
	for(int i = x.len - 1; i > 0; --i) {
		printf("%d", x.a[i]);
	}
}

void Multiply(BigInteger x, int y, BigInteger &rhs) {
	if(y < 0 && x.a[0] == 1) rhs.a[0] = 0;
	else if(y < 0 && x.a[0] == 0) rhs.a[0] = 1;
	else if(y > 0 && x.a[0] == 1) rhs.a[0] = 1;
	else if(y > 0 && x.a[0] == 0) rhs.a[0] = 0;
	y = (y > 0 ? y : -y);
	
	rhs.len = x.len;
	for(int i = 1; i <= x.len; ++i) rhs.a[i] = x.a[i] * y;
	for(int i = 1; i <= x.len; ++i) {
		rhs.a[i + 1] += (rhs.a[i] / BASE);
		rhs.a[i] %= BASE;
	}
	rhs.len++;
	while(rhs.a[rhs.len] >= BASE) {
		rhs.a[rhs.len + 1] += (rhs.a[rhs.len] / BASE);
		rhs.a[rhs.len] %= BASE;
		rhs.len++;
	}
	if(rhs.a[rhs.len] == 0) rhs.len--;
}

void Minus(BigInteger x, BigInteger y, BigInteger &rhs) {
	int check = BigInt_cmp(x, y);
	if(check == 0) {
		rhs.a[0] = 0;
		rhs.a[1] = 0;
		rhs.len = 1;
		return ;
	}
	if(x.a[0] == y.a[0]) {
		if(x.a[0] == 0) {
			if(check > 0) {
				rhs.a[0] = 0;
				rhs.len = x.len;
				for(int i = 1; i <= x.len; ++i) {
					rhs.a[i] = x.a[i] - y.a[i];
					if(rhs.a[i] < 0) {
						rhs.a[i] += BASE;
						x.a[i + 1]--;
					}
				}
				while(!rhs.a[rhs.len]) rhs.len--;
			}
			else if(check < 0) {
				rhs.a[0] = 1;
				rhs.len = y.len;
				for(int i = 1; i <= y.len; ++i) {
					rhs.a[i] = y.a[i] - x.a[i];
					if(rhs.a[i] < 0) {
						rhs.a[i] += BASE;
						y.a[i + 1]--;
					}
				}
				while(!rhs.a[rhs.len]) rhs.len--;
			}
		}
		else if(x.a[0] == 1) {
			if(check > 0) {
				rhs.a[0] = 0;
				rhs.len = y.len;
				for(int i = 1; i <= y.len; ++i) {
					rhs.a[i] = y.a[i] - x.a[i];
					if(rhs.a[i] < 0) {
						rhs.a[i] += BASE;
						y.a[i + 1]--;
					}
				}
				while(!rhs.a[rhs.len]) rhs.len--;
			}
			else if(check < 0) {
				rhs.a[0] = 1;
				rhs.len = x.len;
				for(int i = 1; i <= x.len; ++i) {
					rhs.a[i] = x.a[i] - y.a[i];
					if(rhs.a[i] < 0) {
						rhs.a[i] += BASE;
						x.a[i + 1]--;
					}
				}
				while(!rhs.a[rhs.len]) rhs.len--;
			}
		}
	}
	else if(x.a[0] != y.a[0]) {
		if(check > 0) {
			rhs.a[0] = 0;
			int len = (x.len > y.len ? x.len : y.len);
			for(int i = 1; i <= len; ++i) {
				rhs.a[i] = x.a[i] + y.a[i];
				if(rhs.a[i] >= BASE) {
					rhs.a[i + 1] += (rhs.a[i] / BASE);
					rhs.a[i] %= BASE;
				}
				while(rhs.a[rhs.len]) rhs.len++;
				rhs.len--;
			}
		}
		else if(check < 0) {
			rhs.a[0] = 1;
			int len = (x.len > y.len ? x.len : y.len);
			for(int i = 1; i <= len; ++i) {
				rhs.a[i] = x.a[i] + y.a[i];
				if(rhs.a[i] >= BASE) {
					rhs.a[i + 1] += (rhs.a[i] / BASE);
					rhs.a[i] %= BASE;
				}
				while(rhs.a[rhs.len]) rhs.len++;
				rhs.len--;
			}
		}
	}
}

void Plus(BigInteger x, BigInteger y, BigInteger &rhs) {  //我承认我很懒
	y.a[0] ^= 1;
	Minus(x, y, rhs);
}


BigInteger a, b;
int x;

int main() {
	read(a);
	read(b);
	Minus(a, b, a);
	Print(a);
	return 0;
}

/*-----版本2:重载版-----*/

#include <cstdio>
#include <cstring>

int max(int a, int b) {
	return (a > b ? a : b);
}

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
