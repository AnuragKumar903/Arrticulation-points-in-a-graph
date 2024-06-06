#include <bits/stdc++.h>

using namespace std;


void dfs(int node, int parent, unordered_map<int, list<int>> &adj,
          vector<int> &disc,  vector<int> &low, unordered_map<int, bool> &vis,
          int timer, vector<int> &ap){

  vis[node] = true;
  disc[node] = low[node] = timer++;
  int child = 0;

  // neighbour travel
  for(auto nbr : adj[node]){
    if(nbr == parent)  continue;

    if(!vis[nbr]){
      dfs(nbr, node, adj, disc, low, vis, timer, ap);

      // while returning -->   child ka back edge ho tub
      low[node] = min(low[node], low[nbr]);

      // cut edge check
      if(low[nbr] >= disc[node] && parent != -1)
        ap[node] = true; 

      child++;
    }

    else // back edge
      low[node] = min(low[node], disc[nbr]);
  }
  if(parent == -1 && child > 1){
    ap[node] = true;
  }
          }

int main() {
  // edge vector
  int v = 5;
  int e = 6;
  vector<pair<int,int> > edges;
  edges.push_back(make_pair(0, 3));
  edges.push_back(make_pair(0, 4));
  edges.push_back(make_pair(4, 3));
  edges.push_back(make_pair(0, 1));
  edges.push_back(make_pair(1, 2));

  // adjacency list
  unordered_map<int, list<int>> adj;
  for(int i = 0; i < e; i++){
    int u = edges[i].first;
    int v = edges[i].second;

    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  // data structures
  int timer = 0;
  int parent = -1;
  vector<int> disc(v);
  vector<int> low(v);
  unordered_map<int, bool> vis;

  vector<int> ap(v,0);

  for(int i = 0; i < v; i++){
    disc[i] = -1;
    low[i] = -1;
  }

  // dfs traversal
  for(int i = 0; i < v; i++){
    if(!vis[i]){
      dfs(i, parent, adj, disc, low, vis, timer, ap);
    }
  }

  cout<<"The cut vertices are: "<<endl;
  for(int i = 0; i < v; i++){
    cout<<ap[i]<<" ";
  }
  cout<<endl;

  return 0;
}