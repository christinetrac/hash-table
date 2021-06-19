#include <iostream>
#include <string>
#include <vector>
using namespace std;

class LinkedList {
public:
    long long key; //the phone number of the caller, used in hashFunction
    string value; //the name of the caller
    LinkedList *next;

    LinkedList(long long key, string value) {
        this->key = key;
        this->value = value;
        this->next = nullptr;
    }
};

class HashTable {
public:
    int bucket = 0;
    vector<LinkedList*> table;

    HashTable();
    void resize(int m);
    void insert(long long k, string caller);
    void search(long long k);
    void remove(long long k);
    void print(int i);

    long hashFunction(long long k){
        return (k % bucket);
    }
};

HashTable::HashTable(){
}

void HashTable::resize(int m){
    bucket = m;
    table.resize(m, nullptr);
    for(int i = 0; i<bucket; i++){
        delete table[i];
        table[i] = nullptr; 
    }
    cout << "success" << endl;
}

void HashTable::insert(long long k, string caller) {
    long long index = hashFunction(k); //long long
    bool failure = false;
    if(table[index] == nullptr){
        table[index] = new LinkedList(k, caller); //the entry is empty
        cout << "success" << endl; //new entry is added
    } else {
        LinkedList *entry = table[index]; //a linked list at the entry already exists
        LinkedList *previous = nullptr;
        LinkedList *temp = new LinkedList(k, caller);
        while((entry != nullptr) && (entry->key <= k)){
            if(entry->key == k){
                cout << "failure" << endl; //key already exists
                failure = true;
            }
            previous = entry;
            entry = entry->next;
        }
        if(!failure){
            if(previous != nullptr){
                previous->next = temp; //new entry is added, not at beginning of list
            } else {
                table[index] = temp; //new entry is at the beginning of the list
            }
            temp->next = entry;
            cout << "success" << endl;
        }
    }
}

void HashTable::search(long long k) {
    long long index = hashFunction(k);
    bool success = false;
    if(table[index] == nullptr){
        cout << "not found" << endl; //not found because no entries
    } else {
        LinkedList *entry = table[index];
        while(entry != nullptr){
            if(entry->key == k){
                cout << "found " << entry->value << " in " << index << endl; //the match is found
                success = true;
            }
            entry = entry->next;
        }
        if(!success){
            cout << "not found" << endl; //a matching key was never found
        }
    }
}

void HashTable::remove(long long k) {
    long long index = hashFunction(k);
    if(table[index] == nullptr){
        cout << "failure" << endl; //cant delete because no entries
    } else {
        LinkedList *entry = table[index];
        LinkedList *previous = nullptr;
        while(entry->next != nullptr && entry->key != k) {
            previous = entry;
            entry = entry->next;
        }
        if(entry->key == k){
            LinkedList *next = entry->next;
            delete entry;
            if(previous == nullptr){
                table[index] = next;
            } else {
                previous->next = next;
            }
            cout << "success" << endl; //the key is found and deleted
        } else {
            cout << "failure" << endl; //key is not found, cannot be deleted
        }
    }
}

void HashTable::print(int i) {
    if(table[i] != nullptr){
        LinkedList *entry = table[i];
        while(entry != nullptr){
            cout << entry->key << " ";
            entry = entry->next;
        }
        cout << endl;
    }
}

int main() {
    string input;
    HashTable test;
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
        } else if(input.substr(0, 1) == "p"){
            int i = stoi(input.substr(2));
            test.print(i);
        }
    }
    return 0;
}
