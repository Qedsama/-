#include<cstdio>
#include<vector>
#include<string>
#include<algorithm>
#include<stack>
#include<cstdlib>
#include<iostream>
using namespace std;
struct pt{
    int id;
    int in=0;
    int out=0;
    vector<int> edge;
    vector<int> length;
    vector<int> edge1;
    vector<int> length1;   
}ptg[102],ptg1[102];
int inde[102],pai[102],t[102],pai1[102];
vector<string>path[102];
bool operator<(pt a,pt b){
    if(inde[a.id]<inde[b.id])return 1;
    else return 0;
}
string tostring(int r){
    string a,b,c;
    c=to_string(r%10);
    b=to_string(r/10%10);
    a=to_string(r/100%10);
    return a+b+c;
}
int main(){
    int n;scanf("%d",&n);
    for(int i=0;i<n;i++){    //建立pt图
        int iid,fr;scanf("%d%d",&iid,&t[i]);
        ptg[iid].id=iid;ptg1[iid].id=iid;
        bool flag;char c=getchar();
        while(c!='\n'){
            int x=0,y=0;
            while(isdigit(c=getchar())){x=x*10+c-48;y=1;}
            if(!y)break;
            fr=x;
            ptg[fr].out++;
            ptg[iid].in++;
            ptg[iid].edge.push_back(fr);
            ptg[fr].edge1.push_back(iid);
            ptg1[fr].out++;
            ptg1[iid].in++;
            ptg1[iid].edge.push_back(fr);
            ptg1[fr].edge1.push_back(iid);
        };
    }
    for(int i=0;i<n;i++){
        int lv=ptg[i].edge.size();
        for(int j=0;j<lv;j++){
            int r=ptg[i].edge[j];
            ptg[i].length.push_back(t[r]);
            ptg1[i].length.push_back(t[r]);
            ptg[r].length1.push_back(t[r]);
            ptg1[r].length1.push_back(t[r]);
        }
    }
    ptg[n].id=n;
    for(int i=0;i<n;i++){
        if(!ptg[i].out){
            ptg[n].in++;
            ptg[n].edge.push_back(i);
            ptg[n].length.push_back(t[i]);
            ptg[i].edge1.push_back(n);
            ptg[i].length1.push_back(t[i]);
            ptg[i].out++;
            ptg1[n].in++;
            ptg1[n].edge.push_back(i);
            ptg1[n].length.push_back(t[i]);
            ptg1[i].out++;
        }
    }
    int h=0;
    while(h<n+1){
        for(int i=0;i<n+1;i++){
            if(!ptg1[i].in){
                inde[i]=h++;
                ptg1[i].in=-1;
                for(int j=0;j<n+1;j++){
                    vector<int>::iterator Iter;
                    for(Iter=ptg1[j].edge.begin();Iter!=ptg1[j].edge.end();Iter++){
                        if (*Iter==i){
                            ptg1[j].edge.erase(Iter);
                            ptg1[j].in--;
                            break;
                        }
                    }
                }
            }
        }
    }
    sort(ptg,ptg+n+1);
    for(int i=0;i<n+1;i++){
        if(!ptg[i].in){pai[i]=0;path[i].push_back(tostring(ptg[i].id));continue;}
        int next=0;
        for(int j=0;j<ptg[i].in;j++){
            int ago=ptg[i].edge[j],agol=ptg[i].length[j],agoi=0;
            for(int r=0;r<i;r++){
                if(ptg[r].id==ago){
                    agoi=r;break;
                }
            }
            int now=pai[agoi]+agol;
            if(now==pai[i]){
                int r=path[agoi].size();
                for(int q=0;q<r;q++){
                    path[i].push_back(path[agoi][q]+tostring(ptg[i].id));
                }
            }
            if(now>pai[i]){
                path[i].clear();
                pai[i]=now;
                int r=path[agoi].size();
                for(int q=0;q<r;q++){
                    path[i].push_back(path[agoi][q]+tostring(ptg[i].id));
                }
            }
        }
    }
    for(int i=n;i>=0;i--){
        if(!ptg[i].out){pai1[i]=0;continue;}
        int next=0;
        for(int j=0;j<ptg[i].out;j++){
            int ago=ptg[i].edge1[j],agol=ptg[i].length1[j],agoi=0;
            for(int r=n;r>i;r--){
                if(ptg[r].id==ago){
                    agoi=r;break;
                }
            }
            int now=pai1[agoi]+agol;
            if(now>pai1[i])pai1[i]=now;
        }
    }
    printf("%d\n",pai[n]);
    int lp=path[n].size();
    for(int i=0;i<lp;i++){
        printf("[");
        string x=path[n][i];
        int lx=x.length(),l0=-1;
        while(l0<lx-4){
            if(x[l0+1]=='0'){
                if(x[l0+2]=='0')printf("%c->",x[l0+3]);
                else printf("%c%c->",x[l0+2],x[l0+3]);
            }
            else printf("%c%c%c->",x[l0+1],x[l0+2],x[l0+3]);
            l0+=3;
        }
        printf("end]\n");
    }
    int h1=0;
    while(h1<n){
        for(int i=0;i<n;i++){
            if(ptg[i].id==h1){
                printf("%d\n",pai[n]-pai1[i]-pai[i]);
                h1++;
            }
        }
    }
}