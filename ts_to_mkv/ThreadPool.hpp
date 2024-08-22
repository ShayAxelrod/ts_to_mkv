#pragma once
#include <thread>
#include <vector>
#include <condition_variable>
#include <mutex>
#include <functional>
#include <queue>

class ThreadPool {
public:
	ThreadPool() {}

	~ThreadPool() {
		disable();
	}

	void enable(size_t num_of_threads = std::thread::hardware_concurrency()) {
		for (size_t i = 0; i < num_of_threads; ++i) {
			m_threads.emplace_back([this] {
				while (true) {
					std::function<void()> task;
					{
						std::unique_lock<std::mutex> lock(m_queue_mutex);
						m_cv.wait(lock, [this] {
							return !m_tasks.empty() || m_stop;
						});

						if (m_stop && m_tasks.empty()) return;

						task = std::move(m_tasks.front());
						m_tasks.pop();
					}
					task();
				}
			});
		}
	}

	void disable() {
		{
			std::unique_lock<std::mutex> lock(m_queue_mutex);
			m_stop = true;
		}
		m_cv.notify_all();
		for (auto& t : m_threads)
			t.join();
		m_threads.clear();
	}

	void queueTask(std::function<void()> task) {
		{
			std::unique_lock<std::mutex> lock(m_queue_mutex);
			m_tasks.emplace(std::move(task));
		}
		m_cv.notify_all();
	}

	bool busy() {
		bool pool_busy;
		{
			std::unique_lock<std::mutex> lock(m_queue_mutex);
			pool_busy = !m_tasks.empty();
		}
		return pool_busy;
	}

private:
	std::vector<std::thread> m_threads;
	std::queue<std::function<void()>> m_tasks;
	std::mutex m_queue_mutex;
	std::condition_variable m_cv;
	bool m_stop = false;;
};