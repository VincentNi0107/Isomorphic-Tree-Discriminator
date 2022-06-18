#include "tree.h"
tree::tree(string file){
    ifstream file_ifs;
    file_ifs.open(file, ios::in);
    string line;
    
    while (getline(file_ifs, line)) {
        if (line.empty())
            break;
        int pos=line.find("->");
        int i=0;
        while(line[i]==' ')i++;
        string from=line.substr(i,pos);
        string to=line.substr(pos+2);
        while(to.back()==' ')to.pop_back();
        //create node id - node name pair
        auto it = name.find(from);
        if (it == name.end()){
            name[from]=children.size();
            children.push_back(vector<int>());
            parent.push_back(-1);
        }
        it = name.find(to);
        if (it == name.end()){
            name[to]=children.size();
            children.push_back(vector<int>());
            parent.push_back(-1);
        }
        children[name[from]].push_back(name[to]);
        ASSERT(parent[name[to]]==-1,"more than one parent");
        parent[name[to]]=name[from];
    }
    //Check one root
    vector<int> parent_num;
    for(int i=0;i<children.size();++i){
        parent_num.push_back(0);
    }
    for(int i=0;i<children.size();++i){
        for(int j=0;j<children[i].size();++j){
            parent_num[children[i][j]]++;
        }
    }
    root=-1;
    for(int i=0;i<parent_num.size();++i){
        if(parent_num[i]==0){
            ASSERT(root==-1,"more than one root!");
            root=i;
            // cout<<root;
        }
    }
    node_name.resize(name.size());
    file_ifs.close();
    
    get_pos(root,0);
    
}
void tree::assign_name_(int node){
    //node name for AHU
    if(children[node].size()==0){
        node_name[node]="10";
        return;
    }
    priority_queue < string , vector < string >, greater < string > > q;
    for(int i=0;i<children[node].size();++i){
        assign_name_(children[node][i]);
        q.push(node_name[children[node][i]]);
    }
    node_name[node]="1";
    while (q.size()>0)
    {
        node_name[node]+=q.top();q.pop();
    }
    node_name[node]+="0";
    return;
}



int tree::assign_shared_id_(int node,int id){
    // create shared id - id for node hightlight
    shared_id[node]=id++;
    priority_queue < pair<string,int> > q;
    for(int i=0;i<children[node].size();++i){
        q.push(pair<string,int>(node_name[children[node][i]],children[node][i]));
    }
    while (q.size()>0)
    {
        id=assign_shared_id_(q.top().second,id);
        q.pop();
    }
    return id;
}

void tree::get_pos(int node,int depth){
    // calculate the position of each node
    if(pos.size()<=depth){
        pos.push_back(vector<int>());
    }
    pos[depth].push_back(node);
    for(int i=0;i<children[node].size();++i){
        get_pos(children[node][i],depth+1);
    }
    return;
}