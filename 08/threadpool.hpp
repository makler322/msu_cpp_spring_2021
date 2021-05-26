#pragma once
#include <vector>
#include <queue>
#include <functional>
#include <thread>
#include <future>
#include <iostream>
#include <condition_variable>



using namespace std;

enum class Error
{
    ThreadError
};

class ThreadPool
{
public:
    using thr_vec = vector<thread>;
    using func_queue = queue<function<void()>>;

    void working_with_thread()
    {
        while(my_flag)
        {
            unique_lock<mutex> lock(my_mutex);
            if (!my_queue.empty())
            {
                auto cur_goal = move(my_queue.front());
                my_queue.pop();
                lock.unlock();
                cur_goal();
            }
            else
            {
                for_queue.wait(lock, [this](){ return this->my_queue.empty(); });
            }
        }
    }


    explicit ThreadPool(size_t pool_size): my_flag(true)
    {
        for (size_t i = 0; i < pool_size; i++)
        {
            my_thr_vector.emplace_back([this]() { working_with_thread(); });
        }
    }


    template <class T, class... TArgs>
    auto exec(T func, TArgs... args) -> future<decltype(func(args...))>
    {
        using type_f = decltype(func(args...));
        auto goal = make_shared<packaged_task<type_f()>>(
            bind(forward<T>(func), forward<TArgs>(args)...)
        );
        unique_lock<mutex> lock(my_mutex);
        my_queue.emplace([goal]()
        {
            (*goal)();
        });
        if (!my_flag)
        {
            throw Error::ThreadError;
        }
        for_queue.notify_one();
        return goal->get_future();
    }


    ~ThreadPool()
    {
        my_flag = false;
        for_queue.notify_all();
        for (auto & i: my_thr_vector)
        {
            i.join();
        }
    }
private:
    thr_vec my_thr_vector;
    mutex my_mutex;
    func_queue my_queue;
    condition_variable for_queue;
    atomic_bool my_flag;
};