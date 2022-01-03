#include <iostream>
//#include "Tree/Tree.hpp"
//#include "interface.h"
#include "HierManager/HierManager.hpp"
using namespace std;

void prinfFile(string path) {
    ifstream file;
    file.open(path);
    if(!file) return;
    string str;
    while (file) {
        getline(file, str);
        cout << str << endl;
    }
}


int main() {
    // node_t* node = new node_t("Uspeshnia");
    // Tree test(node);
    // test.print();
    // cout << endl;
    // node_t* add = test.findNode("Uspeshnia");
    // add->addChild("Gosho");
    // add->addChild("Misho");
    // add->addChild("Slavi");
    // test.print();
    // cout << endl;

    // add = test.findNode("Gosho");
    // // cout << add->getData();
    // add->addChild("Dancho");
    // add->addChild("Pesho");

    // add = test.findNode("Slavi");
    // add->addChild("Slav1");
    // add->addChild("Slav2");

    // //test.print();
    string str = "Uspeshnia-Gosho\nUspeshnia-Misho\nUspeshnia-Slavi\nGosho-Dancho\nGosho-Pesho\nSlavi-Slav1\nSlavi-Slav2\nDancho-Boris\nDancho-Kamen\nPesho-Alex\nSlav1-Mecho\nMecho-Q12Adl\n";
    // //string str = "Uspeshnia-Gosho\nUspeshnia-Misho\nUspeshnia-Slavi\n";
    Hierarchy test(str);
    // cout << test.print() << endl;
    string name = "idk";
    HierarchyExtended test_extended(test, name);
    cout << test_extended.print() << endl;
    HierManager hm;
    hm.add(test_extended);
    if(hm.getAtIndex(0)) cout << hm.getAtIndex(0)->print() << endl;
    hm.findHierarchy(name)->fire("Slavi");
    hm.save(name , "D:\\Other\\Projects\\Uni\\sdp\\sdp-21-22\\HW-2-Hierarchy\\Files\\bruh.txt");
    //hm.save("test", "D:\\Other\\Projects\\Uni\\sdp\\sdp-21-22\\HW-2-Hierarchy\\Files\\index.txt");
    hm.load("val", "D:\\Other\\Projects\\Uni\\sdp\\sdp-21-22\\HW-2-Hierarchy\\val.txt");
    prinfFile("D:\\Other\\Projects\\Uni\\sdp\\sdp-21-22\\HW-2-Hierarchy\\Files\\bruh.txt");
    cout << hm.findHierarchy("val")->print() << endl;
    //if(hm.getAtIndex(1)) cout << hm.getAtIndex(1)->print() << endl;
    // cout << test.stringifyBFS();
    // cout << test.getSize() << ' ' << test.getDepth() << endl;
    // cout << test.getSalary(BOSS_NAME) << endl;
    // cout << test.getOverloaded(20) << endl;
    // cout << endl;
    
    // test.removeNode("Q12Adl");
    // cout << test.stringifyBFS();
    // cout << test.getSize() << ' ' << test.getDepth() << endl;
    // cout << test.getSalary(BOSS_NAME) << endl;;
    // cout << test.getOverloaded(20) << endl;
    // cout << endl;
    
    // test.removeNode("Slavi");
    // cout << test.stringifyBFS();
    // cout << test.getSize() << ' ' << test.getDepth() << endl;
    // cout << test.getSalary(BOSS_NAME) << endl;
    // cout << test.getOverloaded(20) << endl;

    //test.print();

}