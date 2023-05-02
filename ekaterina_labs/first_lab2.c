#include <stdio.h>

void report(int p[], int n, int lb, int ub) {
	long int a = 1;
	int i;
	int temp;

	for (i = 0; i < n - 1; i++) {
		a <<= 1;
		a++;
		/// 0000.....0000000001
		/// 0000.....0000000010
		/// 0000.....0000000011
		/// 0000.....0000000110
		/// 0000.....0000000111
		/// 0000.....0000001110
		/// <...>
		/// 0000.....0011...111
	}
	temp = a;
	for (i = 0; i < temp; i++) {
		int j;
		int sum = 0;

		for (j = n - 1; j >= 0; j--) {
			if (a & (1 << j)) {
				sum += p[n - j - 1];
			}
		}
		if (sum >= lb && sum <= ub) {
			printf("{ ");
			for (j = n - 1; j >= 0; j--) {

				if (a & (1 << j)) {
					printf(" %d ", n - j - 1);
				}
			}
			printf(" }\n");
		}
		a -= 1;
	}
}


int main() {
	int pole[] = { 1, 5, 6, -1, 1 , 2, 3, 4, 5};
	report(pole, 9, 2, 5);
	return 0;
}