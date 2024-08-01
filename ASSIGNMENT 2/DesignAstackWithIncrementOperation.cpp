class CustomStack {
public:
    vector<int> st;
    int ms ;
    int curr;
    CustomStack(int maxSize) {
        ms = maxSize;
        st.resize(ms,-1);
        curr = 0;
    }
    
    void push(int x) {
        if(curr == ms){
            return;
        }

        st[curr] = x;
        // cout << curr << endl;
        curr++;
    }
    
    int pop() {
        if(curr == 0){
            return -1;
        }
        // cout << curr << endl;

        int k = st[curr-1];
        st[curr-1] = -1;
        curr--;
        return k;
    }
    
    void increment(int k, int val) {
        int n = min(curr,k);
        for(int i=0;i<n;i++){
            st[i] += val;
        }
        return;
    }
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */