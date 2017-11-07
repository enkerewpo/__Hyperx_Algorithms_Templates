int lowbit(int x) {
	return x & -x;
}

void add(int x, int y, int d) {
	int i, j;
	for (i = x; i < N; i += lowbit(i))
		for (j = y; j < N; j += lowbit(j)) mat[i][j] += d;
}

int sum(int x, int y) {
	int ret = 0;
	int i, j;
	for (i = x; i > 0; i -= lowbit(i))
		for (j = y; j > 0; j -= lowbit(j)) ret += mat[i][j];
	return ret;
}