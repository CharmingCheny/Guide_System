#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxInt 32767
int path[10][10],D[10][10]={0}; //定义存储路径数组和最短路径数组 
typedef int ArcType;
typedef struct
{ 
	char name[100];
	char info[10000];
}VertexType; //顶点结构
typedef struct
{ 
	VertexType vexs[10];
	int arcs[100][100];//邻接矩阵
	int vexnum,arcnum;//顶点个数，边的个数
}AMGraph; //图结构 
int LocateVex(AMGraph G,VertexType u)  //定位函数 
{
	int i;
	for(i=0;i<G.vexnum;i++)
	{
		if(strcmp(u.name,G.vexs[i].name)==0) return i; //比较是否两个字符串相等 
	}
	return -1;
}
void Search(AMGraph &G) //对景点的了解 
{
	char c;
	int num;
	printf("本校景点有：\n");
	for(int i=0;i<G.vexnum;i++)  //打印景点名称 
		printf("%d.%s\n",i+1,G.vexs[i].name);
	printf("请输入想要了解地点的编号:");
	scanf("%d",&num);
	int p=1;  //指示变量 ，判定结束时期 
	while(p)
	{
		if(num>G.vexnum||num<1)  //输入数字不合法 
		{
			printf("请重新输入想要了解地点的编号:");
			scanf("%d",&num);
			continue;
		 } 
		 printf("%s",G.vexs[num-1].info); //合法则输出对应信息 
		p=0;
	}
	printf("\n");
}
void Floyd(AMGraph G) //弗洛伊德算法，获得最短路径
{  
    int i,j,k;
    for(i=0;i<G.vexnum;i++)  //对应结点之间已知路径和距离 
        for(j=0;j<G.vexnum;j++) 
			D[i][j]=MaxInt;
    for(i=0;i<G.vexnum;i++)  //对应结点之间已知路径和距离 
        for(j=0;j<G.vexnum;j++)
		{
            D[i][j]=G.arcs[i][j];
            if(D[i][j]<MaxInt&&i!=j)
                path[i][j]=i;
            else
                path[i][j]=-1;
        }
    for(k=0;k<G.vexnum;k++)
        for(i=0;i<G.vexnum;i++)
            for(j=0;j<G.vexnum;j++)
                if(D[i][k]+D[k][j]<D[i][j])  //从i经k到j更短 
				{
                    D[i][j]=D[i][k]+D[k][j];
                    path[i][j]=path[k][j];  //更改j的前驱为k 
                }
}

void Path(AMGraph G,int a,int b) //获得具体路径
{
	a--;b--; //与下表保持一致 
   int p[10];  //存储经过点的序号 
   p[0]=b;   //尾结点存储在第一个 
   int i=1;
   while(a!=b)  //两端点不同 
   {
    b=path[a][b];
    p[i]=b;
    i++;
   }
   printf("路径:%s",G.vexs[a].name); //打印初始顶点 
   i=i-2;  //i下表回溯到数组p最后一位 
   while(i>=0)
   {
   	printf("-->%s",G.vexs[p[i]].name); //打印下一个经过的顶点 
    i--;
   }
   printf("\n");
}
void Ask(AMGraph &G)  //问路
{
	int n1,n2;
    char c;
	printf("本校景点有：\n");
	for(int i=0;i<G.vexnum;i++)
		printf("%d.%s\n",i+1,G.vexs[i].name);
	while(1)
	{
		printf("您现在所在位置:");
		scanf("%d",&n1);
		printf("您要去的位置:");
		scanf("%d",&n2);
		if(n1<1||n1>G.vexnum) //不合法 
		{
			printf("请重新输入正确的您现在所在位置:");
			scanf("%d",&n1);
			continue; 
		}
		if(n2<1||n2>G.vexnum) 
		{
			printf("请重新输入正确的您要去的位置:");
			scanf("%d",&n2);
			continue; 
		}
		break;
	}
    Floyd(G);  //调用最短路径方法求 
    if(D[n1-1][n2-1]==MaxInt)
    	printf("我们抱歉的通知：您选择的地点暂时无法到达！\n");
	else
	{ 
	    printf("最短路径长度为：%d\n",D[n1-1][n2-1]);
	    Path(G,n1,n2);//调用路径函数打印路径 
	}
}
void AddVertex(AMGraph &G) //增加新的顶点 
{
	G.vexnum++;
	if (G.vexnum == 1000)   //顶点上限 
	{
		printf("错误：已超过最大顶点限度！\n");
		exit(0);
	}
	printf("请输入你想加入景点的名字：\n");
    scanf("%s", G.vexs[G.vexnum-1].name);
    printf("请输入你想加入景点的信息：\n");
    scanf("%s", G.vexs[G.vexnum-1].info);
}
void ChangeInfo(AMGraph &G) //改变信息 
{
	int num;
	printf("请输入您想修改信息的景点编号：\n");
	scanf("%d",&num);
	printf("请输入该景点的新信息是：\n");
    scanf("%s", G.vexs[num-1].info);
}
int min(int a, int b)  
{
	if(a<b) return a;
	else return b;
}
void Addegde(AMGraph &G) 
{
	int v,w, z;
	printf("本校景点有：\n");
	for(int i=0;i<G.vexnum;i++)
		printf("%d.%s\n",i+1,G.vexs[i].name);
	printf("请输入你要添加两景点之间路径的景点序号：\n");
	scanf("%d%d",&v,&w) ;
	printf("请输入你要添加景长度：\n");
	scanf("%d",&z) ;
	G.arcs[v-1][w-1] = G.arcs[w-1][v-1] = min(z,G.arcs[v-1][w-1]);  //领接矩阵赋值 
	G.arcnum++; //边数+1 
	printf("加边成功！\n");
}
void Welcome(AMGraph G)  //欢迎函数 
{
	printf("**********欢迎来到北京林业大学**********\n");
	printf("1.查询景点信息\n2.问路查询\n3.增加一个新景点及其相关信息\n4.修改一个已有景点的相关信息\n5.增加一条新的路径\n6.退出\n");
	int num;
	while (1) //服务选择 
		{
			num=0;
			printf("**********北林校园导游系统**********\n");
			printf("请输入你要的服务：");
			scanf("%d",&num);
			if(num==1) Search(G);
			else if(num==2) Ask(G);
			else if(num==3) AddVertex(G);
			else if(num==4) ChangeInfo(G);
			else if(num==5) Addegde(G);
			else if(num==6) {printf("感谢使用本系统，期待与您再次相见！\n");break;}
			else printf("该功能暂未开放,敬请期待！\n");
		}
}
void CreateUDN(AMGraph &G)  //创建无向图 
{
	int i,j,k,num=0,w;
	VertexType v1,v2;
	char c;
	FILE *fp=fopen("graph.txt","r");
	if(!fp)
	{
		printf("ERROR!\n");
		exit(0);
	}
	fscanf(fp,"%d",&G.vexnum);  //顶点数 
	fscanf(fp,"%d",&G.arcnum);  // 边数 
	for(i=0;i<G.vexnum;i++)
	{
		fscanf(fp,"%s%s",G.vexs[i].name,G.vexs[i].info); //从文件中读入名称和信息 
	}
	for(i=0;i<100;i++)
		for(j=0;j<100;j++)
			G.arcs[i][j]=MaxInt; //全部赋值最大值 
	for(k=0;k<G.arcnum;k++)
	{
		fscanf(fp,"%s%s%d",v1.name,v2.name,&w);
		i=LocateVex(G,v1);
		j=LocateVex(G,v2);
		G.arcs[i][j]=w;  //赋权值 
		G.arcs[j][i]=G.arcs[i][j];
	}
	fclose(fp);
}
int main()
{
	AMGraph G; 
	CreateUDN(G); //创建无向图 
	Welcome(G);
	return 0; 
}
