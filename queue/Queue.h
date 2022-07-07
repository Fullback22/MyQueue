#pragma once

template <typename T>
struct Node
{
	Node* nextNode{};
	Node* previousNode{};
	T value{};
};

template <typename T>
class MyQueue
{
	size_t quantityNodes_{};
	Node<T>* head_{};
	Node<T>* tail_{};

public:
	MyQueue();
	MyQueue(const MyQueue& temp);
	MyQueue(MyQueue&& temp);

	MyQueue<T>& operator=(const MyQueue& temp);
	MyQueue<T>& operator=(MyQueue&& temp);

	~MyQueue();

	void push(const T& newValue);

	void pop();
	void clear();

	size_t size() const;
	bool empty() const;

	Node<T>& front();
	const Node<T>& front() const;
	Node<T>& back();
	const Node<T>& back() const;
};


template<typename T>
inline MyQueue<T>::MyQueue()
{
}

template<typename T>
inline MyQueue<T>::MyQueue(const MyQueue& temp)
{
	Node<T>* activTempNode{ temp.head_ };
	while (temp.quantityNodes_ > quantityNodes_)
	{
		pushBack(activTempNode->value);
		activTempNode = activTempNode->nextNode;
	}
}

template<typename T>
inline MyQueue<T>::MyQueue(MyQueue&& temp)
{
	quantityNodes_ = temp.quantityNodes_;
	head_ = temp.head_;
	tail_ = temp.tail_;
	temp.quantityNodes_ = 0;
}

template<typename T>
inline MyQueue<T>& MyQueue<T>::operator=(const MyQueue& temp)
{
	while (quantityNodes_ > temp.quantityNodes_)
		pop();

	Node<T>* activTempNode{ temp.head_ };
	Node<T>* activNode{ head_ };
	for (size_t copiedNodes{}; quantityNodes_ > copiedNodes; ++copiedNodes)
	{
		activNode->value = activTempNode->value;
		activTempNode = activTempNode->nextNode;
		activNode = activNode->nextNode;
	}

	while (quantityNodes_ < temp.quantityNodes_)
	{
		pushBack(activTempNode->value);
		activTempNode = activTempNode->nextNode;
	}

	return *this;
}

template<typename T>
inline MyQueue<T>& MyQueue<T>::operator=(MyQueue&& temp)
{
	head_ = temp.head_;
	tail_ = temp.tail_;
	quantityNodes_ = temp.quantityNodes_;

	temp.quantityNodes_ = 0;
}

template<typename T>
inline MyQueue<T>::~MyQueue()
{
	clear();
}


///ADD ELEMENTS
template<typename T>
inline void MyQueue<T>::push(const T& newValue)
{
	Node<T>* newTail{ new Node<T>{} };
	newTail->value = newValue;
	if (tail_ == nullptr)
	{
		tail_ = newTail;
		head_ = newTail;
	}
	else
	{
		newTail->previousNode = tail_;
		tail_->nextNode = newTail;
		tail_ = newTail;
	}
	++quantityNodes_;
}

///DELETED ELEMENTS

template<typename T>
inline void MyQueue<T>::pop()
{
	if (head_ == tail_)
	{
		delete head_;
		tail_ = nullptr;
		head_ = nullptr;
		quantityNodes_ = 0;
	}
	else
	{
		Node<T>* newHead{};
		newHead = head_->nextNode;
		newHead->previousNode = nullptr;
		delete head_;
		head_ = newHead;
		--quantityNodes_;
	}
}

template<typename T>
inline void MyQueue<T>::clear()
{
	while (quantityNodes_)
	{
		pop();
	}
}

template<typename T>
inline size_t MyQueue<T>::size() const
{
	return quantityNodes_;
}

template<typename T>
inline bool MyQueue<T>::empty() const
{
	if (quantityNodes_ == 0)
		return true;
	else
		return false;
}

template<typename T>
inline Node<T>& MyQueue<T>::front()
{
	if (quantityNodes_ == 0)
		throw ("list emplace");
	return *head_;
}

template<typename T>
inline const Node<T>& MyQueue<T>::front() const
{
	if (quantityNodes_ == 0)
		throw ("list emplace");
	return *head_;
}

template<typename T>
inline Node<T>& MyQueue<T>::back()
{
	if (quantityNodes_ == 0)
		throw ("list emplace");
	return *tail_;
}

template<typename T>
inline const Node<T>& MyQueue<T>::back() const
{
	if (quantityNodes_ == 0)
		throw ("list emplace");
	return *tail_;
}
