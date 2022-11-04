#ifndef NODE_H
#define NODE_H
#include <string>

template <typename T=int>
class Node
{
public:
    Node<T> * NW;
    Node<T> * NE;
    Node<T> * SW;
    Node<T> * SE;
    T value;
    std::string name;
    // non-leaf(gray), leaf(black)
    std::string type;   
    // quadrant
    std::string Q;      
    Node();
    Node(std::string _type, std::string _Q); 
    Node(T _value, std::string _type, std::string _Q);    
    Node<T> * getSon(std::string s);
    void automatate(Node<T> * N);
};

template<typename T>
Node<T>::Node()
{
    NW=NE=SW=SE=nullptr;
    type = "gray";
}

template<typename T>
Node<T>::Node(std::string _type, std::string _Q)
{
    NW=NE=SW=SE=nullptr;
    type = _type;
    Q = _Q;
}

template<typename T>
Node<T>::Node(T _value, std::string _type, std::string _Q)
{
    NW=NE=SW=SE=nullptr;
    value = _value;
    type = _type;
    Q = _Q;
}

template<typename T>
Node<T> * Node<T>::getSon(std::string s) 
{
    if(s == "NW") return NW;
    if(s == "NE") return NE;
    if(s == "SW") return SW;
    else return SE;
}

template<typename T>
void Node<T>::automatate(Node<T>* N)
{
    if(!N)
        return;
    automatate(N->NW);
    automatate(N->NE);
    automatate(N->SW);
    automatate(N->SE);
    delete N;
}

#endif