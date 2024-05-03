import java.util.Scanner; // 导入Scanner类

// 定义一个名为Calculator的类
class Calculator {
    // 成员变量
    private int num1;
    private int num2;

    // 构造方法
    public Calculator(int num1, int num2) {
        this.num1 = num1;
        this.num2 = num2;
    }

    // 成员方法 - 计算两数之和
    public int add() {
        return num1 + num2;
    }
}

public class Main { // 定义一个名为Main的类

    public static void main(String[] args) { // 主函数入口
        // 创建Calculator对象并初始化
        Calculator calculator = new Calculator(5, 10);

        // 调用成员方法计算两数之和
        int sum = calculator.add();

        // 输出变量值
        System.out.println("Sum of " + calculator.getNum1() + " and " + calculator.getNum2() + " is: " + sum);

        // 控制流程示例 - if-else条件语句
        if (sum > 10) {
            System.out.println("Sum is greater than 10");
        } else {
            System.out.println("Sum is less than or equal to 10");
        }

        // 控制流程示例 - for循环
        System.out.print("Printing numbers from 1 to 5: ");
        for (int i = 1; i <= 5; i++) {
            System.out.print(i + " ");
        }
        System.out.println(); // 换行

        // 控制流程示例 - while循环
        int countdown = 3;
        System.out.println("Countdown:");
        while (countdown > 0) {
            System.out.println(countdown);
            countdown--;
        }
        System.out.println("Go!");

        // 输入示例 - 使用Scanner类
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your name: ");
        String name = scanner.nextLine();
        System.out.println("Hello, " + name + "!");

        // 数组示例
        int[] numbers = {1, 2, 3, 4, 5};
        System.out.print("Array elements: ");
        for (int num : numbers) {
            System.out.print(num + " ");
        }
        System.out.println(); // 换行
    }
}
