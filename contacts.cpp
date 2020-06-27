#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//结构体定义
typedef struct contact{
    char name[20];//姓名
    char phoneNumber[15];//号码（防止溢出、故略微加大了存储空间）
    char address[200];//住址
    struct contact *next;//next域
};
contact *Read(){//建立通讯录,将文件中的通讯录信息存储进链表
    contact *head,*temp,*s;
    FILE *fp;
    fp=fopen("contacts.txt","r");//打开存储通讯录的文件
    head=(struct contact*)malloc(sizeof(contact));//为头指针分配内存空间
    s=head;
    while(!feof(fp)){//文件非空
        temp=(struct contact*)malloc(sizeof(contact));
        fscanf(fp,"%s %s %s",temp->name,temp->phoneNumber,temp->address);//扫描通讯录文件中信息，存储至链表中
        s->next=temp;//尾插法建立
        s=temp;
    }
    fclose(fp);
    s->next=0;//将链表最后一位的next域置空
    return head;//返回链表头指针
}
int search(contact *head) {//查找功能
    int i = 0;//查找条件控制，1为姓名查找，2为号码查找，3为住址查找
    int flag = 0;//标志查找成功和失败，成功>0,失败=0;
    char searName[20], searPhoneNum[15], searAddress[200];
    contact *temp = head;
    printf("请输入查找方式(1.按姓名查找 2.按电话号码查找 3. 按住址查找)：");
    scanf("%d",&i);
    switch (i) {
        case 1:
            printf("请输入姓名：");
            scanf("%s", searName);
            while (temp->next != 0) {//遍历链表
                if (strcmp(temp->name, searName) == 0) {//找到符合姓名条件的联系人
                    printf("%s %s %s", temp->name, temp->phoneNumber, temp->address);
                    flag++;//查找成功，flag+1
                    break;
                }
                else{
                    temp = temp->next;//否则继续向下遍历
                }
            }
            break;
        case 2://号码查找,思路同上，不再赘述
            printf("请输入电话号码：");
            scanf("%s", searPhoneNum);
            while (temp->next != 0) {
                if (strcmp(temp->phoneNumber, searPhoneNum) == 0) {
                    printf("%s %s %s", temp->name, temp->phoneNumber, temp->address);
                    flag++;
                    break;
                }
                else{
                    temp = temp->next;
                }
            }
            break;
        case 3://地址查找
            printf("请输入家庭住址：");
            scanf("%s", searAddress);
            while (temp->next != 0) {
                if (strcmp(temp->address, searAddress) == 0) {
                    printf("%s %s %s", temp->name, temp->phoneNumber, temp->address);
                    flag++;
                    break;
                }
                else{
                    temp=temp->next;
                }
            }
            break;
        default:
            printf("格式错误!");
    }
    if(flag>0){
        printf("\n查找成功!\n");
    }
    else{
        printf("\n查找失败!\n");
    }
}
//增加新的联系人
int add(contact *head){
    //已经通过测试
    contact *addman;//用于存储可能增加的联系人信息
    contact *s;
    s = head;
    addman = (contact *)malloc(sizeof(contact)); //为可能新增的链表结点分配内存空间
    printf("请输入要添加的联系人姓名、电话号码以及住址，以空格分隔：");
    scanf("%s %s %s",addman->name,addman->phoneNumber,addman->address);
    while(s->next!=NULL){//遍历列表
        if((strcmp(addman->phoneNumber,s->phoneNumber)==0)&&(strcmp(addman->name,s->name)==0)){//判断是否存在，考虑有可能重名，故使用姓名号码双重确认
            printf("此联系人已存在！\n");
            return 0;//存在时退出函数，不确定能不能这么写
        }
        else{//不重复，继续读
            s=s->next;
        }
    }
    s->next=addman;//表尾插入新结点
    s=addman;
    s->next=0;
    return 0;
}
int Delete(contact *head){
    //测试通过
    contact *temp;//中间结点
    char delNum[15],delName[20];//存储输入的号码姓名数据
    printf("请输入要删除的联系人姓名：");
    scanf("%s",delName);
    printf("请输入要删除的联系人电话：");
    scanf("%s",delNum);
    while(head->next!=0){//遍历链表
        if((strcmp(delNum,head->phoneNumber)==0)&&(strcmp(delName,head->name)==0)){//比较判定是否为要删除对象
            temp=head->next;//删除操作
            head->next=temp->next;
            printf("删除成功");
            return 0;
        }
        else{
            head=head->next;//继续遍历
        }
    }
printf("删除失败!\n");
}
void change(contact *head){//更新联系人
    //测试通过
    contact *temp=head;
    int mode=0;
    int flag=0;
    char tempName[20],tempNum[15];//存储用于识别比较的原姓名及原号码
    printf("请输入要更改的联系人姓名：");
    scanf("%s",tempName);
    printf("请输入要更改的联系人原电话：");
    scanf("%s",tempNum);
    printf("请输入要修改的内容,1为姓名,2为号码,3为住址：");
    scanf("%d",&mode);
    switch (mode) {
        case 1:{
            char changeName[20];
            printf("请输入修改后的名字：");
            scanf("%s",changeName);
            while(temp->next!=0){
                if ((strcmp(tempNum,temp->phoneNumber)==0)&&(strcmp(tempName,temp->name)==0)){
                    strcpy(temp->name,changeName);
                    flag=1;
                    break;
                }
                else
                    temp=temp->next;
            }
        }
            break;
        case 2: {
            char changeNum[20];
            printf("请输入修改后的号码：");
            scanf("%s", changeNum);
            while (temp->next != 0) {
                if ((strcmp(tempNum, temp->phoneNumber) == 0) && (strcmp(tempName, temp->name) == 0)) {
                    strcpy(temp->phoneNumber, changeNum);
                    flag = 1;
                    break;
                } else
                    temp = temp->next;
            }
        }
            break;
        case 3:{
            char changeAddress[200];
            printf("请输入修改后的住址：");
            scanf("%s", changeAddress);
            while(temp->next!=0){
                if ((strcmp(tempNum,temp->phoneNumber)==0)&&(strcmp(tempName,temp->name)==0)){
                    strcpy(temp->address,changeAddress);
                    flag=1;
                    break;
                }
                else
                    temp=temp->next;
            }
        }
            break;
    }
    if(flag==1){
        printf("修改成功!\n");
    }
    else{
        printf("修改失败!\n");
    }
}
void update(contact *head){//通过测试
    contact *s=head->next;
    FILE *fp1;
    fp1 = fopen("contacts.txt", "w");
    while(s!=0){
        printf("%s %s %s\n", s->name, s->phoneNumber, s->address);
        if(s->next!=0)
            fprintf(fp1, "%s %s %s\n", s->name, s->phoneNumber, s->address);
        else
            fprintf(fp1, "%s %s %s", s->name, s->phoneNumber, s->address);
        s=s->next;
    }
    fclose(fp1);
    printf("更新成功!\n");
}
void SetNULL(contact *head){//链表和存储文件置空
    head=0;
    FILE *fp;
    fp=fopen("contacts.txt","w");
    fprintf(fp,"\n");
}
int main() {
    printf("欢迎使用通讯录管理系统!");
    contact *headp;
    headp = Read();//读取文件
    while (1)
    {
        printf("\n请选择接下来要进行的操作:\n1.查看并保存全部通讯录\n2.增加联系人");
        printf("\n3.删除联系人\n4.查找联系人\n5.更改联系人\n6.关闭程序\n请输入:");
        //各个数字的功能如上
        int choose;
        scanf("%d",&choose);
        //选择模块
        switch(choose){
            case 1:{
                update(headp);
                break;
            }
            case 2:{
                add(headp);
                break;
            }
            case 3:{
                Delete(headp);
                break;
            }
            case 4:{
                search(headp);
                break;
            }
            case 5:{
                change(headp);
                break;
            }
            case 6:{
                exit(0);
                break;
            }
            default:{
                break;
            }
        }
    }
    return 0;
}
