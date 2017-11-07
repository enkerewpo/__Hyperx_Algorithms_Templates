#ifndef __HYPERX_POLLARD_RHO_HPP
#define __HYPERX_POLLARD_RHO_HPP

#include <bits/stdc++.h>
/**
 * This is a Template of Pollard Rho and .Miller Rabin Prime Test
 * email: enkerewpo@gmail.com
 * blog: enkerewpo.github.io
 */
ll mult_mod(ll a, ll b, ll c) {
	a %= c;
	b %= c;
	ll ret = 0;
	while (b) {
		if (b & 1) {
			ret += a;
			ret %= c;
		}
		a <<= 1;
		if (a >= c)a %= c;
		b >>= 1;
	}
	return ret;
}

ll q_pow(ll x, ll n, ll mod) {
	if (n == 1) return x % mod;
	x %= mod;
	ll tmp = x;
	ll ret = 1;
	while (n) {
		if (n & 1) ret = mult_mod(ret, tmp, mod);
		tmp = mult_mod(tmp, tmp, mod);
		n >>= 1;
	}
	return ret;
}

bool check(ll a, ll n, ll x, ll t) {
	ll ret = q_pow(a, x, n);
	ll last = ret;
	for (int i = 1; i <= t; i++) {
		ret = mult_mod(ret, ret, n);
		if (ret == 1 && last != 1 && last != n - 1) return true;
		last = ret;
	}
	if (ret != 1) return true;
	return false;
}

bool Miller_Rabin(ll n) {
	if (n < 2) return false;
	if (n == 2) return true;
	if ((n & 1) == 0) return false;
	ll x = n - 1;
	ll t = 0;
	while ((x & 1) == 0) {
		x >>= 1;
		t++;
	}
	for (int i = 0; i < S; i++) {
		ll a = rand() % (n - 1) + 1;
		if (check(a, n, x, t))
			return false;
	}
	return true;
}

ll fac[100];
int tot;

ll gcd(ll a, ll b) {
	if (a == 0) return 1;
	if (a < 0) return gcd(-a, b);
	while (b) {
		ll t = a % b;
		a = b;
		b = t;
	}
	return a;
}

ll Pollard_rho(ll x, ll c) {
	ll i = 1, k = 2;
	ll x0 = rand() % x;
	ll y = x0;
	while (1) {
		i++;
		x0 = (mult_mod(x0, x0, x) + c) % x;
		ll d = gcd(y - x0, x);
		if (d != 1 && d != x) return d;
		if (y == x0) return x;
		if (i == k) {
			y = x0;
			k += k;
		}
	}
}

void findfac(ll n) {
	if (Miller_Rabin(n)) {
		fac[tot++] = n;
		return;
	}
	ll p = n;
	while (p >= n)
		p = Pollard_rho(p, rand() % (n - 1) + 1);
	findfac(p);
	findfac(n / p);
}

#endif //__HYPERX_POLLARD_RHO_HPP
