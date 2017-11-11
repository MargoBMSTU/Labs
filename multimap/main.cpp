#include <iostream>
#include "multimap.hpp"
#include <string>
#include <fstream>

using namespace std;

template <class K, class V>
void mapping(Multimap<K,V>& result,const Multimap<K,V>& A, const Multimap<K,V>& B){
    result = (A+B) - (A*B);
}

int main(int argc, char **argv) {
    try {
        ifstream input(*++argv);
        Multimap<string, int> M1;
            if (input.is_open()) {
                while (!input.eof()) {
                    string key;
                    int data;
                    input >> key >> data;
                    if (!input.eof())
                        M1.add(key,data);
                }
            } else
                throw 1;
        ifstream input2(*++argv);
        Multimap<string, int> M2;
        if (input2.is_open()) {
            while (!input2.eof()) {
                string key;
                int data;
                input2 >> key >> data;
                if (!input2.eof())
                    M2.add(key,data);
            }
        } else
            throw 1;
        cout << M1 << endl;
        cout << M2 << endl;
        Multimap<string, int> result;
        mapping<string, int>(result, M1, M2);
        cout << result << endl;
    } catch (int a) {
        if (a == 1){
            cerr << "can't open file" << endl;
        }
    }
    return 0;
}
