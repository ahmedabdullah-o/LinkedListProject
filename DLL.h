#ifndef DLL_H
#define DLL_H

#include<iostream>
#include<stdexcept>

template <typename T>
struct Node {
    T data;
    Node *prev;
    Node *next;
    Node(T data, Node* prev = nullptr, Node* next = nullptr)
    : data(data), prev(prev), next(next) {}
};

template <typename T>
class DLL {
    private:
        Node<T>* head;
        Node<T>* tail;
        size_t size;

    public:
        DLL() : head(nullptr), tail(nullptr), size(0) {}
        ~DLL(){clear();}
        void push_back(T data){
            Node<T>* newnode = new Node<T>(data);
            if (!head){
                tail = head = newnode;
            } else {
                tail->next = newnode;
                newnode->prev = tail;
                tail = newnode;
            }
            size++;
        }
        T pop_back(){
            if (!head){
                throw std::out_of_range("The list is empty");
            } else if (size == 1){
                T out = tail->data;
                clear();
                return out;
            } else {
                T out = tail->data;
                tail = tail->prev;
                delete tail->next;
                tail->next = nullptr;
                size--;
                return out;
            }
        }
        void push_front(T data){
            Node<T>* newnode = new Node<T>(data);
            if (!head){
                head = tail = newnode;
            } else {
                head->prev = newnode;
                newnode->next = head;
                head = newnode;
            }
            size++;
        }
        T pop_front(){
            if (!head){
                throw std::out_of_range("The list is empty");
            } else if (size == 1){
                T out = head->data;
                clear();
                return out;
            } else {
                T out = head->data;
                head = head->next;
                delete head->prev;
                head->prev = nullptr;
                size--;
                return out;
            }
        }
        void insert(T data, size_t index){
            if (index >= size){
                throw std::out_of_range("Index out of bound");
            } else {
                Node<T>* current = head;
                int count = 0;
                Node<T>* newnode = new Node<T>(data);
                if (index == 0){
                    push_front(data);
                } else if (index == size){
                    push_back(data);
                } else
                    while (current){
                        if (count == index){
                            newnode->prev = current->prev;
                            current->prev->next = newnode;
                            newnode->next = current;
                            current->prev = newnode;
                            size++;
                            break;
                        }
                        current = current->next;
                        count++;
                    }
            }
        }
        void erase(size_t index){
            if (index >= size){
                throw std::out_of_range("Index out of bound");
            } else {
                Node<T>* current = head;
                int count = 0;
                if (index == 0){
                    pop_front();
                } else if (index == size - 1){
                    pop_back();
                } else 
                    while (current){
                        if (count == index){
                            current->next->prev = current->prev;
                            current->prev->next = current->next;
                            delete current;
                            size--;
                            break;
                        }
                        current = current->next;
                        count++;
                    }
            }
        }
        int find(T data){
            Node<T>* current = head;
            int count = 0;
            while (current){
                if (current->data == data)
                    return count;
                current = current->next;
                count++;
            }
            return -1;
        }
        T query(size_t index){
            Node<T>* current = head;
            size_t count = 0;
            while (current){
                if (count == index)
                    return current;
            }
            return NULL;
        }
        void traverse(){
            Node<T>* current = head;
            size_t count = 0;
            while (current){
                std::cout<<'['<<count<<"]: "<<current->data<<'\n';
                current = current->next;
                count++;
            }
        }

        size_t get_size(){return size;}

        void clear() {
            while (head) {
                Node<T>* toDelete = head;
                head = head->next;
                delete toDelete;
            }
            head = tail = nullptr;
            size = 0;
        }
};

#endif //DLL_H