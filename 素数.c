// 包含标准输入/输出头文件，用于使用printf和scanf函数
#include <stdio.h>

int main() {
	// 声明整数变量x，用于存储用户输入的值
	int x;
	
	// 读取用户输入并将其存储在变量x中
	scanf("%d", &x);
	
	// 声明整数变量i，用于遍历可能的因数
	int i;
	
	// 初始化标志变量isPrime，假设x是素数
	int isPrime = 1; // x是否是素数的标志，初始值为真（即假设x是素数）
	
	// 遍历从2到x-1的所有整数，检查是否有能整除x的因数
	for (i = 2; i < x; i++) {
		// 如果x能被当前因数i整除，则x不是素数
		if (x % i == 0) {
			isPrime = 0; // 发现因数，置标志为假（即x不是素数）
		}
	}
	
	// 根据最终的标志值输出结果
	if (isPrime == 1) {
		// 如果isPrime仍为1，表明未找到因数，故x是素数
		printf("是素数\n");
	} else {
		// 否则，x不是素数
		printf("不是素数\n");
	}
	
	// 主函数返回值，表示程序执行成功
	return 0;
}
