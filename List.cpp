#include <iostream>

template <typename T> class List {
  struct Node {
    T data;
    Node *next;
    Node *prev;
  };

  Node *head;
  Node *tail;
  std ::size_t size_;

public:
  class iterator {
    Node *current;

  public:
    using value_type = T;
    using reference = T &;
    using pointer = T *;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

    iterator(){};
    iterator(Node *node) : current(node) {}
    const reference operator*() const { return current->data; }
    reference operator*() { return current->data; }
    const pointer operator->() const { return &(current->data); }
    pointer operator->() { return &(current->data); }
    iterator &operator++();
    iterator operator++(int);
    iterator &operator--();
    iterator operator--(int);
    friend const bool operator==(iterator lhs, iterator rhs) {
      return lhs.current == rhs.current;
    }
    friend const bool operator!=(iterator lhs, iterator rhs) {
      return !(lhs == rhs);
    }
    friend class List;
  };

  List() {
    endnode = new Node;
    head = endnode;
    tail = endnode;
    endnode->next = head;
    endnode->prev = tail;
    size_ = 0;
  };
  List(size_t count, const T &value = T()) {

    if (count == 0) {
      List();
    } else {
      endnode = new Node;
      Node *node = new Node;
      node->data = value;
      node->prev = endnode;
      node->next = nullptr;
      head = node;
      for (size_t i = 1; i < count; i++) {
        Node *temp = new Node;
        temp->data = value;
        temp->prev = node;
        temp->next = nullptr;
        node->next = temp;
        node = temp;
      }
      tail = node;
      tail->next = endnode;
      endnode->next = head;
      endnode->prev = tail;
    }
  };
  List(const List &other) {
    if (other.head == other.endnode) {
      List();
    } else {
      endnode = new Node;
      size_ = other.size_;
      Node *node = new Node;
      node->data = other.head->data;
      node->prev = endnode;
      node->next = nullptr;
      head = node;
      for (Node *temp = other.head->next; temp != endnode; temp = temp->next) {
        Node *temp2 = new Node;
        temp2->prev = node;
        temp2->next = nullptr;
        temp2->data = temp->data;
        node->next = temp2;
        node = temp2;
      }
      tail = node;
      tail->next = endnode;
      endnode->next = head;
      endnode->prev = tail;
    }
  };
  List(List &&other) {
    head = std::move(other.head);
    tail = std::move(other.tail);
    size_ = std::move(other.size_);
    endnode = std::move(other.endnode);
  }
  List(std::initializer_list<T> ilist) {
    if (!(ilist.size()))
      List();
    else {
      endnode = new Node;
      size_ = ilist.size();
      Node *node = new Node;
      node->data = *(ilist.begin());
      node->prev = endnode;
      node->next = nullptr;
      head = node;
      typename std::initializer_list<T>::iterator it = ilist.begin();
      ++it;
      for (; it != ilist.end(); ++it) {
        Node *temp = new Node;
        temp->prev = node;
        temp->next = nullptr;
        temp->data = *it;
        node->next = temp;
        node = temp;
      }
      tail = node;
      tail->next = endnode;
      endnode->next = head;
      endnode->prev = tail;
    }
  }

  ~List() {
    while (head != endnode) {
      Node *temp = head;
      head = head->next;
      delete temp;
    }
    delete endnode;
  }

  List &operator=(const List &other);
  List &operator=(List &&other);
  List &operator=(std::initializer_list<T> ilist);

  // Element access
  T &front();
  const T &front() const;
  T &back();
  const T &back() const;

  // erase
  iterator erase(iterator pos);
  iterator erase(iterator first, iterator last);
  // Capacity
  bool empty() const;
  size_t size() const;

  // Modifiers
  iterator insert(iterator pos, const T &value);
  iterator insert(iterator pos, T &&value);
  iterator insert(iterator pos, std::initializer_list<T> ilist);

  void push_front(const T &value);
  void push_front(T &&value);
  void push_back(const T &value);
  void push_back(T &&value);

  void pop_front();
  void pop_back();

  // Iterators
  iterator begin() { return iterator(head); }
  iterator end() { return iterator(endnode); }
  // Comparison
  friend bool operator==(const List<T> &lhs, const List<T> &rhs);

private:
  Node *endnode;
};

// compraision operators for iterators
// template <typename T>
// const bool operator==(typename List<T>::iterator lhs,
//                       typename List<T>::iterator rhs) {
//   return lhs.current == rhs.current;
// }
// template <typename T>
// const bool operator!=(typename List<T>::iterator lhs,
//                       typename List<T>::iterator rhs) {
//   return !(lhs == rhs);
// }
// increment and decrement operators for iterators
template <typename T>
typename List<T>::iterator &List<T>::iterator::operator++() {
  current = current->next;
  return *this;
}
template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int) {
  iterator temp = *this;
  ++(*this);
  return temp;
}
template <typename T>
typename List<T>::iterator &List<T>::iterator::operator--() {
  current = current->prev;
  return *this;
}
template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int i) {
  iterator temp = *this;
  --(*this);
  return temp;
}
// operator =
template <typename T> List<T> &List<T>::operator=(List<T> &&other) {
  if (this == other)
    return *this;
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(size_, other.size_);
  std::swap(endnode, other.endnode);
  return *this;
}
template <typename T>
List<T> &List<T>::operator=(std::initializer_list<T> ilist) {
  List<T> temp(ilist);
  this->operator=(std::move(temp));
  return *this;
}
template <typename T> List<T> &List<T>::operator=(const List<T> &other) {
  if (this == &other)
    return *this;
  List<T> temp(other);
  this->operator=(std::move(temp));
  return *this;
}
// front and back
template <typename T> T &List<T>::front() { return head->data; }

template <typename T> const T &List<T>::front() const { return head->data; }
template <typename T> T &List<T>::back() { return tail->data; }

template <typename T> const T &List<T>::back() const { return tail->data; }

// empty and size
template <typename T> bool List<T>::empty() const { return size_ == 0; }

template <typename T> size_t List<T>::size() const { return size_; }

// erase
template <typename T>
typename List<T>::iterator List<T>::erase(typename List<T>::iterator pos) {
  if (pos == end())
    return pos;
  Node *temp = pos.current;
  pos.current->prev->next = pos.current->next;
  pos.current->next->prev = pos.current->prev;
  if (pos == begin())
    head = pos.current->next;
  if (pos.current == tail)
    tail = pos.current->prev;
  pos = pos.current->next;
  delete temp;
  size_--;
  return pos;
}
template <typename T>
typename List<T>::iterator List<T>::erase(typename List<T>::iterator first,
                                          typename List<T>::iterator last) {
  for (; first != last;) {
    auto temp = first;
    first++;
    erase(temp);
  }
  return last;
}

// modifers
template <typename T>
typename List<T>::iterator List<T>::insert(typename List<T>::iterator pos,
                                           const T &value) {
  List<T>::Node *new_node = new List<T>::Node;
  new_node->data = value;
  new_node->next = pos.current;
  new_node->prev = pos.current->prev;
  pos.current->prev->next = new_node;
  pos.current->prev = new_node;
  if (pos.current == head)
    head = new_node;
  if (pos.current == endnode)
    tail = new_node;
  ++size_;
  return new_node;
}
template <typename T>
typename List<T>::iterator List<T>::insert(typename List<T>::iterator pos,
                                           T &&value) {
  List<T>::Node *new_node = new List<T>::Node;
  new_node->data = std::move(value);
  new_node->next = pos.current;
  new_node->prev = pos.current->prev;
  pos.current->prev->next = new_node;
  pos.current->prev = new_node;
  if (pos.current == head)
    head = new_node;
  if (pos.current == endnode)
    tail = new_node;
  ++size_;
  return new_node;
}
template <typename T>
typename List<T>::iterator List<T>::insert(typename List<T>::iterator pos,
                                           std::initializer_list<T> ilist) {
  if (ilist.size() == 0)
    return pos;
  typename List<T>::iterator ret = insert(pos, *(ilist.begin()));
  auto it = ilist.begin();
  ++it;
  for (; it != ilist.end(); ++it) {
    insert(pos, *it);
  }
  return ret;
}

// push_back and push_front
template <typename T> void List<T>::push_front(const T &value) {
  List<T>::Node *new_node = new List<T>::Node;
  new_node->data = value;
  new_node->next = head;
  new_node->prev = endnode;
  endnode->next = new_node;
  head->prev = new_node;
  head = new_node;
}
template <typename T> void List<T>::push_front(T &&value) {
  List<T>::Node *new_node = new List<T>::Node;
  new_node->data = std::move(value);
  new_node->next = head;
  new_node->prev = endnode;
  endnode->next = new_node;
  head->prev = new_node;
  head = new_node;
}
template <typename T> void List<T>::push_back(const T &value) {
  List<T>::Node *new_node = new List<T>::Node;
  new_node->data = value;
  new_node->prev = tail;
  new_node->next = endnode;
  tail->next = new_node;
  endnode->prev = new_node;
  tail = new_node;
}
template <typename T> void List<T>::push_back(T &&value) {
  List<T>::Node *new_node = new List<T>::Node;
  new_node->data = std::move(value);
  new_node->prev = tail;
  new_node->next = endnode;
  tail->next = new_node;
  endnode->prev = new_node;
  tail = new_node;
}

// pop_front and pop_back
template <typename T> void List<T>::pop_back() {
  if (tail == endnode)
    return;
  endnode->prev = tail->prev;
  tail->prev->next = endnode;
  delete tail;
  tail = endnode->prev;
  --size_;
  if (tail == endnode)
    head = endnode;
}
template <typename T> void List<T>::pop_front() {
  if (head == endnode)
    return;
  endnode->next = head->next;
  head->next->prev = endnode;
  delete head;
  head = endnode->next;
  --size_;
  if (head == endnode)
    tail = endnode;
}

// compraison of List
template <typename T> bool operator==(const List<T> &l1, const List<T> &l2) {
  if (l1.size() != l2.size())
    return false;
  typename List<T>::Node *it1 = l1.head;
  typename List<T>::Node *it2 = l2.head;
  for (; it1 != l1.end(); ++it1, ++it2)
    if (it1->data != it2->data)
      return false;
  return true;
}

template <typename T> void particalsort(List<T> &l, T n) {
  typename List<T>::iterator left = l.begin();
  typename List<T>::iterator right = l.end();
  --right;
  while (left != right) {
    if (*left >= n) {
      std::swap(*left, *right);
      left++;
      if (left == right)
        break;
      right--;
      if (left == right)
        break;
    } else
      left++;
    if (left == right)
      break;
  }
}

void fuse_letters_to_big(List<char> &l) {
  typename List<char>::iterator it = l.begin();
  typename List<char>::iterator temp = it;
  it++;
  bool morethanone = false;
  while (it != l.end()) {
    if (*temp == *it) {
      l.erase(it++);
      morethanone = true;
      continue;
    } else if (morethanone) {
      *temp += 'A' - 'a';
      ++temp;
      morethanone = false;
    } else
      ++temp;
    ++it;
  }
}
int main() {
  // List<int> ilist{5, 8, 9, 7, 4, 45, 20, 1, 3, 2, 6};
  // particalsort(ilist, 7);
  List<char> ilist{'c', 'c', 'a', 'd', 'd', 'b', 'b', 'b', 't'};
  fuse_letters_to_big(ilist);
  for (auto it : ilist)
    std::cout << it << " ";

  return 0;
}
