#include<stdio.h>
#include<string.h>

struct node
{
    int x;
    int y;
}; 

struct node q[10000001];

struct node2
{
    int data;
    int prex;
    int prey;
};

struct node2 a[1001][1001][2];

int mapp[1001][1001]; 

void begin(int n,int m)
{
	int i;
	for(i=0;i<=n;i++)
    {
    	int j;
        for(j=0;j<=m;j++)
        {
            if(i==0||i==n)
        	{
                a[i][j][1].data=1;
                a[i][j][0].data=1;
                continue;
            }
            if(i>=j&&n-i>=m-j)
            {
                a[i][j][1].data=1;
                a[i][j][0].data=1;
            }
        }
    }
}

void result(int n,int m)
{
	int tempx=0;
	int tempy=0;
	int markx=0;
	int marky=0;
	printf("初始状态下，河此岸有%d个商人，%d个随从。\n",n,m);
	int ship=1;
	int step=1;
	while(1)
	{            
	    if(ship==1)
	    {
	        if(markx==n&&marky==m)
	        { 
	            break;
	        }
	        tempx=a[markx][marky][0].prex;
	        tempy=a[markx][marky][0].prey;
	        printf("第%d步：河此岸有%d个商人，%d个随从，对岸有%d个商人，%d个随从，船在彼岸。\n",step,n-tempx,m-tempy,tempx,tempy);
	        markx=tempx;
	        marky=tempy;
	        step++;
	    }
	    else
	    {
	        if(markx==n&&marky==m)
	        { 
	            break;
	        }
	        tempx=a[markx][marky][1].prex;
	        tempy=a[markx][marky][1].prey;
	        printf("第%d步：河此岸有%d个商人,%d个随从，对岸有%d个商人，%d个随从，船在此岸。\n",step,n-tempx,m-tempy,tempx,tempy);
	        markx=tempx;
	        marky=tempy;
	        step++;
	    }
	    ship^=1; 
	}
}

int num[2];
int flag;
int front;
int rear;

void build(int n,int m,int xx,int yy)
{
	int temp=2*flag-1;
	int tempx=q[front].x+temp*xx;
	int tempy=q[front].y+temp*yy;
	if(tempx>=0&&tempx<=n&&tempy>=0&&tempy<=m)
    {
        if(a[tempx][tempy][flag].data==1)
        {
            rear++;
            q[rear].x=tempx;
            q[rear].y=tempy;
            a[q[rear].x][q[rear].y][flag].prex=q[front].x;
            a[q[rear].x][q[rear].y][flag].prey=q[front].y;
            num[flag]++;
        }
    }
}

void line(int n,int m,int k)
{
	int i;
	for(i=0;i<=n&&i<=k;i++)
	{
		int j;
		for(j=0;j<=m&&j<=k;j++)
		{
			if(i==0)
        	{
                mapp[i][j]=1;
                continue;
            }
            if(i>=j&&i+j<=k)
            {
                mapp[i][j]=1;
            }
		}
	}
	mapp[0][0]=0;
}

void BFS(int n,int m,int k)
{
	num[1]=1;
    num[0]=0;
	flag=0;
    front=0;
    rear=0;
    q[rear].x=n;
    q[rear].y=m;
    while(front<=rear)
    {
        if(q[front].x==0&&q[front].y==0)
        { 
            break;
        }
        if(a[q[front].x][q[front].y][1-flag].data==1)
        {
            if(flag==1&&q[front].x==0&&q[front].y==0)
            { 
                break;
            } 
            a[q[front].x][q[front].y][1-flag].data=0;
            int i;
			for(i=0;i<=n&&i<=k;i++)
			{
				int j;
				for(j=0;j<=m&&j<=k;j++)
				{
					if(mapp[i][j]==1)
		        	{
		                build(n,m,i,j);
		            }
				}
			}
        }
        num[1-flag]--;
        if(num[1-flag]==0)
        { 
            flag^=1;
        }
        front++;
    }
	if(front>rear)
    {
        printf("没有可行的方案\n");
    }
    else
    {
	    result(n,m);
	}
}

int main()
{
    int n;
    int m;
    int k;
    while(1)
    {    
        printf("请输入商人数：");
        scanf("%d",&n);
        printf("请输入随从数：");
        scanf("%d",&m);
        printf("请输入船上最大人数：");
        scanf("%d",&k);
        if(n>1000||m>1000||k>1000)
        {
            printf("三输入值均不得超过1000，请重新输入\n");
            continue;
        }
        memset(a,0,sizeof(a));
        memset(mapp,0,sizeof(mapp));
        begin(n,m);
        line(n,m,k);
        BFS(n,m,k);
        int choice;
        printf("如果您要继续测试，请输入1，退出请输入0:");
        scanf("%d",&choice);
        if(choice==0)
        { 
            break;
        }
    }
    return 0;
}
