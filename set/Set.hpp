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
  Set();

private:
  // TODO
  struct TREE_NODE
  {
      key_type data;
      int color;
      struct TREE_NODE* left;
      struct TREE_NODE* right;
      //struct TREE_NODE* parent;
      TREE_NODE()
      {
          color=0;  //1-红色 0-黑色
      }
  };
  int total_data_count=0;
  struct TREE_NODE* root;
  struct TREE_NODE* rotate_left(struct TREE_NODE* head);
  struct TREE_NODE* rotate_right(struct TREE_NODE* head);
  void split_node(struct TREE_NODE* head);

}; // TODO

#endif