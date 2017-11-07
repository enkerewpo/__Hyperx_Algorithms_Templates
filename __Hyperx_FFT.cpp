#include <bitset>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define N 400005
#define pi acos (-1.0) // PI value
using namespace std;
struct complex {
	double r, i;
	complex (double real = 0.0, double image = 0.0) {
		r = real; i = image;
	}
	// The following is the definition of three kinds of imaginary arithmetic
	complex operator + (const complex o) {
		return complex (r + o.r, i + o.i);
	}
	complex operator - (const complex o) {
		return complex (r - o.r, i - o.i);
	}
	complex operator * (const complex o) {
		return complex (r * o.r - i * o.i, r * o.i + i * o.r);
	}
} x1 [N], x2 [N];
char a [N / 2], b [N / 2];
int sum [N]; // The result exists in sum
int vis [N];
void brc (complex * a, int l) {
	// original bingliang binary parallel reversal replacement Taifeng do not understand, wrote an O (n) ......
	memset (vis, 0, sizeof (vis)); // O (logn) is followed
	for (int i = 1; i < l - 1; i ++) {
		int x = i, y = 0;
		int m = (int) log2 (l) + 0.1;
		if (vis [x]) continue;
		while (m--) {
			y <<= 1;
			y |= (x & 1);
			x >>= 1;
		}
		vis [i] = vis [y] = 1;
		swap (a [i], a [y]);
	}
}
void fft (complex * y, int l, double on) {// FFT O (nlogn)
// where DFT is on== 1, on== - 1 is IDFT
	register int h, i, j, k;
	complex u, t;
	brc (y, l); // Call reversal permutation
	for (h = 2; h <= l; h <<= 1) { // Control the number of layers
// initial unit complex root
		complex wn (cos (on * 2 * pi / h), sin (on * 2 * pi / h));
		for (j = 0; j < l; j += h) { // Controls the start subscript
			complex w (1, 0); // Initialize the spiral factor
			for (k = j; k < j + h / 2; k ++) { // paired
				u = y [k];
				t = w * y [k + h / 2];
				y [k] = u + t;
				y [k + h / 2] = u - t;
				w = w * wn; // Update the spiral factor
			} // It is said that the operation above is called butterfly operation ...
		}
	}
	if (on == -1) for (i = 0; i < l; i ++) y [i] .r /= l; // IDFT
}
int main () {
	int l1, l2, l;
	register int i;
	while (scanf("%s%s", a, b) != EOF) {
		l1 = strlen (a);
		l2 = strlen (b);
		l = 1;
		while (l < l1 * 2 || l < l2 * 2) l <<= 1; //The number of boundaries into 2 ^ n
		// with the dichotomy and reverse replacement
		for (i = 0; i < l1; i ++) { // Inverted
			x1 [i] .r = a [l1 - i - 1] - '0';
			x1 [i] .i = 0.0;
		}
		for (; i < l; i ++) x1 [i] .r = x1 [i] .i = 0.0;
		// Initialize the extra count to zero
		for (i = 0; i < l2; i ++) {
			x2 [i] .r = b [l2 - i - 1] - '0';
			x2 [i] .i = 0.0;
		}
		for (; i < l; i ++) x2 [i] .r = x2 [i] .i = 0.0;
		fft (x1, l, 1); // DFT (a)
		fft (x2, l, 1); // DFT (b)
		for (i = 0; i < l; i ++) x1 [i] = x1 [i] * x2 [i];
		fft (x1, l, -1); // IDFT (a * b)
		for (i = 0; i < l; i ++) sum [i] = x1 [i] .r + 0.5; // round off
		for (i = 0; i < l; i ++) { // Carry
			sum [i + 1] += sum [i] / 10;
			sum [i] %= 10;
		}
		l = l1 + l2 - 1;
		while (sum [l] <= 0 && l > 0) l--; // retrieve the most significant bit
		for (i = l; i >= 0; i--) putchar (sum [i] + '0'); // output in reverse
		putchar ('\n');
	}
	return 0;
}