#include <cstdio>
#include <algorithm>
#include <ctime>
#include <cstring>
#include <cstdlib>
#define S(...) system(__VA_ARGS__)
using namespace std;

int main() {
	FILE* out = fopen("__Hyperx_Test.txt", "w");
	int sed;
	srand(clock() + sed  << 3);
	int lenA = rand() % 10007 + 8000;
	int lenB = rand() % 10009 + 8000;
	// printf("lenA = %d,  lenB = %d\n", lenA, lenB);
	int cur = 0;
	char tmp[20005];
	memset(tmp, 0, sizeof tmp);
	if (rand() % 4 == 0) tmp[++cur] = '-';
	tmp[++cur] = rand() % 9 + 1 + '0';
	while (cur <= lenA) tmp[++cur] = rand() % 10 + '0';
	// printf("%s ", tmp + 1);
	fprintf(out, "%s\n", tmp + 1);
	cur = 0;
	memset(tmp, 0, sizeof tmp);
	if (rand() % 2 == 0) tmp[++cur] = '-';
	tmp[++cur] = rand() % 9 + 1 + '0';
	while (cur <= lenB) tmp[++cur] = rand() % 10 + '0';
	// printf("%s ", tmp + 1);
	fprintf(out, "%s\n", tmp + 1);
	fclose(out);
	return 0;
}