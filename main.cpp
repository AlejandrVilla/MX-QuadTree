#include <iostream>
#include "mx_quadtree.h"
using namespace std;

int main()
{
    int W = 8;
    MX_QuadTree<string> tree(8);
    tree.insert(4,6,"Toronto");
    tree.insert(6,5,"Buffalo");
    tree.insert(0,3,"Denver");
    tree.insert(2,3,"Chicago");
    tree.insert(2,2,"Omaha");
    tree.insert(4,0,"Mobile");
    tree.insert(6,1,"Atlanta");
    tree.insert(7,0,"Miami");
    tree.postOrden();
    cout<<tree.size()<<'\n';
    tree.graphic("mx_quadtree.dot");
    // cout<<"termino\n";
}