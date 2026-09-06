#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

typedef struct {
    double real;
    double imag;
} Complex;

Complex add(Complex a, Complex b) {
    Complex c = {a.real + b.real, a.imag + b.imag};
    return c;
}

Complex sub(Complex a, Complex b) {
    Complex c = {a.real - b.real, a.imag - b.imag};
    return c;
}

Complex mul(Complex a, Complex b) {
    Complex c = {
        a.real * b.real - a.imag * b.imag,
        a.real * b.imag + a.imag * b.real
    };
    return c;
}

void fft(Complex a[], int n, int inverse) {
    if (n == 1)
        return;

    Complex even[n / 2], odd[n / 2];

    for (int i = 0; i < n / 2; i++) {
        even[i] = a[2 * i];
        odd[i] = a[2 * i + 1];
    }

    fft(even, n / 2, inverse);
    fft(odd, n / 2, inverse);

    double angle = 2 * PI / n * (inverse ? -1 : 1);
    Complex w = {1, 0};
    Complex wn = {cos(angle), sin(angle)};

    for (int k = 0; k < n / 2; k++) {
        Complex t = mul(w, odd[k]);

        a[k] = add(even[k], t);
        a[k + n / 2] = sub(even[k], t);

        w = mul(w, wn);
    }

    if (inverse) {
        for (int i = 0; i < n; i++) {
            a[i].real /= 2;
            a[i].imag /= 2;
        }
    }
}

int main() {
    int m, n;

    printf("Enter size of A: ");
    scanf("%d", &m);

    printf("Enter size of B: ");
    scanf("%d", &n);

    double A[m], B[n];

    printf("Enter elements of A:\n");
    for (int i = 0; i < m; i++)
        scanf("%lf", &A[i]);

    printf("Enter elements of B:\n");
    for (int i = 0; i < n; i++)
        scanf("%lf", &B[i]);

    int size = m + n - 1;
    int N = 1;

    while (N < size)
        N *= 2;

    Complex FA[N], FB[N];

    for (int i = 0; i < N; i++) {
        FA[i].real = (i < m) ? A[i] : 0;
        FA[i].imag = 0;

        FB[i].real = (i < n) ? B[i] : 0;
        FB[i].imag = 0;
    }

    fft(FA, N, 0);
    fft(FB, N, 0);

    for (int i = 0; i < N; i++)
        FA[i] = mul(FA[i], FB[i]);

    fft(FA, N, 1);

    printf("Convolution:\n");

    for (int i = 0; i < size; i++)
        printf("%.2f ", FA[i].real);

    printf("\n");

    return 0;
}