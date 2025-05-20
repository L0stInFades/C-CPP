#include <stdio.h>

int main() {
    int x;
    int n = 0;
    printf("请输入一个整数: ");
    scanf("%d", &x);
    n++;
    x /= 10;
    while (x > 0) {
        n++;
        x /= 10;
        printf("x=%d, n=%d\n", x, n);
    }
    printf("数字的位数: %d\n", n);
    return 0;
}







