#ifndef NODE_H
#define NODE_H
#include <string>

template <typename T=int>
class Node
{
public:
    Node* NW;
    Node* NE;
    Node* SW;
    Node* SE;
    T value;
    // non-leaf(gray), leaf(black)
    std::string type;   
    // quadrant
    std::string Q;      
    Node();
    Node(std::string _type, std::string _Q); 
    Node(T _value, std::string _type, std::string _Q);    
    void automatate(Node<T>* N);
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