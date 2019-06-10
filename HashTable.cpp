#include<assert.h>
#include<iostream>
#include<vector>
#include<string>

using std::vector;
using std::string;
using std::cin;
using std::cout;
const int DefaultHashTableSize = 8;
const int GrowFactor = 2;
const double MaxKeysCount = 3.0/4.0;
const int NotInTable = -1;

unsigned long Hash( const string& key, unsigned long tableSize) {
    unsigned long hash = 0;
    unsigned long size = key.size();
    for(int i = 0; i < size; i++) {
        hash = (hash * 127 + key[i]) % tableSize;
    }
    return hash;
}

template<class T>
class HashTable {
public:
    HashTable();
    ~HashTable();
    bool Has( const T& key ) const;
    bool Add( const T& key );
    bool Delete( const T& key );
private:
    vector<T> data;
    vector<bool> flag;
    vector<bool> had;
    int keysCount;
    void growTable();
};

template<class T>
HashTable<T>::HashTable() : keysCount(0) { data.resize(DefaultHashTableSize); flag.assign(DefaultHashTableSize, false); had.assign(DefaultHashTableSize, false);}

template<class T>
HashTable<T>::~HashTable(){
    data.clear();
    flag.clear();
    had.clear();
}

template<class T>
bool HashTable<T>::Has( const T& key ) const {
    unsigned long hash = Hash(key, data.size()-1);
    for (int iterator = 0; iterator < data.size(); iterator++) {
        if (!had[hash])
            break;
        else if (data[hash] == key && flag[hash])
            return true;
        hash = (hash +  iterator/2 + iterator * iterator/2) % (data.size());
    }
    return false;
}

template<class T>
bool HashTable<T>::Add( const T& key ) {
    unsigned long hash;
    hash = Hash(key, data.size()-1);
    int safeIndex = NotInTable;
    bool FirstDelete = false;
    unsigned long newIndex = NotInTable;
    if(keysCount + 1 >  data.size() * MaxKeysCount)
        growTable();
    for (int iteration = 0; iteration < data.size(); iteration++) {
        if (!had[hash]){
            newIndex = hash;
            break;
        } else if(!flag[hash]) {
            if (FirstDelete != true){
                FirstDelete = true;
                safeIndex = hash;
            }
        } else if (data[hash] == key && flag[hash]) {
            return false;
        }
        hash = (hash +  iteration/2 + iteration * iteration/2) % (data.size());
    }
    if (newIndex == NotInTable){
        if (safeIndex != NotInTable){
            newIndex = safeIndex;
        }
    }
    data[newIndex] = key;
    flag[newIndex] = true;
    had[newIndex] = true;
    keysCount++;
    return true;
}

template<class T>
void HashTable<T>::growTable() {
    vector<T> oldTable = data;
    vector<bool> oldFlag = flag;
    vector<bool> oldHad = had;
    data.resize(data.size() * GrowFactor);
    had.assign(had.size()* GrowFactor, false);
    flag.assign(flag.size() * GrowFactor, false);
    keysCount = 0;
    for (size_t i = 0; i < oldTable.size(); ++i) {
        if (oldHad[i]  && oldFlag[i]) {
            Add(oldTable[i]);
            keysCount++;
        }
    }
    oldTable.clear();
    oldFlag.clear();
    oldHad.clear();
}

template<class T>
bool HashTable<T>::Delete( const T& key ) {
    unsigned long hash;
    hash = Hash(key, data.size()-1);
    for (int iteration = 0; iteration < data.size(); iteration++) {
        if (!had[hash]) {
            break;
        }else if (data[hash] == key && flag[hash]) {
            flag[hash] = false;
            keysCount--;
            return true;
        }
        hash = (hash +  iteration/2 + iteration * iteration/2) % (data.size());
    }
    return false;
}

int main() {
    HashTable<string> table;
    char command = 0;
    string key;
    while( cin >> command >> key ) {
        switch( command ) {
            case '+':
                cout << (table.Add( key ) ? "OK" : "FAIL") << "\n";
                break;
            case '-':
                cout << (table.Delete( key ) ? "OK" : "FAIL") << "\n";
                break;
            case '?':
                cout << (table.Has( key ) ? "OK" : "FAIL") << "\n";
                break;
            default:
                return 0;
        }
    }
    return 0;
}
