#include "stdafx.h"
#include "ServerImp.h"

#include "threadpool.hpp"

//Necesario este .nsmap para que se reconozcan los namespaces de SOAP
//Evitar WITH_NONAMESPACE, o las peticiones SOAP no se parsearan correctamente
//Evitar también soapcpp2 -n
#include "soap_srv.nsmap"

CServerImp::CServerImp(int poolSize)
	: m_poolsize(poolSize), m_port(8080), m_safeOff(false)
{
	ptr_srv.reset(new NotificationConsumer);
}

CServerImp::~CServerImp(void)
{
	if (m_th.joinable())
	{
		std::cout<<"Closing soap interface";

		m_bFinalizarTh = true;
		//Cerrar el socket
#ifdef _WIN32
		closesocket(m_socket);
#else
		close(m_socket);
#endif 
		m_th.join();
	}
}

void CServerImp::connect(int port)
{
	m_bFinalizarTh = false;
	m_port = port;
	m_th = std::thread((std::bind(&CServerImp::thReceiver, this)));
}

void CServerImp::disconnect()
{
	m_bFinalizarTh = true;
}

void CServerImp::thReceiver()
{
	boost::threadpool::fifo_pool tp(m_poolsize);

	struct soap *_soap = soap_new();

	{
#ifndef _WIN32
		//Establece un timeout de 1 segundo porque en linux close no cierra el socket master
		_soap->accept_timeout = 1;
#endif

		m_socket = soap_bind(_soap, NULL, m_port, 100);

		if (!soap_valid_socket(m_socket))
		{
			std::cout << "Error al hacer el bind al puerto " << m_port << std::endl;
			soap_destroy(_soap);
			soap_end(_soap);
			soap_free(_soap); // only safe when abc, uvw, xyz are also deleted 

			return;
		}

		while (m_bFinalizarTh == false)	// TO-CHECK
		{
			SOAP_SOCKET sock = soap_accept(_soap);

			if (m_bFinalizarTh == false && !soap_valid_socket(sock))
			{
				if (_soap->errnum != 0) //En Linux como accept_timeout = 1 cada segundo entra aquí, a pesar de no ser un error
					std::cout << "Error en soap_accept %d" << _soap->errnum << std::endl;
			}
			else
			{
				if (m_bFinalizarTh == false)
				{
					struct soap *_soapCopy = soap_copy(_soap);
					if (_soapCopy != nullptr)
					{
						typedef std::function<void()> void_function_t;
						void_function_t f = std::bind(&CServerImp::process, this, _soapCopy);
						tp.schedule(f);
					}
				}
			}
		}
	}

	tp.wait();
	tp.clear();

	soap_destroy(_soap);
	soap_end(_soap);
	soap_free(_soap); // only safe when abc, uvw, xyz are also deleted 

	std::cout<<"Closed soap interface";

	m_safeOff = true;
}


void CServerImp::process(struct soap* _soap)
{
	soap_set_namespaces(_soap, srv_namespaces);	// srv_namespaces defined in soap_srv.nsmap, won't work if not included

	int err = soap_begin_serve(_soap);
	if (err != SOAP_OK)
	{
		std::cout << "SOAP incoming call error " << _soap->errnum << std::endl;
	}
	else
	{
		 //if (ptr_srv->process(_soap) != SOAP_NO_METHOD)	TO-CHECK
			//break;

		ptr_srv->process(_soap);
	}

	soap_destroy(_soap);
	soap_end(_soap);
	soap_free(_soap);
}