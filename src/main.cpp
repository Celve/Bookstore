//
// Created by Okami on 2021/12/4.
//

#include "BPlusTree.h"
#include "Book.h"

using namespace std;

int n;
vector<int> ans;

char opt[65], ptr[65];

int main() {
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