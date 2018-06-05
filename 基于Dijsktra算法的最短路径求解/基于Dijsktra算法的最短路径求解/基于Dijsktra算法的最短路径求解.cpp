#include<iostream> 
#include<cstdio>  
#include<cstring> 
using namespace std;
#define MaxInt 32767
#define MVNum 100
typedef char VerTexType;
typedef int ArcType;
typedef struct {
	VerTexType vexs[MVNum];
	ArcType arcs[MVNum][MVNum];
	int vexnum, arcnum;
}AMGraph;
int LocateVex(AMGraph G, VerTexType u)
{//存在则返回u在顶点表中的下标;否则返回-1
	int i;
	for (i = 0; i<G.vexnum; ++i)
		if (u == G.vexs[i])
			return i;
	return -1;
}

void CreateUDN(AMGraph &G, int m, int n) {
	char v1, v2;
	int i, j, k, w;
	G.vexnum = m;
	G.arcnum = n;;
	for (i = 0; i < G.vexnum; i++) {
		cin >> G.vexs[i];
	}
	for (i = 0; i < G.vexnum; i++)
		for (j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = MaxInt;	//初始化邻接矩阵
	for (k = 0; k < G.arcnum; k++) {
		cin >> v1 >> v2 >> w;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G.arcs[i][j] = w;
		G.arcs[j][i] = G.arcs[i][j];
	}
}
void ShortestPath(AMGraph G, char a, char b) {
	int v0 = LocateVex(G, a);
	int final = LocateVex(G, b);
	int n = G.vexnum;
	int v;
	int min, w, flag = 0;
	int D[100], Recode[100];
	bool S[100];
	int Path[100];
	memset(S, false, sizeof(S));
	memset(D, 0, sizeof(D));
	memset(Recode, 0, sizeof(Recode));
	memset(Path, 0, sizeof(Path));
	for (v = 0; v < n; v++) {
		S[v] = false;
		D[v] = G.arcs[v0][v];
		if (D[v] < MaxInt)
			Path[v] = v0;
		else
			Path[v] = -1;
	}
	S[v0] = true;
	D[v0] = 0;
	for (int i = 1; i < n; i++) {
		min = MaxInt;
		for (w = 0; w < n; w++)
			if (!S[w] && D[w] < min) {
				v = w;
				min = D[w];
			}
		S[v] = true;
		for (w = 0; w < n; w++) {
			if (!S[w] && D[v] + G.arcs[v][w] < D[w]) {
				D[w] = D[v] + G.arcs[v][w];
				Path[w] = v;
			}
		}
		if (S[final] == true)
			break;
	}
	cout << D[final] << endl;
	int k = final;
	while (1) {
		Recode[flag] = k;
		flag++;
		k = Path[k];
		if (k == v0) {
			Recode[flag] = k;
			break;
		}
	}
	for (int i = flag; i >= 0; i--) {
		if (flag>0)
			cout << G.vexs[Recode[i]] << " ";
		else
			cout << G.vexs[Recode[i]];
	}
	cout << endl;
}
int main() {
	AMGraph G;
	int m, n;
	char a, b;
	cin >> m >> n;
	while (1) {
		if (m != 0 && n != 0) {
			CreateUDN(G, m, n);
			cin >> a >> b;
			ShortestPath(G, a, b);
			cin >> m >> n;
		}
		else
			exit(0);
	}
	system("pause");
	return 0;
}
