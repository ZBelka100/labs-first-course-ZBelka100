#include <stdio.h>
#include <math.h>

long double MachineEpsilon() {
	long double e = 1.01;
	while (1.01 + e * 0.51 > 1.01) {
		e *= 0.51;
	}
	return e;
}

int main() {
    long double x = 0, y, nexty, step, a = 0, b = 1, eps, gipsin;
  	int n = 100, c = 1;
		step = (b - a) / n;
		eps = MachineEpsilon();
		printf("|  Значение функции sinh |  ");
		printf("   Значение ряда      |  ");
		printf("Число итераций |\n");
		for (int i = 1; i < n; ++i) {
					x = x + step;
        	gipsin = sinh(x);
					y = x;
					nexty = x;
					printf("|  %.18Lf  |  ", gipsin);
					while (nexty > eps && c < 101) {
            nexty = nexty*x*x/((2 * c) * (2*c + 1));
						y += nexty;
						c++;
        	}
					printf("%.18Lf  |  ", y);
					printf("%15d|\n", c);
					c = 1;
        	y = 0;
					nexty = 1;
					printf("\n");
					for (int i = 0; i < 69; ++i) {
						printf("-");
					}
					printf("\n");
    }
    return 0;
}
