#include <bits/stdc++.h>
using namespace std;
/**
 * This is a leftist heap practice implement coded by Kvar_ispw17.
 * email: enkerewpo@gmail.com
 * blog: enkerewpo.github.io
 */
class node
{
public:
	node* ls;
	node* rs;
	int x, npl;
};

typedef node heap;
typedef node* node_addr;

heap* mesh(heap* &lhs, heap* &rhs)
{
	if (lhs == NULL) return rhs;
	if (rhs->x > lhs->x) swap(lhs, rhs);
	lhs->rs = mesh(lhs->rs, rhs);
	int l, r;
	if (lhs->ls == NULL) l = 0;
	else l = lhs->ls->npl;
	r = lhs->rs->npl;
	if (l < r) swap(lhs->ls, lhs->rs);
	else lhs->npl = lhs->rs->npl + 1;
	return lhs;
}

heap* meld(heap* &lhs, heap* &rhs)
{
	if (lhs == NULL)
		return rhs;
	if (rhs == NULL)
		return lhs;
	return mesh(lhs, rhs);
}

void insert(int _x, heap* &h)
{
	node* x = new node;
	x->x = _x;
	x->ls = NULL;
	x->rs = NULL;
	x->npl = 0;
	h = meld(x, h);
}

int pop(heap* &h)
{
	int ret = h->x;
	h = meld(h->ls, h->rs);
	return ret;
}

int main()
{
	heap* h = NULL;
	while (1) {
		int t;
		cin >> t;
		insert(t, h);
	}
	return 0;
}