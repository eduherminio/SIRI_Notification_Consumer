// SIRI_Notification_Consumer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ServerImp.h"

const int defaultPort = 8081;

int main(int argc, char* argv[])
{
	CServerImp srv(20);

	int connectionPort = argc == 2 ? atoi(argv[1]) : defaultPort;

	srv.connect(connectionPort);

	std::cout << "Awaiting info on http://localhost:" << connectionPort << std::endl;

	bool input;
	do
	{
		std::cin >> input;
	} while (input == true);

	srv.disconnect();

	while (true)
		if (srv.get_m_safeOff() == true)
			return 0;
}

