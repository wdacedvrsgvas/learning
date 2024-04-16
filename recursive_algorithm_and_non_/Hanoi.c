#include<stdio.h>

void hanoi_recursion(int n,char source,char auxiliary,char destination){
    if(n==1){
        printf("Move disk 1 from rod %c to rod %c\n",source,destination);
        return;
    }
    hanoi_recursion(n-1,source,destination,auxiliary);
    printf("Move disk %d from rod %c to rod %c\n",n-1,source,destination);
    hanoi_recursion(n-1,auxiliary,source,destination);
}

int main()
{
    int n;
    printf("Please enter disk numbers");
    scanf("%d",&n);
    hanoi_recursion(n,'A','B','C');
    return 0;
}