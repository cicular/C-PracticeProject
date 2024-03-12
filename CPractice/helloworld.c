#include <stdio.h>

double avg(double l, double m) {
	double result = (l + m) / 2.0;
	return result;
}

void main() {
	printf("HelloWorld.\n");
	double r = avg(4.1, 5.7);
	printf("r = %f", r);
}
