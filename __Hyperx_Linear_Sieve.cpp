#pragma GCC optimize("O3")
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#define N int(1e7 + 10)
using namespace std;

int num_mindiv[N];
int min_div[N];
int sum_div[N], t1[N], t2[N];
int num_div[N];
int phi[N];
int miu[N];
bool is_prime[N];
int prime[N], tot;

void slieve(int n) {
	miu[1] = 1;
	memset(is_prime, true, sizeof is_prime);
	for (int i = 2; i <= n; i++) {
		if (is_prime[i]) {
			min_div[i] = prime[++tot] = i;
			phi[i] = i - 1;
			num_mindiv[i] = 1;
			num_div[i] = 2;
			miu[i] = -1;
			sum_div[i] = 1 + i;
			t1[i] = 1 + i;
			t2[i] = i;
		}
		for (int j = 1; j <= tot && prime[j] * i <= n; j++) {
			int k = prime[j] * i;
			is_prime[k] = false;
			if (i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
				num_mindiv[k] = num_mindiv[i] + 1;
				num_div[k] = num_div[i] / (num_mindiv[i] + 1) * (num_mindiv[k] + 1);
				miu[i] = 0;
				t2[k] = t2[i] * prime[j];
				t1[k] = t1[i] + t2[k];
				sum_div[k] = sum_div[i] / t1[i] * t1[k];
				break;
			}
			phi[k] = phi[i] * phi[prime[j]];
			num_mindiv[k] = 1;
			num_div[k] = num_div[i] * 2;
			miu[k] -= miu[i];
			sum_div[k] = sum_div[i] * sum_div[prime[j]];
			t1[k] = 1 + prime[j];
			t2[k] = prime[j];
		}
	}
}

int main() {
	int n = 1e9 + 9;
	slieve(n);
	printf("n %s", is_prime[n] ? "is prime" : "not prime");
	return 0;
}
