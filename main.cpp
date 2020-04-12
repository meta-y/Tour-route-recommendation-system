#include<bits/stdc++.h>
#define MAXVEX 100
#define MAX 100
#define INFINITE 89757
#define TRUE 1
#define FALSE 0
using namespace std;
typedef int Boolean;
Boolean visited[MAX];
typedef char VertexType;
int visit[MAXVEX]={0},ans[MAXVEX];
typedef int ShortPathTable[MAXVEX];
typedef int Patharc[MAXVEX];

typedef struct
{
	int arrive_distance;
	int arrive_price;
}EdgeType;

typedef struct
{
	VertexType vexs[MAXVEX];
	EdgeType arc[MAXVEX][MAXVEX];
	int numVertexes,numEdges;
}MGraph;

void Create_MGraph(MGraph *G,FILE *fp)
{
	int i,j,k,d,p;
	fscanf(fp,"%d %d",&G->numVertexes,&G->numEdges);
	for(i=0;i<G->numVertexes;i++)
		fscanf(fp," %c",&G->vexs[i]);
	for(i=0;i<G->numVertexes;i++)
    {
		for(j=0;j<G->numVertexes;j++)
        {
			G->arc[i][j].arrive_distance=INFINITE;
			G->arc[i][j].arrive_price=INFINITE;
		}
    }
	for(k=0;k<G->numEdges;k++)
    {
		fscanf(fp,"%d %d %d %d",&i,&j,&d,&p);
		G->arc[i][j].arrive_distance=d;
		G->arc[i][j].arrive_price=p;
	}
}

void print_all(MGraph G,int k)
{

	int mile=0,price=0;
	cout<<"所有路线为:"<<endl;
	cout<<G.vexs[ans[0]];
	for(int i=0;i<k;i++)
    {
        cout<<G.vexs[ans[i+1]];
        mile+=G.arc[ans[i]][ans[i+1]].arrive_distance;
        price+=G.arc[ans[i]][ans[i+1]].arrive_price;
	}
	cout<<endl;
	cout<<"总路程为："<<mile<<endl;
	cout<<"总价格为："<<price<<endl;
	cout<<endl;
}

void DFS(MGraph G,int vs,int ve,int k)//vs开始，ve结束
{
	ans[k]=vs;
	if(vs==ve)
    {
		print_all(G,k);
		return ;
	}
	for(int i=0;i<G.numVertexes;i++)
	{
		if(i==vs)
            continue;
		if(G.arc[vs][i].arrive_distance<INFINITE&&(visit[i]==FALSE))
		{
            visit[i]=TRUE;
            DFS(G,i,ve,k+1);
            visit[i]=FALSE;
		}
	}
}

void ShortPath_Dijkstra1(MGraph G,int vs,Patharc *P) //已知起点位置
{
	ShortPathTable D;
	int v,w,k,min1;
	int final[MAXVEX];//final[w]=1表示求得顶点vs到vw的最短路径
	for(v=0;v<G.numVertexes;v++)
	{
		final[v]=0;
		D[v]=G.arc[vs][v].arrive_distance;//将与vs有连线的顶点加上权值
		(*P)[v]=vs;//路径数组P初始化为0
	}
	D[vs]=0;//vs到vs的路径为0
	final[vs]=1;//vs到vs不需要求路径
	//开始主循环，每次求得vs到某个v顶点的最短路径
	for(v=1;v<G.numVertexes;v++)
	{
		min1=INFINITE;
		for(w=0;w<G.numVertexes;w++)
		{
			if(!final[w]&&D[w]<min1)
			{
				k=w;
				min1=D[w];
			}
		}
		final[k]=1;
		for(w=0;w<G.numVertexes;w++)
		{
			if(!final[w]&&(min1+G.arc[k][w].arrive_distance<D[w]))
			{
				D[w]=min1+G.arc[k][w].arrive_distance;
				(*P)[w]=k;
			}
		}
	}
}
//迪杰斯特拉算法 求最短路
void print_Shortest1(MGraph G,Patharc *ans1,int vs,int ve)
{
	int temp[MAXVEX],z;
	cout<<"由"<<G.vexs[vs]<<"到"<<G.vexs[ve]<<"的推荐路线为:"<<endl;
	temp[0]=ve;//temp数组倒过来输出
	for(int i=1;i<G.numVertexes;i++)
    {
        ve=ans1[vs][ve];
        temp[i]=ve;
        z=i;
        if(ve==vs)
        {
            break;
        }
	}
	int mile=0;
	cout<<G.vexs[temp[z]];
	for(int i=z-1;i>=0;i--)
    {
        cout<<G.vexs[temp[i]];
        mile+=G.arc[temp[i+1]][temp[i]].arrive_distance;
	}
	cout<<endl;
	cout<<"总路程为："<<mile<<endl;
}

void ShortPath_Dijkstra2(MGraph G,int vs,Patharc *P) //已知起点位置
{
	ShortPathTable D;
	int v,w,k,min1;
	int final[MAXVEX];//final[w]=1表示求得顶点vs到vw的最短路径
	for(v=0;v<G.numVertexes;v++)
	{
		final[v]=0;
		D[v]=G.arc[vs][v].arrive_price;//将与vs有连线的顶点加上权值
		(*P)[v]=vs;//路径数组P初始化为0
	}
	D[vs]=0;//vs到vs的路径为0
	final[vs]=1;//vs到vs不需要求路径
	//开始主循环，每次求得vs到某个v顶点的最短路径
	for(v=1;v<G.numVertexes;v++)
	{
		min1=INFINITE;
		for(w=0;w<G.numVertexes;w++)
		{
			if(!final[w]&&D[w]<min1)
			{
				k=w;
				min1=D[w];
			}
		}
		final[k]=1;
		for(w=0;w<G.numVertexes;w++)
		{
			if(!final[w]&&(min1+G.arc[k][w].arrive_price<D[w]))
			{
				D[w]=min1+G.arc[k][w].arrive_price;
				(*P)[w]=k;
			}
		}
	}
}
//迪杰斯特拉算法 求最短路
void print_Shortest2(MGraph G,Patharc *ans2,int vs,int ve)
{
	int temp[MAXVEX],z;
	cout<<"由"<<G.vexs[vs]<<"到"<<G.vexs[ve]<<"的推荐路线为:"<<endl;
	temp[0]=ve;//temp数组倒过来输出
	for(int i=1;i<G.numVertexes;i++)
    {
        ve=ans2[vs][ve];
        temp[i]=ve;
        z=i;
        if(ve==vs)
        {
            break;
        }
	}
	int price=0;
	cout<<G.vexs[temp[z]];
	for(int i=z-1;i>=0;i--)
    {
        cout<<G.vexs[temp[i]];
        price+=G.arc[temp[i+1]][temp[i]].arrive_price;
	}
	cout<<endl;
	cout<<"总价格为："<<price<<endl;
}

void ShortPath_Dijkstra3(MGraph G,int vs,Patharc *P,int a,int b) //已知起点位置
{
	ShortPathTable D;
	int v,w,k,min3;
	int final[MAXVEX];//final[w]=1表示求得顶点vs到vw的最短路径
	for(v=0;v<G.numVertexes;v++)
	{
		final[v]=0;
		D[v]=b*G.arc[vs][v].arrive_price+a*G.arc[vs][v].arrive_distance;//将与vs有连线的顶点加上权值
		(*P)[v]=vs;//路径数组P初始化为0
	}
	D[vs]=0;//vs到vs的路径为0
	final[vs]=1;//vs到vs不需要求路径
	//开始主循环，每次求得vs到某个v顶点的最短路径
	for(v=1;v<G.numVertexes;v++)
	{
		min3=INFINITE;
		for(w=0;w<G.numVertexes;w++)
		{
			if(!final[w]&&D[w]<min3)
			{
				k=w;
				min3=D[w];
			}
		}
		final[k]=1;
		for(w=0;w<G.numVertexes;w++)
		{
			if(!final[w]&&(min3+G.arc[k][w].arrive_price+G.arc[k][w].arrive_distance<D[w]))
			{
				D[w]=min3+b*G.arc[k][w].arrive_price+a*G.arc[k][w].arrive_distance;
				(*P)[w]=k;
			}
		}
	}
}
//迪杰斯特拉算法 求最短路
void print_Shortest3(MGraph G,Patharc *ans3,int vs,int ve)
{
	int temp[MAXVEX],z;
	cout<<"由"<<G.vexs[vs]<<"到"<<G.vexs[ve]<<"的推荐路线为:"<<endl;
	temp[0]=ve;//temp数组倒过来输出
	for(int i=1;i<G.numVertexes;i++)
    {
        ve=ans3[vs][ve];
        temp[i]=ve;
        z=i;
        if(ve==vs)
        {
            break;
        }
	}
	cout<<G.vexs[temp[z]];
	for(int i=z-1;i>=0;i--)
    {
        cout<<G.vexs[temp[i]];
	}
	cout<<endl;
}

int main()
{
	cout<<"欢迎使用**个性化旅游路线推荐系统**！"<<endl;
	cout<<"请输入选择的路线图（1,2,3）："<<endl;
	int mp;
	cin>>mp;
	FILE *fp;
	switch(mp)
	{
		case 1:
		    fp=fopen("map1.txt","r");
		    break;
		case 2:
		    fp=fopen("map2.txt","r");
		    break;
		case 3:
		    fp=fopen("map3.txt","r");
		    break;
		default:
		    break;
	}
	MGraph G;
	Create_MGraph(&G,fp);//地图由机器自动导入
	Patharc ans1[MAXVEX],ans2[MAXVEX],ans3[MAXVEX];//ans是二维数组 ，存储每一个点，到其他每一个点的最短路径时的前驱
	int vs,ve;
	cout<<"请输入您旅游的起点和终点(输入0 0运行结束)："<<endl;
	while(cin>>vs>>ve)
    {
	   if(vs==0&&ve==0)
          break;
	   cout<<"请输入您想进行的操作(输入1获得所有旅游路线，输入2获得推荐旅游路线)："<<endl;
	   int casing;
	   cin>>casing;
	   switch(casing)
	   {
		  case 1:
              cout<<"<--所有旅游路线-->"<<endl;
              DFS(G,vs,ve,0);
              break;
		  case 2:
              cout<<"<--推荐旅游路线-->"<<endl;
              cout<<"请输入您想进行的操作(输入1获得(距离优先)旅游路线，输入2获得(价格优先)旅游路线,输入3获得(距离+价格优先)旅游路线："<<endl;
              int choose;
              cin>>choose;
              switch(choose)
              {
                  case 1:
	                  for(int i=0;i<G.numVertexes;i++)
                      {
                          ShortPath_Dijkstra1(G,i,ans1+i);
                      }
                      print_Shortest1(G,ans1,vs,ve);
                      break;
                  case 2:
                      for(int i=0;i<G.numVertexes;i++)
                      {
                          ShortPath_Dijkstra2(G,i,ans2+i);
                      }
                      print_Shortest2(G,ans2,vs,ve);
                      break;
                  case 3:
                      cout<<"请输入您对距离和价格要求的权重比(距离:价格):"<<endl;
                      int a,b;
                      cin>>a>>b;
	                  for(int i=0;i<G.numVertexes;i++)
                      {
                          ShortPath_Dijkstra3(G,i,ans3+i,a,b);
                      }
                      print_Shortest3(G,ans3,vs,ve);
                      break;
              }
              break;
	   }
	   cout<<endl<<endl;
	   cout<<"请输入您旅游的起点和终点："<<endl;
    }
	cout<<"~~程序运行结束,谢谢使用~~"<<endl;
	return 0;
}
