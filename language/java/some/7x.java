// Main类是程序的入口，负责用户交互和调用UserDao进行相应的操作
import java.io.*;

public class Application {
    private UserDao userDao;

    public Application(UserDao userDao) {
        this.userDao = userDao;
    }

    public void setUserDao(UserDao userDao) {
        this.userDao = userDao;
    }

    public void registe() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        System.out.println("******注册用户******");
        System.out.print("请输入用户名:");
        String userName = br.readLine();

        User existingUser = userDao.getUser(userName, "");
        if (existingUser != null) {
            System.out.println("用户名已存在，请重新输入！");
            return;
        }

        System.out.print("请输入密码:");
        String password = br.readLine();

        System.out.print("请重新输入密码:");
        String confirmPassword = br.readLine();

        if (!password.equals(confirmPassword)) {
            System.out.println("两次输入的密码不相符，请重新输入！");
            return;
        }

        User newUser = new User(userName, password);
        if (userDao.addUser(newUser)) {
            System.out.println(userName + "，注册成功!");
        } else {
            System.out.println("注册失败，请稍后再试。");
        }
    }

    public void login() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        System.out.println("******登录******");
        System.out.print("请输入用户名:");
        String userName = br.readLine();

        System.out.print("请输入密码:");
        String password = br.readLine();

        User user = userDao.getUser(userName, password);
        if (user != null) {
            System.out.println(userName + "已登录");
        } else {
            System.out.println("用户名或密码错误，请重新输入！");
        }
    }

    public static void main(String[] args) throws IOException {
        UserDao userDao = new UserDaoForArray();
        Application app = new Application(userDao);

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        while (true) {
            System.out.println("请选择操作: 1.注册 2.登录 0.退出");
            String choice = br.readLine();

            switch (choice) {
                case "1":
                    app.registe();
                    break;
                case "2":
                    app.login();
                    break;
                case "0":
                    System.out.println("退出系统");
                    return;
                default:
                    System.out.println("无效选择，请重新输入！");
            }
        }
    }
}

// User类表示用户对象，包含用户名和密码信息
class User{
    private String username; // 用户名
    private String password; // 密码

    User(){}; // 无参构造函数

    User(String username,String password){ // 带参构造函数，接受用户名和密码作为参数
        this.username=username;
        this.password=password;
    }

    public String getUsername(){ // 获取用户名的方法
        return username;
    }

    public void setUsername(String username){ // 设置用户名的方法
        this.username=username;
    }

    public String getPassword(){ // 获取密码的方法
        return password;
    }

    public void setPassword(String password){ // 设置密码的方法
        this.password=password;
    }
}

// UserDao接口定义了对用户数据进行操作的规范
interface UserDao{
    boolean addUser(User user); // 添加用户的方法
    User getUser(String userName,String password); // 根据用户名和密码获取用户的方法
}

// UserDaoForArray类实现了UserDao接口，使用数组来存储用户数据
class UserDaoForArray implements UserDao{
    private User[] data; // 存储用户数据的数组
    private int count=0; // 用户数量

    public UserDaoForArray() {
        data = new User[100]; // 假设最大用户数量为100
        count = 0;
    }

    @Override
    public boolean addUser(User user){ // 实现添加用户的方法
        if(count==data.length){
            return false;
        }
        data[count]=user;
        count++;
        return true;
    }

    @Override
    public User getUser(String userName,String password){ // 实现根据用户名和密码获取用户的方法
        for(int i=0;i<count;i++){
            if(data[i].getUsername().equals(userName) && data[i].getPassword().equals(password)) {
                return data[i];
            }
        }
        return null;
    }
}
