#include <iostream>
#include<vector>


using namespace std;

namespace custom_map {
	template<typename Key, typename Value>
	struct Pair {
		Key _key;
		Value _value;
		Pair() : _key(Key()), _value(Value()) {}
		Pair(Key key, Value val) : _key(key), _value(val) {}
	};
	template<typename Key, typename Value>
	struct Node {
		Node* _next;
		Pair<Key, Value> pair_data;
		Node(const Pair<Key, Value>& data, Node* next = nullptr) : pair_data(data), _next(next) {}
		Node() : pair_data(Pair<Key, Value>()), _next(nullptr) {}
	};
	template<typename Key, typename Value>
	class Map {
		vector<Node<Key, Value>*> _data;
		size_t size_fullness;
		size_t hash_function(const Key& key) {
			return static_cast<size_t>(key % _data.size());
		}

	public:
		Map(size_t size) : _data(size), size_fullness(0) {}
		~Map() {
			clear();
		}
		Map(const Map& a) : _data(a._data.size()), size_fullness(0) {
			size_t size = a._data.size();
			for (size_t i = 0; i < size; i++) {
				if (a._data[i]) {
					Node<Key, Value>* ptr = a._data[i];
					while (ptr) {
						insert(ptr->pair_data._key, ptr->pair_data._value);
						ptr = ptr->_next;
					}
				}
			}
		}
		void swap(Map& a) {
			std::swap(_data, a._data);
			std::swap(size_fullness, a.size_fullness);
		}
		Map& operator=(Map a) {
			swap(a);
			return *this;
		}
		void clear() {
			size_t size = _data.size();
			for (size_t i = 0; i < size; i++) {
				if (_data[i]) {
					Node<Key, Value>* head = _data[i];
					while (head) {
						Node<Key, Value>* temp = head;
						head = head->_next;
						delete temp;
					}
				}
			}
			_data.clear();
		}
		size_t count(Key key) const {
			return int(contains(key));
		}
		bool contains(Key key) {
			size_t index = hash_function(key);
			if (!_data[index]) {
				return false;
			}
			Node<Key, Value>* ptr = _data[index];
			while (ptr) {
				if (ptr->pair_data._key == key) {
					return true;
				}
				ptr = ptr->_next;
			}
			return false;
		}
		Value* search(const Key& key) {
			size_t index = hash_function(key);
			if (!_data[index]) {
				return nullptr;
			}
			Node<Key, Value>* ptr = _data[index];
			while (ptr) {
				if (ptr->pair_data._key == key) {
					return &ptr->pair_data._value;
				}
				ptr = ptr->_next;
			}
			return nullptr;
		}
		void print() const {
			size_t size = _data.size();
			for (size_t i = 0; i < size; i++) {
				if (_data[i]) {
					Node<Key, Value>* ptr = _data[i];
					while (ptr) {
						cout << ptr->pair_data._key << " : " << ptr->pair_data._value << endl;
						ptr = ptr->_next;
					}
				}
			}
		}
		void insert(const Key& key, const Value& value) {
			if (contains(key)) {
				return;
			}
			size_t index = hash_function(key);
			if (!_data[index]) {
				_data[index] = new Node<Key, Value>(Pair<Key, Value>(key, value));
			}
			else {
				Node<Key, Value>* newNode = new Node<Key, Value>(Pair<Key, Value>(key, value));
				newNode->_next = _data[index];
				_data[index] = newNode;
			}
			size_fullness++;
		}
		void insert_or_assign(const Key& key, const Value& value) {
			size_t index = hash_function(key);
			Node<Key, Value>* temp = _data[index];
			while (temp) {
				if (temp->pair_data._key == key) {
					temp->pair_data._value = value;
					return;
				}
				temp = temp->_next;
			}
			Node<Key, Value>* newNode = new Node<Key, Value>(Pair<Key, Value>(key, value));
			newNode->_next = _data[index];
			_data[index] = newNode;
			size_fullness++;
		}

		bool erase(Key key) {
			size_t index = hash_function(key);
			Node<Key, Value>* cur = _data[index];
			Node<Key, Value>* prev = nullptr;

			while (cur) {
				if (cur->pair_data._key == key) {
					if (prev) {
						prev->_next = cur->_next;
					}
					else {
						_data[index] = cur->_next;
					}
					delete cur;
					return true;
				}
				prev = cur;
				cur = cur->_next;
			}
			return false;
		}

	};
}