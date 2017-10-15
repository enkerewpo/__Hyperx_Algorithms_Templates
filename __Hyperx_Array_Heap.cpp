#include <bits/stdc++.h>
/**
 * This is a heap practice implement coded by Kvar_ispw17.
 * email: enkerewpo@gmail.com
 * blog: enkerewpo.github.io
 */
namespace __gnu_cxx_heap
{

int inline __left(int _x)
{
	return _x * 2;
}

int inline __right(int _x)
{
	return _x * 2 + 1;
}

int inline __parent(int _x)
{
	return floor(_x / 2);
}

template <typename _Tp> void inline
/**
 * @brief This function will obtain the heap feature along in subheap rooted at @idx.
 *        using the datas in array @A[] with size @heap_size.
 * @param A         Input Array
 * @param idx       Rooted being processed root
 * @param heap_size the size of the full structure
 */
max_heapify(_Tp A[], int idx, size_t heap_size)
{
	int l = __left(idx);
	int r = __right(idx);
	int max_e;
	if (l <= (int)heap_size && A[l] > A[idx]) max_e = l;
	else max_e = idx;
	if (r <= (int)heap_size && A[r] > A[max_e]) max_e = r;
	if (max_e != idx) {
		std::swap(A[max_e], A[idx]);
		max_heapify(A, max_e, heap_size);
	}
}

template <typename _Tp> void inline
/**
 * @brief This is going to build a heap from pointer @begin to @end.
 * @param begin pointer
 * @param end   pointer
 */
build_max_heap(_Tp* begin, _Tp* end)
{
	size_t size = end - begin - 1;
	for (int iter = size / 2; iter >= 0; iter--) {
		max_heapify(begin, iter, size);
	}
}

template <typename _Tp> inline
/**
 * [__swap description]
 * @param lhs [description]
 * @param rhs [description]
 */
void __swap(_Tp &lhs, _Tp &rhs)
{
	_Tp tmp = rhs;
	rhs = lhs;
	lhs = tmp;
}

template <typename _Tp> inline
/**
 * sort on heap function
 * @param begin pointer
 * @param end   pointer
 */
void sort_heap(_Tp* begin, _Tp* end)
{
	build_max_heap(begin, end);
	size_t size = end - begin - 1;
	for (int iter = size; iter >= 1; iter--) {
		__swap(begin[0], begin[iter]);
		max_heapify(begin, 0, --size);
	}
}

template <typename _Tp> inline
_Tp maximum_heap(_Tp* begin)
{
	return begin[0];
}

template <typename _Tp> inline
/**
 * pop heap top element to positoin @end
 * @param begin pointer
 * @param end   pointer
 */
void pop(_Tp* begin, _Tp* end)
{
	size_t size = end - begin - 1;
	if (end - begin < 1) {
		fprintf(stderr, "heap size is zero when it was instruct to pop()\n");
	}
	__swap(begin[0], begin[size]);
	size--;
	max_heapify(begin, 0, size);
}

template <typename _Tp> inline
/**
 * increase key in heap
 * @param A   array store _Tp vars
 * @param idx index
 * @param key keyword
 */
void heap_increase(_Tp A[], int idx, _Tp key)
{
	A[idx] = key;
	while (idx > 1 and A[__parent(idx)] < A[idx]) {
		__swap(A[idx], A[__parent(idx)]);
		idx = __parent(idx);
	}
}

template <typename _Tp> inline
/**
 * push to heap function
 * @param begin pointer
 * @param end   pointer
 * @param _x    input _Tp type varibles
 */
void push(_Tp* begin, _Tp* end, _Tp _x)
{
	size_t size = end - begin;
	heap_increase(begin, size, _x);
}

}

int main()
{
	int a[20] = {0, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
	puts("original sequences:");
	for (int i = 1; i <= 10; i++) printf("%d ", a[i]);
	__gnu_cxx_heap::build_max_heap(a + 1, a + 10 + 1);
	printf("\n\n");

	puts("after build_max_heap:");
	for (int i = 1; i <= 10; i++) printf("%d ", a[i]);
	printf("\n\n");

	puts("after sort_heap:");
	__gnu_cxx_heap::sort_heap(a + 1, a + 10 + 1);
	for (int i = 1; i <= 10; i++) printf("%d ", a[i]);
	printf("\n\n");

	__gnu_cxx_heap::build_max_heap(a + 1, a + 10 + 1);
	puts("got maximum element:");
	printf("%d\n", __gnu_cxx_heap::maximum_heap(a + 1));
	printf("\n");

	puts("after pop element:");
	__gnu_cxx_heap::pop(a + 1, a + 10 + 1);
	for (int i = 1; i <= 10; i++) printf("%d ", a[i]);
	printf("\n\n");

	__gnu_cxx_heap::build_max_heap(a + 1, a + 10 + 1);
	puts("after push 15:");
	__gnu_cxx_heap::push(a + 1, a + 11, 15);
	for (int i = 1; i <= 11; i++) printf("%d ", a[i]);
	printf("\n\n");

	return 0;
}
