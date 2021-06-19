#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Data {
public:
    long long key; //the phone number of the caller, used in hashFunction
    string value; //the name of the caller

    Data(long long key, string value) {
        this->key = key;
        this->value = value;
    }
};

class DoubleHash{
public:
    int bucket = 0;
    int size = 0; //current number of items in hash table
    vector<Data*> table;

    DoubleHash();
    void resize(int m);
    void insert(long long k, string caller);
    void search(long long k);
    void remove(long long k);

    long long hashFunction1(long long k){
        return (k % bucket);
    }

    long long hashFunction2(long long k) {
        long long result = (k / bucket) % bucket;
        if (result % 2 == 0) {
            result += 1;
        }
        return (result);
    }
};

DoubleHash::DoubleHash(){
}

void DoubleHash::resize(int m) {
    bucket = m;
    size = 0;
    table.resize(m, nullptr);
    for(int i = 0; i<bucket; i++){
        delete table[i];
        table[i] = nullptr;
    }
    cout << "success" << endl;
}

void DoubleHash::insert(long long k, string caller) {
    bool success = true;
    long long index = hashFunction1(k);
    long long offset = hashFunction2(k); //if a collision happens, hash function 2 must be used
    if(size >= bucket){
        cout << "failure" << endl; //hash table is full
        return;
    }
    if(table[index] == nullptr){
        table[index] = new Data(k, caller); //entry is empty so a data item can be added
        size++;
        cout << "success" << endl; //new entry is added
    } else { //collision occurs
        while(table[index] != nullptr) {
            if(table[index]->key == k){
                cout << "failure" << endl; //key already exists
                success = false;
            }
            index = (index + offset) % bucket;
        }
        if(success){
            table[index] = new Data(k, caller);
            size++;
            cout << "success" << endl; //new entry is added
        }
    }
}

void DoubleHash::search(long long k) {
    long long index = hashFunction1(k);
    long long offset = hashFunction2(k);
    for(int i = 0; i<=size; i++) {
        if(table[index] != nullptr){
            if(table[index]->key == k){
                cout << "found " << table[index]->value << " in " << index << endl; //the match is found
                return;
            }
        }
        index = (index + offset) % bucket;
    }
    cout << "not found" << endl; //a matching key was never found
}

void DoubleHash::remove(long long k) {
    long long index = hashFunction1(k);
    long long offset = hashFunction2(k);
    for(int i = 0; i<=size; i++){
        if(table[index] != nullptr){
            if(table[index]->key == k){
                delete table[index];
                table[index] = nullptr;
                size--;
                cout << "success" << endl; //the key is found and deleted
                return;
            }
        }
        index = (index + offset) % bucket;
    }
    cout << "failure" << endl; //a matching key was never found
}

int main() {
    string input;
    DoubleHash test;
    while(getline(cin, input)){
        if(input.substr(0, 1) == "n"){
            int m = stoi(input.substr(2));
            test.resize(m);
        }
        if(input.substr(0, 1) == "i"){
            long long k = stoll(input.substr(2, 10));
            string caller = input.substr(13);
            test.insert(k, caller);
        } else if(input.substr(0, 1) == "s"){
            long long k = stoll(input.substr(2, 10));
            test.search(k);
        } else if(input.substr(0, 1) == "d"){
            long long k = stoll(input.substr(2, 10));
            test.remove(k);
        }
    }
    return 0;
}
