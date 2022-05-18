#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxInt 32767
int path[10][10],D[10][10]={0}; //����洢·����������·������ 
typedef int ArcType;
typedef struct
{ 
	char name[100];
	char info[10000];
}VertexType; //����ṹ
typedef struct
{ 
	VertexType vexs[10];
	int arcs[100][100];//�ڽӾ���
	int vexnum,arcnum;//����������ߵĸ���
}AMGraph; //ͼ�ṹ 
int LocateVex(AMGraph G,VertexType u)  //��λ���� 
{
	int i;
	for(i=0;i<G.vexnum;i++)
	{
		if(strcmp(u.name,G.vexs[i].name)==0) return i; //�Ƚ��Ƿ������ַ������ 
	}
	return -1;
}
void Search(AMGraph &G) //�Ծ�����˽� 
{
	char c;
	int num;
	printf("��У�����У�\n");
	for(int i=0;i<G.vexnum;i++)  //��ӡ�������� 
		printf("%d.%s\n",i+1,G.vexs[i].name);
	printf("��������Ҫ�˽�ص�ı��:");
	scanf("%d",&num);
	int p=1;  //ָʾ���� ���ж�����ʱ�� 
	while(p)
	{
		if(num>G.vexnum||num<1)  //�������ֲ��Ϸ� 
		{
			printf("������������Ҫ�˽�ص�ı��:");
			scanf("%d",&num);
			continue;
		 } 
		 printf("%s",G.vexs[num-1].info); //�Ϸ��������Ӧ��Ϣ 
		p=0;
	}
	printf("\n");
}
void Floyd(AMGraph G) //���������㷨��������·��
{  
    int i,j,k;
    for(i=0;i<G.vexnum;i++)  //��Ӧ���֮����֪·���;��� 
        for(j=0;j<G.vexnum;j++) 
			D[i][j]=MaxInt;
    for(i=0;i<G.vexnum;i++)  //��Ӧ���֮����֪·���;��� 
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
                if(D[i][k]+D[k][j]<D[i][j])  //��i��k��j���� 
				{
                    D[i][j]=D[i][k]+D[k][j];
                    path[i][j]=path[k][j];  //����j��ǰ��Ϊk 
                }
}

void Path(AMGraph G,int a,int b) //��þ���·��
{
	a--;b--; //���±���һ�� 
   int p[10];  //�洢���������� 
   p[0]=b;   //β���洢�ڵ�һ�� 
   int i=1;
   while(a!=b)  //���˵㲻ͬ 
   {
    b=path[a][b];
    p[i]=b;
    i++;
   }
   printf("·��:%s",G.vexs[a].name); //��ӡ��ʼ���� 
   i=i-2;  //i�±���ݵ�����p���һλ 
   while(i>=0)
   {
   	printf("-->%s",G.vexs[p[i]].name); //��ӡ��һ�������Ķ��� 
    i--;
   }
   printf("\n");
}
void Ask(AMGraph &G)  //��·
{
	int n1,n2;
    char c;
	printf("��У�����У�\n");
	for(int i=0;i<G.vexnum;i++)
		printf("%d.%s\n",i+1,G.vexs[i].name);
	while(1)
	{
		printf("����������λ��:");
		scanf("%d",&n1);
		printf("��Ҫȥ��λ��:");
		scanf("%d",&n2);
		if(n1<1||n1>G.vexnum) //���Ϸ� 
		{
			printf("������������ȷ������������λ��:");
			scanf("%d",&n1);
			continue; 
		}
		if(n2<1||n2>G.vexnum) 
		{
			printf("������������ȷ����Ҫȥ��λ��:");
			scanf("%d",&n2);
			continue; 
		}
		break;
	}
    Floyd(G);  //�������·�������� 
    if(D[n1-1][n2-1]==MaxInt)
    	printf("���Ǳ�Ǹ��֪ͨ����ѡ��ĵص���ʱ�޷����\n");
	else
	{ 
	    printf("���·������Ϊ��%d\n",D[n1-1][n2-1]);
	    Path(G,n1,n2);//����·��������ӡ·�� 
	}
}
void AddVertex(AMGraph &G) //�����µĶ��� 
{
	G.vexnum++;
	if (G.vexnum == 1000)   //�������� 
	{
		printf("�����ѳ�����󶥵��޶ȣ�\n");
		exit(0);
	}
	printf("������������뾰������֣�\n");
    scanf("%s", G.vexs[G.vexnum-1].name);
    printf("������������뾰�����Ϣ��\n");
    scanf("%s", G.vexs[G.vexnum-1].info);
}
void ChangeInfo(AMGraph &G) //�ı���Ϣ 
{
	int num;
	printf("�����������޸���Ϣ�ľ����ţ�\n");
	scanf("%d",&num);
	printf("������þ��������Ϣ�ǣ�\n");
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
	printf("��У�����У�\n");
	for(int i=0;i<G.vexnum;i++)
		printf("%d.%s\n",i+1,G.vexs[i].name);
	printf("��������Ҫ���������֮��·���ľ�����ţ�\n");
	scanf("%d%d",&v,&w) ;
	printf("��������Ҫ��Ӿ����ȣ�\n");
	scanf("%d",&z) ;
	G.arcs[v-1][w-1] = G.arcs[w-1][v-1] = min(z,G.arcs[v-1][w-1]);  //��Ӿ���ֵ 
	G.arcnum++; //����+1 
	printf("�ӱ߳ɹ���\n");
}
void Welcome(AMGraph G)  //��ӭ���� 
{
	printf("**********��ӭ����������ҵ��ѧ**********\n");
	printf("1.��ѯ������Ϣ\n2.��·��ѯ\n3.����һ���¾��㼰�������Ϣ\n4.�޸�һ�����о���������Ϣ\n5.����һ���µ�·��\n6.�˳�\n");
	int num;
	while (1) //����ѡ�� 
		{
			num=0;
			printf("**********����У԰����ϵͳ**********\n");
			printf("��������Ҫ�ķ���");
			scanf("%d",&num);
			if(num==1) Search(G);
			else if(num==2) Ask(G);
			else if(num==3) AddVertex(G);
			else if(num==4) ChangeInfo(G);
			else if(num==5) Addegde(G);
			else if(num==6) {printf("��лʹ�ñ�ϵͳ���ڴ������ٴ������\n");break;}
			else printf("�ù�����δ����,�����ڴ���\n");
		}
}
void CreateUDN(AMGraph &G)  //��������ͼ 
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
	fscanf(fp,"%d",&G.vexnum);  //������ 
	fscanf(fp,"%d",&G.arcnum);  // ���� 
	for(i=0;i<G.vexnum;i++)
	{
		fscanf(fp,"%s%s",G.vexs[i].name,G.vexs[i].info); //���ļ��ж������ƺ���Ϣ 
	}
	for(i=0;i<100;i++)
		for(j=0;j<100;j++)
			G.arcs[i][j]=MaxInt; //ȫ����ֵ���ֵ 
	for(k=0;k<G.arcnum;k++)
	{
		fscanf(fp,"%s%s%d",v1.name,v2.name,&w);
		i=LocateVex(G,v1);
		j=LocateVex(G,v2);
		G.arcs[i][j]=w;  //��Ȩֵ 
		G.arcs[j][i]=G.arcs[i][j];
	}
	fclose(fp);
}
int main()
{
	AMGraph G; 
	CreateUDN(G); //��������ͼ 
	Welcome(G);
	return 0; 
}
