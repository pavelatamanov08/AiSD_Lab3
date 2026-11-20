export module sort;
import LinkedList;
import gen;
import std;

export struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};

Node* vec_to_list(const std::vector<int>& vec)
{
	Node* head = new Node(vec[0]);
	Node* cur = head;
	for (int i = 1; i < vec.size(); ++i)
	{
		cur->_next = new Node(vec[i]);
		cur = cur->_next;
	}
	return head;
}

stats selection_sort(std::vector<int>& vec) //сортировка выбором
{
	stats count;
	if (vec.empty()) return count;
	Node* head = vec_to_list(vec);
	for (int i = 0; i < static_cast<int>(vec.size()); ++i)
	{
		Node* cur = head;
		Node* for_swap = head;
		for (int k = 0; k < i; ++k)
		{
			cur = cur->_next;
			for_swap = for_swap->_next;
		}
		Node* min_ptr = cur;
		for (int j = i + 1; j < static_cast<int>(vec.size()); ++j)
		{
			++count.comparison_count;
			if (cur->_next->_value < min_ptr->_value)
			{
				min_ptr = cur->_next;
			}
			cur = cur->_next;
		}
		if (min_ptr != for_swap)
		{
			std::swap(min_ptr->_value, for_swap->_value);
			count.copy_count += 3;
		}
	}
	Node* current = head;
	for (size_t i = 0; i < vec.size(); ++i)
	{
		vec[i] = current->_value;
		if (current->_next)
		{
			current = current->_next;
		}
	}
	while (head)
	{
		Node* tmp = head;
		head = head->_next;
		delete tmp;
	}
	return count;
}

stats comb_sort(std::vector<int>& vec) // сорттровка расчёской
{
	stats count;
	if (vec.empty()) return count;
	for (int step = static_cast<int>(vec.size()); step > 1; int(step /= 1.247))
	{
		for (int i = 0; i < static_cast<int>(vec.size()) - step; ++i)
		{
			++count.comparison_count;
			if (vec[i] > vec[i + step])
			{
				std::swap(vec[i], vec[i+step]);
				count.copy_count += 3;
			}
		}
	}
	for (int i = 0; i < static_cast<int>(vec.size()) - 1; ++i)
	{
		++count.comparison_count;
		if (vec[i] > vec[i + 1])
		{
			std::swap(vec[i], vec[i + 1]);
			count.copy_count += 3;
		}
	}
	return count;
}

