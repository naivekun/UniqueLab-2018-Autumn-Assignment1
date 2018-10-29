#include <queue>
#include <vector>
#include <random>
#include <iostream>
#include "../include/gtest/gtest.h"
#include "Priority_queue.hpp"

typedef typename Priority_queue::value_type value_type;

class queueTest : public testing::Test {
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

TEST_F(queueTest, random_small) {

    std::random_device rd;
    std::mt19937 e(rd());
    std::uniform_real_distribution<value_type> dis(0, 100);

    std::priority_queue<value_type, std::vector<value_type>> std_queue;
    Priority_queue custom_queue;

    for (unsigned i = 0; i != 100; ++i) {
        value_type num = dis(e);
        std_queue.push(num);
        custom_queue.push(num);
    }
    ASSERT_EQ(std_queue.size(), custom_queue.size());
    while (!std_queue.empty()) {
        ASSERT_EQ(std_queue.top(), custom_queue.top());
        std_queue.pop();
        custom_queue.pop();
    }
    ASSERT_EQ(custom_queue.size(), 0);
}

TEST_F(queueTest, random_large) {

    std::random_device rd;
    std::mt19937 e(rd());
    std::uniform_real_distribution<value_type> dis(0, 100);

    std::priority_queue<value_type, std::vector<value_type>> std_queue;
    Priority_queue custom_queue;

    for (unsigned i = 0; i != 500000; ++i) {
        value_type num = dis(e);
        std_queue.push(num);
        custom_queue.push(num);
    }

    ASSERT_EQ(std_queue.size(), custom_queue.size());
    while (!std_queue.empty()) {
        ASSERT_EQ(std_queue.top(), custom_queue.top());
        std_queue.pop();
        custom_queue.pop();
    }
    ASSERT_EQ(custom_queue.size(), 0);
}

TEST_F(queueTest, ordered_data) {
    std::priority_queue<value_type, std::vector<value_type>> std_queue;
    Priority_queue custom_queue;

    for (unsigned int i = 0; i != 100000; ++i) {
        std_queue.push(value_type(i));
        custom_queue.push(value_type(i));
        ASSERT_EQ(std_queue.top(), custom_queue.top());
    }
    ASSERT_EQ(std_queue.size(), custom_queue.size());
    while (!custom_queue.empty())
        custom_queue.pop();
    ASSERT_EQ(custom_queue.size(), 0);
}

TEST_F(queueTest, repeated_data) {
    std::priority_queue<value_type, std::vector<value_type>> std_queue;
    Priority_queue custom_queue;
    for (unsigned int i = 0; i != 100000; ++i) {
        std_queue.push(value_type(i));
        std_queue.push(value_type(i + 1));
        custom_queue.push(value_type(i));
        custom_queue.push(value_type(i + 1));
        ASSERT_EQ(std_queue.top(), custom_queue.top());
    }
    ASSERT_EQ(std_queue.size(), custom_queue.size());
    while (!custom_queue.empty())
        custom_queue.pop();
    ASSERT_EQ(custom_queue.size(), 0);
}

TEST_F(queueTest, random) {
    std::random_device rand_dev;
    std::default_random_engine e(rand_dev());
    std::uniform_real_distribution<value_type> dis(0, 100);

    std::priority_queue<value_type, std::vector<value_type>> std_queue;
    Priority_queue custom_queue;
    for (unsigned times = 0; times < 10; ++times) {
        for (unsigned i = 0; i != 80000; ++i) {
            double num = dis(e);
            std_queue.push(num);
            custom_queue.push(num);
        }

        ASSERT_EQ(std_queue.size(), custom_queue.size());

        while (!std_queue.empty())
            std_queue.pop();
        while (!custom_queue.empty())
            custom_queue.pop();
        ASSERT_EQ(std_queue.size(), 0);
        ASSERT_EQ(custom_queue.size(), 0);
    }
}

TEST_F(queueTest,ordered_big){
    Priority_queue custom_queue;
    for(unsigned i =0;i<1000000;i++){
        custom_queue.push((value_type(i)));
    }
    ASSERT_EQ(custom_queue.size(),1000000);
}

template <typename PriQueue>
void findKBig(std::vector<value_type> &in_data, int K, std::vector<value_type> &out_data, PriQueue& pri_queue) {
    for (auto ele: in_data) {
        pri_queue.push(ele);
    }

    for (int i=0; i < K; i++) {
        out_data.emplace_back(pri_queue.top());
        pri_queue.pop();
    }
}

TEST_F(queueTest, find_big) {
    std::random_device rd;
    std::mt19937 e(rd());
    std::uniform_real_distribution<value_type> dis(0, 100);

    std::vector<value_type> in_data;
    for (unsigned i=0; i < 100000; i++) {
        in_data.push_back(value_type(dis(e)));
    }
    std::vector<value_type> out_std;
    std::vector<value_type> out_custom;
    std::priority_queue<value_type, std::vector<value_type>> std_queue;
    Priority_queue custom_queue;

    findKBig(in_data, 200, out_std, std_queue);
    findKBig(in_data, 200, out_custom, custom_queue);
    ASSERT_EQ(std_queue.size(), custom_queue.size());

    for (unsigned i=0; i < out_std.size(); i++) {
        ASSERT_EQ(out_std[i], out_custom[i]);
    }
}