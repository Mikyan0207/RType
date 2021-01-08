#include <Threads/ThreadPool.hpp>

/// <summary>
/// Initialize ThreadPool.
/// </summary>
/// <param name="size">Size of the pool.</param>
ThreadPool::ThreadPool(const std::size_t& size)
{
	m_IsRunning = false;
	m_Size = size;
	m_Threads.reserve(size);
}

/// <summary>
/// Notify and stop all threads.
/// </summary>
ThreadPool::~ThreadPool()
{
	Stop();
}

/// <summary>
/// Start threads.
/// </summary>
void ThreadPool::Run()
{
	m_IsRunning = true;

	for (std::size_t i = 0; i < m_Size; i += 1)
		m_Threads.emplace_back(std::async(std::launch::async, &ThreadPool::_ThreadRun, this));
}

/// <summary>
/// Stop all threads.
/// </summary>
void ThreadPool::Stop()
{
	m_IsRunning = false;
	m_Condition.notify_all();

	// May block the program...
	for (auto& future : m_Threads)
		future.get();
}

/// <summary>
/// Restart all threads
/// </summary>
void ThreadPool::Reset()
{
	Stop();
	Run();
}

/// <summary>
/// Add a new Task to the queue.
/// </summary>
/// <param name="task">A task to execute.</param>
void ThreadPool::Queue(ITask&& task)
{
	m_Tasks.Push(&task);
	m_Condition.notify_one();
}

void ThreadPool::AddThreads(const std::size_t& size)
{
	m_Size += size;

	for (std::size_t i = 0; i < size; i += 1)
		m_Threads.emplace_back(std::async(std::launch::async, &ThreadPool::_ThreadRun, this));
}

/// <summary>
/// Function used for thread.
/// </summary>
/// yerim la pute de merde 
void ThreadPool::_ThreadRun()
{
	while (m_IsRunning)
	{
		Pointer<ITask> task = nullptr;

		{
			std::unique_lock<std::mutex> lock(m_Mutex);

			m_Condition.wait(lock, [&]() -> bool
			{
				return !m_Tasks.IsEmpty();
			});

			task = m_Tasks.Front();
			m_Tasks.Pop();
		}

		if (task == nullptr)
			continue;

		task->Execute();
		delete task;
	}
}
