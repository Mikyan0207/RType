#pragma once
#include <future>
#include <mutex>
#include <vector>
#include <condition_variable>

#include <Core.hpp>
#include <RType.Common.hpp>

#include <Threads/ITask.hpp>
#include <Threads/SafeQueue.hpp>

class RTYPECOMMON_API ThreadPool
{
public:
	explicit ThreadPool(const std::size_t& size);
	ThreadPool(const ThreadPool&) = delete;
	ThreadPool(ThreadPool&&) = delete;
	~ThreadPool();

public:
	ThreadPool& operator=(const ThreadPool&) = delete;
	ThreadPool& operator=(ThreadPool&&) noexcept = delete;

public:
	void Run();
	void Stop();
	void Reset();
	void Queue(ITask&& task);
	void AddThreads(const std::size_t& size);

private:
	void _ThreadRun();

private:
	std::size_t m_Size;
	std::vector<std::future<void>> m_Threads;
	std::mutex m_Mutex;
	std::condition_variable m_Condition;
	SafeQueue<Pointer<ITask>> m_Tasks;
	bool m_IsRunning;
};