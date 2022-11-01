#ifndef MX_QUADTREE_H
#define MX_QUADTREE_H
#include <iostream>
#include <sstream>
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
    int nodo_name;
public:
    MX_QuadTree(int _W);
    ~MX_QuadTree();
    std::string MX_compare(int x, int y, int _W);
    void insert(int x, int y, T value);     // ya esta
    bool search(Node<T>* N);                // samuel
    void erase(T value);                    // julio
    void postOrden();

    void graphic(std::string dir);          // grafica
    void graph_node(std::ofstream& f, Node<T>* nodo, int& null_n);

    int size(){return _size;}
};

template<typename T>
MX_QuadTree<T>::MX_QuadTree(int _W)
{
    W=_W;
    root = nullptr;
    _size = 0;
    nodo_name = 1;
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
        root->name = std::to_string(nodo_name++);
        _size++;
        return;
    }
    else if(!root)
    {
        root = new Node<T>("gray", "root");
        root->name = std::to_string(nodo_name++);
    }
    Node<T>* tmp = root;
    int _W = W/2;
    std::string Q = MX_compare(x,y,_W);
    while(_W>1)
    {
        // std::cout<<value<<"-> "<<Q<<'\n';
        if(Q=="NW" && !tmp->NW)
        {
            tmp->NW = new Node<T>("gray", Q);
            tmp->NW->name = std::to_string(nodo_name++);
            tmp = tmp->NW;
        }
        else if(Q=="NW")
            tmp = tmp->NW;
        if(Q=="NE" && !tmp->NE)
        {
            tmp->NE = new Node<T>("gray", Q);
            tmp->NE->name = std::to_string(nodo_name++);
            tmp = tmp->NE;
        }
        else if(Q=="NE")
            tmp = tmp->NE;
        if(Q=="SW" && !tmp->SW)
        {
            tmp->SW = new Node<T>("gray", Q);
            tmp->SW->name = std::to_string(nodo_name++);
            tmp = tmp->SW;
        }
        else if(Q=="SW")
            tmp = tmp->SW;
        if(Q=="SE" && !tmp->SE)
        {
            tmp->SE = new Node<T>("gray", Q);
            tmp->SE->name = std::to_string(nodo_name++);
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
    {
        if(tmp->NW)         // ya existe nodo
            tmp->NW->value = value;     // reemplaza
        else
            tmp->NW = nodo;
    }
    else if(Q=="NE")        // ya existe nodo
    {
        if(tmp->NE)
            tmp->NE->value = value;     // reemplaza
        else 
            tmp->NE = nodo;
    }
    else if(Q=="SW")        // ya existe nodo
    {
        if(tmp->SW)
            tmp->SW->value = value;     // reemplaza
        else
            tmp->SW = nodo;
    }
    else if(Q=="SE")        // ya existe nodo
    {
        if(tmp->SE)
            tmp->SE->value = value;     // reemplaza
        else
            tmp->SE = nodo;
    }
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
    std::cout<<N->value<<" "<<N->type<<" "<<N->Q<<" "<<N->name<<'\n';
}

template<typename T>
void MX_QuadTree<T>::graphic(std::string dir)
{
    int null_n = 1;
    std::ofstream f(dir);
    f<<"graph T{\n";
    graph_node(f, root, null_n);
    f<<"}";
    f.close();

    std::stringstream dir1(dir);
    std::string name, ext, aux;
    std::getline(dir1,aux,'.');
    name = aux;
    std::getline(dir1,aux,'.');
    ext = aux;
    system(&(("dot "+ dir + " -o " + name + ".png -Tpng")[0]));
    system(&((name + ".png")[0]));
    // system("dot grafo.dot -o grafo.png -Tpng");           //dot grafo.dot -o grafo.png -Tpng
    // system("grafo.png");
}

template<typename T>
void MX_QuadTree<T>::graph_node(std::ofstream& f, Node<T>* nodo, int& null_n)
{
    if(!nodo)
        return;
    f<<nodo->Q<<"_"<<nodo->name<<"[style = filled, color="<<nodo->type<<"];\n";
    if(nodo->NW)        // tiene hijo
    {
        f<<nodo->Q<<"_"<<nodo->name<<" -- "<<nodo->NW->Q<<"_";
        if(nodo->NW->name=="")              // es hoja
        {
            f<<nodo->NW->value<<";\n";
            f<<nodo->NW->Q<<"_"<<nodo->NW->value<<"[style = filled, color="
            <<nodo->NW->type<<", fontcolor = white];\n";
        }
        else
        {
            f<<nodo->NW->name<<";\n";
            graph_node(f,nodo->NW,null_n);
        }
    }
    else
        f<<nodo->Q<<"_"<<nodo->name<<" -- NULL_"<<null_n++<<";\n";
    if(nodo->NE)        // tiene hijo
    {
        f<<nodo->Q<<"_"<<nodo->name<<" -- "<<nodo->NE->Q<<"_";
        if(nodo->NE->name=="")          // es hoja
        {
            f<<nodo->NE->value<<";\n";
            f<<nodo->NE->Q<<"_"<<nodo->NE->value<<"[style = filled, color="
            <<nodo->NE->type<<", fontcolor = white];\n";
        }
        else
        {
            f<<nodo->NE->name<<";\n";
            graph_node(f,nodo->NE,null_n);
        }
    }
    else
        f<<nodo->Q<<"_"<<nodo->name<<" -- NULL_"<<null_n++<<";\n";
    if(nodo->SW)        // tiene hijo
    {
        f<<nodo->Q<<"_"<<nodo->name<<" -- "<<nodo->SW->Q<<"_";
        if(nodo->SW->name=="")          // es hoja
        {
            f<<nodo->SW->value<<";\n";
            f<<nodo->SW->Q<<"_"<<nodo->SW->value<<"[style = filled, color="
            <<nodo->SW->type<<", fontcolor = white];\n";
        }
        else
        {
            f<<nodo->SW->name<<";\n";
            graph_node(f,nodo->SW,null_n);
        }
    }
    else
        f<<nodo->Q<<"_"<<nodo->name<<" -- NULL_"<<null_n++<<";\n";
    if(nodo->SE)        // tiene hijo
    {
        f<<nodo->Q<<"_"<<nodo->name<<" -- "<<nodo->SE->Q<<"_";
        if(nodo->SE->name=="")          // es hoja
        {
            f<<nodo->SE->value<<";\n";
            f<<nodo->SE->Q<<"_"<<nodo->SE->value<<"[style = filled, color="
            <<nodo->SE->type<<", fontcolor = white];\n";
        }
        else
        {
            f<<nodo->SE->name<<";\n";
            graph_node(f,nodo->SE,null_n);
        }
    }
    else
        f<<nodo->Q<<"_"<<nodo->name<<" -- NULL_"<<null_n++<<";\n";
}

#endif