#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <cassert>
#include <initializer_list>
template <typename T> class Vector {
private:
  size_t m_size;
  size_t capasity;
  T *arr;
  void copy(const Vector<T> &vec) {
    for (size_t i = 0; i < m_size; ++i)
      arr[i] = vec.arr[i];
  }

public:
  Vector() : capasity(10), m_size(0), arr(new T[capasity]) {}
  Vector(size_t num)
      : capasity(2 * num), m_size(num), arr(new T[capasity]{}) {}
  Vector(size_t num, T elem)
      : capasity(2 * num), m_size(num), arr(new T[capasity]{}) {
        for(size_t i=0; i< num; ++i)
          arr[i]=elem;
      }
  Vector(const Vector<T> &vec) : Vector(vec.m_size) { copy(vec); }
  Vector(Vector<T> &&vec): capasity(10), m_size(0), arr(new T[capasity])
  { 
    std::swap(arr, vec.arr);
    std::swap(capasity, vec.capasity);
    std::swap(m_size, vec.m_size);
  }
  Vector(std::initializer_list<T> list):Vector(list.size())
  {
      std::size_t count=0;
      for(std::initializer_list<int>::iterator it = list.begin(); it!=list.end(); ++it)
      {
          arr[count]= *it;
          ++count;
      }
  }
  ~Vector() { delete[] arr; }

  Vector<T>& operator=(const Vector<T>& other) {
    if (other.m_size <= capasity)
      m_size = other.m_size;
    else {
      capasity = 2 * other.m_size;
      m_size = other.m_size;
      delete[] arr;
      arr = new T[capasity];
    }
    for (size_t i = 0; i < m_size; ++i)
      arr[i] = other.arr[i];
    return *this;
  }
  Vector<T> &operator=(Vector<T> &&other) {
    if (arr == other.arr)
      return *this;
    delete[] arr;
    capasity = 10;
    m_size = 0;
    arr = new T[capasity];
    std::swap(capasity, other.capasity);
    std::swap(m_size, other.m_size);
    std::swap(arr, other.arr);
    return *this;
  }
 
  size_t size() const { return m_size; }
  size_t cap() const { return capasity; }

  bool empty() const { return m_size == 0; }
  const T &operator[](size_t index) const { return arr[index]; }
  T &operator[](size_t index) { return arr[index]; }
  const T &at(size_t index) const {
     assert(index<m_size);
      return arr[index];
  }
  T &at(size_t index) {
    assert(index<m_size);
      return arr[index];
  }
  void push_back(const T &x) {
    if (m_size >= capasity) {
      Vector<T> temp(m_size);
      temp = *this;
      std::swap(temp.arr, arr);
      std::swap(temp.m_size, m_size);
      std::swap(temp.capasity, capasity);
    }
    arr[m_size++] = x;
  }
  void push_back(T &&x) {
     if (m_size >= capasity) {
      Vector<T> temp(m_size);
      temp = *this;
      std::swap(temp.arr, arr);
      std::swap(temp.m_size, m_size);
      std::swap(temp.capasity, capasity);
    }
    arr[m_size++] = std::move(x);
  }
  void pop_back() {
    if (m_size)
      --m_size;
  }
  void clear() { m_size = 0; }
};

Vector<int> Multi(Vector<int>  vec)
{
  int left_score=1;
  int right_score=1;
  Vector<int> result(vec.size(), 1);
  for(std::size_t i =0; i<vec.size(); ++i)
  {
    result[i]*=left_score;
    left_score*= vec[i];
  }
  for(std::size_t i =vec.size()-1; i<vec.size(); --i)
  {
    result[i]*=right_score;
    right_score*= vec[i];
  }
  
  return result;
}
Vector<int> Lucky(Vector<Vector<int>>&vec)
{
    Vector<int> lucky_numbers;
    int max;
    int min;
    for(size_t i=0; i<vec.size(); ++i)
    {
      max = INT32_MIN;
      min = INT32_MAX;
      int index;
      for(size_t j =0; j<vec[i].size(); ++j)
      {
        if(min>vec[i][j])
        {
          min = vec[i][j];
          index = j;
        }
      }
      for(size_t z =0; z<vec.size(); ++z)
      {
        if(max<vec[z][index])
            max = vec[z][index];
      }
      if(min==max)
        lucky_numbers.push_back(min);
    }
    return lucky_numbers;
}
int main() 

{
  Vector<int> vec({1, 7, 5 ,8});
  Vector <int> vec2 = Multi(vec);
  for(std::size_t i =0; i<vec2.size(); ++i)
        std::cout<<vec2[i]<<" ";
  return 0;
}
