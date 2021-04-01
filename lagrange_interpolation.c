#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

/*

    Note: some minor inconvience in input.

    Input consists of entering x-points and then y-points.
    Thus, there will be two arrays of x and y-points, respectively.

    E.g:
    *User input for x-points*: 4  -1  3.5 -> x[4, -1, 3.5]
    *User input for y-points*: 1  -8  2.7 -> y[1, -8, 2.7]

    Therefore, point-pairs will be (the program will not create those):
    1 -> (4, 1)
    2 -> (-1, -8)
    3 -> (3.5, 2.7)

    Keep in mind this thing before testing!

*/

void print_err(char *str) {

    write(2, str, strlen(str));

}

void show_arr(double *arr, int n) {

    for(int i = 0; i < n; ++i) {

        printf("arr[%d] = %lf\t", i, arr[i]);

        if(i == n - 1) {

            printf("\n");

        }

    }
}

double *create_arr(int n) {

    double *arr = (double*)malloc(n * sizeof(double));

    for(int i = 0; i < n; ++i) {

        scanf("%lf", &arr[i]);

    }

    return arr;
}

double get_polynomial(double *x, int n,  int i, double x_val){

    /*

    PROD -> equivalent of math product sign Π (pi)
    x.j -> x with index j

    Polynomial
    l.n(x) = PROD(0, n && i != j) { (x - x.j) / (x.i - x.j) }

    */

    double res = 1;
    for(int j = 0; j <= n; ++j) {

        if(i == j) { continue; }

        if(x[i] == x[j]) {

            print_err("Error: division by zero\n");
            exit(0);

        }

        res *= (x_val - x[j]) / (x[i] - x[j]);

    }
    
    return res;
}

double lagrange_interpol(double *x, double *y, int n, double x_val) {

    /* 
    
    x.k -> x with index k
    SUM -> equivalent of math sum sign Σ (sigma)
    l.k(x) -> Polynomial (l) of x with index k -> [l(x)].k

    Lagrange Polynomial Interpolation
    P.n(x) = SUM(0, n) { l.k(x) * f(x.k) }

    */

    double res = 0;

    for(int i = 0; i < n; ++i) {

        res += (get_polynomial(x, n, i, x_val) * y[i]);

    }

    return res;
}

int main() {

    printf("Enter the amount of points:\n");
    double n = 0;
    scanf("%lf", &n);

    printf("Enter x-points:\n");
    double *x = create_arr(n);

    printf("Enter y-points:\n");
    double *y = create_arr(n);

    printf("Enter x-value to calculate:\n");
    double x_val = 0;
    scanf("%lf", &x_val);

    printf("X-points:\n");
    show_arr(x, n);
    printf("Y-points:\n");
    show_arr(y, n);

    printf("The result is:\n%lf", lagrange_interpol(x, y, n, x_val));
}
