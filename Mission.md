# UniqueLab 2018 Autumn Assignment 1

> How to define 'difficult'?

## Description

<<<<<<< HEAD
We expect you to implement three basic containers in C++ STL, set iiand priority queue.
=======
We expect you to implement two basic containers in C++ STL, set and priority queue.
>>>>>>> 050c39c9f19ddd0d0b71f814577a98ec12f6dbc2

The methods are given below, and you may have fun with them.

1. Set

   ```cpp
     bool empty() const;
     size_type size() const;
     void clear();
     void insert(const key_type& key);
     size_type erase(const key_type& key);
     size_type count(const key_type& key);
   ```

2. Priority Queue

   ```cpp
     const_reference top() const;
     bool empty() const;
     size_type size() const;
     void push(const value_type& value);
     void pop();
   ```

To make your task easier, we have simplified the promblem, which means you don't need to implement a template or an iterator.  What may help is in this [repository](https://github.com/ThinCats/UniqueLab-2018-Autumn-Assignment1)

## Requirements

1. You **are asked to** use **LLRB** as the internal DS for set, and **Heap** for priority queue.
2. You should ensure that your implemention could pass all test-cases.

## Specifications

* **Programming Language**: It's recommended to use C++ as your programming launguage.

* **CodeStyle**:  It's necessary to keep a good codestyle.  The [Google Coding Style Guide](https://google.github.io/styleguide/cppguide.html#C++_Version) may help.

* **Submisson**:  To submit your work, you may fork this [repository](https://github.com/ThinCats/UniqueLab-2018-Autumn-Assignment1), and create a unique branch. Every time you commit and push your code, you'll need to make a pull request for mentors to review your code.

## Evaluation

* **Basic**: 
  * Passing all test-cases
* **Advance**:
<<<<<<< HEAD
  * Implement the templates
  * Implement the iterators
  * Help us to improve the test-case
=======
  * Not using recursion in **LLRB**
  * Implementing the templates
  * Help us to improve the test-cases
>>>>>>> 050c39c9f19ddd0d0b71f814577a98ec12f6dbc2

## Reference

[Learn C++ in Y minutes](https://learnxinyminutes.com/docs/c++/)

[Left Leaning Red-Black Trees, Princeton](https://www.cs.princeton.edu/~rs/talks/LLRB/RedBlack.pdf)

[Priority Queue](https://en.wikipedia.org/wiki/Priority_queue)

[GNU libstdc++](https://gcc.gnu.org/onlinedocs/libstdc++/)

