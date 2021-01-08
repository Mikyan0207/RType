#pragma once
#include <queue>
#include <mutex>
#include <optional>

#include <Core.hpp>
#include <RType.Common.hpp>

template<class T>
class RTYPECOMMON_API SafeQueue
{
public:
	SafeQueue() = default;
	SafeQueue(const SafeQueue&) = default;
	SafeQueue(SafeQueue&&) noexcept = default;
	~SafeQueue() = default;

public:
	SafeQueue& operator=(const SafeQueue&) = default;
	SafeQueue& operator=(SafeQueue&&) noexcept = default;

public:
	void Push(const T& value)
	{
		std::scoped_lock<std::mutex> lock(m_Mutex);

		m_Queue.push(value);
	}

	void Push(T&& value)
	{
		std::scoped_lock<std::mutex> lock(m_Mutex);

		m_Queue.push(value);
	}

	void Emplace(const T& value)
	{
		std::scoped_lock<std::mutex> lock(m_Mutex);

		m_Queue.emplace(value);
	}

	void Emplace(T&& value)
	{
		std::scoped_lock<std::mutex> lock(m_Mutex);

		m_Queue.emplace(value);
	}

	void Pop()
	{
		std::scoped_lock<std::mutex> lock(m_Mutex);

		m_Queue.pop();
	}

	void Swap(std::queue<T>& queue)
	{
		std::scoped_lock<std::mutex> lock(m_Mutex);

		m_Queue.swap(queue);
	}

	T& Front()
	{
		std::scoped_lock<std::mutex> lock(m_Mutex);
		
		return m_Queue.front();
	}

	T& Back()
	{
		std::scoped_lock<std::mutex> lock(m_Mutex);

		return m_Queue.back();
	}

	std::deque<T>& AsDeque()
	{
		std::scoped_lock<std::mutex> lock(m_Mutex);

		return m_Queue.c;
	}

	std::size_t Size()
	{
		std::scoped_lock<std::mutex> lock(m_Mutex);

		return m_Queue.size();
	}

	bool IsEmpty()
	{
		std::scoped_lock<std::mutex> lock(m_Mutex);
		
		return m_Queue.empty();
	}
	
private:
	std::mutex m_Mutex;
	std::queue<T> m_Queue;
};
