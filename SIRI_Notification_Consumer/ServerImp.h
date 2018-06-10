#pragma once

#include "stdsoap2.h"

#include "NotificationConsumer.h"
#include <mutex>
#include <atomic>
#include <memory>

class CServerImp
{
public:
	CServerImp(int poolSize);
	~CServerImp(void);

	void connect(int port);
	void disconnect();

	const bool get_m_safeOff() const { return m_safeOff; }
protected:
	void thReceiver();
	void process(struct soap* _soap);

private:
	mutable std::mutex m;

	int m_port;
	int m_poolsize;
	std::atomic_bool m_bFinalizarTh;
	std::atomic_bool m_safeOff;

	std::unique_ptr<NotificationConsumer> ptr_srv;

	std::thread m_th;

	SOAP_SOCKET m_socket;
};