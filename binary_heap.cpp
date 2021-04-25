#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

template<class T>
class BinaryHeap;
template<class T>
std::istream &operator>>(std::istream &in, BinaryHeap<T> &heap);

template<class T>
class BinaryHeap {
 public:
  using Mptr = void (BinaryHeap<T>::*)();
  void Insert();
  void GetMin();
  void ExtractMin();
  void DecreaseKey();
  friend std::istream &operator>><T>(std::istream &in, BinaryHeap &heap);
 private:
  void SiftUp(int i);
  void SiftDown(int i);
 private:
  std::vector<T> heap_;

};

template<class T>
void BinaryHeap<T>::Insert() {
	T value;
	std::cin >> value;
	heap_.push_back(std::move(value));
	SiftUp(heap_.size() - 1);
}

template<class T>
void BinaryHeap<T>::GetMin() {
	std::cout << heap_.front() << std::endl;
}

template<class T>
void BinaryHeap<T>::ExtractMin() {
	//not for all types will work well! [prevent copying]
	std::swap(heap_[0], heap_.back());
	heap_.pop_back();
	SiftDown(0);
}

template<class T>
void BinaryHeap<T>::DecreaseKey() {
	int i = 0;
	std::cin >> i;
	T value;
	std::cin >> value;
	heap_[i - 1] -= value;
	SiftUp(i - 1);
}

template<class T>
std::istream &operator>>(std::istream &in, BinaryHeap<T> &heap) {
	static std::unordered_map<std::string, typename BinaryHeap<T>::Mptr> operations = {
		{"insert", &BinaryHeap<T>::Insert},
		{"getMin", &BinaryHeap<T>::GetMin},
		{"extractMin", &BinaryHeap<T>::ExtractMin},
		{"decreaseKey", &BinaryHeap<T>::DecreaseKey}
	};
	int size = 0;
	std::cin >> size;
	int ip = 0;
	std::string tmp;
	while (ip < size) {
		std::cin >> tmp;
		(heap.*operations.at(tmp))();
		++ip;
	}
	return in;
}

template<class T>
void BinaryHeap<T>::SiftUp(int i) {
	while (i > 0 && heap_[i] < heap_[i / 2]) {
		std::swap(heap_[i], heap_[i / 2]);
		i /= 2;
	}
}

template<class T>
void BinaryHeap<T>::SiftDown(int i) {
	int j{-1};
	if (heap_.empty()) {
		return;
	}
#define left(i) (2 * (i))
#define right(i) (2 * (i) + 1)

	while (left(i) <= heap_.size() - 1) {
		if (heap_[left(i)] < heap_[i]) {
			j = left(i);
		}
		if (right(i) <= (heap_.size() - 1) && heap_[right(i)] < heap_[i] &&
			(j == -1 || heap_[right(i)] < heap_[left(i)])) {
			j = right(i);
		}
		if (j == -1) {
			break;
		} else {
			std::swap(heap_[i], heap_[j]);
			i = j;
		}
	}

#undef left
#undef right
}

int main() {
	try {
		BinaryHeap<int> heap;
		std::cin >> heap;
	}
	catch (const std::exception &ex) {
		std::cout << ex.what();
	}
	return 0;
}

