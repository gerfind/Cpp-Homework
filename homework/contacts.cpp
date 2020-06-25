#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
 * 姓名地址中不能含有空格！！
 * 该问题难以解决，故我考虑放弃
 * （考虑到姓名地址在同一行存储，上次的方法并不能分割）
 */
//结构体定义
typedef struct node{
    char name[20];//姓名
    char phoneNumber[15];//号码（防止溢出、故略微加大了存储空间）
    char address[200];//住址
    struct node *next;//next域
}contact;
//建立通讯录,将文件中的通讯录信息存储进链表
contact *Read(){
    contact *head,*temp,*s;
    FILE *fp;
    fp=fopen("通讯录.txt","r");//打开存储通讯录的文件
    head=(contact*)malloc(sizeof(contact));//为头指针分配内存空间
    s=head;
    while(!feof(fp)){//文件非空
        fscanf(fp,"%s %s %s",&temp->name,&temp->address,&temp->phoneNumber);//扫描通讯录文件中信息，存储至链表中
        s->next=temp;//尾插法建立
        s=temp;
    }
    fclose(fp);
    s->next=NULL;//将链表最后一位的next域置空
    return head;//返回链表头指针
}
void search(contact *head) {//查找功能
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
            while (temp->next != NULL) {//遍历链表
                if (strcmp(temp->name, searName) == 0) {//找到符合姓名条件的联系人
                    printf("%s %s %s", temp->name, temp->phoneNumber, temp->address);
                    flag++;//查找成功，flag+1
                }
                else{
                    temp = temp->next;//否则继续向下遍历
                }
            }
            if(flag>0){
                printf("查找成功!\n");

            }
            else
                printf("查找失败!\n");
        break;
        case 2://号码查找,思路同上，不再赘述
            printf("请输入电话号码：");
            scanf("%s", searPhoneNum);
            while (temp->next != NULL) {
                if (strcmp(temp->phoneNumber, searPhoneNum) == 0) {
                    printf("%s %s %s", temp->name, temp->phoneNumber, temp->address);
                    flag++;
                    break;
                }
                else{
                    temp = temp->next;
                }
                if(flag>0){
                    printf("查找成功!\n");
                }
                else{
                    printf("查找失败!\n");
                }
            }
            break;
        case 3://地址查找
            printf("请输入家庭住址：");
            scanf("%s", searAddress);
            while (temp->next != NULL) {
                if (strcmp(temp->address, searAddress) == 0) {
                    printf("%s %s %s", temp->name, temp->phoneNumber, temp->address);
                    break;
                }
                else{
                    temp=temp->next;
                }
            }
            break;
        default:
            printf("格式错误!\n");
    }
}
//增加新的联系人
void add(contact *head){
    contact *addman;//用于存储可能增加的联系人信息
    contact *s=head;
    addman=(contact*)malloc(sizeof(contact));//为可能新增的链表结点分配内存空间
    printf("请输入要添加的联系人姓名、电话号码以及住址，以空格分隔：");
    scanf("%s %s %s",addman->name,addman->phoneNumber,addman->address);
    while(s->next!=NULL){//遍历列表
        if((strcmp(addman->phoneNumber,s->phoneNumber)==0)&&(strcmp(addman->name,s->name)==0)){//判断是否存在，考虑有可能重名，故使用姓名号码双重确认
            printf("此联系人已存在！\n");
            return;//存在时退出函数，不确定能不能这么写
        }
        else{//不重复，继续读
            s=s->next;
        }
    }
    s->next=addman;//表尾插入新结点
    s=addman;
    s->next=NULL;
}
void Delete(contact *head){//删除符合条件的结点
    contact *temp;//中吉街店
    char delNum[15],delName[20];//存储输入的号码姓名数据
    printf("请输入要删除的联系人姓名：");
    scanf("%s",delName);
    printf("请输入要删除的联系人电话：");
    scanf("%s",delNum);
    while(head->next!=NULL){
        if((strcmp(delNum,head->phoneNumber)==0)&&(strcmp(delName,head->name)==0)){//比较要删除的内容的
            temp=head->next;
            head->next=temp->next;
            return;
        }
        else{
            head=head->next;
        }
    }
printf("删除失败!\n");
}
void update(contact *head){//更新存储文件
    contact *s=head;
    FILE *fp1,*fp2;
    fp1=fopen("通讯录.txt","w");
    while(s->next!=NULL){
        fprintf(fp1,"%s %s %s\n",s->name,s->phoneNumber,s->address);
        s=s->next;
    }
    printf("更新成功!\n");
}
void SetNULL(contact *head){//链表和存储文件置空
    head=NULL;
    FILE *fp;
    fp=fopen("通讯录.txt","w");
    fprintf(fp,"\n");
}
int main() {

}
