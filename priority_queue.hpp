#ifndef _PRIORITY_QUEUE_HPP
#define _PRIORITY_QUEUE_HPP

#include <vector>
#include <functional>

using T = double;
using Container = std::vector<T>;
using Compare = std::less<T>;

class Priorty_queue {
public:
  typedef Container     container_type;
  typedef typename      container_type::value_type value_type;
  typedef typename      container_type::reference reference;
  typedef typename      container_type::const_reference const_reference;
  typedef typename      container_type::size_type size_type;

public:
  const_reference top() const;
  bool empty() const;
  size_type size() const;
  void push(const value_type& value);
  void pop();

private:
  // TODO
}; // TODO

#endif