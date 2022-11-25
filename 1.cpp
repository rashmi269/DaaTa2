#include <bits/stdc++.h>
using namespace std;
int cost_tree = 0 ;
void adjacent(vector<vector<int>> &matrix , int n)
{
    int r;
    cout<<"Adjacaceney matrix"<<endl;
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < i ; j++)
        {
            r= (rand() % 10) + 1;
            matrix[i][j] = r;
            matrix[j][i] = r;
        }
    }

    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
             cout<<matrix[i][j];
             cout<<" ";
        }
        cout<<endl;
    }

    int per = (((n*n)*0.01)*40)/2;
    for(int k = 0 ; k < per ; k++)
    {
        int i = (rand() % (n-1)) + 1;
        int j = (rand() % (n-1)) + 1;

        if(i==j || matrix[i][j] == 0 )
        {
            k--;
        }

        matrix[i][j] = 0 ;
        matrix[j][i] = 0 ;
    }


    cout<<"Conditional Randomization"<<endl;
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
             cout<<matrix[i][j];
             cout<<" ";
        }
        cout<<endl;
    }

}

void findingpaths(vector<vector<int> >& paths,vector<int>& path,vector<int> parent[],int n, int u)
{

    if (u == -1) {
        paths.push_back(path);
        return;
    }


    for (int par : parent[u]) {


        path.push_back(u);

        findingpaths(paths, path, parent,
                   n, par);

        path.pop_back();
    }

}
void path_matrix(vector<vector<int>> adj,vector<int> parent[],int n, int start)
{

    vector<int> dist(n, INT_MAX);
    queue<int> q;

    q.push(start);
    parent[start] = { -1 };
    dist[start] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] > dist[u] + 1) {


                dist[v] = dist[u] + 1;
                q.push(v);
                parent[v].clear();
                parent[v].push_back(u);
            }
            else if (dist[v] == dist[u] + 1) {


                parent[v].push_back(u);
            }
        }
    }

    for(int i = 0 ; i < dist.size() ; i++)
    {
        cost_tree+=dist[i];
    }
}
vector<vector<int>> convert( vector<vector<int>> &a)
{
    vector<vector<int>> AdjList(a.size());
    for (int i = 0; i < a.size(); i++)
    {

        for (int j = 0; j < a[i].size(); j++)
        {
            if (a[i][j] > 0)
            {
                AdjList[i].push_back(j);
            }
        }

    }

    return AdjList;
}

void mst_1(vector<vector<int>> &G , int V)
{
    int no_edge , cost = 0 , count=0;
    int selected[V];
    memset(selected, false, sizeof(selected));
    cout<<selected[3];
    no_edge = 0;
    selected[0] = true;
    int x;  //  row number
    int y;  //  col number

    while (no_edge < V - 1) {
             int min = 9999;
    x = 0;
    y = 0;

    for (int i = 0; i < V; i++) {
      if (selected[i]) {
        for (int j = 0; j < V; j++) {
          if (!selected[j] && G[i][j]) {  // not in selected and there is an edge
            if (min > G[i][j]) {
              min = G[i][j];
              x = i;
              y = j;
              count++;
            }
          }
        }
      }
    }
    if(count == 0)
      cout <<x<< " - " << y;
    else
      cout<< " - " << y;
    cost+=G[x][y];
    selected[y] = true;
    no_edge++;
  }
  cout<<endl<<"COST IS : "<<cost<<endl;
}

void mst_l(vector<vector<int>> adj,int n, int start, int end)
{
    vector<vector<int> > paths;
    vector<int> path;
    vector<int> parent[n];


    path_matrix(adj, parent, n, start);


    findingpaths(paths, path, parent, n, end);
    for (auto v : paths) {


        reverse(v.begin(), v.end());

        for (int u : v)
            cout <<u<<" - ";
      
    }
    cout<<endl<<"COST IS : "<<cost_tree<<endl;
}

void ins_dlt(vector<vector<int>> &matrix)
{
    int n;
    int in;
    cout<<"ENTER THE NUMBER OF INPUT OPERATION : ";
    cin>>n;

    do{
            cout<<"1.INSERT"<<endl<<"2.DELETE"<<endl;
            cin>>in;
            switch(in)
            {
               case 1:
                      int s , d , cost;
                      cout<<"Source :";
                      cin>>s;
                      cout<<endl<<"Destination :";
                      cin>>d;
                      cout<<"Enter cost :";
                      cin>>cost;
                      matrix[s][d] = cost;
                      cout<<"Data insterted!!"<<endl;
                      n--;
                break;

                case 2:
                      int s1 , d1;
                      cout<<"ENTER SOURCE :";
                      cin>>s1;
                      cout<<endl<<"ENTER DESTINATION :";
                      cin>>d1;
                      matrix[s][d] = 0;
                      cout<<"PATH DELETED SUCCESSFULLY!!"<<endl;
                      n--;
                break;
            }

    }while(n!=0);
}

int main()
{
    int input_size=0;
    cout<<"ENTER THE INPUT SIZE : ";
    cin>>input_size;
    vector<vector<int>> matrix(input_size, vector<int> (input_size, 0)) ;
    adjacent(matrix , input_size);
   vector<vector<int>> AdjList = convert(matrix);
   cout<<"Min cost spanning tree"<<endl;

   mst_1(matrix,input_size);

   cout<<"   MINIMUM COST spanning tree of paticular source to node to destination: "<<endl;


   int source , destination;
   cout<<"ENTER SOURCE NODE :";
   cin>>source;
   cout<<"ENTER DESTINATION NODE :";
   cin>>destination;
   mst_l(AdjList , input_size ,source, destination );
   
   cout<<"Insertion Deletion operation"<<endl;
   
   ins_dlt(matrix);
   
   cout<<"  Min cost spanning tree after doing changes"<<endl;
   
   mst_l(AdjList , input_size ,source, destination );
    return 0;
}
