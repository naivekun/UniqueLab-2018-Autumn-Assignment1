#ifndef _SET_HPP
#define _SET_HPP

#include <functional>
using T = double;
using Compare = std::less<T>;

class Set {
public:
  typedef T                 key_type;
  typedef key_type&         reference;
  typedef const key_type&   const_reference;
  typedef size_t            size_type;
  typedef Compare           key_compare;

public:
  bool empty() const;
  size_type size() const;
  void clear();
  void insert(const key_type& key);
  size_type erase(const key_type& key);
  size_type count(const key_type& key);

private:
  // TODO
}; // TODO

#endif