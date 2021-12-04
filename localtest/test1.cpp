//
// Created by Okami on 2021/12/4.
//

#include "BPlusTree.h"

using namespace std;

int main() {
    BPlusTree system("data.dat");
    system.Initialize();
    system.Insert("05", 1);
    system.Output();
    system.Insert("08", 2);
    system.Output();
    system.Insert("10", 3);
    system.Output();
    system.Insert("15", 4);
    system.Output();
    system.Insert("16", 5);
    system.Output();
    system.Insert("17", 6);
    system.Output();
    system.Insert("18", 7);
    system.Output();
    system.Insert("19", 8);
    system.Output();
    system.Insert("20", 9);
    system.Output();
    system.Insert("21", 10);
    system.Output();
    system.Insert("22", 11);
    system.Output();
    system.Insert("06", 12);
    system.Output();
    system.Insert("09", 13);
    system.Output();
    system.Insert("07", 14);
    system.Output();
    system.Insert("23", 9);
    system.Output();
    system.Insert("24", 9);
    system.Output();
    system.Insert("25", 9);
    system.Output();
    system.Insert("26", 9);
    system.Output();
    system.Insert("27", 9);
    system.Output();
    system.Insert("28", 9);
    system.Output();
}