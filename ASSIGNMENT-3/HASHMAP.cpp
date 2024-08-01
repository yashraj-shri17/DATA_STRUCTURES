#include <iostream>
#include <vector>
#include <string>

using namespace std;

class LinearProbingHashMap {
private:
    vector<string> keys;
    vector<string> values;
    int capacity;
    int size;

    int hash(const string& key) {
        size_t hashValue = 0;
        for (char c : key) {
            hashValue = hashValue * 31 + c;
        }
        return hashValue % capacity;
    }

    void resize() {
        vector<string> oldKeys = keys;
        vector<string> oldValues = values;
        capacity *= 2;
        keys = vector<string>(capacity, "");
        values = vector<string>(capacity, "");
        size = 0;
        for (size_t i = 0; i < oldKeys.size(); ++i) {
            if (!oldKeys[i].empty()) {
                insert(oldKeys[i], oldValues[i]);
            }
        }
    }

    void rehash(int start_index) {
        int index = (start_index + 1) % capacity;
        while (!keys[index].empty()) {
            string keyToRehash = keys[index];
            string valueToRehash = values[index];
            keys[index] = "";
            values[index] = "";
            size--;
            insert(keyToRehash, valueToRehash);
            index = (index + 1) % capacity;
        }
    }

public:
    LinearProbingHashMap(int initial_capacity = 8) : capacity(initial_capacity), size(0) {
        keys.resize(capacity);
        values.resize(capacity);
    }

    void insert(const string& key, const string& value) {
        if (size * 1.0 / capacity >= 0.7) {
            resize();
        }
        int index = hash(key);
        while (!keys[index].empty()) {
            if (keys[index] == key) {
                values[index] = value;
                return;
            }
            index = (index + 1) % capacity;
        }
        keys[index] = key;
        values[index] = value;
        size++;
    }

    bool find(const string& key) {
        int index = hash(key);
        while (!keys[index].empty()) {
            if (keys[index] == key) {
                return true;
            }
            index = (index + 1) % capacity;
        }
        return false;
    }

    void remove(const string& key) {
        int index = hash(key);
        while (!keys[index].empty()) {
            if (keys[index] == key) {
                keys[index] = "";
                values[index] = "";
                size--;
                rehash(index);
                return;
            }
            index = (index + 1) % capacity;
        }
    }
};

class Node {
public:
    string key;
    string value;
    Node* next;
    Node(const string& _key, const string& _value) : key(_key), value(_value), next(nullptr) {}
};

class SeparateChainingHashMap {
private:
    vector<Node*> buckets;
    int capacity;

    int hash(const string& key) {
        size_t hashValue = 0;
        for (char c : key) {
            hashValue = hashValue * 31 + c;
        }
        return hashValue % capacity;
    }

public:
    SeparateChainingHashMap(int initial_capacity = 8) : capacity(initial_capacity) {
        buckets.resize(capacity, nullptr);
    }

    void insert(const string& key, const string& value) {
        int index = hash(key);
        Node* head = buckets[index];
        while (head != nullptr) {
            if (head->key == key) {
                head->value = value;
                return;
            }
            head = head->next;
        }
        Node* newNode = new Node(key, value);
        newNode->next = buckets[index];
        buckets[index] = newNode;
    }

    bool find(const string& key) {
        int index = hash(key);
        Node* head = buckets[index];
        while (head != nullptr) {
            if (head->key == key) {
                return true;
            }
            head = head->next;
        }
        return false;
    }

    void remove(const string& key) {
        int index = hash(key);
        Node* head = buckets[index];
        Node* prev = nullptr;
        while (head != nullptr) {
            if (head->key == key) {
                if (prev != nullptr) {
                    prev->next = head->next;
                } else {
                    buckets[index] = head->next;
                }
                delete head;
                return;
            }
            prev = head;
            head = head->next;
        }
    }
};

int main() {
    // Linear Probing Hash Map
    LinearProbingHashMap lp_hash_map;
    lp_hash_map.insert("key1", "value1");
    lp_hash_map.insert("key2", "value2");
    cout << lp_hash_map.find("key1") << endl; // returns 1 (true)
    cout << lp_hash_map.find("key3") << endl; // returns 0 (false)
    lp_hash_map.remove("key1");
    cout << lp_hash_map.find("key1") << endl; // returns 0 (false)

    // Separate Chaining Hash Map
    SeparateChainingHashMap sc_hash_map;
    sc_hash_map.insert("key1", "value1");
    sc_hash_map.insert("key2", "value2");
    cout << sc_hash_map.find("key1") << endl; // returns 1 (true)
    cout << sc_hash_map.find("key3") << endl; // returns 0 (false)
    sc_hash_map.remove("key1");
    cout << sc_hash_map.find("key1") << endl; // returns 0 (false)

    return 0;
}
