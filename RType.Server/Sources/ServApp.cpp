#include <ServApp.hpp>

ServApp::ServApp()
{
    m_Server = CreateUnique<RType::TCPServer>(4242);
    m_ThreadPool = CreateShared<ThreadPool>(5);
}

ServApp::~ServApp()
{
}

void ServApp::Run()
{
    m_Server->Start();
}