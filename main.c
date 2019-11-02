#include <stdio.h>
#include <stdlib.h>
#define MAX 50
typedef struct node
{
    char data;
    struct node *Lchild,*Rchild;
    int Ltag,Rtag;//����������ʱʹ��
}node,*Tree;

int i=0;
char m[MAX];//������ļ��ж�ȡ��������Ϣ

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
        T=(Tree)malloc(sizeof(node));
        T->data=ch;
        T->Lchild=Create(m[++i]);
        T->Rchild=Create(m[++i]);
    }
    return T;
}

void ShowTree(node *p)//��ʾ��
{
    node *r,*l;
    r=p->Rchild;
    l=p->Lchild;
    printf(" %c\n",p->data);
    if(l!=NULL)
    {
        printf("    %c's left is:",p->data);
        ShowTree(p->Lchild);
    }
    else
        printf("    %c's left is NULL",p->data);
    if(r!=NULL)
    {
        printf("    %c's right is:",p->data);
        ShowTree(p->Rchild);
    }
    else
        printf("    %c's right is NULL\n",p->data);
}

node *n=NULL;
void InThreding(Tree T)//������������������
{
   if(T)
    {
        InThreding(T->Lchild);
        if(!T->Lchild)
        {
            T->Ltag=0;
            T->Lchild=n;
        }
        else
            T->Ltag=1;
        if(!n->Rchild)
        {
            n->Rtag=0;
            n->Rchild=T;
        }
        else
            n->Rtag=1;
        n=T;
        InThreding(T->Rchild);

    }
}

void InOrderThreding(Tree *p,Tree T)//����ͷ��㣬ʹ�������γɻ�
{
    (*p)=(Tree)malloc(sizeof(node));
    (*p)->Ltag=1;
    (*p)->Rtag=0;
    (*p)->Rchild=(*p);//ͷ�����Ҷ���ָ���Լ�
    (*p)->Lchild=T;//ͷ���������Ϊ�������ĸ�
    n=(*p);
    InThreding(T);
    (*p)->Rchild=n;
    n->Rtag=0;
    n->Rchild=(*p);

}

void In(Tree T)//����ǵݹ����
{
    Tree p;
    p=T->Lchild;
    while(p!=T)
    {
        while(p->Ltag==1)
            p=p->Lchild;
        printf("%c ",p->data);
        while(!p->Rtag&&(p->Rchild!=T))
        {
            p=p->Rchild;
            printf("%c ",p->data);
        }
        p=p->Rchild;
    }
}

node* PreNext(Tree T,char ch)//�����Һ��
{
    Tree x,temp;
    node *result=NULL;
    x=T->Lchild;
    while(x!=T)
    {
        while(x->Ltag==1)
        {
            x=x->Lchild;
        }
        if(x->data==ch)
            temp=x;
        while((x->Rtag==0)&&(x->Rchild!=T))
        {
            x=x->Rchild;
            if(x->data==ch)
                temp=x;
        }
        x=x->Rchild;
    }//���������������ҵ����p

    if(temp->Ltag==1)
    {
        result=temp->Lchild;
    }
    else
    {
        result=temp;
        while(result->Rtag==0)
            result=result->Rchild;
    }
    return result;
}

node* InNext(Tree T,char ch)//�����Һ��
{
    Tree x,temp;
    node *result=NULL;
    x=T->Lchild;
    while(x!=T)
    {
        while(x->Ltag==1)
        {
            x=x->Lchild;
        }
        if(x->data==ch)
            temp=x;
        while((x->Rtag==0)&&(x->Rchild!=T))
        {
            x=x->Rchild;
            if(x->data==ch)
                temp=x;
        }
        x=x->Rchild;
    }//���������������ҵ����p
    if(!temp->Rtag)
        result=temp->Rchild;
    else
    {
        result=temp->Rchild;
        while(result->Ltag)
            result=result->Lchild;
    }
    return result;
}

node* PostNext(Tree T,char ch)//�����Һ��
{
    Tree x,temp,f;
    node *result=NULL;
    x=T->Lchild;
    while(x!=T)
    {
        while(x->Ltag==1)
        {
            x=x->Lchild;
        }
        if(x->data==ch)
        {
            temp=x;
        }
        while((x->Rtag==0)&&(x->Rchild!=T))
        {
            x=x->Rchild;
            if(x->data==ch)
            {
                temp=x;
            }
        }
        x=x->Rchild;
    }
    f=temp;
    while(f->Rtag)
        f=f->Rchild;
    f=f->Rchild;

    if(temp==f->Lchild)//����õ��������
        f=f;//�õ����������Ϊ���ڵ�
    else//����õ����Ҷ���
    {
        f=f->Lchild;
        while(f->Rchild!=temp)
        {
            f=f->Rchild;
        }
    }
    //�ҵ����ڵ�

    if(f->Rtag)
    {
        temp=f->Rchild;
        while(temp->Ltag||temp->Rtag)
        {
            if(temp->Lchild)
                temp=temp->Lchild;
            if(temp->Rchild)
                temp=temp->Rchild;
        }
        result=temp;
    }
    else result=f;
    return result;
}

void Pre(Tree T)//�����������������
{
    Tree p,q;
    p=T->Lchild;
    while(p!=q)
    {
        printf("%c ", p->data);
        q=p;
        while(p->Ltag)
        {
            p=p->Lchild;
            printf("%c ", p->data);
        }
        if(!p->Rtag)
            p=p->Rchild;
        if(p->Rtag)
            p=p->Rchild;
    }
}//

void Post(Tree p)//�����������������
{
    if(p!=NULL)
    {
        if(p->Ltag)
            Post(p->Lchild);
        if(p->Rtag)
            Post(p->Rchild);
        printf("%c ", p->data);
    }

}

void ShowNode(node *x)//��ʾ����ĳ���
{
    printf("The next is %c\n",x->data);
    if(x->Ltag==1)
        printf("It's left is %c",x->Lchild->data);
    else
        printf("It's left is NULL");
    if(x->Rtag==1)
        printf(" and right is %c\n\n",x->Rchild->data);
    else
        printf(" and right is NULL\n\n");
}

int main()
{
    node* M=NULL;
    Tree T,T1;
    Tree t;

    FILE *fp;
    fp=fopen("tree.txt","r");
    if(fp==NULL)
    {
        printf("Reading failed!\n");
        exit(0);
    }
    else
        fscanf(fp,"%s",&m);
    fclose(fp);
    i=0;
    T=Create(m[i]);
    node *p=T;
    printf("root:");
    ShowTree(p);

    InOrderThreding(&t,T);
    printf("\nInorder Tree��");
    T1=t;
    In(t);
    printf("\n");

    printf("PreOrder Tree��");
    Pre(T1);
    printf("\n");

    printf("PostOrder Tree��");
    Tree m;
    m=t->Lchild;
    Post(m);
    printf("\n");

    node *next1=NULL,*next2=NULL,*next3=NULL;
    char c;
    printf("\ninput the node \n");
    scanf("%c",&c);

    printf("\nFind in PreOrder: \n");
    next1=PreNext(t,c);
    ShowNode(next1);

    printf("Find in InOrder: \n");
    next2=InNext(t,c);
    ShowNode(next2);

    printf("Find in PostOrder: \n");
    next3=PostNext(t,c);
    ShowNode(next3);
    getchar();

    return 0;
}

