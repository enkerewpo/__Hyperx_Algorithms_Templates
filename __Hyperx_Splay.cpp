#include <bits/stdc++.h>
#define MAXN 1000 + 5

int cnt, rt;
int Add[MAXN];

struct Tree {
	int key, num, size, fa, son[2];
} T[MAXN];

inline void PushUp (int x) {
	T[x].size = T[T[x].son[0]].size + T[T[x].son[1]].size + T[x].num;
}

inline void PushDown (int x) {
	if (Add[x]) {
		if (T[x].son[0]) {
			T[T[x].son[0]].key += Add[x];
			Add[T[x].son[0]] += Add[x];

		}
		if (T[x].son[1]) {
			T[T[x].son[1]].key += Add[x];
			Add[T[x].son[1]] += Add[x];

		}
		Add[x] = 0;

	}
}

inline int Newnode (int key, int fa) {// Create a new node and return
	++ cnt;
	T[cnt].key = key;
	T[cnt].num = T[cnt].size = 1;
	T[cnt].fa = fa;
	T[cnt].son[0] = T[cnt].son[1] = 0;
	return cnt;
}

inline void Rotate (int x, int p) {// 0 L-1 dextrorotation
	int y = T[x].fa;
	PushDown (y);
	PushDown (x);
	T[y].son[!p] = T[x].son[p];
	T[T[x].son[p]].fa = y;
	T[x].fa = T[y].fa;
	if (T[x].fa)
		T[T[x].fa].son[T[T[x].fa].son[1] == y] = x;
	T[x].son[p] = y;
	T[y].fa = x;
	PushUp (y);
	PushUp (x);
}

void Splay (int x, int To) {// Move the x node to the child of To
	while (T[x].fa != To) {
		if (T[T[x].fa].fa == To)
			Rotate (x, T[T[x].fa].son[0] == x);
		else {
			int y = T[x].fa, z = T[y].fa;
			int p = (T[z].son[0] == y);
			if (T[y].son[p] == x) Rotate (x, ! p), Rotate (x, p);
			else Rotate (y, p), Rotate (x, p);// a word spin

		}

	}
	if (To == 0) rt = x;
}

int GetPth (int p, int To) {// Returns the pth smallest node and moves to the child of To
	if (! rt || p > T[rt].size) return 0;
	int x = rt;
	while (x) {
		PushDown (x);
		if (p >= T[T[x].son[0]].size + 1 && p <= T[T[x].son[0]].size + T[x].num)
			break;
		if (p > T[T[x].son[0]].size + T[x].num) {
			p -= T[T[x].son[0]].size + T[x].num;
			x = T[x].son[1];

		} else
			x = T[x].son[0];

	}
	Splay (x, 0);
	return x;
}

int Find (int key) {
	// Returns the key value of the node if not returned 0 If it is transferred to the root
	if (! rt) return 0;
	int x = rt;
	while (x) {
		PushDown (x);
		if (T[x].key == key) break;
		x = T[x].son[key > T[x].key];

	}
	if (x) Splay (x, 0);
	return x;
}

int Prev () {
	// return to the root node of the non - focus
	if (! rt || ! T[rt].son[0]) return 0;
	int x = T[rt].son[0];
	while (T[x].son[1]) {
		PushDown (x);
		x = T[x].son[1];

	}
	Splay (x, 0);
	return x;
}

int Succ () {// Returns the successor to the root node
	if (! rt || ! T[rt].son[1]) return 0;
	int x = T[rt].son[1];
	while (T[x].son[0]) {
		PushDown (x);
		x = T[x].son[0];

	}
	Splay (x, 0);
	return x;
}

void Insert (int key) {// Insert the key value
	if (! rt)
		rt = Newnode (key, 0);
	else {
		int x = rt, y = 0;
		while (x) {
			PushDown (x);
			y = x;
			if (T[x].key == key) {
				T[x].num ++;
				T[x].size ++;
				break;

			}
			T[x].size ++;
			x = T[x].son[key > T[x].key];

		}
		if (! x)
			x = T[y].son[key > T[y].key] = Newnode (key, y);
		Splay (x, 0);

	}
}

void Delete (int key) {// Delete 1 node whose value is key
	int x = Find (key);
	if (! x) return;
	if (T[x].num > 1) {
		T[x].num--;
		PushUp (x);
		return;

	}
	int y = T[x].son[0];
	while (T[y].son[1])
		y = T[y].son[1];
	int z = T[x].son[1];
	while (T[z].son[0])
		z = T[z].son[0];
	if (! y && ! z) {
		rt = 0;
		return;

	}
	if (! y) {
		Splay (z, 0);
		T[z].son[0] = 0;
		PushUp (z);
		return;

	}
	if (! z) {
		Splay (y, 0);
		T[y].son[1] = 0;
		PushUp (y);
		return;

	}
	Splay (y, 0);
	Splay (z, y);
	T[z].son[0] = 0;
	PushUp (z);
	PushUp (y);
}

int GetRank (int key) {// Get the number of nodes with value <= key
	if (! Find (key)) {
		Insert (key);
		int tmp = T[T[rt].son[0]].size;
		Delete (key);
		return tmp;

	} else
		return T[T[rt].son[0]].size + T[rt].num;
}

void Delete (int l, int r) {// Delete all nodes with values ​​in[l, r] l!= r
	if (! Find (l)) Insert (l);
	int p = Prev ();
	if (! Find (r)) Insert (r);
	int q = Succ ();
	if (! p && ! q) {
		rt = 0;
		return;

	}
	if (! p) {
		T[rt].son[0] = 0;
		PushUp (rt);
		return;

	}
	if (! q) {
		Splay (p, 0);
		T[rt].son[1] = 0;
		PushUp (rt);
		return;

	}
	Splay (p, q);
	T[p].son[1] = 0;
	PushUp (p);
	PushUp (q);
}

int main () {
	return 0;
}