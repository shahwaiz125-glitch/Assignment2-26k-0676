#include <stdio.h>

int sumOfProperDivisors(int x) {
    int sum = 0;
    for (int i = 1; i <= x / 2; i++) {
        if (x % i == 0) {
            sum += i;
        }
    }
    return sum;
}
int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    printf("\nAmicable pairs up to %d:\n", n);
    int count = 0;

    for (int a = 1; a <= n; a++) {
        int b = sumOfProperDivisors(a);
        if (b > a && b <= n && sumOfProperDivisors(b) == a) {
            printf("(%d, %d)\n", a, b);
            count++;
        }
    }

    if (count == 0) {
        printf("No amicable pairs found up to %d.\n", n);
    } else {
        printf("Total pairs: %d\n", count);
    }
}