#include<iostream>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<vector>
#include<deque>
#include<list>
#include<assert.h>
using namespace std;

//#include"MinHeap.h"
//#include"UFSets.h"
#define MAXCOST 0x7fffffff

template<class Type>
void Swap(Type &a,Type &b)
{
	Type x = a;
	a = b;
	b = x;
}
template<class DistType>
struct MSTEdgeNode 
{
	int head,tail;
	DistType cost;
public:
	bool operator<(const MSTEdgeNode<DistType> &mst) const
	{
		return cost<mst.cost;
	}

	bool operator>=(const MSTEdgeNode<DistType> &mst) const
	{
		return !(*this<mst);
	}

	bool operator>(const MSTEdgeNode<DistType> &mst) const
	{
		return cost>mst.cost;
	}

	bool operator<=(const MSTEdgeNode<DistType> &mst) const
	{
		return !(*this>mst);
	}
};

template<class NameType,class DistType>
class Graph
{
private:
	vector<NameType> vexlist;
	vector<vector<DistType> > edges;
	int vexnum;
	int arcnum;
	int kind;// 0 1 2 3 
public:
	Graph():vexnum(0),arcnum(0),kind(0){}
	~Graph(){}
	int GetVexnum() const { return vexnum;}
	int GetArcnum() const { return arcnum;}

public:
	friend istream & operator>>(istream &in,Graph<NameType,DistType> &myg)
	{
		int v,u;
		int i;
		DistType w;
		cout<<"请输入顶点的个数 : "<<endl;
		in>>myg.vexnum;
		cout<<"请输入顶点信息: "<<endl;
		for(i = 0;i<myg.vexnum;++i)
		{
			NameType item;
			in>>item;
			myg.vexlist.push_back(item);
		}
		myg.edges.resize(myg.vexnum);
		for(i = 0;i<myg.vexnum;++i)
		{
			myg.edges[i].resize(myg.vexnum,MAXCOST);
		}
		for(i = 0;i<myg.vexnum;++i)
		{
			myg.edges[i][i] = 0;
		}
		
		cout<<"请输入边的个数 : "<<endl;
		in>>myg.arcnum;
		for(i = 0;i<myg.arcnum;++i)
		{
			cout<<"输入第 "<<i+1<<" 边和权值"<<endl;
			cin>>v>>u>>w;
			myg.edges[v][u] = w;
			myg.edges[u][v] = w;
		}
		return in;
	}
	friend ostream & operator<<(ostream &out,const Graph<NameType,DistType> &myg)
	{
		int i ,j;
		out<<"输出顶点个数和信息 "<<endl;
		out<<myg.vexnum<<endl;
		for(i = 0;i<myg.vexnum;++i)
		{
			out<<myg.vexlist[i]<<" ";
		}
		out<<endl;
		out<<"输出邻接矩阵: "<<endl;
		for(i = 0;i<myg.vexnum;++i)
		{
			for(j = 0;j<myg.vexnum;++j)
			{
				if(myg.edges[i][j] == MAXCOST)
				{
					cout<<"$"<<" ";
				}else
				{
					out<<myg.edges[i][j]<<" ";
				}
			}
			out<<endl;
		}
		out<<endl;
		return out;
	}
	
	void Kruskal(vector<MSTEdgeNode<DistType> > &mst)
	{
		MinHeap<MSTEdgeNode<DistType> > mh;
		UFSets set(vexnum);
		for(int i = 1;i<vexnum;++i)
		{
			for(int j = 0;j<i;++j)
			{
				if(edges[i][j] != MAXCOST)
				{
					MSTEdgeNode<DistType> item={i,j,edges[i][j]};
					mh.Insert(item);
				}
			}
		}

		MSTEdgeNode<DistType> dist;
		int k = 0;
		while(k<vexnum-1 && !mh.empty())
		{
			mh.Remove(dist);
			if(set.Union(dist.head,dist.tail))
			{
				mst.push_back(dist);
				++k;
			}
		}
	}
	void Prim(int v,vector<MSTEdgeNode<DistType> > &mst)
	{
		int i,j;
		for(i = 0;i<vexnum;++i)
		{
			if(v != i)
			{
				MSTEdgeNode<DistType> item={v,i,edges[v][i]};
				mst.push_back(item);
			}
		}//edges
		for(i = 0;i<vexnum-1;++i)
		{
			int k = i;
			DistType min = MAXCOST;
			for(j = i;j<vexnum-1;++j)
			{
				if(min > mst[j].cost )
				{
					k =j;
					min = mst[j].cost;
				}
			}
			int u = mst[k].tail;
			Swap(mst[i],mst[k]);
			for(j = i+1;j<vexnum-1;++j)
			{
				if(edges[u][mst[j].tail] < mst[j].cost)
				{
					mst[j].cost = edges[u][mst[j].tail];
					mst[j].head = u;
				}
			}
		}
	}

	void AllLengths(int v,vector<MSTEdgeNode<DistType> > &mst)
	{
		int i;
		vector<DistType> dist(vexnum);
		vector<int> next(vexnum);
		for( i = 0;i<vexnum;++i)
		{
			if(i == v)
				next[i] = -1;
			else
				next[i] =v;
		}
		for(i = 0;i<vexnum;++i)
		{
			dist[i] = edges[v][i];
		}
		int k = 0;
		while(k < vexnum-1)
		{
			for(i = 0;i<vexnum;++i)
			{
				for(int j = i+1;j<vexnum;++j)
				{
					if(next[j] != -1 )
					{
					}
				}
				//
			}

		}
	}

};

void main()
{
	Graph<char,int> myg;
	cin>>myg;
	cout<<myg<<endl;
	vector<MSTEdgeNode<int> >mst;

	//myg.Kruskal(mst);
	myg.AllLengths(0,mst);
	myg.Prim(0,mst);
	vector<MSTEdgeNode<int> >::iterator it = mst.begin();
	for(; it != mst.end(); ++it)
	{
		cout<<it->head<<" : "<<it->tail <<"--> "<<it->cost<<endl;
	}


}