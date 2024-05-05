//创建了一个Student类来表示学生，包含学生的姓名、年龄和年级等信息。然后，我们创建了一个StudentManager类来管理学生信息，包括添加学生和删除学生的方法。在主类Main中，我们创建了一个学生对象并将其添加到学生管理器中，然后又将其从学生管理器中删除。这个例子展示了如何使用类的封装和方法调用来组织和管理代码。


// 定义一个名为Student的类来表示学生
public class Student {
    private String name;
    private int age;
    private String grade;

    // 构造方法
    public Student(String name, int age, String grade) {
        this.name = name;
        this.age = age;
        this.grade = grade;
    }

    // 获取学生姓名
    public String getName() {
        return name;
    }

    // 获取学生年龄
    public int getAge() {
        return age;
    }

    // 获取学生年级
    public String getGrade() {
        return grade;
    }
}

// 定义一个名为StudentManager的类来管理学生信息
public class StudentManager {
    // 添加学生方法
    public void addStudent(Student student) {
        // 在实际应用中，可以将学生信息添加到数据库中
        System.out.println("Added student: " + student.getName());
    }

    // 删除学生方法
    public void removeStudent(Student student) {
        // 在实际应用中，可以从数据库中删除学生信息
        System.out.println("Removed student: " + student.getName());
    }
}

// 主类
public class Main {
    public static void main(String[] args) {
        // 创建一个学生对象
        Student student1 = new Student("Alice", 20, "Sophomore");

        // 创建一个学生管理器对象
        StudentManager studentManager = new StudentManager();

        // 向学生管理器中添加学生
        studentManager.addStudent(student1);

        // 从学生管理器中删除学生
        studentManager.removeStudent(student1);
    }
}
