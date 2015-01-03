#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXVEX 10
#define INFINITY 32768

int visited[MAXVEX+1]={0};

int PATH[20];
int d = 0;



typedef struct ArcNode
{
    int adjvex;
    int weight;
    struct ArcNode *next;
}ArcNode;

typedef struct
{
    char vexname[20];
    
    char vexinfo[500];
	ArcNode *head;
}VertexNode;

typedef struct
{
    VertexNode vertex[MAXVEX];
    int vexnum;
}AdjList;

typedef struct
{
    char linkname[20][20];
    char vexinfo[500];
    char vexname[20];
    int n;                           //保存与该地点相邻地点的总个数
    int  weight[20];
}LinkName;









typedef struct node
{
    int vex;

    struct node *next;
}QNode;

typedef struct
{
    QNode *front;
    QNode *rear;
}LQueue;


int path[20][20] = {0};

void wenjian(void)
{
    LinkName *t;
    int i,j;

    FILE *fp;

    
    
    if((fp = fopen("xiaoyuan","w")) == NULL)
    {
        printf("cant open the file\n");
        exit(0);
    }
    
    
    t = (LinkName *)malloc(sizeof(LinkName));
    while(1)
    {
        
        printf("请输入地点:");
        scanf("%s",t->vexname);
        
        printf("vexname:%s\n\n",t->vexname);
        if(strcmp(t->vexname,"quit") == 0)
        {
            break;
        }
        getchar();
        printf("请输入地点简介:");
        gets(t->vexinfo);
        setbuf(stdin,NULL);
        for(i=0;;i++)
        {
            printf("请分别输入与%s相邻的地点的名称和权值:",t->vexname);
            scanf("%s",t->linkname[i]);
            
            if(strcmp(t->linkname[i],"quit") == 0)
            {
                break;
            }
            scanf("%d",&t->weight[i]);
            getchar();
        }
        t->n = i;
        
        fwrite(t,sizeof(LinkName),1,fp);
        
        t = (LinkName *)malloc(sizeof(LinkName));
    }
    fclose(fp);
    fp = fopen("xiaoyuan","r");

    
    for(i=0;;i++)
    {
        t = (LinkName *)malloc(sizeof(LinkName));
        fread(t,sizeof(LinkName),1,fp);
        
        if(feof(fp))
        {
            break;
        }
        printf("%s\n",t->vexname);
        for(j=0;j<t->n;j++)
        {
            printf("(%s   %d)",t->linkname[j],t->weight);
        }
    }
    

    

}

LQueue *InitQueue(void)             // 队列初始化
{
    QNode *p;
    LQueue *q;
    p = (QNode *)malloc(sizeof(QNode));
    q = (LQueue *)malloc(sizeof(LQueue));
    p->next = NULL;
    q->rear = q->front = p;
    return q;
}

void EnterQueue(LQueue *q,int v0)      //入队
{
    QNode *p;
    p = (QNode *)malloc(sizeof(QNode));
    p->vex = v0;
    p->next = NULL;
    q->rear->next = p;
    q->rear = p;
}

int Empty(LQueue *q)                  //判断队空
{
    if(q->front == q->rear)
    {
        return 1;
    }
    else
        return 0;
}

void DeleteQueue(LQueue *q,int *v)              //出队
{
    QNode *p;
    if(Empty(q))
    {
        printf("队空\n");
        exit(0);
    }
    else
    {
        p = q->front->next;
        q->front->next = p->next;
        *v = p->vex;
        free(p);
        if(q->front->next == NULL)
        {
            q->rear = q->front;
        }
    }

}



void Print_AdjList(AdjList *g)                //打印邻接表
{
    int i;
    ArcNode *p;
    for(i=1;i<=g->vexnum;i++)
    {
        p = g->vertex[i].head;
        
        printf("%s->",g->vertex[i].vexname);
        while(p)
        {
            printf("(%s %d)->",g->vertex[p->adjvex].vexname,p->weight);
            p = p->next;
            
        }
        printf("NULL\n");
		
    }
}





void SaveFile(AdjList *g)                     //保存文件
{
    FILE *fp;
    LinkName *t;
    int i,j;
    ArcNode *p;

    t = (LinkName *)malloc(sizeof(LinkName));

    if(fopen("xiaoyuan","w") == NULL)
    {
        printf("文件打开失败!\n");
        exit(0);
    }

    for(i=1;i<=g->vexnum;i++)
    {
        p = g->vertex[i].head;
        
        strcpy(t->vexname,g->vertex[i].vexname);
        strcpy(t->vexinfo,g->vertex[i].vexinfo);
        for(j=0;p;j++)
        {
            strcpy(t->linkname[j],g->vertex[p->adjvex].vexname);
            t->weight[j] = p->weight;
        }
        t->n = j;
        fwrite(t,sizeof(LinkName),1,fp);
        memset(t,0,sizeof(LinkName));
        
    }

    
    fclose(fp);
}

void Create(AdjList *g)             //创建邻接表
{
    int i,j,k;
    LinkName t1;
    ArcNode *p,*t;
    FILE *fp;
    

    printf("ssss\n");

    g->vexnum = 0;

    if((fp = fopen("xiaoyuan","r")) == NULL)
    {
        printf("open the file fail\n");
        exit(0);
    }
    
    
    for(i=1;;i++)
    {
        
        fread(&t1,sizeof(LinkName),1,fp);
        
        if(feof(fp))
        {
            break;
        }
        strcpy(g->vertex[i].vexname,t1.vexname);
        strcpy(g->vertex[i].vexinfo,t1.vexinfo);
        g->vertex[i].head = NULL;
        g->vexnum++;
    }
    
    printf("vexnum = %d\n",g->vexnum); 
    fclose(fp);
    
    
    
    if((fp = fopen("xiaoyuan","r")) == NULL)
    {
        printf("cant open the file\n");
        exit(0);
    }
    
    
    for(i=1;i<=g->vexnum;i++)
    {
        
        fread(&t1,sizeof(LinkName),1,fp);
        
        

        
        for(j=0;j < t1.n;j++)
        {
            t = (ArcNode *)malloc(sizeof(ArcNode));
            
            for(k=1;k<=g->vexnum;k++)                //找出名字对应的下标
            {
                
                if(strcmp(t1.linkname[j],g->vertex[k].vexname) == 0)
                {
                    break;
                }
            }
        
            t->adjvex = k;
            t->weight = t1.weight[j];

            if(g->vertex[i].head == NULL)
            {
                g->vertex[i].head = p = t;
                
                
            }
            else
            {
                p->next = t;
                p = t;
                
                
            
            }
        }
        p->next = NULL;
    }
    
    
    
    
    Print_AdjList(g);

    
}


void AddPlace(AdjList *g)                //增加一个先地点
{
    int i=1,j=1;
    VertexNode *p;
    char s1[20];
    
    int weight;
    ArcNode *tail,*t,*t1,*t2;
    p = &(g->vertex[++g->vexnum]);
    printf("请输入要添加的节点名称:");
    scanf("%s",p->vexname);
    getchar();
    printf("请输入要添加节点的信息:");
    scanf("%s",p->vexinfo);
    p->head = NULL;
    
    
    while(1)
    {
        t = (ArcNode *)malloc(sizeof(ArcNode));
        printf("请输入%s的第%d个相邻地点的名称:",p->vexname,j);
        scanf("%s",s1);
        if(strcmp(s1,"quit") == 0)
        {
            break;
        }
        printf("请输入这俩个相邻地点所对应的公里数:");
        scanf("%d",&weight);

        for(i=1;i<=g->vexnum;i++)
        {
            if(strcmp(g->vertex[i].vexname,s1) == 0)
            {
                t->weight = weight;
                t->adjvex = g->vexnum;
                t1 = g->vertex[i].head;
                while(t1->next)
                {
                    t1 = t1->next;
                }
                t1->next = t;
                t->next = NULL;
                break;
            }
        }
        
        
        t2 = (ArcNode *)malloc(sizeof(ArcNode));
        t2->adjvex = i;
        t2->weight = weight;
        if(p->head == NULL)
        {
            p->head = tail = t2; 
        }
        else
        {
            tail->next = t2;
            tail = t2;
        }

        j++;
    }
    tail->next = NULL;    
}

ArcNode *DeleteArc(ArcNode *head,int x)         //已知head删除其中一个arc节点
{
    ArcNode *pf,*pb;
    pf = pb = head;
    while(pb)
    {
        if(pb->adjvex == x)
        {
            if(head == pb)
            {
                head = pb->next;
                return head;
            }
            else
            {
                pf->next = pb->next;
            }
            printf("修改成功\n");
        }
        pf = pb;
        pb = pb->next;
    }
    return head;
}

void DeleteVex(AdjList *g)                  //删除一个地点
{
    int i,j;
    char s[20];
    VertexNode *p;
    ArcNode *q;

    printf("请输入要删除的地点名称:");
    scanf("%s",s);
    for(i=1;i<=g->vexnum;i++)
    {
        if(strcmp(g->vertex[i].vexname,s) == 0)
        {
            break;
        }
    }
    if(i != g->vexnum)
    {
        p = &(g->vertex[g->vexnum]);
        
        
        
        strcpy(g->vertex[i].vexinfo,p->vexinfo);
        g->vertex[i].head = p->head;
        strcpy(g->vertex[i].vexname,p->vexname);
        
    }
    --g->vexnum;
    j = i;
    for(i=1;i<=g->vexnum;i++)
    {
        q = g->vertex[i].head;

        while(q)
        {
            if(q->adjvex == j)
            {
                g->vertex[i].head = DeleteArc(g->vertex[i].head,j);
                
            }
            if(q->adjvex == g->vexnum+1)
            {
                q->adjvex = j;
            }
            q = q->next;
        }
    }


}

void AddRuter(AdjList *g)                     //增加一条路线
{
    int i,t1,t2;
    char s1[20];
    char s2[20];
    int weight;
    ArcNode *p,*t;
    

    t = (ArcNode *)malloc(sizeof(ArcNode));
    printf("请输入您要增加路线的地点1和地点2\n");
    scanf("%s",s1);
    getchar();
    scanf("%s",s2);
    printf("请输入它们之间的权值:");
    scanf("%d",&weight);
    
    for(i=1;i<=g->vexnum;i++)
    {
        if(strcmp(g->vertex[i].vexname,s1) == 0)
        {
            t1 = i;
            
        }
        if(strcmp(g->vertex[i].vexname,s2) == 0)
        {
            t2 = i;
            
        }
    }

    p = g->vertex[t1].head;
    t->adjvex = t2;
    t->weight = weight;
    while(p->next != NULL)
    {
        p = p->next;
    }
    p->next = t;
    t->next = NULL;

    t = (ArcNode *)malloc(sizeof(ArcNode));
    p = g->vertex[t2].head;
    t->adjvex = t1;
    t->weight = weight;
    while(p->next != NULL)
    {
        p  = p->next;
    }
    p->next = t;
    t->next = NULL;

}

void DeleteRuter(AdjList *g)             //删除一条路线
{
    char s1[20];
    char s2[20];
    int i;
    int t1,t2;

    printf("请分别输入要删除的俩个地点的名称:");
    scanf("%s",s1);
    getchar();
    scanf("%s",s2);
    for(i=1;i<=g->vexnum;i++)
    {
        if(strcmp(g->vertex[i].vexname,s1) == 0)
        {
            t1 = i;
        }
        if(strcmp(g->vertex[i].vexname,s2) == 0)
        {
            t2 = i;
        }
    }

    g->vertex[t1].head = DeleteArc(g->vertex[t1].head,t2);
    g->vertex[t2].head = DeleteArc(g->vertex[t2].head,t1);

}

void Modify(AdjList *g)               //修改，包括增加一条路线或删除一条路线
{
    int x;

    printf("此修改线路只涉及增加一条线路，或删除一条线路\n");
    printf("\t\t1.增加线路\n");
    printf("\t\t2.删除线路\n\n");
    printf("请输入您的选择:");
    scanf("%d",&x);
    if(x == 1)
    {
        AddRuter(g);
    }
    else if(x == 2)
    {
        DeleteRuter(g);
    }
    else
    {
        printf("您的输入有误\n");
    }
}





int FirstAdjVex(AdjList *g,int v)           //第一个邻接点
{
    if(g->vertex[v].head == NULL)
    {
        return -1;
    }
    return g->vertex[v].head->adjvex;
}

int NextAdjVex(AdjList *g,int v0,int w)       //下一个相邻的点
{
    ArcNode *p;

    p = g->vertex[v0].head;
    
    while(p->adjvex != w)
    {
        p = p->next;
    }
    
    if(p->next == NULL)
    {
        return -1;    
    }

    else
    {
        return p->next->adjvex;
    }
}

void DFS(AdjList *g,int v0)        // 深度优先遍历
{
    int w;
    char s[20];
    ArcNode *p;
    
    printf("请输入您要查找的地点名称:");
    scanf("%s",s);


    visited[v0] = 1;
    if(strcmp(g->vertex[v0].vexname,s) == 0)
    {
        printf("地点:%s\n地点简绍:%s\n",g->vertex[v0].vexname,g->vertex[v0].vexinfo);
        p = g->vertex[v0].head;
        printf("与它相邻的地点名称:");
        while(p)
        {
            printf("%s  ",g->vertex[p->adjvex].vexname);
        }

    }
    w = FirstAdjVex(g,v0);
    while(w != -1)
    {
          if(strcmp(g->vertex[w].vexname,s) == 0)
          {
            printf("地点:%s\n地点简绍:%s\n",g->vertex[w].vexname,g->vertex[w].vexinfo);
            p = g->vertex[w].head;
            printf("与它相邻的地点名称:");
            while(p)
            {
                printf("%s  ",g->vertex[p->adjvex].vexname);
            }
            break;

         }

        if(!visited[w])
        {
            DFS(g,w);
        }
        w = NextAdjVex(g,v0,w);
    }
}




void DFS1(AdjList *g,int start,int end,int *path,int d)
{
    int m,i;
    ArcNode *p;
    visited[start] = 1;
    d++;
    path[d] = start;
    if(start == end)
    {
        for(i=1;i<d;i++)
        {
            printf("%s-->",g->vertex[path[i]].vexname);
        }
        printf("%s",g->vertex[path[d]].vexname);
        printf("\n");
    }

    p = g->vertex[start].head;
    while(p != NULL)
    {
        m = p->adjvex;
        if(!visited[m])
        {
            DFS1(g,m,end,path,d);
        }
        p = p->next;
    }
    visited[start] = 0;
}




void Search(AdjList *g)
{
    char s[20];
    int t,i;

    printf("请输入您要查找的地点名称");
    scanf("%s",s);

    for(i=1;i<=g->vexnum;i++)
    {
        if(strcmp(g->vertex[i].vexname,s) == 0)
        {
            t = i;
            break;
        }
    }
    printf("%s\n%s\n",g->vertex[t].vexname,g->vertex[t].vexinfo);

}


void BFS(AdjList *g,int v0,int v)                //广度优先遍历,搜寻最短路径
{
    LQueue *Q;
    int w;
    int i,j=1;
    int t;
    int flag;
    ArcNode *p,*q;
    int t1 = v0;
    for(i=1;i<=g->vexnum;i++)
        visited[i] = 0;
    visited[v0] = j;
    Q = InitQueue();
    EnterQueue(Q,v0);
    while(!Empty(Q))
    {
        DeleteQueue(Q,&v0);
        w = FirstAdjVex(g,v0);
        while(w != -1)
        {
            if(!visited[w])
            {
                visited[w] = ++j;
                if(w == v)
                {
                    printf("%s",g->vertex[w].vexname);
                    p = g->vertex[w].head;//临接点
                    q = g->vertex[w].head;
                    while(1)
                    {
                      while(p->next) //当还有临接点时
                      {
                        for(q=p->next;q;q = q->next)   //遍历临接点
                        {
                            if((visited[p->adjvex]>visited[q->adjvex]&&visited[q->adjvex]!=0)||(!visited[p->adjvex])) 
                            {
                                t = q->adjvex;
                                q->adjvex = p->adjvex;
                                p->adjvex = t;
                                t = q->weight;
                                q->weight = p->weight;
                                p->weight = t;
                            }
                        }
                        break;
                        p = p->next;
                      }
                      printf("-->%s",g->vertex[p->adjvex].vexname);
                      if(p->adjvex == t1)
                      {
                        break;
                      }
                      p = g->vertex[p->adjvex].head;
                      q = p;
                    }
                }
                EnterQueue(Q,w);
            }
            w = NextAdjVex(g,v0,w);
        }
    }
}







void ShortestPathZ(AdjList *g)                //中转点最少
{
    char s1[20];
    char s2[20];
    int i;
    int t1,t2;

    printf("请分别输入起点和终点:");
    scanf("%s%s",s1,s2);

    for(i=1;i<=g->vexnum;i++)
    {
        if(strcmp(g->vertex[i].vexname,s1) == 0)
        {
            t1 = i;
        }
        if(strcmp(g->vertex[i].vexname,s2) == 0)
        {
            t2 = i;
        }
    }
    
    BFS(g,t1,t2);

}


void Dijkstra(AdjList *g,int start,int end,int *dist,int path[][20])      //找俩点间公里数最少的路径
{
    int mindist,i,j,k,n,t=1;
    ArcNode *p;

    
    for(i=1;i<=g->vexnum;i++)
    {
        p = g->vertex[i].head;
    
        dist[i] = INFINITY;


        while(p)
        {
            if(p->adjvex == start)
            {
                dist[i] = p->weight;
                break;
            }
            p = p->next;
        }
        path[i][1] = start;
    }
    

    path[start][0] = 1;
    
    for(i=2;i<=g->vexnum;i++)
    {
        mindist = INFINITY;
        for(j=1;j<=g->vexnum;j++)                //选择最小权值的路径
        {
            if(!path[j][0] && dist[j] < mindist)
            {
                k = j;
                mindist = dist[j];
            }
        }
        
        if(mindist == INFINITY)
        {
            exit(0);
        }

        path[k][0] = 1;

        if(k == end)
        {
            
            for(n=1;path[k][n] != 0;n++)
            {
                printf("%s->",g->vertex[path[k][n]].vexname);
            }
            printf("%s\n",g->vertex[end].vexname);
            
        }

        
        for(j=1;j<=g->vexnum;j++)
        {
            


            if(!path[j][0] )
            {
                p = g->vertex[k].head;
                while(p)
                {
                    if(p->adjvex == j)
                    {
                        if(dist[k]+p->weight < dist[j])
                        {
                            dist[j] = dist[k]+p->weight;
                            t=1;
                            while(path[k][t] != 0)
                            {
                                path[j][t] = path[k][t];
                                t++;
                            }
                            path[j][t] = k;
                            path[j][t+1] = 0;
                            break;
                        }
                    }
                    p = p->next;
                }
            }
       }
    }
}



void ShortestPathL(AdjList *g)              //公里数最少
{
        int start,end;
        int dist[g->vexnum];
        
        char s1[20];
        char s2[20];
        int i,t1,t2;

        printf("请分别输入求最短公里数的俩个地点名称:");
        scanf("%s",s1);
        getchar();
        scanf("%s",s2);

        for(i=1;i<=g->vexnum;i++)
        {
            if(strcmp(g->vertex[i].vexname,s1) == 0)
            {
                t1 = i;
            }
            if(strcmp(g->vertex[i].vexname,s2) == 0)
            {
                t2 = i;
            }
        }
        printf("hello\n");
        Dijkstra(g,t1,t2,dist,path);

}




void BestNetwork(AdjList *g,int start)                            //最佳布网图
{
    struct
    {
       int adjvex;
       int lowcost;
    }closedge[MAXVEX];
    
    ArcNode *p;
    int i,e,k,m,min;
    closedge[start].lowcost = 0;
    
    
    for(i=1;i<=g->vexnum;i++)
    {
        if(i != start)
        {
            p = g->vertex[start].head;       //重置头指针     
            closedge[i].adjvex = start;
            closedge[i].lowcost = INFINITY;
            while(p)
            {
                if(p->adjvex == i)
                {
                    closedge[i].lowcost = p->weight;
                    break;
                }
                p = p->next;
            }
        }
    }

        for(e=1;e<g->vexnum;e++)                   //控制选中的n-1条符合条件的边
        {
            //选择最小权值的边
            min = INFINITY;
            for(k=1;k<=g->vexnum;k++)
            {
                if(closedge[k].lowcost != 0 && closedge[k].lowcost < min)
                {
                    m = k;
                    min = closedge[k].lowcost;
                }
            }
        

        closedge[m].lowcost = 0;  //标志顶点m加入到U集合
        printf("(%s---%s)\n",g->vertex[m].vexname,g->vertex[closedge[m].adjvex].vexname);
        //更新closedge数组信息
        for(i=1;i<=g->vexnum;i++)
        {
            p = g->vertex[m].head;
            while(p)
            {
               if(i == p->adjvex)
               {
                    if(i != m && p->weight < closedge[i].lowcost)
                    {
                        closedge[i].lowcost = p->weight;
                        closedge[i].adjvex = m;
                    }
               }
               p = p->next;
            }
        }
    }
}


void PrintGraph(void)
{
printf("\t\t┣               西安邮电学院校园图                 ┫\n\n");
printf("\t\t┣╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬┫\n");
printf("\t\t┣            ┏━ ━━━ ━━┓                         ┫\n");
printf("\t\t┣    ╔═══════┫①超市 ┣════┳  ━━━ ━━━ ━━━     ━━━┓                ┫\n");
printf("\t\t┣    ║       ┗━━ ━━━ ━┛              ┃②宿舍┃     ┫\n");
printf("\t\t┣    ║                             ┗  ━━┳┛  ┫\n");
printf("\t\t┣  ┏③┓            ┏━━━━ ━━━┓            ║    ┫\n");
printf("\t\t┣  ┃体┃           ┃    旭  ┃            ║    ┫\n");
printf("\t\t┣  ┃育┃           ┃    ④   ┃          ┏⑤━  ┓┫\n");
printf("\t\t┣  ┃馆┃           ┣━━  日━━┣ ═══ ━━━ ━━━     ═┫网吧   ┃┫\n");
printf("\t\t┣  ┗┳┛            ┃        ┃          ┗┳  ━┛┫\n");
printf("\t\t┣    ║            ┃    苑  ┃           ║    ┫\n");
printf("\t\t┣    ║            ┗┳━ ┳ ━━━   ━┛           ║    ┫\n");
printf("\t\t┣    ║┏━━━ ━━━━━┓  ║  ║     ┏   ━━┓ ║    ┫\n");
printf("\t\t┣    ┗┫ ⑥图书馆 ┣  ┛        ┗══⑦美广┣═╝    ┫\n");
printf("\t\t┣     ┣━━━ ━━━━━┛           ┗━━━━┳┛        ┫\n");
printf("\t\t┣┏⑧  ━┫                        ┏ ━━━┻━┓      ┫\n");
printf("\t\t┣┃大学┃                        ┃   实 ┃      ┫\n");
printf("\t\t┣┃生活┃         ┏━ ━━━━━━━┓    ┃ ⑩ 验 ┃      ┫\n");
printf("\t\t┣┃动中┣════      ⑨喷泉 ┣═ ┫        楼 ┃      ┫\n");
printf("\t\t┣┃ 心 ┃         ┗ ━━━  ┳  ┛    ┗━━┳━ ━┛      ┫\n");
printf("\t\t┣┗  ━┳┛                ║          ║            ┫\n");
printf("\t\t┣    ║                 ║      ┏━ ━┻ ━━┓      ┫\n");
printf("\t\t┣    ║                 ║      ┃⑾教学楼┃      ┫\n");
printf("\t\t┣    ║                 ║      ┗━━┳━  ━┛      ┫\n");
printf("\t\t┣┏━⑿   ━┓              ║         ║            ┫\n");
printf("\t\t┣┃行政楼┃              ║         ║      ┏━  ━━┓ ┫\n");
printf("\t\t┣┗━━━━━━┻══┳━ ━⒀━━┳════━━━━━━━━━ ┛      ┃东╬西┃ ┫\n");
printf("\t\t┣          ┗ 北门 ┛                     ┗━  ━━┛ ┫\n");
printf("\t\t┗┻┻┻┻┻┻┻┻┻      ┻┻┻┻┻┻┻┻┻┻┻┻┻┛\n");
}


void AllRuter(AdjList *g)
{
    char s1[20];
    char s2[20];
    int i,t1,t2;
    printf("请分别输入您想查询俩点之间的所有简单路径的地点:");
    scanf("%s%s",s1,s2);
    
    for(i=1;i<=g->vexnum;i++)
    {
        if(strcmp(g->vertex[i].vexname,s1) == 0)
        {
            t1 = i;
        }
        if(strcmp(g->vertex[i].vexname,s2) == 0)
        {
            t2 = i;
        }

    }
    DFS1(g,t1,t2,PATH,0);

}


void menu(AdjList *g)
{
    int x,i;

    printf("\t\t校园导游\n\n");
    printf("\t1.打印校园图\n");
    printf("\t2.地点查询\n");
    printf("\t3.修改路线\n");
    printf("\t4.增加一个地点\n");
    printf("\t5.删除一个地点\n");
    printf("\t6.输出任意俩点之间的所有简单路径\n");
    printf("\t7.输出俩点之间中转点最少的最短路径\n");
    printf("\t8.输出俩点之间公里数最少的路径\n");
    printf("\t9.输出最佳布网方案\n");
    printf("\t10.打印邻接表\n");
    printf("\t0.退出");

    printf("请输入您的选择:");
    scanf("%d",&x);

    while(x)
    {
        switch(x)
        {
            case 1:PrintGraph();break;
            case 2:Search(g);break;
            case 3:Modify(g);break;
            case 4:AddPlace(g);break;
            case 5:DeleteVex(g);break;
            case 6:AllRuter(g);break;
            case 7:ShortestPathZ(g);break;
            case 8:ShortestPathL(g);break;
            case 9:BestNetwork(g,1);break;
            case 10:Print_AdjList(g);
        }
        printf("请按任意键继续....\n");
        getchar();
        getchar();
        printf("请输入您的选择:");
        scanf("%d",&x);
    }
}


int main(int argc,char ** argv)
{
    AdjList *g;
    
    g = (AdjList *)malloc(sizeof(AdjList));
    wenjian();
    Create(g);
    menu(g);
}
