//
// Created by Okami on 2021/12/4.
//

#include "BPlusTree.h"

using namespace std;

int n;
vector<int> ans;



int main() {
    BPlusTree system("data.dat");
//    system.Initialize();
    string opt, index;
    int value;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> opt >> index;
        if (opt == "insert") {
            cin >> value;
            system.Insert(index.c_str(), value);
        }
        else if (opt == "find") {
            ans.clear();
            system.Find(index.c_str(), ans);
            if (!ans.size()) {
                puts("null");
                continue;
            }
            for (int i = 0; i < ans.size(); ++i)
                cout << ans[i] << " ";
            cout << endl;
        }
        else {
            cin >> value;
            system.Delete(index.c_str(), value);
        }
//        system.Output();
    }
}