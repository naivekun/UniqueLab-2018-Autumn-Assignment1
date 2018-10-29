# Assignment 1

祖传代码启动
> test case for set is from the old repository

## Usage
* 修改对应文件夹的hpp，添加自己定义的cpp
* 使用cmake 构建
  ```sh
  [-d build] && mkdir build
  cd build
  cmake ..
  ```
  当你实现特定容器后，若需要进行测试， 请进入build文件夹，并开启相应的cmake变量
  ```sh
  cmake .. -Dset_test=on
  # OR
  cmake .. -Dpri_test=on
  # OR
  cmake .. -Dset_test=on -Dpri_test=on
  ```
  运行build下的相应文件