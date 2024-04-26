// if...else switch
// for while do while
// break con
// type[
//基本数据类型 引用类型(zz)
// int a[];
// int[] p;
//a p是引用类型
//p=new int{1,2,3,4,5} 静态初始化 p是数组变量 new:申请内存
//a=p 
//简:type[] "名字"={元素}
//int[] ip new int[5];   //动态初始化  
//Object[] opp =new String  Object是最根本的类,前提都是子类    字符串默认是null
//opp.length            //求长度
//p["超过长度"] 抛出异常,使程序更加可控
//for(type variableName:arry | collection){
//   System.out.println(variavleName)
//}
//int[][] b=new int[5][];
//b[0]=new int[2];
//b[1]=new int[5];    b[1]还是引用类型
//b.length   5
//b[1].length  1
//b[0].length 2
//如果是:
//三维数组
//Arrays
//
//
//[修饰符(可选的)] class 类名 {...类体...}
//[修饰符] 属性

//static 如果在class中,则属于类 如果没有,则属于对象

class 1
{
    public static void main(String[] args)
    {
        byte b=(byte)233;
        System.out.println()
        int a[];
        int[] p;
        p=new int{1,2,3,4,5}   
        a=p;            //a和b在z中,类在z中
        p=a=null;       //p和a指向空  int{1,2,3,4,5} 变成内存垃圾 垃圾清除机制
        Student s=new Student();
        System.out.println(s.name)

        void swap(Data p){
            int x=p.x;
            p.x=p.y;
        
        Data p=new Data(a,b);
        s.swap(p);
        System.out.println("p.x="+p.x,"p.x="+p.y)
        }
    }
}
class Student
{
    //构造器:特殊的函数或者方法 如果没有,会默认一个没有参数的构造器
    static int age;
    Student(string str){           //和类的名字保持一样
        stuno=str;
    }
    Student(string str){           //构造器的重载
        this();                    //this 指正 类中的对象  类的属主
    }
    int age;
    String name;
    int getAge()

    void swap(Data p){
        int c=p.x;
        p.x=p.y;
        p.y=c;
    }
}

class Data
{
    int x;
    int y;
    Data(int x,int y){
        this.x=x;
        this.y=y;
    }
}
