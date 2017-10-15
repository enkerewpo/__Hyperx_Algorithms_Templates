#ifndef __HYPERX_FLOYD_TRANS_CLOSURE_HPP
#define __HYPERX_FLOYD_TRANS_CLOSURE_HPP
void floyd()
{
	int i, j, k;
	int n;
	bool* con = new bool[n + 1][n + 1];
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				con[i][j] |= con[i][k] & con[k][j];
}
#endif //__HYPERX_FLOYD_TRANS_CLOSURE_HPP
