export module LinkedList;
import std;

export struct Node {
	int _value = int();
	Node* _next = nullptr;
	Node(int val, Node* next = nullptr) : _value(val), _next(next) {}
};

export class LinkedList {
private:
	Node* _end = nullptr;
	int _size = 0;	
public:
	LinkedList() {}

	LinkedList(const LinkedList& other)
	{
		if (other._end == nullptr) return;
		if (other._size == 0) return;
		if (other._size < 0) throw std::invalid_argument("Error! Degenerate size!");
		_size = other._size;
		_end = new Node(other._end->_value);
		Node* cur = _end;
		Node* otherNext = other._end->_next;
		while (otherNext != other._end)
		{
			cur->_next = new Node(otherNext->_value);
			cur = cur->_next;
			otherNext = otherNext->_next;
		}
		cur->_next = _end;
	}

	LinkedList(int size)
	{
		if (size < 0) throw std::invalid_argument("Error! Degenerate size!");
		if (size == 0) return;
		_size = size;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(-100, 100);
		_end = new Node(dist(gen));
		Node* cur = _end;
		for (int i = 1; i < _size; ++i)
		{
			Node* el = new Node(dist(gen));
			cur->_next = el;
			cur = cur->_next;
		}
		cur->_next = _end;
	}

	~LinkedList()
	{
		if (_end == nullptr) return;
		Node* cur = _end->_next;
		while (cur != _end)
		{
			Node* next = cur->_next;
			delete cur;
			cur = next;
		}
		delete _end;
		_end = nullptr;
		_size = 0;
	}

	int getSize() const { return _size; }
	const Node* getEnd() const { return _end; }


	LinkedList& operator=(const LinkedList& other)
	{
		if (this == &other) return *this;
		if (_end != nullptr)
		{
			Node* cur = _end->_next;
			while (cur != _end)
			{
				Node* next = cur->_next;
				delete cur;
				cur = next;
			}
			delete _end;
			_end = nullptr;
			_size = 0;
		}
		if (other._end == nullptr) return *this;
		_end = new Node(other._end->_value);
		_size = other._size;
		Node* cur = _end;
		Node* otherNext = other._end->_next;
		while (otherNext != other._end)
		{
			cur->_next = new Node(otherNext->_value);
			cur = cur->_next;
			otherNext = otherNext->_next;
		}
		cur->_next = _end;
		return *this;
	}

	void push_tail(int value)
	{
		if (_end == nullptr)
		{
			_end = new Node(value);
			_end->_next = _end;
			++_size;
		}
		else
		{
			Node* newVal = new Node(value);
			newVal->_next = _end->_next;
			_end->_next = newVal;
			_end = newVal;
			++_size;
		}
	}

	void push_tail(const LinkedList& other)
	{
		if (other._end == nullptr) return;

		Node* otherCur = other._end->_next;
		while (otherCur != other._end)
		{
			push_tail(otherCur->_value);
			otherCur = otherCur->_next;
		}
		push_tail(otherCur->_value);
	}

	void push_head(int value)
	{
		if (_end == nullptr)
		{
			_end = new Node(value);
			_end->_next = _end;
			++_size;
		}
		else
		{
			Node* newVal = new Node(value);
			newVal->_next = _end->_next;
			_end->_next = newVal;
			++_size;
		}
	}

	void push_head(const LinkedList& other)
	{
		if (other._end == nullptr) return;

		Node* otherCur = other._end;
		do
		{
			push_head(otherCur->_value);

			for (int i = 0; i < other._size - 1; ++i)
			{
				otherCur = otherCur->_next;
			}
		} while (otherCur != other._end);
	}

	void pop_head()
	{
		if (_end == nullptr) return;
		if (_size == 1)
		{
			delete _end;
			_end = nullptr;
			--_size;
			return;
		}
		Node* tmp = _end->_next;
		_end->_next = tmp->_next;
		delete tmp;
		--_size;
	}

	void pop_tail()
	{
		if (_end == nullptr) return;
		if (_size == 1)
		{
			delete _end;
			_end = nullptr;
			--_size;
			return;
		}
		for (int i = 0; i < _size - 1; ++i)
		{
			_end = _end->_next;
		}
		Node* tmp = _end->_next;
		_end->_next = tmp->_next;
		delete tmp;
		--_size;
	}

	void delete_node(int value)
	{
		if (_end == nullptr) return;

		while (_end->_next->_value == value)
		{
			pop_head();
			if (_end == nullptr) return;
		}

		Node* cur = _end->_next;
		while (cur->_next != _end)
		{
			if (cur->_next->_value == value)
			{
				Node* tmp = cur->_next;
				cur->_next = tmp->_next;
				delete tmp;
				--_size;
			}
			else
			{
				cur = cur->_next;
			}
		}

		if (_end->_value == value)
		{
			pop_tail();
		}
	}

	const int operator[](int index) const
	{
		if (_size == 0) throw std::invalid_argument("Empty list");
		index %= _size;
		if (index < 0) index += _size;
		Node* cur = _end;
		for (int i = 0; i <= index; ++i)
		{
			cur = cur->_next;
		}
		return cur->_value;
	}

	int& operator[](int index)
	{
		if (_size == 0) throw std::invalid_argument("Empty list");
		index %= _size;
		if (index < 0) index += _size;
		Node* cur = _end;
		for (int i = 0; i <= index; ++i)
		{
			cur = cur->_next;
		}
		return cur->_value;
	}
};

export std::ostream& operator<<(std::ostream& os, const LinkedList& obj)
{
	if (obj.getSize() == 0)
	{
		os << "[]\n";
		return os;
	}
	os << "...-->";
	for (int i = 0; i < obj.getSize(); ++i)
	{
		os << "[" << obj[i] << "|*]-->";
	}
	os << "...\n\n";
	return os;
}