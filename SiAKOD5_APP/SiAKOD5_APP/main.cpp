#include <iostream>
#include <string>
#include <ctime>

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
	T check() { return head->data; }
	void push_front(T data);
	void push_back(T data);
	int get_size() { return size; }
	void clear() { while (size) pop_front(); }
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


//////////////////////Стек
template<typename T>
class Stack
{
private:
	SLLList<T> block;

public:
	void push(T data) { block.push_front(data); }
	T pop() { return block.pop_front(); }
	bool isEmpty() { return block.get_size() == 0; }
	T check_top() { return block.check(); }
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
	T check_top() { return block.check(); }
};


//////////////////////Задача
class Task
{
private:
	std::string name;
	unsigned time;
	unsigned type;

public:
	Task(std::string name = "", unsigned time = 0, unsigned type = 0)
	{
		this->name = name;
		this->time = time;
		this->type = type;
	}
	void generate()
	{
		std::cout << "Введите имя задачи -> ";
		std::getline(std::cin, name);
		time = (rand() % 4) + 1;
		type = (rand() % 3) + 1;
	}
	std::string get_name() { return name; }
	unsigned get_time() { return time; }
	unsigned get_type() { return type; }
	void countdown() { --time; }
	bool isFinished() { return time == 0; }
	void output_status()
	{
		std::cout << "Имя задачи: " << name << " ; время: " << time << ".\n";
	}
};


//////////////////////Процессор
class Processor
{
private:
	Task processed_task;

public:
	Processor() { processed_task = Task(); }
	void push(Task task) { processed_task = task; }
	void delete_task() { processed_task = Task(); }
	bool check_task() { return processed_task.get_time() > 0; }
	bool isEmpty() { return processed_task.isFinished(); }
	void task_processing()
	{
		if (this->check_task())
		{
			processed_task.countdown();
			if (processed_task.isFinished())
			{
				std::cout << "Процесс обработки задачи \"" << processed_task.get_name() << "\" завершен.\n";
				this->delete_task();
			}
		}
	}
	void show_task_status()
	{
		if (processed_task.get_time() > 5 || processed_task.get_time() == 0) std::cout << " пусто\n";
		else processed_task.output_status();
	}
};


//////////////////////Распределитель
class Distributor
{
private:
	Task received_task;

public:
	Distributor() { received_task = Task(); }
	void push(Task task) { received_task = task; }
	void clear() { received_task = Task(); }
	Task get_task() { return received_task; }
};



int main()
{
	using namespace std;
	setlocale(0, "");
	srand(time(NULL));
	Processor P1;
	Processor P2;
	Processor P3;
	Processor pArr[3];
	pArr[0] = P1;
	pArr[1] = P2;
	pArr[2] = P3;
	Distributor R;
	bool R_tumblr;
	Queue<Task> F;
	Stack<Task> S;
	unsigned dec_time = 0;
	cout << "ПРОГРАММА МОДЕЛИРОВАНИЯ ОБРАБОТКИ ЗАДАЧ\n\n";
	cout << "Нажмите любую клавишу, чтобы сгенерировать задачу (q - выход): ";
	char ask;
	cin >> ask;
	while (cin.get() != '\n') continue;
	cout << endl;
	while (ask != 'q' || !pArr[0].isEmpty() || !pArr[1].isEmpty() || !pArr[2].isEmpty() || !S.isEmpty() || !F.isEmpty())
	{
		R_tumblr = true;
		dec_time++;
		Task new_task;
		if (ask != 'q') new_task.generate(); //Генерируем задачу
		cout << "Тип задачи - (" << new_task.get_type() << ") Время выполнения - (" << new_task.get_time() << ")\n";
		F.push(new_task); //Ставим задачу в очередь
		if (!S.isEmpty() && pArr[(S.check_top()).get_type() - 1].isEmpty()) //Проверяем, освободился ли процессор для обработки верхнего элемента стека
		{
			R.push(S.pop());
			pArr[(S.check_top()).get_type() - 1].push(R.get_task());
			R.clear();
		}
		while (!F.isEmpty() && R_tumblr)
		{
			R.push(F.pop()); //Передаем задачу из очереди в распределитель
			if (pArr[(R.get_task()).get_type() - 1].isEmpty()) //Если нужный процессор свободен - ставим задачу на обработку
			{
				pArr[(R.get_task()).get_type() - 1].push(R.get_task());
				R.clear();
				R_tumblr = false;
			}
			else //Если занят - кладем задачу в стек и извлекаем из очереди следующую (если она есть), но перед этим проверяем процессор для вершины стека
			{
				S.push(R.get_task());
				R.clear();
				R_tumblr = true;
			}
		}


		cout << "\nСтатус работы программы на времени <" << dec_time << ">.\n\n";

		for (int i = 0; i < 3; i++) //Обработка задачи в процессоре
		{
			if (!pArr[i].isEmpty()) pArr[i].task_processing();

		}
		for (int i = 0; i < 3; i++)
		{
			cout << "P" << i + 1 << " ----- ";
			pArr[i].show_task_status();
		}
		if (!S.isEmpty())
		{
			cout << "S ---- ";
			(S.check_top()).output_status();
		}
		else cout << "S ---- пусто\n";
		if (!F.isEmpty())
		{
			cout << "F ---- ";
			(F.check_top()).output_status();
		}
		else cout << "F ---- пусто\n";

		cout << "\n\nНажмите любую клавишу, чтобы сгенерировать задачу (q - выход): ";
		cin >> ask;
		while (cin.get() != '\n') continue;
		cout << endl;
	}
	return 0;
}
