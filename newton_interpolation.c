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

double get_divided_diff(double *x, double *y, int n) {

    /* 
    
    x.n -> x with index n
    SUM -> equivalent of math sum sign Σ (sigma)
    PROD -> equivalent of math product sign Π (pi)

    Newton Divided Difference
    f[x.0, ... , x.n] = SUM(0, n) { 

        y.i / PROD(0, n && i != j) { x.i - x.j } 

    }

    */

    double res = 0, temp = 1;
    for (int i = 0; i < n; ++i) {

        for(int j = 0; j < n; ++j) {

            if(i == j) { continue; }

            if(x[i] == x[j]) {

                print_err("Error: division by zero\n");
                exit(0);

            }

            temp *= (x[i] - x[j]);
            
        }

        res += (y[i] / temp);
        temp = 1;

    }

    return res;
}

double get_polynomial(double *x, double x_val, int n){

    /*

    x.(n - 1) -> x with index (n - 1)

    Polynomial
    e.n(x) = (x - x.0) * (x - x.1) * ... * (x - x.(n - 1))

    */

    double res = 1;
    for(int i = 0; i < n - 1; ++i) {

        res *= (x_val - x[i]);

    }

    return res;
}

double newton_interpol(double *x, double *y, int n, double x_val) {

    /* 
    
    x.k -> x with index k
    SUM -> equivalent of math sum sign Σ (sigma)
    e.k(x) -> Polynomial (e) of x with index k -> [e(x)].k

    Newton Polynomial Interpolation
    P.n(x) = f[x.0] + SUM(1, n) { f[x.0, ... , x.k] * e.k(x) }

    */

    double res = 0;

    for(int i = 0; i < n; ++i) {

        res += (get_divided_diff(x, y, i + 1) * get_polynomial(x, x_val, i + 1));

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

    printf("The result is:\n%lf", newton_interpol(x, y, n, x_val));
}
