# UniqueLab 2018 Autumn Assignment 1

> How to define 'difficult'?

## Description

We expect you to implement two basic containers in C++ STL, set iiand priority queue.

The methods are given below, and you can have fun with them.

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

Here, we simplify the promblem, you don't need to implement template or iterator.  What you need is in the [repository](https://github.com/ThinCats/UniqueLab-2018-Autumn-Assignment1)

## Requirement

1. You must use **LLRB** as internal DS for set, and **Heap** for priority queue.
2. Your implemention must pass all the test-case.

## Specifications

* **Programming Language**: It's recommended to use C++.

* **Coding Style**:  You should keep a good coding style.  The [Google Coding Style Guide](https://google.github.io/styleguide/cppguide.html#C++_Version) may help.

* **Submisson**:  You will fork this [repository](https://github.com/ThinCats/UniqueLab-2018-Autumn-Assignment1), and create a unique branch. Every time you commit and push your code, you'll need to make a pull request, for mentors code reviewing.

## Evaluation

* **Basic**: 
  * Pass all test-case
  * Not use recursive in **LLRB**
* **Advance**:
  * Implement the templates
  * Help us to improve the test-case

## Reference

[Learn C++ in Y minutes](https://learnxinyminutes.com/docs/c++/)

[Left Leaning Red-Black Trees, Princeton](https://www.cs.princeton.edu/~rs/talks/LLRB/RedBlack.pdf)

[Priority Queue](https://en.wikipedia.org/wiki/Priority_queue)

[GNU libstdc++](https://gcc.gnu.org/onlinedocs/libstdc++/)

