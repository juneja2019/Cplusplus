#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST
#include <string>
#include <vector>

using namespace std;
typedef string E;
struct Node {
    Node* prev;
    E item;
    Node* next;
    Node(E e) { item = e; next = nullptr; prev = nullptr; }
};
class DoublyLinkedList
{
private:
    Node * front;
    Node * rear;
    int num_items;
    Node* getNodeAt(int pos);
public:
    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList& other);
    ~DoublyLinkedList();
    void add(E item);
    void add(int pos, E item);
    bool contains(E item);
    int size();
    bool isEmpty();
    E get(int pos);
    E remove(int pos);
    void show();
    void reverse();
    vector<E> toVector(bool reverse);
};
#endif

