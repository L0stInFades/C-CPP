#include<stdio.h>

int main() {
	int x; // 声明一个整数变量 x 用于存储输入的数字
	scanf("%d", &x); // 从用户输入读取一个整数并存储在 x 中
	
	int digit; // 声明一个整数变量 digit 用于存储 x 的每一位数字
	int ret = 0; // 声明并初始化一个整数变量 ret 用于存储逆序后的数字
	
	// 通过循环将数字 x 的各位数字逆序
	while (x > 0) {
		digit = x % 10; // 获取 x 的最后一位数字
		// 通过取模运算获取 x 的最后一位数字
		ret = ret * 10 + digit; // 将 digit 加到 ret 中，并将之前的数字左移一位
		// 将获取的数字加到 ret 中，并将 ret 的现有数字左移一位（乘以 10）
		printf("x=%d, digit=%d, ret=%d\n", x, digit, ret); // 打印当前 x、digit 和 ret 的值
		x /= 10; // 此处若只剩个位可以出循环，否则继续去掉去掉最后一位
    }
	
	printf("%d", ret); // 打印逆序后的数字
	return 0; // 返回 0 表示程序成功执行
}

