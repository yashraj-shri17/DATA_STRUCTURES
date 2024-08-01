class RandomizedSet {
public:
    unordered_set<int>st;
    RandomizedSet() {
        st = {};
    }
    
    bool insert(int val) {
        if(st.find(val) != st.end())
            return 0;
        st.insert(val);
        return 1;
    }
    
    bool remove(int val) {
        auto it = st.find(val);
        if(it != st.end())
        {
            st.erase(it);
            return 1;
        }
        return 0;
    }
    
    int getRandom() {
        int n = rand();
        return *next(st.begin(),n%st.size());
    }
};