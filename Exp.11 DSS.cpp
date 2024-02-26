#include <stdio.h>

// Function to find the greatest common divisor using Euclidean Algorithm
int gcd(int a, int b) {
    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int a, b;

    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);

    int result = gcd(a, b);
    printf("GCD of %d and %d is %d\n", a, b, result);

    return 0;
}

