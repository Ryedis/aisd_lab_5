#include <iostream>
#include <random>
#include <vector>

using namespace std;

namespace custom_map {
	const string CHARS = "abcdefghijklmnopqrstuvwxyz";

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
		Map(size_t size, size_t size_of_string) : _data(size), size_fullness(0) {
			random_device rd;
			mt19937 generator(rd());
			uniform_int_distribution<int> distribution(0, CHARS.size() - 1);
			for (size_t i = 0; i < size; i++)
			{
				string s = "";
				for (size_t j = 0; j < size_of_string; j++)
				{
					s += CHARS[distribution(generator)];
				}
				insert(i, s);
			}
		}
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
	const char T[256] = {
		0x01, 0x03, 0x05, 0x07, 0x09, 0x0B, 0x0D, 0x0F,
		0x11, 0x13, 0x15, 0x17, 0x19, 0x1B, 0x1D, 0x1F,
		0x21, 0x23, 0x25, 0x27, 0x29, 0x2B, 0x2D, 0x2F,
		0x31, 0x33, 0x35, 0x37, 0x39, 0x3B, 0x3D, 0x3F,
		0x41, 0x43, 0x45, 0x47, 0x49, 0x4B, 0x4D, 0x4F,
		0x51, 0x53, 0x55, 0x57, 0x59, 0x5B, 0x5D, 0x5F,
		0x61, 0x63, 0x65, 0x67, 0x69, 0x6B, 0x6D, 0x6F,
		0x71, 0x73, 0x75, 0x77, 0x79, 0x7B, 0x7D, 0x7F,
		0x81, 0x83, 0x85, 0x87, 0x89, 0x8B, 0x8D, 0x8F,
		0x91, 0x93, 0x95, 0x97, 0x99, 0x9B, 0x9D, 0x9F,
		0xA1, 0xA3, 0xA5, 0xA7, 0xA9, 0xAB, 0xAD, 0xAF,
		0xB1, 0xB3, 0xB5, 0xB7, 0xB9, 0xBB, 0xBD, 0xBF,
		0xC1, 0xC3, 0xC5, 0xC7, 0xC9, 0xCB, 0xCD, 0xCF,
		0xD1, 0xD3, 0xD5, 0xD7, 0xD9, 0xDB, 0xDD, 0xDF,
		0xE1, 0xE3, 0xE5, 0xE7, 0xE9, 0xEB, 0xED, 0xEF,
		0xF1, 0xF3, 0xF5, 0XF7, 0xF9, 0xFB, 0xFD, 0xFF
	};

	int pearson_hash(string s) {
		unsigned char hash_val = 0;
		for (char c : s) {
			hash_val = T[(hash_val ^ static_cast<unsigned char>(c)) & 0xFF];
		}
		return hash_val;
	}

	bool compare_string(int hash, string s) {
		return hash == pearson_hash(s);
	}
}