#include <iostream>
#include <string>

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
	void push_front(T data);
	void push_back(T data);
	int get_size() { return size; }
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
void SLLList<T>::push_front(T data)
{
	head = new Node<T>(data, head);
	size++;
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


//////////////////////Задача
class Task
{
private:
	std::string name;
	unsigned time;
	unsigned priority;

public:
	Task()
	{
		name = "";
		time = 0;
		priority = 1000;
	}
	Task(std::string name, int time, int priority)
	{
		this->name = name;
		this->time = time;
		this->priority = priority;
	}
	std::string get_name() { return name; }
	unsigned get_time() { return time; }
	int get_priority() { return priority; }
	void countdown() { --time; }
	bool isFinished() { return time == 0; }
	void output_status()
	{
		std::cout << "Имя задачи: " << name << " ; время выполнения: " << time << ".\n";
	}
};


//////////////////////Стек
template<typename T>
class Stack
{
private:
	SLLList<T> block;

public:
	void push(T data) { block.push_front(data); }
	T pop() { return block.pop_back(); }
	bool isEmpty() { return block.get_size() == 0; }
};


//////////////////////Очередь
template<typename T>
class Queue
{
private:
	SLLList<T> block;

public:
	void push(T data) { block.push_back(data); }
	T pop() { return block.pop_front(); }
	bool isEmpty() { return block.get_size() == 0; }
};


//////////////////////Процессор



int main()
{
	setlocale(0, "");

	return 0;
}
