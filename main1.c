#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>
#define  MAXSIZE 100
//���������Ľṹ���ʾ��ʽ
typedef struct BitNode
{
    char    data;
    struct BitNode* left,*right;
}BitTree,*Tree;

//ջ�Ľṹ���ʾ��ʽ
typedef struct stacke
{
    BitTree* a[MAXSIZE];
    int top;
}Stack;

//���еĽṹ��ı�ʾ��ʽ
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

//ǰ��������ݹ�
void Preorder(BitTree* bt)
{
    if (NULL!=bt)
    {
        printf("%c ",bt->data);
        Preorder(bt->left);
        Preorder(bt->right);
    }
}

//ǰ��������ǵݹ�
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

//����������ݹ�
void Inorder(BitTree* bt)
{
    if (NULL!=bt)
    {
        Inorder(bt->left);
        printf("%c ",bt->data);
        Inorder(bt->right);
    }
}

//����������ǵݹ�
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

//����������ݹ�
void Postorder(BitTree* bt)
{
    if (bt!=NULL)
    {
        Postorder(bt->left);
        Postorder(bt->right);
        printf("%c ",bt->data);
    }
}

//����������ǵݹ�
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
            if (bt->right==t)  //t:��ʾΪnull���������ӽڵ㱻���ʹ��ˡ�
            {
                printf("%c ",bt->data);
                st.top--;
                t=bt;  //t��¼�¸ոշ��ʵĽڵ�
            }
            else
            {
                bt=bt->right;
                break;
            }
        }
    } while (st.top!=-1);
}

//��α���,�ö���
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
    printf("�����ɹ�\n");
    printf("    root= ");
    BitTree *p=btr;
    ShowTree(p);
    printf("ǰ��������ݹ�ͷǵݹ�ʵ�֣�\n");
    Preorder(btr);
    printf("\n");
    Preorder2(btr);
    printf("\n");
    printf("����������ݹ�ͷǵݹ�ʵ�֣�\n");
    Inorder(btr);
    printf("\n");
    Inorder2(btr);
    printf("\n");
    printf("����������ݹ�ͷǵݹ�ʵ�֣�\n");
    Postorder(btr);
    printf("\n");
    Postorder2(btr);
    printf("\n");
    printf("��α���������:\n");
    Level(btr);
    printf("\n");

    return 0;
}
