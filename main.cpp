#include <iostream>
#include "mx_quadtree.h"
using namespace std;

int main()
{
    int W = 8;
    MX_QuadTree<string> tree(8);
    tree.insert(4,6,"Toronto");
    // tree.graphic("punto1.dot");
    tree.insert(6,5,"Buffalo");
    // tree.graphic("punto2.dot");
    tree.insert(0,3,"Denver");
    // tree.graphic("punto3.dot");
    tree.insert(2,3,"Chicago");
    // tree.graphic("punto4.dot");
    tree.insert(2,2,"Omaha");
    // tree.graphic("punto5.dot");
    tree.insert(4,0,"Mobile");
    // tree.graphic("punto6.dot");
    tree.insert(6,1,"Atlanta");
    // tree.graphic("punto7.dot");
    tree.insert(7,0,"Miami");
    // tree.graphic("punto8.dot");
    if(tree.search(8,8, "Miami"))   
    {    
        cout << "Encontrado.\n";
    }
    else
        cout << "No encontrado.\n";
    tree.postOrden();
    cout<<tree.size()<<'\n';
    tree.graphic("mx_quadtree1.dot");
    tree.insert(0,3,"PERU");
    tree.postOrden();
    tree.graphic("mx_quadtree2.dot");
}