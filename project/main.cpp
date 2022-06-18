#include "tree.h"
# include "std_lib_facilities.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include "myline.h"

using namespace std;

// callback function for every node
void copy_cb( Fl_Widget* o , void* p) {
    Fl_Button* b1=(Fl_Button*)o;
    Fl_Button* b2=(Fl_Button*)p;
    b1->label(b1->label());
    b2->label(b2->label());
    if(b1->color()!=FL_RED){
        b1->color(FL_RED);
        b2->color(FL_RED);  
    }
    else{
        b1->color(FL_DARK_GREEN);
        b2->color(FL_DARK_GREEN); 
    }
}

int main(int argc,char* argv[]){
    ASSERT(argc==3,"argument wrong!!");
    tree t1(argv[1]);
    tree t2(argv[2]);
    //create tree and determine isomorphic
    t1.assign_name();
    t1.assign_shared_id();
    t2.assign_name();
    t2.assign_shared_id();
    string title;
    bool iso=t1.get_name()==t2.get_name()?true:false;

    vector<vector<int>> tree1_pos=t1.get_position();
    vector<vector<int>> tree2_pos=t2.get_position();
    map<int,int> tree1_x,tree2_x,tree1_y,tree2_y;//coordinate x y of nodes
    Fl_Window* win= new Fl_Window(1500,800, "tree visualize");
    win->begin();
    //draw nodes
    if(iso){
        Fl_Box* box=new Fl_Box(700,0,100,100,"Isomorphic Trees");
        box->labelfont(FL_BOLD_ITALIC);
        box->labelsize(20);
        int max_wid=-1;
        for(int dep=0;dep<tree1_pos.size();++dep){
            int wid=tree1_pos[dep].size();
            max_wid=max(max_wid,wid);
        }
        int width_of_node=700/max_wid;//max node number in a line determines node width
        vector<int> x_pos;

        x_pos.resize(max_wid);
        for(int i=0;i<max_wid;++i){
            x_pos[i]=width_of_node*i;
        }
        for(int dep=0;dep<tree1_pos.size();++dep){
            for(int wid=0;wid<tree1_pos[dep].size();wid++){
                int shared_id=t1.id2shared(tree1_pos[dep][wid]);
                char * name1=new char [t1.shared_id2name(shared_id).length()+1];
                std::strcpy (name1, t1.shared_id2name(shared_id).c_str());
                int x1=10+x_pos[max_wid/2-tree1_pos[dep].size()/2+wid];
                Fl_Button* but1 = new Fl_Button( x1, 100*(dep+1), width_of_node*0.7, 50, name1);
                tree1_x[shared_id]=x1+width_of_node*0.35;
                tree1_y[shared_id]=100*(dep+1);
                but1->color(FL_DARK_GREEN);
                but1->box(FL_OFLAT_BOX);
                char * name2=new char [t2.shared_id2name(shared_id).length()+1];
                std::strcpy (name2, t2.shared_id2name(shared_id).c_str());
                int wid2=t2.shared_id2pos(shared_id,dep);
                int x2=760+x_pos[max_wid/2-tree1_pos[dep].size()/2+wid2];
                tree2_x[shared_id]=x2+width_of_node*0.35;
                tree2_y[shared_id]=100*(dep+1);
                Fl_Button* but2 = new Fl_Button(x2, 100*(dep+1), width_of_node*0.7, 50, name2);
                but2->color(FL_DARK_GREEN);
                but2->box(FL_OFLAT_BOX);
                but1->callback(copy_cb,but2);
                but2->callback(copy_cb,but1);
            }
        }
    }
    else{
        Fl_Box* box=new Fl_Box(700,0,100,100,"Non-Isomorphic Trees");
        box->labelfont(FL_BOLD_ITALIC);
        box->labelsize(20);
        int max_wid1=-1;
        for(int dep=0;dep<tree1_pos.size();++dep){
            int wid=tree1_pos[dep].size();
            max_wid1=max(max_wid1,wid);
        }
        int max_wid2=-1;
        for(int dep=0;dep<tree2_pos.size();++dep){
            int wid=tree2_pos[dep].size();
            max_wid2=max(max_wid2,wid);
        }
        int width_of_node1=700/max_wid1;
        int width_of_node2=700/max_wid2;
        vector<int> x_pos1;
        vector<int> x_pos2;
        x_pos1.resize(max_wid1);
        x_pos2.resize(max_wid2);
        for(int i=0;i<max_wid1;++i){
            x_pos1[i]=width_of_node1*i;
        }
        for(int i=0;i<max_wid2;++i){
            x_pos2[i]=width_of_node2*i;
        }
        for(int dep=0;dep<tree1_pos.size();++dep){
            for(int wid=0;wid<tree1_pos[dep].size();wid++){
                int shared_id=t1.id2shared(tree1_pos[dep][wid]);
                char * name1=new char [t1.shared_id2name(shared_id).length()+1];
                std::strcpy (name1, t1.shared_id2name(shared_id).c_str());
                int x1=10+x_pos1[max_wid1/2-tree1_pos[dep].size()/2+wid];
                Fl_Button* but1 = new Fl_Button( x1, 100*(dep+1), width_of_node1*0.7, 50, name1);
                tree1_x[shared_id]=x1+width_of_node1*0.35;
                tree1_y[shared_id]=100*(dep+1);
                but1->color(FL_DARK_GREEN);
                but1->box(FL_OFLAT_BOX);
            }
        }
        for(int dep=0;dep<tree2_pos.size();++dep){
            for(int wid=0;wid<tree2_pos[dep].size();wid++){
                int shared_id=t2.id2shared(tree2_pos[dep][wid]);
                char * name2=new char [t2.shared_id2name(shared_id).length()+1];
                std::strcpy (name2, t2.shared_id2name(shared_id).c_str());
                int x2=760+x_pos2[max_wid2/2-tree2_pos[dep].size()/2+wid];
                Fl_Button* but2 = new Fl_Button(x2, 100*(dep+1), width_of_node2*0.7, 50, name2);
                tree2_x[shared_id]=x2+width_of_node2*0.35;
                tree2_y[shared_id]=100*(dep+1);
                but2->color(FL_DARK_GREEN);
                but2->box(FL_OFLAT_BOX);
            }
        }
    }
    // draw lines
    for(int i=1;i<tree1_x.size();++i){
        int parent=t1.sharedid2parent(i);
        myline* line1 = new myline(tree1_x[i],tree1_y[i],tree1_x[parent],tree1_y[parent]+50);
    }
    for(int i=1;i<tree2_x.size();++i){
        int parent=t2.sharedid2parent(i);
        myline* line2 = new myline(tree2_x[i],tree2_y[i],tree2_x[parent],tree2_y[parent]+50);
    }

    win->end();
    win->show();
    return Fl::run();
}