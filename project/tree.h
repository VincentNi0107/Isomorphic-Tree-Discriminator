#ifndef TREE_H
#define TREE_H
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

#define ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << ":" << __LINE__ << " msg: " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)

class tree{
public:
    tree();
    tree(string file);
    void draw();
    void assign_name_(int node);
    void assign_name(){
        assign_name_(root);
    }
    int assign_shared_id_(int node,int id);
    void assign_shared_id(){
        assign_shared_id_(root,0);
        for(auto it=shared_id.begin();it!=shared_id.end();it++){
            inv_shared_id[it->second]=it->first;
            // cout<<it->first<<":"<<it->second<<'\n';
        }
        // cout<<"                                       \n";
    }
    void get_pos(int node,int depth);
    int get_root(){
        return root;
    }
    string get_name(){
        return node_name[root];
    }
    vector<vector<int>> get_position(){
        return pos;
    }
    int id2shared(int id){
        return shared_id[id];
    }
    int shared2id(int id){
        return inv_shared_id[id];
    }
    int shared_id2pos(int id,int dep){
        id=inv_shared_id[id];
        int wid;
        for(wid=0;wid<pos[dep].size();wid++){
            if(id==pos[dep][wid])return wid; 
        }
        return -1;
    }
    string shared_id2name(int id){
        id=inv_shared_id[id];
        for(auto it=name.begin();it!=name.end();it++){
            if(it->second==id)return it->first;
        }
        return "??";
    }
    int num_of_nodes(){
        return children.size();
    }
    int sharedid2parent(int id){
        id=inv_shared_id[id];
        int par=parent[id];
        return shared_id[par];
    }
    

private:
    vector<vector<int>> children; //children id of each node
    map<string,int> name; //node name - node id
    vector<int> parent;// parent id of each node, -1 means root
    vector <string> node_name;// name for AHU
    map<int,int> shared_id;// node id - shared node id
    map<int,int> inv_shared_id;// shared node id - node id
    int root;// id of root node
    vector<vector<int>> pos;
};
#endif