#include <Application.hpp>
#include <TCPClient.hpp>

int main()
{
	Application app("45.32.144.87", 4242);
	app.Run();
}
