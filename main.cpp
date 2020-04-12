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
	cout<<"����·��Ϊ:"<<endl;
	cout<<G.vexs[ans[0]];
	for(int i=0;i<k;i++)
    {
        cout<<G.vexs[ans[i+1]];
        mile+=G.arc[ans[i]][ans[i+1]].arrive_distance;
        price+=G.arc[ans[i]][ans[i+1]].arrive_price;
	}
	cout<<endl;
	cout<<"��·��Ϊ��"<<mile<<endl;
	cout<<"�ܼ۸�Ϊ��"<<price<<endl;
	cout<<endl;
}

void DFS(MGraph G,int vs,int ve,int k)//vs��ʼ��ve����
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

void ShortPath_Dijkstra1(MGraph G,int vs,Patharc *P) //��֪���λ��
{
	ShortPathTable D;
	int v,w,k,min1;
	int final[MAXVEX];//final[w]=1��ʾ��ö���vs��vw�����·��
	for(v=0;v<G.numVertexes;v++)
	{
		final[v]=0;
		D[v]=G.arc[vs][v].arrive_distance;//����vs�����ߵĶ������Ȩֵ
		(*P)[v]=vs;//·������P��ʼ��Ϊ0
	}
	D[vs]=0;//vs��vs��·��Ϊ0
	final[vs]=1;//vs��vs����Ҫ��·��
	//��ʼ��ѭ����ÿ�����vs��ĳ��v��������·��
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
//�Ͻ�˹�����㷨 �����·
void print_Shortest1(MGraph G,Patharc *ans1,int vs,int ve)
{
	int temp[MAXVEX],z;
	cout<<"��"<<G.vexs[vs]<<"��"<<G.vexs[ve]<<"���Ƽ�·��Ϊ:"<<endl;
	temp[0]=ve;//temp���鵹�������
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
	cout<<"��·��Ϊ��"<<mile<<endl;
}

void ShortPath_Dijkstra2(MGraph G,int vs,Patharc *P) //��֪���λ��
{
	ShortPathTable D;
	int v,w,k,min1;
	int final[MAXVEX];//final[w]=1��ʾ��ö���vs��vw�����·��
	for(v=0;v<G.numVertexes;v++)
	{
		final[v]=0;
		D[v]=G.arc[vs][v].arrive_price;//����vs�����ߵĶ������Ȩֵ
		(*P)[v]=vs;//·������P��ʼ��Ϊ0
	}
	D[vs]=0;//vs��vs��·��Ϊ0
	final[vs]=1;//vs��vs����Ҫ��·��
	//��ʼ��ѭ����ÿ�����vs��ĳ��v��������·��
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
//�Ͻ�˹�����㷨 �����·
void print_Shortest2(MGraph G,Patharc *ans2,int vs,int ve)
{
	int temp[MAXVEX],z;
	cout<<"��"<<G.vexs[vs]<<"��"<<G.vexs[ve]<<"���Ƽ�·��Ϊ:"<<endl;
	temp[0]=ve;//temp���鵹�������
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
	cout<<"�ܼ۸�Ϊ��"<<price<<endl;
}

void ShortPath_Dijkstra3(MGraph G,int vs,Patharc *P,int a,int b) //��֪���λ��
{
	ShortPathTable D;
	int v,w,k,min3;
	int final[MAXVEX];//final[w]=1��ʾ��ö���vs��vw�����·��
	for(v=0;v<G.numVertexes;v++)
	{
		final[v]=0;
		D[v]=b*G.arc[vs][v].arrive_price+a*G.arc[vs][v].arrive_distance;//����vs�����ߵĶ������Ȩֵ
		(*P)[v]=vs;//·������P��ʼ��Ϊ0
	}
	D[vs]=0;//vs��vs��·��Ϊ0
	final[vs]=1;//vs��vs����Ҫ��·��
	//��ʼ��ѭ����ÿ�����vs��ĳ��v��������·��
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
//�Ͻ�˹�����㷨 �����·
void print_Shortest3(MGraph G,Patharc *ans3,int vs,int ve)
{
	int temp[MAXVEX],z;
	cout<<"��"<<G.vexs[vs]<<"��"<<G.vexs[ve]<<"���Ƽ�·��Ϊ:"<<endl;
	temp[0]=ve;//temp���鵹�������
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
	cout<<"��ӭʹ��**���Ի�����·���Ƽ�ϵͳ**��"<<endl;
	cout<<"������ѡ���·��ͼ��1,2,3����"<<endl;
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
	Create_MGraph(&G,fp);//��ͼ�ɻ����Զ�����
	Patharc ans1[MAXVEX],ans2[MAXVEX],ans3[MAXVEX];//ans�Ƕ�ά���� ���洢ÿһ���㣬������ÿһ��������·��ʱ��ǰ��
	int vs,ve;
	cout<<"�����������ε������յ�(����0 0���н���)��"<<endl;
	while(cin>>vs>>ve)
    {
	   if(vs==0&&ve==0)
          break;
	   cout<<"������������еĲ���(����1�����������·�ߣ�����2����Ƽ�����·��)��"<<endl;
	   int casing;
	   cin>>casing;
	   switch(casing)
	   {
		  case 1:
              cout<<"<--��������·��-->"<<endl;
              DFS(G,vs,ve,0);
              break;
		  case 2:
              cout<<"<--�Ƽ�����·��-->"<<endl;
              cout<<"������������еĲ���(����1���(��������)����·�ߣ�����2���(�۸�����)����·��,����3���(����+�۸�����)����·�ߣ�"<<endl;
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
                      cout<<"���������Ծ���ͼ۸�Ҫ���Ȩ�ر�(����:�۸�):"<<endl;
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
	   cout<<"�����������ε������յ㣺"<<endl;
    }
	cout<<"~~�������н���,ллʹ��~~"<<endl;
	return 0;
}
