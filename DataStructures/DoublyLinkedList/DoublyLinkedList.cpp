#include "DoubyLinkedList.h"
#include <iostream>
#include <vector>
using namespace std;

DoublyLinkedList::DoublyLinkedList() : num_items(0), front(nullptr), rear(nullptr) {}

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& other) {

    num_items = other.num_items;

    front = nullptr;
    rear = nullptr;

    if (num_items == 0)
        return;

    Node* orig = other.front;
    Node* copy = new Node(orig->item);

    front = copy;
    orig = orig->next;

    while (orig != nullptr) {
        copy->next = new Node(orig->item);
        copy->next->prev = copy;
        orig = orig->next;
        copy = copy->next;
    }
    rear = copy;
    // Orig is one step ahead of copy so copy will point at the last node
}
DoublyLinkedList::~DoublyLinkedList() {
    int n = num_items;
    for (int pos = 1; pos <= n; pos++)
        remove(0);
}
void DoublyLinkedList::add(E item) {
    add(num_items, item);
}
void DoublyLinkedList::add(int pos, E item) {
    if (pos < 0 || pos > num_items)
        throw "invalid position specified";
    Node* p = new Node(item);
    
    if (pos == 0){
        if (num_items == 0) {
            front = p;
            rear = front;
        }
        else {
            p->next = front;
            front->prev = p;
            front = p;
        }
    }
    else if (pos == num_items) {
        rear->next = p;
        p->prev = rear;
        rear = p;
    }
    // Find node that will be before new node
    else {
        Node* prevNode = getNodeAt(pos - 1);

        p->next = prevNode->next;
        p->prev = prevNode;
        p->next->prev = p;
        prevNode->next = p;
    }

    num_items++;
}
bool DoublyLinkedList::contains(E item) {
    Node* p = front;
    while (p != nullptr) {
        if (p->item == item)
            return true;
        p = p->next;
    }
    return false;
}
int DoublyLinkedList::size() {
    return num_items;
}
bool DoublyLinkedList::isEmpty() {
    return num_items == 0;
}
E DoublyLinkedList::get(int pos) {
    if (pos < 0 || pos >= num_items)
        throw "invalid position specified";
    Node* p = getNodeAt(pos);
    return p->item;
}
E DoublyLinkedList::remove(int pos) {
    if (pos < 0 || pos >= num_items)
        throw "invalid position specified";

    if (pos == 0)
    {
        Node * p = front;
        E item = p->item;

        if (num_items == 1) {
            front = nullptr;
            rear = nullptr;
        }
        // Remove the first node in the list
        else {
            front = front->next;
            front->prev = nullptr;
            p->next = nullptr;
        }

        delete p;
        num_items--;
        return item;
    }
    else if (pos == num_items - 1) {
        // That means we want to remove the last element
        Node* p = rear;
        E item = p->item;
        rear = rear->prev;
        rear->next = nullptr;
        p->prev = nullptr;
        delete p;
        num_items--;
        return item;
    }
    else {
        // Find node that is before the one to remove
        Node* prevNode = getNodeAt(pos - 1);
        Node* p = prevNode->next;
        E item = p->item;
        prevNode->next = p->next;
        prevNode->next->prev = prevNode;
        p->next = nullptr;
        p->prev = nullptr;
        // Free the node
        delete p;
        num_items--;
        return item;
    }
}
void DoublyLinkedList::show() {
    Node* p = front;
    cout << "[ ";
    while (p != nullptr) {
        cout << p->item << " ";
        p = p->next;
    }
    cout << "]" << endl;
}
// Private
Node* DoublyLinkedList::getNodeAt(int pos) {
    if (pos < num_items / 2) {
        Node* p = front;
        for (int skip = 1; skip <= pos; skip++)
            p = p->next;
        return p;
    }
    else {
        Node* p = rear;
        for (int skip = num_items - 1; skip > pos; skip--)
            p = p->prev;
        return p;
    }
}
void DoublyLinkedList::reverse() {
    Node * temp = rear;
    rear = front;
    front = temp;
    Node * orig = front;
    temp->next = temp->prev;
    temp->prev = nullptr;
    temp = temp->next;
    for (int i = num_items - 1; i >= 1; i--) {
        temp->next = temp->prev;
        temp->prev = orig;
        orig = orig->next;
        temp = temp->next;
    }
}
vector<E> DoublyLinkedList::toVector(bool reverse) {
    vector<E> arr;
    if (reverse) {
        Node * p = rear;
        while(p != nullptr) {
            arr.push_back(p->item);
            p = p->prev;
        }
    }
    else {
        Node * p = front;
        while (p != nullptr) {
            arr.push_back(p->item);
            p = p->next;
        }
    }
    return arr;
}