#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>
#define  MAXSIZE 100
//二叉树结点的结构体表示形式
typedef struct BitNode
{
    char    data;
    struct BitNode* left,*right;
}BitTree,*Tree;

//栈的结构体表示形式
typedef struct stacke
{
    BitTree* a[MAXSIZE];
    int top;
}Stack;

//队列的结构体的表示形式
typedef struct queue
{
    BitTree* b[MAXSIZE];
    int front,rear;
}Queue;

int i=0;
char Reading[100];
Tree Create(char ch)
{
    Tree T;
    if(ch=='#')
    {
        T=NULL;
    }
    else if(ch=='\0')
        return T;
    else
    {
        T=(Tree)malloc(sizeof(BitTree));
        T->data=ch;
        T->left=Create(Reading[++i]);
        T->right=Create(Reading[++i]);
    }
    return T;
}

void ShowTree(BitTree *p)
{
    BitTree *r,*l;
    l=p->left;
    r=p->right;
    printf(" %c\n",p->data);
    if(l!=NULL)
    {
        printf("    %c's left :",p->data);
        ShowTree(p->left);
    }
    else
        printf("    %c's left  is NULL",p->data);
    if(r!=NULL)
    {
        printf("    %c's right :",p->data);
        ShowTree(p->right);
    }
    else
        printf("    %c's right  is NULL\n",p->data);
}

//前序遍历，递归
void Preorder(BitTree* bt)
{
    if (NULL!=bt)
    {
        printf("%c ",bt->data);
        Preorder(bt->left);
        Preorder(bt->right);
    }
}

//前序遍历，非递归
void Preorder2(BitTree* bt)
{
    BitTree* p;
    Stack st;
    st.top=-1;
    if (NULL==bt)
    {
        return;
    }
    else
    {
        st.top++;
        st.a[st.top]=bt;
        while (st.top!=-1)
        {
            p=st.a[st.top];
            st.top--;
            printf("%c ",p->data);
            if (p->right!=NULL)
            {
                st.top++;
                st.a[st.top]=p->right;
            }
            if (p->left!=NULL)
            {
                st.top++;
                st.a[st.top]=p->left;
            }
        }
    }
}

//中序遍历，递归
void Inorder(BitTree* bt)
{
    if (NULL!=bt)
    {
        Inorder(bt->left);
        printf("%c ",bt->data);
        Inorder(bt->right);
    }
}

//中序遍历，非递归
void Inorder2(BitTree* bt)
{
    BitTree* p,*q;
    Stack st;
    st.top=-1;
    if (NULL==bt)
    {
        return;
    }
    else
    {
        while (bt!=NULL)
        {
            st.top++;
            st.a[st.top]=bt;
            bt=bt->left;
        }
        while (st.top!=-1)
        {
            p=st.a[st.top];
            st.top--;
            printf("%c ",p->data);
            while ( p->right!=NULL )
            {
                st.top++;
                st.a[st.top]=p->right;
                q=p->right;
                while (q->left!=NULL)
                {
                    st.top++;
                    st.a[st.top]=q->left;
                    q=q->left;
                }
                break;
            }
        }
    }
}

//后序遍历，递归
void Postorder(BitTree* bt)
{
    if (bt!=NULL)
    {
        Postorder(bt->left);
        Postorder(bt->right);
        printf("%c ",bt->data);
    }
}

//后序遍历，非递归
void Postorder2(BitTree* bt)
{
    Stack st;
    st.top=-1;
    BitTree* t;
    do
    {
        while (bt!=NULL)
        {
            st.top++;
            st.a[st.top]=bt;
            bt=bt->left;
        }
        t=NULL;
        while (st.top!=-1)
        {
            bt=st.a[st.top];
            if (bt->right==t)  //t:表示为null，或者右子节点被访问过了。
            {
                printf("%c ",bt->data);
                st.top--;
                t=bt;  //t记录下刚刚访问的节点
            }
            else
            {
                bt=bt->right;
                break;
            }
        }
    } while (st.top!=-1);
}

//层次遍历,用队列
void Level(BitTree* bt)
{
    Queue q;
    q.front=q.rear=0;
    if (bt!=NULL)
    {
        printf("%c ",bt->data);
    }
    q.b[q.front]=bt;
    q.rear=q.rear+1;
    while (q.front<q.rear)
    {
        bt=q.b[q.front];
        q.front=q.front+1;
        if (bt->left!=NULL)
        {
            printf("%c ",bt->left->data);
            q.b[q.rear]=bt->left;
            q.rear=q.rear+1;
        }
        if (bt->right!=NULL)
        {
            printf("%c ",bt->right->data);
            q.b[q.rear]=bt->right;
            q.rear=q.rear+1;
        }
    }
}

int main()
{

    FILE *fp;
    fp=fopen("test.txt","r");
    if(fp==NULL)
    {
        printf("Reading failed!\n");
        exit(0);
    }
    else
    {
        fscanf(fp,"%s",&Reading);
    }
    fclose(fp);

    i=0;
    BitTree* btr;
    btr=Create(Reading[i]);
    printf("创建成功\n");
    printf("    root= ");
    BitTree *p=btr;
    ShowTree(p);
    printf("前序遍历：递归和非递归实现：\n");
    Preorder(btr);
    printf("\n");
    Preorder2(btr);
    printf("\n");
    printf("中序遍历：递归和非递归实现：\n");
    Inorder(btr);
    printf("\n");
    Inorder2(btr);
    printf("\n");
    printf("后序遍历：递归和非递归实现：\n");
    Postorder(btr);
    printf("\n");
    Postorder2(btr);
    printf("\n");
    printf("层次遍历二叉树:\n");
    Level(btr);
    printf("\n");

    return 0;
}
