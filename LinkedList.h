#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdexcept>

template <class T>
class LinkedList
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node( T value) : data(value), next(nullptr) {}
    };

    Node *head;
    Node *tail;
    int size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~LinkedList()
    {
        clear();
    }

    int getSize() const
    {
        return size;
    }

    bool isEmpty() const
    {
        std::cout << "check if linked list is empty" << std::endl;
        return (size == 0);
    }

    void prepend( T value)
    {
        Node *node = new Node(value);
        if (head == nullptr)
        {
            head = node;
            tail = node;
        }
        else
        {
            node->next = head;
            head = node;
        }
        size++;
    }

    void insertAtIndex(int index,  T value)
    {
        if (index < 0 || index > size)
        {
            throw std::out_of_range("Index out of range");
        }
        if (index == 0)
        {
            prepend(value);
        }
        else if (index == size)
        {
            append(value);
        }
        else
        {
            Node *node = new Node(value);
            Node *prev = getNode(index - 1);
            node->next = prev->next;
            prev->next = node;
            size++;
        }
    }

    T get(int index) const
    {
        if (index < 0 || index >= size)
        {
            std::cout << "Index out of range" << std::endl;
            throw std::out_of_range("Index out of range");
        }
        Node *node = getNode(index);
        return node->data;
    }

    void remove(int index)
    {
        if (index < 0 || index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        if (index == 0)
        {
            Node *node = head;
            head = head->next;
            delete node;
            if (head == nullptr)
            {
                tail = nullptr;
            }
        }
        else
        {
            Node *prev = getNode(index - 1);
            Node *node = prev->next;
            prev->next = node->next;
            delete node;
            if (prev->next == nullptr)
            {
                tail = prev;
            }
        }
        size--;
    }

    void clear()
    {
        while (head != nullptr)
        {
            Node *node = head;
            head = head->next;
            delete node;
        }
        tail = nullptr;
        size = 0;
    }

    void append( T value)
    {
        Node *node = new Node(value);
        if (tail == nullptr)
        {
            head = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }
        size++;
    }

private:
    Node *getNode(int index) const
    {
        Node *node = head;

        
        for (int i = 0; i < index; i++)
        {
                if(node == nullptr)
                {
                    std::cout << "Node is null" << std::endl;
                }
                else
                {
                    std::cout << "Node is not null" << std::endl;
                      node = node->next;
                }
          
        }
        return node;
    }
};

#endif // LINKEDLIST_H