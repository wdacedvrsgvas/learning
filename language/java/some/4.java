// 定义一个Person类，使用封装
class Person {
    // 私有属性
    private String name;
    private int age;

    // 公共构造函数
    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }

    // 获取name属性的方法
    public String getName() {
        return name;
    }

    // 设置name属性的方法
    public void setName(String name) {
        this.name = name;
    }

    // 获取age属性的方法
    public int getAge() {
        return age;
    }

    // 设置age属性的方法
    public void setAge(int age) {
        this.age = age;
    }

    // 显示Person信息的方法
    public void displayInfo() {
        System.out.println("Name: " + name + ", Age: " + age);
    }
}

// 定义一个Student类，继承Person类，并重写displayInfo方法
class Student extends Person {
    private String studentId;

    public Student(String name, int age, String studentId) {
        super(name, age);
        this.studentId = studentId;
    }

    public String getStudentId() {
        return studentId;
    }

    public void setStudentId(String studentId) {
        this.studentId = studentId;
    }

    // 重写displayInfo方法
    @Override
    public void displayInfo() {
        System.out.println("Name: " + getName() + ", Age: " + getAge() + ", Student ID: " + studentId);
    }
}

// 定义一个Animal接口
interface Animal {
    void makeSound();
    void move();
}

// 实现Animal接口的Dog类
class Dog implements Animal {

    @Override
    public void makeSound() {
        System.out.println("Woof! Woof!");
    }

    @Override
    public void move() {
        System.out.println("The dog runs.");
    }
}

// 实现Animal接口的Cat类
class Cat implements Animal {

    @Override
    public void makeSound() {
        System.out.println("Meow! Meow!");
    }

    @Override
    public void move() {
        System.out.println("The cat walks.");
    }
}

// 定义一个Calculator类，提供基本的数学操作
class Calculator {

    public int add(int a, int b) {
        return a + b;
    }

    public int subtract(int a, int b) {
        return a - b;
    }

    public int multiply(int a, int b) {
        return a * b;
    }

    public double divide(int a, int b) {
        if (b == 0) {
            throw new ArithmeticException("Cannot divide by zero");
        }
        return (double) a / b;
    }
}

public class Main {
    public static void main(String[] args) {
        // 封装示例
        Person person = new Person("Alice", 30);
        person.displayInfo();

        // 方法重写示例
        Student student = new Student("Bob", 20, "S12345");
        student.displayInfo();

        // 接口示例
        Animal dog = new Dog();
        dog.makeSound();
        dog.move();

        Animal cat = new Cat();
        cat.makeSound();
        cat.move();

        // 底层实现示例
        Calculator calculator = new Calculator();
        System.out.println("Add: " + calculator.add(5, 3));
        System.out.println("Subtract: " + calculator.subtract(5, 3));
        System.out.println("Multiply: " + calculator.multiply(5, 3));
        System.out.println("Divide: " + calculator.divide(5, 3));
    }
}
