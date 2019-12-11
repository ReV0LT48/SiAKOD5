#include <iostream>
#include <string>
using namespace std;


//////////////////////Односвязный линейный список
template<typename T>
class SLLList
{
private:
    template<typename T>
    class Node
    {
    public:
        Node* next;
        T data;
        Node(T data = T(), Node* next = nullptr)
        {
            this->data = data;
            this->next = next;
        }
    };
    int size;
    Node<T>* head;
    
public:
    SLLList();
    ~SLLList();
    T pop_front();
    T pop_back();
    void push_front(T data) { head = new Node<T>(data, head); size++; }
    void push_back(T data);
    void insert(T data, int index);
    void remove_at(int index);
    void clear() { while (size) pop_front(); }
    int get_size() { return size; }
    T& operator[](const int index);
    void toNext() { head = head->next; }
};

template<typename T>
SLLList<T>::SLLList()
{
    size = 0;
    head = nullptr;
}

template<typename T>
SLLList<T>::~SLLList()
{
    clear();
}

template<typename T>
T SLLList<T>::pop_front()
{
    Node<T>* temp = head;
    head = head->next;
    T data = temp->data;
    delete temp;
    size--;
    return data;
}

template<typename T>
void SLLList<T>::push_back(T data)
{
    if (head == nullptr) head = new Node<T>(data);
    else
    {
        Node<T>* current = this->head;
        while (current->next != nullptr) current = current->next;
        current->next = new Node<T>(data);
    }
    size++;
}

template<typename T>
void SLLList<T>::insert(T data, int index)
{
    if (index == 0) push_front(data);
    else
    {
        Node<T>* previous = this->head;
        for (int i = 0; i < index; i++) previous = previous->next;
        Node<T>* newNode = new Node<T>(data, previous->next);
        previous->next = newNode;
        size++;
    }
}

template<typename T>
void SLLList<T>::remove_at(int index)
{
    if (index == 0) pop_front();
    else
    {
        Node<T>* previous = this->head;
        for (int i = 0; i < index; i++) previous = previous->next;
        Node<T>* toDelete = previous->next;
        previous->next = toDelete->next;
        delete toDelete;
        size--;
    }
}

template<typename T>
T SLLList<T>::pop_back()
{
    Node<T>* current = this->head;
    while (current->next) current = current->next;
    T data = current->data;
    current = NULL;
    size--;
    return data;
}

template<typename T>
T& SLLList<T>::operator[](const int index)
{
    unsigned counter = 0;
    Node<T>* current = this->head;
    while (current != nullptr)
    {
        if (counter == index) return current->data;
        current = current->next;
        counter++;
    }
}


//////////////////////Задача
class Task
{
private:
    string name;
    int time;
    int priority;
    
public:
    Task()
    {
        name = "";
        time = 0;
        priority = 1000;
    }
    Task(string name, int time, int priority)
    {
        this->name = name;
        this->time = time;
        this->priority = priority;
    }
    string get_name() { return name; }
    int get_time() { return time; }
    int get_priority() { return priority; }
    void countdown() { --time; }
    bool isFinished() { return time == 0; }
    void output_status()
    {
        cout << "Имя задачи: " << name << " ; время выполнения: " << time << ".\n";
    }
};


//////////////////////Стек

//////////////////////Очередь

//////////////////////Процессор



int main()
{
    setlocale(0, "");
    
    return 0;
}
