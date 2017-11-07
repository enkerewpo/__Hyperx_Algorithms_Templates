#include <ext/pb_ds/priority_queue.hpp>

using namespace __gnu_pbds;

typedef priority_queue<int, std::greater<int>, pairing_heap_tag, std::allocator<char> > heap;
heap p;
heap::iterator it;

int main() {
	p.push(5);
	p.push(2);
	p.push(10);
	p.push(1);
	for (int x : p) printf("%d ", x); // iterating by position
	printf("\n");
	for (it = p.begin(); it != p.end(); it++) {
		if (*it == 10) {
			p.erase(it);
		}
		if (*it == 2) {
			p.modify(it, 2333);
		}
	}
	for (int x : p) printf("%d ", x);
	printf("\n");
	heap tmp;
	tmp.push(142857);
	p.join(tmp);
	for (int x : p) printf("%d ", x);
	printf("\n");
	for (int x : tmp) printf("%d ", x);
	printf("\n");
	return 0;
}