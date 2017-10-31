#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>
using namespace __gnu_pbds;
using namespace std;
typedef tree<int, null_type, less<int>, splay_tree_tag, tree_order_statistics_node_update> splay;
splay s;
splay :: iterator it;
int main() {

	for (int i = 20; i >= 15; i--) s.insert(i);  //15 16 17 18 19 20

	for(it = s.begin(); it != s.end(); it++) printf("%d ", *it);
	printf("\n");

	it = s.find_by_order(3);
	printf("NO.4 = %d\n", *it); 	// return NO.k+1 if you input find_by_order(k)

	int rnk = s.order_of_key(16);
	printf("RANK OF 16 is %d\n", rnk + 1);  // return how many items are "less" than your input

	splay t; t.clear();
	t.join(s); // copy 's' to 't'
	printf("    t = ");
	for (it = t.begin(); it != t.end(); it++) printf("%d ", *it);
	printf("\n");

	splay u; u.clear();
	t.split(17, u); // clear 'u' and move items "greater" then 17 to 'u'
	printf("    u = ");
	for (it = u.begin(); it != u.end(); it++) printf("%d ", *it);
	printf("\n");

	return 0;
}
