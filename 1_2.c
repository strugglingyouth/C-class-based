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
int l=0;

void window_choose();
void choose_(adjmatrix *g);		//选择线路
void print_map();		
void creat(adjmatrix *g);	//创建临接矩阵
void print_all_router(adjmatrix *g);	//输出所有路径
void short_address_router(adjmatrix *g);	//输出中转点最少路径
void less_length_router(adjmatrix *g);		//输出最短距离路径
void print_prim(adjmatrix *g);		//
void print_quanzhi(adjmatrix *g);	//打印临接矩阵
void search_all(adjmatrix *g);		//深度,广度遍历


int nextadj(adjmatrix *g,int v0,int w);
int  firstadj(adjmatrix *g,int v0);
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
void dfs1(adjmatrix *g,char *s1,char *s2,int *path,int d)
{
    int m,i,w,start,end;
    //ArcNode *p;
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

    //p = g->vertex[start].head;
    w=firstadj(&*g,start);
    while(w!=-1)
    {
        //m = p->adjvex;
        if(!visited[w])
        {
            dfs1(&*g,g->vex[w].name,&*s2,path,d);
        }
        w=nextadj(&*g,start,w);//p = p->next;
    }
    visited[start] = 0;		//!!!!
}

/*void dfs1(adjmatrix *g,char *s1,char *s2,int v0)		//深度遍历
{
	int w,i;
	visited[v0]=1;
	//strcpy(s3[j++],s1);
	w=firstadj(&*g,v0);	//图g中v0的第一个临接点
	while(w!=-1)
	{
		if(!visited[w])
		{   
			if(strcmp(g->vex[w].name,s2)!=0)
			{
				strcpy(s3[l++],g->vex[w].name);
				dfs1(&*g,g->vex[w].name,&*s2,w);
			}
			else
			{
				strcpy(s3[l++],g->vex[w].name);
				for(i=0;i<l;i++)
					printf("%s-->",s3[i]);
				printf("\n");
				return;
			}
		}
		w=nextadj(&*g,v0,w);	//图g中v0下一个临接点
	}
}*/
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
/*void search_all(adjmatrix *g)		//深度广度遍历
{
	int i=0;
	for(i=0;i<g->vexnum;i++)
		visited[i]=0;
	printf("深度遍历：\n");
	for(i=0;i<g->vexnum;i++)
		if(!visited[i])
			dfs(&*g,i);		//深度遍历
	printf("\t广度遍历:\n");
	for(i=0;i<g->vexnum;i++)
		visited[i]=0;
	for(i=0;i<g->vexnum;i++)
		if(!visited[i])
			bfs(&*g,i);		//广度遍历*/
	

void print_all_router(adjmatrix *g)	//输出所有路径
{
	char s1[50],s2[50];
	int i,v0,d=0;
	printf("请输入起始点和终点:\n");
	scanf("%s %s",s1,s2);
	for(i=0;i<g->vexnum;i++)
	{
		visited[i]=0;
		//strcpy(s3[i],"");
	}
	//strcpy(s3[l++],s1);
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
void less_length_router(adjmatrix *g)		//输出最短距离路径
{
}
void print_prim(adjmatrix *g)		
{
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
		printf("%d %s %s",g->vex[i].num,g->vex[i].name,g->vex[i].intro);
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
printf("\t     ┻┻┻┻┻┻┻┻┻┻┻┻┻┛┻┻┻┻┻┻┻┻┻┻┻┻┻┛    ┗┗┻┻┻┻┻┻┻┻┻      ┻┻┻┻┻┻┻┻┻┻┻┻┻┛\n");
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
			/*case 2:
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
				break;*/
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
				short_address_router(g);	//打印最少节点路线
				printf("\n输入任意键返回:\n");
				while(getchar()!='\n')
					continue;
				getchar();
				system("clear");
				window_choose();
				printf("请输入您的选择:");
				break;
			case 8:
				less_length_router(g);		//打印最短路线
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
				getchar();
				system("clear");
				window_choose();
				printf("请输入您的选择:");
				break;
			/*case 11:
				search_all(g);		//深度，广度遍历
				getchar();
				printf("\n输入任意键返回:\n");
				while(getchar()!='\n')
					continue;
				system("clear");
				window_choose();
				printf("请输入您的选择:");
				break;*/
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













