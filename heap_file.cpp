#include <bits/stdc++.h>
using namespace std;
class page{
    public:
    //mentioned in specification
    int num_records,freespaceaddr;
    page *prevpage, *nextpage;
    //Mine
    int page_id,emptyspace;
    vector<int> records;
    vector<int> directory;
    page(int pgid,page *prev,int pagesize){
        page_id=pgid;
        prevpage=prev;
        num_records=0;
        freespaceaddr=0;
        nextpage=NULL;
        emptyspace=pagesize-16;
    }
    bool insertintopg(int rec_size,int n);
    int searchinpage(int n);
};
class heap_file{
    int pagesize;
    page* head;
    public:
    heap_file(int pgsize){
        pagesize=pgsize;
        head=NULL;
        numpages=0;
    }
    int numpages;
    bool insert(int rec_size,int n);
    bool search(int n);
    void display();

};
void heap_file::display(){
    cout<<numpages<<" ";
    page* currpg=head;
    while(currpg!=NULL){
        cout<<(currpg->num_records)<<" ";
        currpg=currpg->nextpage;
    }
    cout<<endl;
}
bool heap_file::search(int n){
    page* currpg=head;
    while(currpg!=NULL){
        int slot=currpg->searchinpage(n);
        if(slot!=-1){
            cout<<currpg->page_id<<" "<<slot<<endl;
            return true;
        }
        currpg=currpg->nextpage;
    }
    cout<<-1<<" "<<-1<<endl;
    return false;
}
bool heap_file::insert(int rec_size,int n){
    page* currpg=head,*lastpg=NULL;
    while(currpg!=NULL){
        lastpg=currpg;
        if((currpg->emptyspace)>=(rec_size+4)){
            return currpg->insertintopg(rec_size,n);
        }
        currpg=currpg->nextpage;
    }
    // if all pages cannot accomodate this entry
    //if this is first page
    if(head==NULL){
        page* newpage=new page(0,NULL,pagesize);
        numpages++;
        head=newpage;
        return newpage->insertintopg(rec_size,n);
    }
    else{
        page * newpage=new page((lastpg->page_id)+1,lastpg,pagesize);
        lastpg->nextpage=newpage;
        numpages++;
        return newpage->insertintopg(rec_size,n);
    }
}
bool page::insertintopg(int rec_size,int n){
    if(emptyspace<(rec_size+4)){
        return false;
    }
    records.push_back(n);
    directory.push_back(rec_size);
    num_records++;
    freespaceaddr+=rec_size;
    emptyspace-=(rec_size+4);
    return true;
}
int page::searchinpage(int n){
    for(int i=0;i<num_records;i++){
        if(records[i]==n){
            return i;
        }
    }
    return -1;
}
int main(){
    int pgsize;
    cin>>pgsize;
    heap_file h(pgsize);
    int t;
    cin>>t;
    while(t!=4){
        switch(t){
            case 1:{
                int recsize,primary_key;
                cin>>recsize>>primary_key;
                h.insert(recsize,primary_key);
                break;
            }
            case 2:{
                h.display();
                break;
            }
            case 3:{
                int searchval;
                cin>>searchval;
                h.search(searchval);
            }
        }
        cin>>t;
    }
}