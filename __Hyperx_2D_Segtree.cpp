#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 * 1000 * 1.5;
// 2D line tree
struct node {
	short x1, y1, x2, y2; // (a, b) - (c, d)
	float max;
	int * ch;
};
node tree [maxn]; // space: O (N * M * 2) // In fact, 1.4 * N * M is sufficient
int tol;
void maketree (int x1, int y1, int x2, int y2) {// time: O (2 * N * M)
	tol ++;
	int k = tol;
	tree [k] .x1 = x1;
	tree [k] .y1 = y1;
	tree [k] .x2 = x2;
	tree [k] .y2 = y2;
	tree [k] .max = 0.0;
	if (x1 == x2 && y1 == y2) {// c == d
		tree [k] .ch = 0;
		return;

	}
	tree [k] .ch = new int [4];
	int midx = (x1 + x2) / 2;
	int midy = (y1 + y2) / 2;
	if (x1 <= midx && y1 <= midy) {// lower left
		tree [k] .ch [0] = tol + 1;
		maketree (x1, y1, midx, midy);

	} else
		tree [k] .ch [0] = 0;
	if (midx + 1 <= x2 && midy + 1 <= y2) {// top right
		tree [k] .ch [1] = tol + 1;
		maketree (midx + 1, midy + 1, x2, y2);

	} else
		tree [k] .ch [1] = 0;
	if (x1 <= midx && midy + 1 <= y2) {// top left
		tree [k] .ch [2] = tol + 1;
		maketree (x1, midy + 1, midx, y2);

	} else
		tree [k] .ch [2] = 0;
	if (midx + 1 <= x2 && y1 <= midy) {// lower right
		tree [k] .ch [3] = tol + 1;
		maketree (midx + 1, y1, x2, midy);

	} else
		tree [k] .ch [3] = 0;
}
// time: O (logN) // N * N rectangle
void insert (int x, int y, int L, int k) {// Here is a rectangle for the insertion [x, y] - [x, y] .. A unit square
	if (tree [k] .x1 == tree [k] .x2 && tree [k] .y1 == tree [k] .y2) {// leaf node //
		if (L > tree [k] .max)
			tree [k] .max = L;
		return;

	}
	int midx = (tree [k] .x1 + tree [k] .x2) / 2;
	int midy = (tree [k] .y1 + tree [k] .y2) / 2;
	if (x <= midx) {
		if (y <= midy)
			insert (x, y, L, tree [k] .ch [0]);
		else
			insert (x, y, L, tree [k] .ch [2]);

	} else {// x> midx
		if (y <= midy)
			insert (x, y, L, tree [k] .ch [3]);
		else
			insert (x, y, L, tree [k] .ch [1]);

	}
	float m = tree [tree [k] .ch [0]]. max;
	for (int i = 1; i < 4; i ++)
		m = max (m, tree [tree [k] .ch [i]]. max);
	tree [k] .max = m;
}
inline bool corss (int x1, int y1, int x2, int y2, int k) {// Determine if the two rectangles intersect
	int x3 = tree [k] .x1;
	int y3 = tree [k] .y1;
	int x4 = tree [k] .x2;
	int y4 = tree [k] .y2;
	if (y2 < y3 || y4 < y1 || x4 < x1 || x2 < x3)
		return false;
	else
		return true;
}
// time: O (logN) // N * N rectangle
float Query (int x1, int y1, int x2, int y2, int k) {
	if (corss (x1, y1, x2, y2, k) == false || tree [k] .max == 0) // The rectangles do not intersect or the rectangle max == 0 returns 0
		return 0;
	if (x1 <= tree [k] .x1 && y1 <= tree [k] .y1 && tree [k] .x2 <= x2 && tree [k] .y2 <= y2) // If you want to query the rectangular coverage The current rectangle .. Then returns the current rectangle of the max value
		return tree [k] .max;
	// int midx = (tree [k] .x1 + tree [k] .x2) / 2;
	// int midy = (tree [k] .y1 + tree [k] .y2) / 2;
	float m [4] = {0, 0, 0, 0};
	for (int i = 0; i < 4; i ++)
		m [i] = Query (x1, y1, x2, y2, tree [k] .ch [i]);
	float mm = m [0];
	for (int i = 1; i < 4; i ++)
		mm = max (mm, m [i]);
	return mm;
}

int main () {
	return 0;
}