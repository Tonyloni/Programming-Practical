#include <vector>
#include <algorithm>
#include <iostream>

//T is the type of the element, K is the key, so the value that gets compared
template <typename T, typename K>
class PriorityQueue {
public:

    PriorityQueue() {}

  void insert(T element, K key) {
    heap_.push_back(Node(element, key));
    swiftUp(heap_.size() - 1);
  }

  T deleteMin() {
    if (heap_.empty()) {
        std::cout << "heap is empty" << std::endl;
    }
    T minElement = heap_[0].data;
    heap_[0] = heap_.back();
    heap_.pop_back();
    swiftDown(0);
    return minElement;
  }

  void decreaseKey(T element, K newKey) {
    auto it = std::find_if(heap_.begin(), heap_.end(),
      [&element](const Node& node) { return node.data == element; });
    if (it == heap_.end()) {
        std::cout << "element '" << element << "' is not in the heap" << std::endl;
    }
    it->key = newKey;
    swiftUp(std::distance(heap_.begin(), it));
  }

  bool isEmpty() const {
    return heap_.empty();
  }


  bool isElementOf(T element) {
    //see if element is contained in the PQ
    auto it = std::find_if(heap_.begin(), heap_.end(),
      [&element](const Node& node) { return node.data == element; });
    
    if (it == heap_.end()) {
        return false;
    }

    return true;
    }


private:
  struct Node {
    T data;
    K key;

    Node(T data, K key)
      : data(data), key(key) {}

    bool operator<(const Node& other) const {
      return key < other.key;
    }
  };

  std::vector<Node> heap_;

  void swiftUp(int index) {
    while (index > 0) {
      int parent = (index - 1) / 2;
      if (heap_[index] < heap_[parent]) {
        std::swap(heap_[index], heap_[parent]);
        index = parent;
      } else {
        break;
      }
    }
  }

  void swiftDown(int index) {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int smallest = index;
    if (leftChild < heap_.size() && heap_[leftChild] < heap_[smallest]) {
      smallest = leftChild;
    }
    if (rightChild < heap_.size() && heap_[rightChild] < heap_[smallest]) {
      smallest = rightChild;
    }
    if (smallest != index) {
      std::swap(heap_[index], heap_[smallest]);
      swiftDown(smallest);
    }
  }
};

