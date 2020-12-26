#ifndef __STACK

#define __STACK

template <typename T>
class Stack {
private:
	struct elem {		//struct to store values and references to next
		elem(T value, elem* next = nullptr) :value(value), next(next) {};
		T value;
		elem* next;
	};
public:
	Stack() : head(nullptr) {}; //default constructor
	~Stack() { clear(); };		//destructor

	void push(T); 
	T pop();
	T top() const;
	bool empty() const;
	void clear();
private:
	elem* head;			//top of the stack
};

//push element into stack
template <typename T>
void Stack<T>::push(T value) {
	head = new elem(value, head);
}

//pop element from stack
template <typename T>
T Stack<T>::pop() {
	elem* popped = head;
	head = head->next;
	T value = popped->value;
	delete popped;
	return value;
}

//get value at top of stack
template <typename T>
T Stack<T>::top() const {
	return head->value;
}

//checking stack for empty
template <typename T>
bool Stack<T>::empty() const {
	return head == nullptr;
}

//clear stack
template <typename T>
void Stack<T>::clear() {
	while (head != nullptr) {
		elem* del = head;
		head = head->next;
		delete del;
	}
}

#endif 