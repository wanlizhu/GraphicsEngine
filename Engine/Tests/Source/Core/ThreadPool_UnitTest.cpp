#include <gtest/gtest.h>
#include <NTGS/Core/ThreadPool.h>

using namespace NTGS;

void FreeFunc(int& V) {
    V = 999;
}

TEST(Core_ThreadPool, Post_Task) {
    ThreadPool* Pool = ThreadPool::GetInstance();
    std::string Str;
    int X = 0;
    auto Result = Pool->Enqueue([](int Value) { return Value * 2; }, 12);
    auto Result3 = Pool->Enqueue(FreeFunc, X);


    EXPECT_TRUE(Result.get() == 24);
    EXPECT_TRUE(Pool->TaskCount() == 0);
    EXPECT_TRUE(Pool->WorkerCount() == std::thread::hardware_concurrency());

    Result3.get();
    EXPECT_EQ(X, 999);
}