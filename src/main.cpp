//
// Created by Okami on 2021/12/4.
//

#include "BPlusTree.h"

using namespace std;

int n;
vector<int> ans;

char opt[65], ptr[65];

int main() {
//    cin >> opt;
//    Node temp;
//    temp.Insert(opt, 1, 1);
//    temp.Insert(opt, 2, 2);
//    temp.Insert(opt, 3, 3);
//    cout << temp.Find(opt, 2) << endl;
//    cout << temp.Find(opt, 1) << endl;
//    cout << temp.Find(opt, 3) << endl;
    BPlusTree system("data.dat");
//    system.Initialize();
    int value;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%s %s", opt, ptr);
        if (opt[0] == 'i') {
            scanf("%d", &value);
            system.Insert(ptr, value);
        }
        else if (opt[0] == 'f') {
            ans.clear();
            system.Find(ptr, ans);
            if (!ans.size()) {
                puts("null");
                continue;
            }
            for (int i = 0; i < ans.size(); ++i)
                printf("%d ", ans[i]);
            puts("");
        }
        else {
            scanf("%d", &value);
            system.Delete(ptr, value);
        }
//        system.Output();
    }
}