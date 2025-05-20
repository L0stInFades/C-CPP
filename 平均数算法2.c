#include <stdio.h>  // 包含标准输入输出库头文件

int main() {
	int number;     // 定义一个整数变量 number，用于存储用户输入的数字
	int sum = 0;    // 定义并初始化整数变量 sum 为 0，用于存储所有输入数字的总和
	int count = 0;  // 定义并初始化整数变量 count 为 0，用于记录输入数字的个数
	
	// 从标准输入读取一个整数并存储到 number 变量中
	scanf("%d", &number);
	
	// while 循环，当 number 不等于 -1 时继续执行循环体
	while (number != -1) {
		sum += number;  // 将输入的数字加到 sum 中
		count++;        // 计数器加一
		scanf("%d", &number);  // 再次从标准输入读取一个整数并存储到 number 变量中
	}
	
	// 打印所有输入数字的平均值
	// 1.0*sum/count 将整数除法转换为浮点数除法，以得到浮点数结果
	printf("%f\n", 1.0 * sum / count);
	
	return 0;  // 返回 0，表示程序正常结束
}

