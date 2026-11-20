export module gen;
import std;

std::vector<int> gen_array(int size)
{
	if (size < 0) throw std::invalid_argument("Error! Degenerate size!");
	std::vector<int> arr;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(-100000, 100000);
	for (int i = 0; i < size; ++i)
	{
		arr.push_back(dist(gen));
	}
	return arr;
}