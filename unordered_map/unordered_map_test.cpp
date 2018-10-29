#include <unordered_map>
#include <vector>
#include <string>
#include <random>
#include <iostream>
#include "../include/gtest/gtest.h"
#include "Unordered_map.hpp"

typedef typename Unordered_map::mapped_type mapped_type;
typedef typename Unordered_map::key_type key_type;
typedef typename Unordered_map::value_type value_type;

class unorderedMapTest : public testing::Test {
protected:
    virtual void SetUp() {
        start_time = time(NULL);
    }

    virtual void TearDown() {
        time_t end_time = time(NULL);
        std::cout << "This test takes " << end_time-start_time << "times." << std::endl;
        ASSERT_TRUE(end_time - start_time <= 10) << "The test took too long.";
    }

    time_t start_time;
};

std::string genRandomStr(int num) {
    static std::random_device rd;
    static std::mt19937 e(rd());
    static std::uniform_int_distribution<int> dis('!', '~');

    std::string tmp;
    for (int i=0; i < num; i++)
        tmp.push_back(dis(e));
    return tmp;
}

TEST_F(unorderedMapTest, random_small) {

    std::random_device rd;
    std::mt19937 e(rd());
    std::uniform_real_distribution<mapped_type> dis(0, 100);

    std::unordered_map<key_type, mapped_type> std_map;
    Unordered_map custom_map;

    for (unsigned i = 0; i != 100; ++i) {
        key_type key = genRandomStr(int(i) % 5 + 1);
        mapped_type num = dis(e);
        std_map.insert(value_type(key, num));
        custom_map.insert(value_type(key, num));
    }
    ASSERT_EQ(std_map.size(), custom_map.size());
    for (auto &ele: std_map) {
        ASSERT_EQ(custom_map.count(ele.first), 1);
        custom_map.erase(ele.first);
    }
    ASSERT_EQ(custom_map.size(), 0);
}

TEST_F(unorderedMapTest, random_large) {

    std::random_device rd;
    std::mt19937 e(rd());
    std::uniform_real_distribution<mapped_type> dis(0, 100);

    std::unordered_map<key_type, mapped_type> std_map;
    Unordered_map custom_map;

    for (unsigned i = 0; i != 500000; ++i) {
        key_type key = genRandomStr(int(i) % 50 + 1);
        mapped_type num = dis(e);
        std_map.insert(value_type(key, num));
        custom_map.insert(value_type(key, num));
    }
    ASSERT_EQ(std_map.size(), custom_map.size());
    for (auto &ele: std_map) {
        ASSERT_EQ(custom_map.count(ele.first), 1);
        custom_map.erase(ele.first);
    }
    ASSERT_EQ(custom_map.size(), 0);
}

TEST_F(unorderedMapTest, only_data) {

    std::unordered_map<key_type, mapped_type> std_map;
    Unordered_map custom_map;
    std::string name("1");

    for (unsigned int i = 0; i != 100000; ++i) {
        std_map.insert(value_type(name, mapped_type(1)));
        custom_map.insert(value_type(name, mapped_type(1)));
    }
    ASSERT_EQ(std_map.size(), custom_map.size());
    ASSERT_EQ(custom_map.count(name), 1);
}

TEST_F(unorderedMapTest, ordered_data) {

    std::unordered_map<key_type, mapped_type> std_map;
    Unordered_map custom_map;

    for (unsigned i = 0; i != 100000; ++i) {
        auto key = std::to_string(i);
        mapped_type num = i;
        std_map.insert(value_type(key, num));
        custom_map.insert(value_type(key, num));
        ASSERT_EQ(custom_map.count(key), std_map.count(key));
    }
    ASSERT_EQ(std_map.size(), custom_map.size());
    for (auto &ele: std_map) {
        custom_map.erase(ele.first);
    }
    ASSERT_EQ(custom_map.size(), 0);
}

TEST_F(unorderedMapTest, repeated_data) {

    std::unordered_map<key_type, mapped_type> std_map;
    Unordered_map custom_map;

    for (unsigned i = 0; i != 100000; ++i) {
        auto key1 = std::to_string(i);
        auto key2 = std::to_string(i + 1);
        mapped_type num1 = i;
        mapped_type num2 = i + 1;
        std_map.insert(value_type(key1, num1));
        std_map.insert(value_type(key2, num2));
        custom_map.insert(value_type(key1, num1));
        custom_map.insert(value_type(key2, num2));
        ASSERT_EQ(custom_map.count(key1), std_map.count(key1));
        ASSERT_EQ(custom_map.count(key2), std_map.count(key2));
    }
    ASSERT_EQ(std_map.size(), custom_map.size());
    for (auto &ele: std_map) {
        custom_map.erase(ele.first);
    }
    ASSERT_EQ(custom_map.size(), 0);
}

TEST_F(unorderedMapTest, crossing_data) {

    std::unordered_map<key_type, mapped_type> std_map;
    Unordered_map custom_map;

    for (unsigned i = 1; i != 100000; ++i) {
        auto num = (long long)rand() * 100000;
        num %= i;
        auto key_to_del = std::to_string(num);
        auto key1 = std::to_string(i);
        auto key2 = std::to_string(-i);
        mapped_type num1 = i;
        mapped_type num2 = i + 1;

        std_map.insert(value_type(key1, num1));
        std_map.insert(value_type(key2, num2));
        std_map.erase(key_to_del);
        custom_map.insert(value_type(key1, num1));
        custom_map.insert(value_type(key2, num2));
        custom_map.erase(key_to_del);
        ASSERT_EQ(custom_map.count(key1), std_map.count(key1));
        ASSERT_EQ(custom_map.count(key2), std_map.count(key2));
    }
    ASSERT_EQ(std_map.size(), custom_map.size());
    for (auto &ele: std_map) {
        custom_map.erase(ele.first);
    }
    ASSERT_EQ(custom_map.size(), 0);
}

TEST_F(unorderedMapTest, random) {
    std::random_device rand_dev;
    std::default_random_engine e(rand_dev());
    std::uniform_real_distribution<mapped_type> dis(0, 100);

    std::unordered_map<key_type, mapped_type> std_map;
    Unordered_map custom_map;
    for (unsigned times = 0; times < 10; ++times) {
        for (unsigned i = 0; i != 80000; ++i) {
            mapped_type num = dis(e);
            auto key = genRandomStr(int(num) % 500 + 1);
            std_map.insert(value_type(key, num));
            custom_map.insert(value_type(key, num));
        }

        ASSERT_EQ(std_map.size(), custom_map.size());

        if (times % 2) {
            for (auto s:std_map) {
                custom_map.erase(s.first);
                ASSERT_EQ(custom_map.count(s.first), 0);
            }
            std_map.clear();
        } else {
            custom_map.clear();
            std_map.clear();
        }

        ASSERT_EQ(std_map.size(), 0);
        ASSERT_EQ(custom_map.size(), 0);
   }
}

TEST_F(unorderedMapTest, ordered_big){
    Unordered_map custom_map;
    for(unsigned i =0;i<1000000;i++){
        custom_map.insert(value_type(std::to_string(i), i));
    }
    ASSERT_EQ(custom_map.size(),1000000);
}