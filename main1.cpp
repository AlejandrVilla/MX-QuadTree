#include <iostream>
#include "mx_quadtree.h"
using namespace std;

int main()
{
    int W = 160;
    MX_QuadTree<string> tree(W);
    tree.insert(55,32,"Toronto");
    tree.insert(138,15,"Buffalo");
    tree.insert(11,51,"Denver");
    tree.insert(19,102,"Chicago");
    tree.insert(69,85,"Omaha");
    tree.insert(96,141,"Mobile");
    tree.insert(112,85,"Atlanta");
    tree.insert(152,86,"Miami");
    if(tree.search(7,0, "Miami"))   
    {    
        cout << "Encontrado.\n";
    }
    else
        cout << "No encontrado.\n";
    cout<<tree.size()<<'\n';
    tree.graphic("mx_quadtree1.dot");
    //tree.insert(0,3,"PERU");
    //tree.graphic("mx_quadtree2.dot");
}