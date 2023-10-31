#include "doubleNode.h"

doubNode::doubNode()
{   //this will not be excuted, if u r writing something new , dont use it
    data = new char[LEN];
    prev = nullptr;
    next = nullptr;
    line = 0;
}
      // only use this!!
doubNode::doubNode(const char* e, int size, doubNode* prev, doubNode* next) {
    data = new char[size];
    for (int i = 0; i < size; ++i) {
        data[i] = e[i];
    }
    this->prev = prev;
    this->next = next;
}

doubNode::~doubNode()
{
    delete []data;
}
