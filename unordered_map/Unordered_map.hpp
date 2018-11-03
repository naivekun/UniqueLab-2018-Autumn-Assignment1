#ifdef TEST_DEBUG
#define _UNORDERD_MAP_HPP
#include <unordered_map>
#include <string>
typedef typename std::unordered_map<std::string, double> Unordered_map;
#endif // DEBUG

#ifndef _UNORDERD_MAP_HPP
#define _UNORDERD_MAP_HPP

#include <string>
using Key = std::string;
using T = double;

class Unordered_map {

public:
  typedef Key             key_type;
  typedef T               mapped_type;
  typedef key_type&       reference;
  typedef const key_type& const_reference;
  typedef std::pair<const key_type, mapped_type> value_type;
  typedef size_t          size_type;

public:
  bool empty() const;
  size_type size() const;
  void clear();
  void insert(const value_type& value);
  void erase(const key_type& key);
  T& at(const Key& key);
  size_type count(const Key& key);

private:
  // TODO
  const int const_hash_value=43853;
  int total_value_count=0;

  struct LIST_NODE
  {
      key_type key_data;
      mapped_type mapped_data;
      struct LIST_NODE* next;
  };

  struct HASH_TABLE
  {
      key_type key_data;
      mapped_type mapped_data;
      struct LIST_NODE* first=NULL;
      int key_value_count=0;
      HASH_TABLE()
      {
          first=NULL;
          key_value_count=0;
      }
  }hash_table[43853];
  
  void delete_list(struct LIST_NODE* list_begin);
  int hash_func(key_type key);
}; // TODO
#endif
