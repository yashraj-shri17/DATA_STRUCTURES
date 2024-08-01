class MyLinkedList {
public:
   vector<int>ans;
    MyLinkedList() {
    }
    int get(int index) {
      for(int i=0;i<ans.size();i++){
          if(i==index)
           return ans[i];
      }   
        return -1;
    }
    void addAtHead(int val) {
    ans.insert(ans.begin(),val);
    }
    void addAtTail(int val) {
      ans.push_back(val);   
    }
    void addAtIndex(int index, int val) {
       if(index < ans.size())
        ans.insert(ans.begin()+index,val);
         else if(index==ans.size())
          ans.push_back(val);
    }
    void deleteAtIndex(int index) {
       if(index < ans.size())
       ans.erase(ans.begin()+index); 
    }
};