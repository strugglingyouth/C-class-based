#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 20
#define INFINITY 32768
typedef struct{
	int num;
	char name[20];
	char intro[100];	//介绍
}vextype;
typedef struct
{
	int 	arcs[MAX][MAX];	//权值
	vextype vex[MAX];	//顶点
	int	vexnum;		//顶点数
	int 	arcnum;		//边数
}adjmatrix;
typedef struct {
	int num[MAX];
	int front;
	int rear;
}queue;
queue *init_queue()
{
	queue *q;
	q=malloc(sizeof(queue));
	q->front=q->rear=-1;
	return q;
}
int in_queue(queue *q,int x)
{
	if((q->rear)%MAX==q->front)
	{
		printf("队满！！\n");
		return 0;
	}
	q->rear=(q->rear++)%MAX;
	q->num[q->rear]=x;
}
int out_queue(queue *q,int *x)
{
	if(!is_empty(q))
	{
		q->front=(q->front++)%MAX;
		*x=q->num[q->front];
	}
	else
		printf("队空！！！");
		return 0;
}
int is_empty(queue *q)
{
	if(q->front==q->rear)
		return 1;
	else
		return 0;
}
int visited[MAX]={0};
char s3[MAX][50];
int path[MAX];

void window_choose();
void choose_(adjmatrix *g);		//选择线路
void print_map();		
void creat(adjmatrix *g);	//创建临接矩阵
void search_address(adjmatrix *g);  //地点查询
void modify_address(adjmatrix *g);	//修改顶点信息
void add_address(adjmatrix *g);		//添加路线
void delete_address(adjmatrix *g);	//删除路线
void print_all_router(adjmatrix *g);	//输出所有路径
void short_address_router(adjmatrix *g);	//输出中转点最少路径
void dijkstra(adjmatrix *g);		//输出最短距离路径
void print_prim(adjmatrix *g);		//
void print_quanzhi(adjmatrix *g);	//打印临接矩阵
void search_all(adjmatrix *g);		//深度,广度遍历


int nextadj(adjmatrix *g,int v0,int w);
int  firstadj(adjmatrix *g,int v0);
void dfs(adjmatrix *g,int v0);

void dijkstra_(adjmatrix *g1,int start,int end,int dist[],int path[][50]);

void dfs1(adjmatrix *g,char *s1,char *s2,int *path,int d);               //深度遍历
int main(void)
{
	adjmatrix g;
	creat(&g);
	window_choose();	
	choose_(&g);
}
int  firstadj(adjmatrix *g,int v0)
{
	int i;
	for(i=0;i<g->vexnum;i++)
	{
		if(visited[i]==0&&g->arcs[v0][i]!=INFINITY)
				return i;
	}
	return -1;
}
int nextadj(adjmatrix *g,int v0,int w)
{
	int i;
	for(i=w+1;i<g->vexnum;i++)
		if(visited[i]==0&&g->arcs[v0][i]!=INFINITY)
			return i;
	return -1;
}
void dfs(adjmatrix *g,int v0)		//深度遍历
{
	int w;
	printf("%d %s %s\n",g->vex[v0].num,g->vex[v0].name,g->vex[v0].intro);
	visited[v0]=1;
	w=firstadj(&*g,v0);	//图g中v0的第一个临接点
	while(w!=-1)
	{
		if(!visited[w])
			dfs(&*g,w);
		w=nextadj(&*g,v0,w);	//图g中v0下一个临接点
	}
}
void dfs1(adjmatrix *g,char *s1,char *s2,int *path,int d)
{
    int m,i,w,start,end;
    for(i=0;i<g->vexnum;i++)
    {
	    if(strcmp(s1,g->vex[i].name)==0)
		    start=i;
            if(strcmp(s2,g->vex[i].name)==0)
		    end=i;
    } 
    visited[start] = 1;
    d++;
    path[d] = start;
    if(start == end)
    {
        for(i=1;i<d;i++)
        {
            printf("%s-->",g->vex[path[i]].name);
        }
        printf("%s",g->vex[path[d]].name);
        printf("\n");
    }
    w=firstadj(&*g,start);
    while(w!=-1)
    {
        if(!visited[w])
        {
            dfs1(&*g,g->vex[w].name,&*s2,path,d);
        }
        w=nextadj(&*g,start,w);
    }
    visited[start] = 0;		//!!!!!!!
}
void bfs(adjmatrix *g,int v0)		//广度遍历
{
	int x,w;
	queue *q=init_queue();
	printf("\t%d %s %s\n",g->vex[v0].num,g->vex[v0].name,g->vex[v0].intro);
	visited[v0]=1;
	init_queue(&q);
	while(!is_empty(q))
	{
		out_queue(q,&x);
		w=firstadj(&*g,x);
		while(w!=-1)
		{
			if(!visited[w])
			{
				printf("\t%d %s %s\n",g->vex[v0].num,g->vex[v0].name,g->vex[v0].intro);
				visited[w]=1;
				in_queue(q,w);
			}
			w=nextadj(&*g,x,w);
		}
	}
}
void search_all(adjmatrix *g)		//深度广度遍历
{
	int i=0;
	for(i=0;i<g->vexnum;i++)
		visited[i]=0;
	printf("深度遍历：\n");
	for(i=0;i<g->vexnum;i++)
		if(!visited[i])
			dfs(&*g,i);		//深度遍历
	printf("\t\t\t广度遍历:\n");
	for(i=0;i<g->vexnum;i++)
		visited[i]=0;
	for(i=0;i<g->vexnum;i++)
		if(!visited[i])
			bfs(&*g,i);		//广度遍历
	
}
void search_address(adjmatrix *g)	//地点查询
{
	char ch[20];
	int i;
	printf("请输入要查询的地点:\n");
	scanf("%s",ch);
	for(i=0;i<g->vexnum;i++)
	{
		if(strcmp(ch,g->vex[i].name)==0)
		{
			printf("%s:%s",g->vex[i].name,g->vex[i].intro);
			return ;
		}
	}
	printf("未找到！！！");

}
void modify_address(adjmatrix *g)	//修改顶点信息
{
	int i;
	char s[20];
	printf("请输入要查询的地点:\n");
	scanf("%s",s);
	for(i=0;i<g->vexnum;i++)
	{
		if(strcmp(s,g->vex[i].name)==0)
		{
			printf("%d %s %s",g->vex[i].num,g->vex[i].name,g->vex[i].intro);
			printf("请输入修改后的信息:\n");
			scanf("%s",g->vex[i].intro);
		}
	}
}
void add_address(adjmatrix *g)		//添加路线
{
	char s1[50],s2[50];
	int i,m=0,n=0,k,p,q;
	printf("请输入起路线始点,终点和权值:\n");
	scanf("%s %s %d",s1,s2,&k);
	for(i=0;i<g->vexnum;i++)
	{
		if(strcmp(s1,g->vex[i].name)==0)
		{
			m=1;
			p=i;
		}
		if(strcmp(s2,g->vex[i].name)==0)
		{
			n=1;
			q=i;
		}
	}
	if(m==1&&n==1)
	{	
		if(g->arcs[p][q]!=INFINITY)
			printf("添加失败，此路线已存在!\n");
		else
		{
			g->arcs[p][q]=g->arcs[q][p]=k;
			printf("添加成功!\n");
		}
	}
	else
	{
		if(m==0)
			printf("添加失败！ %s未找到!\n",s1);
		if(n==0)
			printf("添加失败！ %s未找到!\n",s2);
		if(m==0&&n==0)
			printf("添加失败！ %s %s都未找打!\n",s1,s2);
	}
}
void delete_address(adjmatrix *g)	//删除路线
{
	char s1[50],s2[50];
	int i,m=0,n=0,p,q;
	printf("请输入起路线始点,终点:\n");
	scanf("%s %s",s1,s2);
	for(i=0;i<g->vexnum;i++)
	{
		if(strcmp(s1,g->vex[i].name)==0)
		{
			m=1;
			p=i;
		}
		if(strcmp(s2,g->vex[i].name)==0)
		{
			n=1;
			q=i;
		}
	}
	if(m==1&&n==1)
	{	
		if(g->arcs[p][q]!=INFINITY)
		{
			g->arcs[p][q]=g->arcs[q][p]=INFINITY;
			printf("删除成功!\n");
		}
		else
			printf("删除失败，此路线不存在!\n");
	}
	else
	{
		if(m==0)
			printf("删除失败！ %s未找到!\n",s1);
		if(n==0)
			printf("删除失败！ %s未找到!\n",s2);
		if(m==0&&n==0)
			printf("删除失败！ %s %s都未找到!\n",s1,s2);
	}
	
}
void print_all_router(adjmatrix *g)	//输出所有路径
{
	char s1[50],s2[50];
	int i,v0,d=0;
	printf("请输入起始点和终点:\n");
	scanf("%s %s",s1,s2);
	for(i=0;i<g->vexnum;i++)
	{
		visited[i]=0;
	}
	for(i=0;i<g->vexnum;i++)
		if(strcmp(s1,g->vex[i].name)==0)
		{
			v0=i;
			break;
		}
	if(i>=g->vexnum)
	{
		printf("%s %s 路线未找到!\n",s1,s2);
		return ;
	}
	for(i=0;i<g->vexnum;i++)
		if(strcmp(s2,g->vex[i].name)==0)
		{
			break;
		}
	if(i>=g->vexnum)
	{
		printf("%s %s 路线未找到!\n",s1,s2);
		return ;
	}
	dfs1(&*g,s1,s2,path,d);
}
void short_address_router(adjmatrix *g)		//输出中转点最少路径
{



}
void dijkstra(adjmatrix *g)		//输出最短距离路径
{
	char s1[50],s2[50];
	adjmatrix g1;
	int i,start=-1,end=-1,dist[MAX],path[MAX][50],j;
	printf("请输入起始点和终点:\n");
	scanf("%s %s",s1,s2);
	for(i=g->vexnum-1;i>=0;i--)
		strcpy(g1.vex[i+1].name,g->vex[i].name);
	for(i=0;i<g->vexnum;i++)		//右移
		for(j=g->vexnum-1;j>=0;j--)	
			g1.arcs[i][j+1]=g->arcs[i][j];
	for(j=1;j<=g->vexnum;j++)		//下移
		for(i=g->vexnum-1;i>=0;i--)
			g1.arcs[i+1][j]=g1.arcs[i][j];
	g1.vexnum=g->vexnum;
	g1.arcnum=g->arcnum;
	for(i=1;i<=g1.vexnum;i++)
	{
		for(j=1;j<=g1.vexnum;j++)
			printf("%5d ",g1.arcs[i][j]);
		printf("\n");
	}
	for(i=1;i<=g1.vexnum;i++)
	{
		if(strcmp(s1,g1.vex[i].name)==0)
			start=i;
		if(strcmp(s2,g1.vex[i].name)==0)
			end=i;
	}
	if(start==-1||end==-1)
	{
		printf("%s-->%s未找到!!!\n",s1,s2);
		return;
	}
	dijkstra_(&g1,start,end,dist,path);
}
void dijkstra_(adjmatrix *g1,int start,int end,int dist[],int path[][50])
{

	int mindist,i,j,k,t=1;
	for(i=1;i<=g1->vexnum;i++)
	{
		dist[i]=g1->arcs[start][i];
		if(g1->arcs[start][i]!=INFINITY)
			path[i][1]=start;
	}
	path[start][0]=1;
	for(i=2;i<=g1->vexnum;i++)
	{
		mindist=INFINITY;
		for(j=1;j<=g1->vexnum;j++)
			if(!path[j][0]&&dist[j]<mindist)
			{
				k=j;
				mindist=dist[j];
			}
		if(mindist==INFINITY) break;
		path[k][0]=1;
		for(j=1;j<=g1->vexnum;j++)
		{
			if(!path[j][0]&&g1->arcs[k][j]<INFINITY&&dist[k]+g1->arcs[k][j]<dist[j])
			{
				dist[j]=dist[k]+g1->arcs[k][j];
				t=1;
				while(path[k][t])
				{
					path[j][t]=path[k][t];
					t++;
				}
				path[j][t]=k;
				path[j][t+1]=0;
			}
		}
	}
	for(i=1;i<=g1->vexnum;i++)
		if(i==end)  
			break;
	printf("%s",g1->vex[start].name);
	for(j=2;path[i][j];j++)
		printf("->%s",g1->vex[path[i][j]].name);
	printf("->%s,距离为%dm\n",g1->vex[end].name,dist[i]);
}
void print_prim(adjmatrix *g)		
{
	char s[50];
	int i,e,k,m,min,start;
	printf("请输入起点:\n");
	scanf("%s",s);
	for(i=0;i<g->vexnum;i++)
		if(strcmp(s,g->vex[i].name)==0)
		{
			start=i;
			break;
		}
	if(i>=g->vexnum)
	{
		printf("地点未找到！\n");
		return ;
	}
	struct {
		int adjvex;
		int lowcost;
	}closedge[MAX];
	closedge[start].lowcost=0;
	printf("%s",g->vex[start].name);
	for(i=0;i<g->vexnum;i++)
	{
		if(i!=start)
		{
			closedge[i].adjvex=start;
			closedge[i].lowcost=g->arcs[start][i];
		}
	}
	for(e=0;e<g->vexnum-1;e++)
	{
		min=INFINITY;
		for(k=0;k<g->vexnum;k++)
			if(closedge[k].lowcost!=0&&closedge[k].lowcost<min)	//寻找最小权值的边
			{
				m=k;
				min=closedge[k].lowcost;
			}
		closedge[m].lowcost=0;
		printf("-->%s",g->vex[m].name);
		for(i=0;i<g->vexnum;i++)
			if(i!=m&&g->arcs[m][i]<closedge[i].lowcost)   //替换原数组
			{
				closedge[i].adjvex=m;
				closedge[i].lowcost=g->arcs[m][i];
			}
	}
	
}
void print_quanzhi(adjmatrix *g)	//打印临接矩阵
{
	int i,j;
	for(i=0;i<g->vexnum;i++)
	{
		for(j=0;j<g->vexnum;j++)
			printf("%5d ",g->arcs[i][j]);
		printf("\n");
	}
	printf("总共有%d个地点，总共有%d条边!\n",g->vexnum,g->arcnum);
}
void creat(adjmatrix *g)
{
	FILE *fp,*fp1;
	int i=0,ct=1,m,n,k=0,t;
	if((fp=fopen("didian","rw"))==NULL)		//读取顶点信息
	{
		printf("打开文件错误!!!\n");
		exit(2);
	}
	while(fscanf(fp,"%d %s %s",&g->vex[i].num,g->vex[i].name,g->vex[i].intro)!=EOF)
	{
		ct++;
		i++;
	}
	g->vexnum=ct-1;
	if((fp1=fopen("quanzhi2","rw"))==NULL)		//读取权值信息
	{
		printf("打开文件错误!!!\n");
		exit(2);
	}
	for(m=0;m<ct-1;m++)
		for(n=m;n<ct-1;n++)
		{
			fscanf(fp1,"%d",&t);
			if(t)
			{
				g->arcs[m][n]=g->arcs[n][m]=t;
				k++;
			}
			else
				g->arcs[m][n]=g->arcs[n][m]=INFINITY;
		}
	g->arcnum=2*k;
	fclose(fp);
	fclose(fp1);
}
void window_choose()
{
     	printf("\t\t校园导游\n\n");
     	printf("\t1.打印校园图\n");
     	printf("\t2.地点查询\n");
     	printf("\t3.修改顶点信息\n");
    	printf("\t4.增加一个路线\n");
     	printf("\t5.删除一个路线\n");
     	printf("\t6.输出任意俩点之间的所有简单路径\n");
     	printf("\t7.输出俩点之间中转点最少的最短路径\n");
     	printf("\t8.输出俩点之间公里数最少的路径\n");
     	printf("\t9.输出最佳布网方案\n");
     	printf("\t10.打印邻接矩阵\n");
	printf("\t11.搜索全部地点\n");		//深度广度遍历
     	printf("\t0.退出\n");
}
void print_map()		//打印校园图
{
printf("\t╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬┣  \t╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬┣┫\n");
printf("\t     ┏━━━━ ━━━┓      ┏━━━━ ━━━┓ ┣  \t┣                                               ┫\n");
printf("\t     ┃        ┃      ┃        ┃ ┣  \t┣            ┏━━━━━━┓                           ┫\n");
printf("\t     ┃        ┃      ┃        ┃ ┣  \t┣    ╔═══════┫①超市 ┣════┳━━━━━━━━━━━━━━━━━┓    ┫\n");
printf("\t     ┣━━  ━  ━┣      ┣━━  ━━  ┣ ┣子\t┣    ║       ┗━━━━━━┛                ┃②宿舍┃    ┫\n");
printf("\t     ┃        ┃      ┃        ┃ ┣  \t┣    ║                               ┗  ━━┳┛    ┫\n");
printf("\t     ┃        ┃      ┃        ┃ ┣  \t┣  ┏③┓             ┏━━━━ ━━━┓             ║     ┫\n");
printf("\t     ┗┳━ ┳ ━━━       ┗┳━ ┳ ━━━  ┣  \t┣  ┃体┃            ┃    旭  ┃             ║     ┫\n");
printf("\t                                ┣午\t┣  ┃育┃            ┃    ④   ┃          ┏⑤━  ┓   ┫\n");
printf("\t                                ┣  \t┣  ┃馆┃            ┣━━  日━━┣ ═══ ━━━━━┫网吧┃   ┫\n");
printf("\t                                ┣  \t┣  ┗┳┛             ┃        ┃          ┗┳  ━┛   ┫\n");
printf("\t═══┣   ═════════════════════════   \t┣    ║             ┃    苑  ┃           ║       ┫\n");
printf("\t   ┣                               \t┣    ║             ┗┳━ ┳ ━━━┛           ║       ┫\n");
printf("\t   ┣      ┣══════════════    ════  \t┣    ║┏━━━ ━━━━━┓   ║  ║    ┏   ━━┓     ║       ┫\n");
printf("\t   ┣      ┣              ║  ║   ┣  \t┣    ┗┫ ⑥图书馆 ┣   ┛       ┗⑦美广┣    ═╝       ┫\n");
printf("\t   ┣      ┣              ║  ║   ┣  \t┣     ┣━━━ ━━━━━┛           ┗━━━━┳┛             ┫\n");
printf("\t   ┣      ┣              ║  ║   ┣大\t┣┏⑧  ━┫                        ┏ ━━━┻━┓         ┫\n");
printf("\t   ┣      ┣    ┏ ━━━┻━┓  ║  ║   ┣  \t┣┃大学┃                        ┃   实 ┃         ┫\n");
printf("\t   ┣      ┣    ┃14 饭 ┃  ║  ║   ┣  \t┣┃生活┃         ┏━ ━━━━━━━┓    ┃ ⑩ 验 ┃         ┫\n");
printf("\t   ┣      ┣    ┃   堂 ┃  ║  ║   ┣  \t┣┃动中┣════      ⑨喷泉 ┣═ ┫        楼 ┃         ┫\n");
printf("\t15 ┣      ┣      超市 ┃  ║  ║   ┣  \t┣┃ 心 ┃         ┗ ━━━  ┳  ┛    ┗━━┳━ ━┛         ┫\n");
printf("\t┏━  ━━┓   ┣    ┗━━┳━ ━┛  ║  ║   ┣道\t┣┗  ━┳┛                ║          ║             ┫\n");
printf("\t┃ 宿舍┃   ┣              ║  ║   ┣  \t┣    ║                 ║      ┏━ ━┻ ━━┓         ┫\n");
printf("\t┗━  ━━┛    ══════════════       ┣  \t┣    ║                 ║      ┃⑾教学楼┃         ┫\n");
printf("\t           ══════════════════┣  ┣  \t┣    ║                 ║      ┗━━┳━  ━┛         ┫\n");
printf("\t                                ┣  \t┣┏━⑿   ━┓              ║         ║              ┫\n");
printf("\t          ┏━    ━┓                 \t┣┃行政楼┃              ║         ║      ┏━  ━━┓ ┫\n");
printf("\t        16┃教学楼┃                 \t┣┗━━━━━━┻══┳━ ━⒀━━┳════━━━━━━━━━ ┛      ┃东╬西┃ ┫\n");
printf("\t          ┗━━━━━━┻                 \t┣          ┗ 北门 ┛                     ┗━  ━━┛ ┫\n");
printf("\t     ┻┻┻┻┻┻┻┻┻┻┻┻┻┛┻┻┻┻┻┻┻┻┻┻┻┻┻┛  \t┗┗┻┻┻┻┻┻┻┻┻      ┻┻┻┻┻┻┻┻┻┻┻┻┻┛			\n");
}
void choose_(adjmatrix *g)
{
	int x;
	char ch;
	printf("请输入您的选择:");
     	
	while(scanf("%d",&x))
	{
		switch(x)
		{
			case 0:
				exit(1);
			case 1:
				print_map();			//打印地图
				printf("\n输入任意键返回:\n");
				while(getchar()!='\n')
					continue;
				getchar();
				system("clear");
				window_choose();
				printf("请输入您的选择:");
				break;
			case 2:
				search_address(g);		//查找地点
				printf("\n输入任意键返回:\n");
				while(getchar()!='\n')
					continue;
				getchar();
				system("clear");
				window_choose();
				printf("请输入您的选择:");
				break;
			case 3:
				modify_address(g);		//修改地点信息
				printf("\n输入任意键返回:\n");
				while(getchar()!='\n')
					continue;
				getchar();
				system("clear");
				window_choose();
				printf("请输入您的选择:");
				break;
			case 4:
				add_address(g);			//添加地点
				printf("\n输入任意键返回:\n");
				while(getchar()!='\n')
					continue;
				getchar();
				system("clear");
				window_choose();
				printf("请输入您的选择:");
				break;
			case 5:
				delete_address(g);		//删除地点
				printf("\n输入任意键返回:\n");
				while(getchar()!='\n')
					continue;
				getchar();
				system("clear");
				window_choose();
				printf("请输入您的选择:");
				break;
			case 6:
				print_all_router(g);		//打印所有路线
				printf("\n输入任意键返回:\n");
				while(getchar()!='\n')
					continue;
				getchar();
				system("clear");
				window_choose();
				printf("请输入您的选择:");
				break;
			case 7:
				short_address_router(&*g);	//打印最少节点路线
				printf("\n输入任意键返回:\n");
				while(getchar()!='\n')
					continue;
				getchar();
				system("clear");
				window_choose();
				printf("请输入您的选择:");
				break;
			case 8:
				dijkstra(&*g);		//打印最短路线
				printf("\n输入任意键返回:\n");
				while(getchar()!='\n')
					continue;
				getchar();
				system("clear");
				window_choose();
				printf("请输入您的选择:");
				break;
			case 9:
				print_prim(g);			//最小生成树
				printf("\n输入任意键返回:\n");	
				while(getchar()!='\n')
					continue;
				getchar();
				system("clear");
				window_choose();
				printf("请输入您的选择:");
				break;
			case 10:
				print_quanzhi(&*g);		//打印权值
				getchar();
				printf("\n输入任意键返回:\n");
				while(getchar()!='\n')
					continue;
				//getchar();
				system("clear");
				window_choose();
				printf("请输入您的选择:");
				break;
			case 11:
				search_all(g);		//深度，广度遍历
				getchar();
				printf("\n输入任意键返回:\n");
				while(getchar()!='\n')
					continue;
				system("clear");
				window_choose();
				printf("请输入您的选择:");
				break;
			default:
				printf("\n输入有误,输入任意键返回!!!\n");
				while(getchar()!='\n')
					continue;
				system("clear");
				window_choose();
				printf("请输入您的选择:");

		}
	}
}













