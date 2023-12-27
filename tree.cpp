#include <iostream>

template <typename T> class Set {
private:
  struct Node {
    T value;
    Node *left;
    Node *right;
    Node *parent;
    ~Node() {
      delete left;
      delete right;
    }
    // Functions can be added if necessary
  };
  Node *root{};
  size_t size_{};

public:
  class iterator {
    Node *current;

  public:
    friend Set;
    using value_type = T;
    using reference = T &;
    using pointer = T *;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    iterator();
    iterator(Node *node) : current(node) {}
    reference operator*() { return current->value; }
    const pointer operator->() { return &(current->value); }
    const iterator operator++();
    iterator operator++(int);
    friend bool operator==(iterator lhs, iterator rhs) {
      return lhs.current == rhs.current;
    }
    friend bool operator!=(iterator lhs, iterator rhs) { return !(lhs == rhs); }
  };

  ~Set() { delete root; }
  iterator begin();

  iterator end() { return iterator(nullptr); };

  iterator find(const T &value);

  void insert(const T &value);
  void erase(iterator &pos);
  void print_inorder();
  void InorderWithNode(Node *node);
};

template <typename T>
const typename Set<T>::iterator Set<T>::iterator::operator++() {
  if (current->right != nullptr) {
    current = current->right;
    while (current->left != nullptr)
      current = current->left;
    return *this;
  } else {
    while (current->parent != nullptr && current->parent->left != current)
      current = current->parent;
    current = current->parent;
    return *this;
  }
}
template <typename T>
typename Set<T>::iterator Set<T>::iterator::operator++(int) {
  iterator temp = *this;
  ++*this;
  return temp;
}
template <typename T> typename Set<T>::iterator Set<T>::begin() {
  Node *current = root;
  while (current->left != nullptr)
    current = current->left;
  return iterator(current);
}

template <typename T> typename Set<T>::iterator Set<T>::find(const T &value) {
  Node *current = root;
  while (current != nullptr) {
    if (current->value > value)
      current = current->left;
    else if (current->value < value)
      current = current->right;
    else
      return iterator(current);
  }
  return iterator(nullptr);
}

template <typename T> void Set<T>::erase(iterator &pos) {
  if (pos.current == nullptr)
    return;
  --size_;
  if (pos.current->right != nullptr) {
    Node *temp = pos.current->right;
    while (temp->left != nullptr)
      temp = temp->left;
    // std::swap(pos.current->value, temp->value);
    if (pos.current->left != nullptr) {
      pos.current->left->parent = temp;
      temp->left = pos.current->left;
    }

    if (pos.current->right == temp) {
      temp->parent = pos.current->parent;
      if (temp->parent == nullptr)
        root = temp;
      else {
        if (pos.current->parent->left == pos.current)
          pos.current->parent->left = temp;
        else
          pos.current->parent->right = temp;
      }
      pos.current->left = nullptr;
      pos.current->right = nullptr;
      delete pos.current;
      return;
    }
    if (temp->right != nullptr) {
      temp->right->parent = temp->parent;
      temp->parent->left = temp->right;

    } else {
      temp->parent->left = nullptr;
    }

    temp->right = pos.current->right;
    pos.current->right->parent = temp;
    temp->parent = pos.current->parent;
    if (temp->parent == nullptr)
      root = temp;
    else {
      if (pos.current->parent->left == pos.current)
        pos.current->parent->left = temp;
      else
        pos.current->parent->right = temp;
    }
    pos.current->left = nullptr;
    pos.current->right = nullptr;
    delete pos.current;
    return;
  }
  if (pos.current->left != nullptr) {
    Node *temp = pos.current->left;
    while (temp->right != nullptr)
      temp = temp->right;
    // std::swap(pos.current->value, temp->value);
    if (pos.current->right != nullptr) {
      pos.current->right->parent = temp;
      temp->right = pos.current->right;
    }

    if (pos.current->left == temp) {
      temp->parent = pos.current->parent;
      if (temp->parent == nullptr)
        root = temp;
      else {
        if (pos.current->parent->left == pos.current)
          pos.current->parent->left = temp;
        else if (pos.current->parent->right == pos.current)
          pos.current->parent->right = temp;
      }
      pos.current->left = nullptr;
      pos.current->right = nullptr;
      delete pos.current;
      return;
    }
    if (temp->left != nullptr) {
      temp->left->parent = temp->parent;
      temp->parent->right = temp->left;

    } else {
      temp->parent->right = nullptr;
    }
    temp->left = pos.current->left;
    pos.current->left->parent = temp;
    temp->parent = pos.current->parent;
    if (temp->parent == nullptr) {
      root = temp;
    } else {
      if (pos.current->parent->left == pos.current)
        pos.current->parent->left = temp;
      else
        pos.current->parent->right = temp;
    }
    pos.current->left = nullptr;
    pos.current->right = nullptr;
    delete pos.current;
    return;
  }
  if (pos.current->parent == nullptr)
    root = nullptr;
  if (pos.current->parent->left == pos.current)
    pos.current->parent->left = nullptr;
  pos.current->parent->right = nullptr;
  pos.current->left = nullptr;
  pos.current->right = nullptr;
  delete pos.current;
  return;
}
int main() {
  Set<int> st;
  st.insert(1);
  st.insert(3);
  st.insert(5);
  st.insert(2);
  st.insert(4);

  auto it = st.find(3);
  st.erase(it);

  for (auto i : st) {
    std::cout << i << std::endl;
  }
}

template <typename T> void Set<T>::insert(const T &value) {
  Set<T>::Node *current = this->root;
  if (current == nullptr) {
    current = new Set<T>::Node();
    current->value = value;
    this->root = current;
    this->size_++;
    return;
  }

  while (true) {
    if (value < current->value) {
      if (current->left == nullptr) {
        current->left = new Set<T>::Node();
        current->left->value = value;
        current->left->parent = current;
        size_++;
        return;
      }
      current = current->left;
    } else if (value > current->value) {
      if (current->right == nullptr) {
        current->right = new Set<T>::Node();
        current->right->value = value;
        current->right->parent = current;
        size_++;
        return;
      }
      current = current->right;
    } else {
      return;
    }
  }
}

template <typename T> void Set<T>::print_inorder() {
  (*this).InorderWithNode(this->root);
}
template <typename T> void Set<T>::InorderWithNode(Node *node) {
  if (node == nullptr)
    return;
  InorderWithNode(node->left);
  std::cout << node->value << " ";
  InorderWithNode(node->right);
}
