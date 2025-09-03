#include <stdio.h>

int main() {
    int n = 0, digit;
    char c;

    // ورودی عدد تا رسیدن به ':' به‌جای \n
    while ((c = getchar()) != ':') {
        digit = c - '0';
        n = n * 10 + digit;
    }

    int is_prime = 1;

    if (n <= 1) {
        is_prime = 0;
    } else {
        for (int i = 2; i < n; i++) {
            if (n % i == 0) {
                is_prime = 0;
                break;
            }
        }
    }

    if (is_prime)
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}
