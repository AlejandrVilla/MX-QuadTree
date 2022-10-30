#ifndef MX_QUADTREE_H
#define MX_QUADTREE_H
#include <iostream>
#include <fstream>
#include "node.h"

template<typename T=int>
class MX_QuadTree
{
private:
    Node<T>* root;
    int _size;
    int W;
    void postOrden(Node<T>* N);

public:
    MX_QuadTree(int _W);
    ~MX_QuadTree();
    std::string MX_compare(int x, int y, int _W);
    void insert(int x, int y, T value);     // ya esta
    bool search(Node<T>* N);                // samuel
    void erase(T value);                    // julio
    void postOrden();

    void graphic(std::string dir);          // grafica

    int size(){return _size;}
};

template<typename T>
MX_QuadTree<T>::MX_QuadTree(int _W)
{
    W=_W;
    root = nullptr;
    _size = 0;
}

template<typename T>
MX_QuadTree<T>::~MX_QuadTree()
{
    root->automatate(root);
    std::cout<<"c murio\n";
}

template<typename T>
std::string MX_QuadTree<T>::MX_compare(int x, int y, int _W)
{
    if(x < _W)
    {
        if(y < _W) return "SW";
        else return "NW";
    }
    else if(y < _W) return "SE";
    return "NE";
}

template<typename T>
void MX_QuadTree<T>::insert(int x, int y, T value)
{
    if(W==1)
    {
        root = new Node<T>(value, "black", "root");
        _size++;
        return;
    }
    else if(!root)
        root = new Node<T>("gray", "root");
    Node<T>* tmp = root;
    int _W = W/2;
    std::string Q = MX_compare(x,y,_W);
    while(_W>1)
    {
        // std::cout<<value<<"-> "<<Q<<'\n';
        if(Q=="NW" && !tmp->NW)
        {
            tmp->NW = new Node<T>("gray", Q);
            tmp = tmp->NW;
        }
        else if(Q=="NW")
            tmp = tmp->NW;
        if(Q=="NE" && !tmp->NE)
        {
            tmp->NE = new Node<T>("gray", Q);
            tmp = tmp->NE;
        }
        else if(Q=="NE")
            tmp = tmp->NE;
        if(Q=="SW" && !tmp->SW)
        {
            tmp->SW = new Node<T>("gray", Q);
            tmp = tmp->SW;
        }
        else if(Q=="SW")
            tmp = tmp->SW;
        if(Q=="SE" && !tmp->SE)
        {
            tmp->SE = new Node<T>("gray", Q);
            tmp = tmp->SE;
        }
        else if(Q=="SE")
            tmp = tmp->SE;
        x = x%_W;
        y = y%_W;
        _W = _W/2;
        Q = MX_compare(x,y,_W);
    }   
    // std::cout<<value<<"-> "<<Q<<'\n';
    Node<T>* nodo = new Node<T>(value, "black", Q);
    if(Q=="NW")
        tmp->NW = nodo;
    else if(Q=="NE")
        tmp->NE = nodo;
    else if(Q=="SW")
        tmp->SW = nodo;
    else if(Q=="SE")
        tmp->SE = nodo;
    _size++;
}

template<typename T>
void MX_QuadTree<T>::postOrden()
{
    postOrden(root);
}

template<typename T>
void MX_QuadTree<T>::postOrden(Node<T>* N)
{
    if(!N)
        return;
    postOrden(N->NW);
    postOrden(N->NE);
    postOrden(N->SW);
    postOrden(N->SE);
    std::cout<<N->value<<" "<<N->type<<" "<<N->Q<<'\n';
}


#endif