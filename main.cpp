#include <bits/stdc++.h>
#include "mx_quadtree.h"
#define coord pair<int,int>
using namespace std;

int main()
{
    int W = 160;
    srand(time(NULL));
    MX_QuadTree<string> tree(8);
    unordered_map<string, coord> locs;
    vector<string> cities = {"Toronto","Buffalo","Denver","Chicago","Omaha","Mobile","Atlanta", "Miami"};
    for(int i = 0; i < 8; ++i){
        int x = 1 + rand() % 8;
        int y = 1 + rand() % 8;
        tree.insert(x,y,cities[i]);
        locs[cities[i]] = {x,y};
    }

    int asserts = 0;
    for(auto aux : locs){
        int val = tree.search(aux.second.first , aux.second.second , aux.first);
        if(val)
            printf("%s se encuentra en el arbol, x = %d , y = %d\n", aux.first, aux.second.first, aux.second.second);
        else
            printf("%s no se encuentra en el arbol, x = %d , y = %d\n", aux.first, aux.second.first, aux.second.second);
        asserts += val;
    }
    printf("Numero de coincidencias: %d.\n", asserts);
    printf("Tamanio del arbol: %d.\n" , tree.size());
    tree.graphic("mx_quadtree1.dot");
    tree.insert(0,3,"PERU");
    tree.erase(locs["Atlanta"].first , locs["Atlanta"].second);
    tree.erase(locs["Buffalo"].first , locs["Buffalo"].second);
    tree.graphic("mx_quadtree2.dot");
}