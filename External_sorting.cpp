#include <bits/stdc++.h>
using namespace std;

typedef long double LD;
typedef long long ll;
#define inf std::numeric_limits<int>::max()
#define pb push_back
#define REP(i,n) for (int i = 0; i < n; i++)
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define REPD(i,n) for (int i = n-1; i >= 0; i--)
#define FORD(i,a,b) for (int i = a; i >= b; i--)
#define vi vector<int>
#define vii iterator::vector<int>
#define FAST_IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define print(v) REP(i,v.size()) cout<<v[i]<<" ";cout<<endl;
/*
void merge(int* v, int s,int m, int e){
    int tmp[e+1-s];
    int i=0;
    int l=s;
    int r=m+1;
    while(l<=m && r<=e){
        cout<<"{"<<l<<","<<r<<"} : ";
        if(v[l]<=v[r]){tmp[i]=v[l];l++;}
        else {tmp[i]=v[r];r++;}
        i++;
    }
    if(i<e+1-s){
        if(l<=m){
            while(i<e+1-s){cout<<"{"<<l<<","<<r<<"} : ";tmp[i]=v[l];i++;l++;}
        }if(r<=e){
            while(i<e+1-s){cout<<"{"<<l<<","<<r<<"} : ";tmp[i]=v[r];i++;r++;}
        }
    }cout<<"\nMerged tmp : ";
    REP(j,e-s+1){
        cout<<tmp[j]<<" ";
    }cout<<endl;
    int j=0;
    for(int k=s;k<=e;k++){
        v[k]=tmp[j];j++;
    }
   //REP(i,v.size()) cout<<v[i]<<" ";cout<<endl;
}
*/
void k_merge(int* arr, int s, int* mid, int e, int k){
    int n=e+1-s;
    if(n<=0)return;
    int tmp[n];
    int ptr[k]; ptr[0]=s;
    for(int j=1;j<k;j++){ptr[j]=mid[j-1]+1;}
    //for(int j=0;j<k;j++)cout<<ptr[j]<<" ";cout<<e<<" "<<endl;
    //FOR(i,s,e+1)cout<<arr[i]<<" ";cout<<endl;
    
    int i=0;
    while(i<n){
        int min=inf;
        int x=-1;
        //for(int j=0;j<k;j++)cout<<ptr[j]<<" ";cout<<e<<" "<<":: ";
        for(int j=0;j<k-1;j++){
            if(ptr[j]<=mid[j]){
                if(arr[ptr[j]]<min){ x=j; min=arr[ptr[j]]; }
            }
        }
        if(ptr[k-1]<=e){if(arr[ptr[k-1]]<min){ x=k-1; min=arr[ptr[k-1]]; }}
        //cout<<"min["<<x<<"]:"<<min<<endl;
        ptr[x]++;tmp[i]=min;
        i++;
    }
    int j=0;
    for(int k=s;k<=e;k++){
        arr[k]=tmp[j];j++;
    }
}

int n_buffer;
//int** buffer;
int size;
int* records;

void k_merge_sort(int* arr, int start, int end, int k){
    
    int n=end-start+1;
    if(n<=size)return;
    int n_pg=n/size+(n%size==0?0:1);
    //cout<<"n_pg: "<<n_pg<<" "<<start<<" "<<end<<" "<<n<<endl;
    if(n_pg<=k){
        //cout<<"k:"<<k<<" n_pg:"<<n_pg<<endl;
        int k2=n_pg;int m[k2-1];FOR(i,1,k2)m[i-1]=start+i*size-1;
        k_merge(arr,start, m, end, k2);
        //cout<<"After merge2: ";REP(i,n) cout<<records[start+i]<<" ";cout<<endl;
        return;
    }
    int x=n_pg/k+(n_pg%k==0?0:1);//cout<<"x:"<<x<<endl;
    //cout<<x*k<<" _ "<<n_pg<<endl;
    /*if(x*k>n_pg){k=n_pg/x+(n_pg%x==0?0:1);}*/
    int m[k-1];
    int y=start;
    FOR(i,1,k){
        if(n_pg%k!=0 && i-1==n_pg%k){x--;}
        y+=x*size;
        m[i-1]=y-1;
    }
    //REP(i,k-1){cout<<m[i]<<" "; }cout<<endl;
    k_merge_sort(arr, start, m[0], k);
    REP(i,k-2) k_merge_sort(arr, m[i]+1, m[i+1], k );
    k_merge_sort(arr, m[k-2]+1, end, k);
    /*int z=0;
    cout<<"before merge: \n";REP(i,n){if(i==m[z]+1){cout<<endl;z++;} cout<<records[start+i]<<" ";}cout<<endl;
    */
    k_merge(arr, start, m, end, k);
    /*z=0;
    cout<<"After merge: \n"; REP(i,n){if(i==m[z]+1){cout<<endl;z++;} cout<<records[start+i]<<" ";}cout<<endl;
    */
}
void k_merge_sort_ittr(int* arr, int start, int end, int k){
    int n=end-start+1;
    n/=size;cout<<n<<endl;
    if(n==0)return;;
    int x=n/k+(n%k==0?0:1);
    int m[k-1];
    FOR(i,1,k){m[i-1]=start+x*i*size;}
    REP(i,k-1) cout<<m[i]<<" ";cout<<endl;
    k_merge_sort(arr, start, m[0], k);
    REP(i,k-2) k_merge_sort(arr, m[i], m[i+1], k );
    k_merge_sort(arr, m[k-2], end, k);
    k_merge(arr,start, m, end, k);
}


signed main(){
    FAST_IO
    cin>>n_buffer>>size;
    int n;cin>>n;

    int n_pg=n/size+(n%size==0?0:1);
    records=(int*)malloc(n*sizeof(int));
    
    REP(i,n){
        cin>>records[i];
    }

    //pass 0 :: n/n_buff runs
    int j=0;
    for(;j<n-size;j+=size){
        sort(records+j,records+j+size);
    }
    sort(records+j,records+n);

    //REP(i,n) cout<<records[i]<<" ";cout<<endl;

    //pass >0 :: runs /= B-1;
    int k=n_buffer-1;   //1 page for output...
    //cout<<k<<endl;
    k_merge_sort(records,0,n-1,k);

    REP(i,n) cout<<records[i]<<endl;
    
}
