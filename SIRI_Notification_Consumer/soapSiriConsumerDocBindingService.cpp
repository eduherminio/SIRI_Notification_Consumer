/* soapSiriConsumerDocBindingService.cpp
   Generated by gSOAP 2.8.50 for SIRI.h

gSOAP XML Web services tools
Copyright (C) 2000-2017, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#include "soapSiriConsumerDocBindingService.h"

SiriConsumerDocBindingService::SiriConsumerDocBindingService()
{	this->soap = soap_new();
	this->soap_own = true;
	SiriConsumerDocBindingService_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

SiriConsumerDocBindingService::SiriConsumerDocBindingService(const SiriConsumerDocBindingService& rhs)
{	this->soap = rhs.soap;
	this->soap_own = false;
}

SiriConsumerDocBindingService::SiriConsumerDocBindingService(struct soap *_soap)
{	this->soap = _soap;
	this->soap_own = false;
	SiriConsumerDocBindingService_init(_soap->imode, _soap->omode);
}

SiriConsumerDocBindingService::SiriConsumerDocBindingService(soap_mode iomode)
{	this->soap = soap_new();
	this->soap_own = true;
	SiriConsumerDocBindingService_init(iomode, iomode);
}

SiriConsumerDocBindingService::SiriConsumerDocBindingService(soap_mode imode, soap_mode omode)
{	this->soap = soap_new();
	this->soap_own = true;
	SiriConsumerDocBindingService_init(imode, omode);
}

SiriConsumerDocBindingService::~SiriConsumerDocBindingService()
{	if (this->soap_own)
		soap_free(this->soap);
}

void SiriConsumerDocBindingService::SiriConsumerDocBindingService_init(soap_mode imode, soap_mode omode)
{	soap_imode(this->soap, imode);
	soap_omode(this->soap, omode);
	static const struct Namespace namespaces[] = {
        {"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
        {"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
        {"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
        {"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
        {"ns4", "http://www.ifopt.org.uk/acsb", NULL, NULL},
        {"ns5", "http://datex2.eu/schema/2_0RC1/2_0", NULL, NULL},
        {"ns2", "http://www.siri.org.uk/siri", NULL, NULL},
        {"ns3", "http://www.ifopt.org.uk/ifopt", NULL, NULL},
        {"ns1", "http://wsdl.siri.org.uk", NULL, NULL},
        {NULL, NULL, NULL, NULL}
    };
	soap_set_namespaces(this->soap, namespaces);
}

void SiriConsumerDocBindingService::destroy()
{	soap_destroy(this->soap);
	soap_end(this->soap);
}

void SiriConsumerDocBindingService::reset()
{	this->destroy();
	soap_done(this->soap);
	soap_initialize(this->soap);
	SiriConsumerDocBindingService_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

#ifndef WITH_PURE_VIRTUAL
SiriConsumerDocBindingService *SiriConsumerDocBindingService::copy()
{	SiriConsumerDocBindingService *dup = SOAP_NEW_COPY(SiriConsumerDocBindingService);
	if (dup)
		soap_copy_context(dup->soap, this->soap);
	return dup;
}
#endif

SiriConsumerDocBindingService& SiriConsumerDocBindingService::operator=(const SiriConsumerDocBindingService& rhs)
{	if (this->soap != rhs.soap)
	{	if (this->soap_own)
			soap_free(this->soap);
		this->soap = rhs.soap;
		this->soap_own = false;
	}
	return *this;
}

int SiriConsumerDocBindingService::soap_close_socket()
{	return soap_closesock(this->soap);
}

int SiriConsumerDocBindingService::soap_force_close_socket()
{	return soap_force_closesock(this->soap);
}

int SiriConsumerDocBindingService::soap_senderfault(const char *string, const char *detailXML)
{	return ::soap_sender_fault(this->soap, string, detailXML);
}

int SiriConsumerDocBindingService::soap_senderfault(const char *subcodeQName, const char *string, const char *detailXML)
{	return ::soap_sender_fault_subcode(this->soap, subcodeQName, string, detailXML);
}

int SiriConsumerDocBindingService::soap_receiverfault(const char *string, const char *detailXML)
{	return ::soap_receiver_fault(this->soap, string, detailXML);
}

int SiriConsumerDocBindingService::soap_receiverfault(const char *subcodeQName, const char *string, const char *detailXML)
{	return ::soap_receiver_fault_subcode(this->soap, subcodeQName, string, detailXML);
}

void SiriConsumerDocBindingService::soap_print_fault(FILE *fd)
{	::soap_print_fault(this->soap, fd);
}

#ifndef WITH_LEAN
#ifndef WITH_COMPAT
void SiriConsumerDocBindingService::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this->soap, os);
}
#endif

char *SiriConsumerDocBindingService::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this->soap, buf, len);
}
#endif

void SiriConsumerDocBindingService::soap_noheader()
{	this->soap->header = NULL;
}

::SOAP_ENV__Header *SiriConsumerDocBindingService::soap_header()
{	return this->soap->header;
}

#ifndef WITH_NOIO
int SiriConsumerDocBindingService::run(int port)
{	if (!soap_valid_socket(this->soap->master) && !soap_valid_socket(this->bind(NULL, port, 100)))
		return this->soap->error;
	for (;;)
	{	if (!soap_valid_socket(this->accept()))
		{	if (this->soap->errnum == 0) // timeout?
				this->soap->error = SOAP_OK;
			break;
		}
		if (this->serve())
			break;
		this->destroy();
	}
	return this->soap->error;
}

#if defined(WITH_OPENSSL) || defined(WITH_GNUTLS)
int SiriConsumerDocBindingService::ssl_run(int port)
{	if (!soap_valid_socket(this->soap->master) && !soap_valid_socket(this->bind(NULL, port, 100)))
		return this->soap->error;
	for (;;)
	{	if (!soap_valid_socket(this->accept()))
		{	if (this->soap->errnum == 0) // timeout?
				this->soap->error = SOAP_OK;
			break;
		}
		if (this->ssl_accept() || this->serve())
			break;
		this->destroy();
	}
	return this->soap->error;
}
#endif

SOAP_SOCKET SiriConsumerDocBindingService::bind(const char *host, int port, int backlog)
{	return soap_bind(this->soap, host, port, backlog);
}

SOAP_SOCKET SiriConsumerDocBindingService::accept()
{	return soap_accept(this->soap);
}

#if defined(WITH_OPENSSL) || defined(WITH_GNUTLS)
int SiriConsumerDocBindingService::ssl_accept()
{	return soap_ssl_accept(this->soap);
}
#endif
#endif

int SiriConsumerDocBindingService::serve()
{
#ifndef WITH_FASTCGI
	this->soap->keep_alive = this->soap->max_keep_alive + 1;
#endif
	do
	{
#ifndef WITH_FASTCGI
		if (this->soap->keep_alive > 0 && this->soap->max_keep_alive > 0)
			this->soap->keep_alive--;
#endif
		if (soap_begin_serve(this->soap))
		{	if (this->soap->error >= SOAP_STOP)
				continue;
			return this->soap->error;
		}
		if ((dispatch() || (this->soap->fserveloop && this->soap->fserveloop(this->soap))) && this->soap->error && this->soap->error < SOAP_STOP)
		{
#ifdef WITH_FASTCGI
			soap_send_fault(this->soap);
#else
			return soap_send_fault(this->soap);
#endif
		}
#ifdef WITH_FASTCGI
		soap_destroy(this->soap);
		soap_end(this->soap);
	} while (1);
#else
	} while (this->soap->keep_alive);
#endif
	return SOAP_OK;
}

static int serve___ns1__NotifySubscriptionTerminated(struct soap*, SiriConsumerDocBindingService*);
static int serve___ns1__NotifyDataReady(struct soap*, SiriConsumerDocBindingService*);
static int serve___ns1__NotifyHeartbeat(struct soap*, SiriConsumerDocBindingService*);
static int serve___ns1__NotifyProductionTimetable(struct soap*, SiriConsumerDocBindingService*);
static int serve___ns1__NotifyEstimatedTimetable(struct soap*, SiriConsumerDocBindingService*);
static int serve___ns1__NotifyStopTimetable(struct soap*, SiriConsumerDocBindingService*);
static int serve___ns1__NotifyStopMonitoring(struct soap*, SiriConsumerDocBindingService*);
static int serve___ns1__NotifyVehicleMonitoring(struct soap*, SiriConsumerDocBindingService*);
static int serve___ns1__NotifyConnectionTimetable(struct soap*, SiriConsumerDocBindingService*);
static int serve___ns1__NotifyConnectionMonitoring(struct soap*, SiriConsumerDocBindingService*);
static int serve___ns1__NotifyGeneralMessage(struct soap*, SiriConsumerDocBindingService*);
static int serve___ns1__NotifyFacilityMonitoring(struct soap*, SiriConsumerDocBindingService*);
static int serve___ns1__NotifySituationExchange(struct soap*, SiriConsumerDocBindingService*);

int SiriConsumerDocBindingService::dispatch()
{	return dispatch(this->soap);
}

int SiriConsumerDocBindingService::dispatch(struct soap* soap)
{
	SiriConsumerDocBindingService_init(soap->imode, soap->omode);

	soap_peek_element(soap);
	if (!soap_match_tag(soap, soap->tag, "ns1:NotifySubscriptionTerminated"))
		return serve___ns1__NotifySubscriptionTerminated(soap, this);
	if (!soap_match_tag(soap, soap->tag, "ns1:NotifyDataReady"))
		return serve___ns1__NotifyDataReady(soap, this);
	if (!soap_match_tag(soap, soap->tag, "ns1:NotifyHeartbeat"))
		return serve___ns1__NotifyHeartbeat(soap, this);
	if (!soap_match_tag(soap, soap->tag, "ns1:NotifyProductionTimetable"))
		return serve___ns1__NotifyProductionTimetable(soap, this);
	if (!soap_match_tag(soap, soap->tag, "ns1:NotifyEstimatedTimetable"))
		return serve___ns1__NotifyEstimatedTimetable(soap, this);
	if (!soap_match_tag(soap, soap->tag, "ns1:NotifyStopTimetable"))
		return serve___ns1__NotifyStopTimetable(soap, this);
	if (!soap_match_tag(soap, soap->tag, "ns1:NotifyStopMonitoring"))
		return serve___ns1__NotifyStopMonitoring(soap, this);
	if (!soap_match_tag(soap, soap->tag, "ns1:NotifyVehicleMonitoring"))
		return serve___ns1__NotifyVehicleMonitoring(soap, this);
	if (!soap_match_tag(soap, soap->tag, "ns1:NotifyConnectionTimetable"))
		return serve___ns1__NotifyConnectionTimetable(soap, this);
	if (!soap_match_tag(soap, soap->tag, "ns1:NotifyConnectionMonitoring"))
		return serve___ns1__NotifyConnectionMonitoring(soap, this);
	if (!soap_match_tag(soap, soap->tag, "ns1:NotifyGeneralMessage"))
		return serve___ns1__NotifyGeneralMessage(soap, this);
	if (!soap_match_tag(soap, soap->tag, "ns1:NotifyFacilityMonitoring"))
		return serve___ns1__NotifyFacilityMonitoring(soap, this);
	if (!soap_match_tag(soap, soap->tag, "ns1:NotifySituationExchange"))
		return serve___ns1__NotifySituationExchange(soap, this);
	return soap->error = SOAP_NO_METHOD;
}

static int serve___ns1__NotifySubscriptionTerminated(struct soap *soap, SiriConsumerDocBindingService *service)
{	struct __ns1__NotifySubscriptionTerminated soap_tmp___ns1__NotifySubscriptionTerminated;
	soap_default___ns1__NotifySubscriptionTerminated(soap, &soap_tmp___ns1__NotifySubscriptionTerminated);
	if (!soap_get___ns1__NotifySubscriptionTerminated(soap, &soap_tmp___ns1__NotifySubscriptionTerminated, "-ns1:NotifySubscriptionTerminated", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->NotifySubscriptionTerminated(soap_tmp___ns1__NotifySubscriptionTerminated.ns1__NotifySubscriptionTerminated);
	if (soap->error)
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__NotifyDataReady(struct soap *soap, SiriConsumerDocBindingService *service)
{	struct __ns1__NotifyDataReady soap_tmp___ns1__NotifyDataReady;
	soap_default___ns1__NotifyDataReady(soap, &soap_tmp___ns1__NotifyDataReady);
	if (!soap_get___ns1__NotifyDataReady(soap, &soap_tmp___ns1__NotifyDataReady, "-ns1:NotifyDataReady", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->NotifyDataReady(soap_tmp___ns1__NotifyDataReady.ns1__NotifyDataReady);
	if (soap->error)
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__NotifyHeartbeat(struct soap *soap, SiriConsumerDocBindingService *service)
{	struct __ns1__NotifyHeartbeat soap_tmp___ns1__NotifyHeartbeat;
	soap_default___ns1__NotifyHeartbeat(soap, &soap_tmp___ns1__NotifyHeartbeat);
	if (!soap_get___ns1__NotifyHeartbeat(soap, &soap_tmp___ns1__NotifyHeartbeat, "-ns1:NotifyHeartbeat", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->NotifyHeartbeat(soap_tmp___ns1__NotifyHeartbeat.ns1__NotifyHeartbeat);
	if (soap->error)
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__NotifyProductionTimetable(struct soap *soap, SiriConsumerDocBindingService *service)
{	struct __ns1__NotifyProductionTimetable soap_tmp___ns1__NotifyProductionTimetable;
	soap_default___ns1__NotifyProductionTimetable(soap, &soap_tmp___ns1__NotifyProductionTimetable);
	if (!soap_get___ns1__NotifyProductionTimetable(soap, &soap_tmp___ns1__NotifyProductionTimetable, "-ns1:NotifyProductionTimetable", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->NotifyProductionTimetable(soap_tmp___ns1__NotifyProductionTimetable.ns1__NotifyProductionTimetable);
	if (soap->error)
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__NotifyEstimatedTimetable(struct soap *soap, SiriConsumerDocBindingService *service)
{	struct __ns1__NotifyEstimatedTimetable soap_tmp___ns1__NotifyEstimatedTimetable;
	soap_default___ns1__NotifyEstimatedTimetable(soap, &soap_tmp___ns1__NotifyEstimatedTimetable);
	if (!soap_get___ns1__NotifyEstimatedTimetable(soap, &soap_tmp___ns1__NotifyEstimatedTimetable, "-ns1:NotifyEstimatedTimetable", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->NotifyEstimatedTimetable(soap_tmp___ns1__NotifyEstimatedTimetable.ns1__NotifyEstimatedTimetable);
	if (soap->error)
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__NotifyStopTimetable(struct soap *soap, SiriConsumerDocBindingService *service)
{	struct __ns1__NotifyStopTimetable soap_tmp___ns1__NotifyStopTimetable;
	soap_default___ns1__NotifyStopTimetable(soap, &soap_tmp___ns1__NotifyStopTimetable);
	if (!soap_get___ns1__NotifyStopTimetable(soap, &soap_tmp___ns1__NotifyStopTimetable, "-ns1:NotifyStopTimetable", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->NotifyStopTimetable(soap_tmp___ns1__NotifyStopTimetable.ns1__NotifyStopTimetable);
	if (soap->error)
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__NotifyStopMonitoring(struct soap *soap, SiriConsumerDocBindingService *service)
{	struct __ns1__NotifyStopMonitoring soap_tmp___ns1__NotifyStopMonitoring;
	soap_default___ns1__NotifyStopMonitoring(soap, &soap_tmp___ns1__NotifyStopMonitoring);
	if (!soap_get___ns1__NotifyStopMonitoring(soap, &soap_tmp___ns1__NotifyStopMonitoring, "-ns1:NotifyStopMonitoring", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->NotifyStopMonitoring(soap_tmp___ns1__NotifyStopMonitoring.ns1__NotifyStopMonitoring);
	if (soap->error)
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__NotifyVehicleMonitoring(struct soap *soap, SiriConsumerDocBindingService *service)
{	struct __ns1__NotifyVehicleMonitoring soap_tmp___ns1__NotifyVehicleMonitoring;
	soap_default___ns1__NotifyVehicleMonitoring(soap, &soap_tmp___ns1__NotifyVehicleMonitoring);
	if (!soap_get___ns1__NotifyVehicleMonitoring(soap, &soap_tmp___ns1__NotifyVehicleMonitoring, "-ns1:NotifyVehicleMonitoring", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->NotifyVehicleMonitoring(soap_tmp___ns1__NotifyVehicleMonitoring.ns1__NotifyVehicleMonitoring);
	if (soap->error)
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__NotifyConnectionTimetable(struct soap *soap, SiriConsumerDocBindingService *service)
{	struct __ns1__NotifyConnectionTimetable soap_tmp___ns1__NotifyConnectionTimetable;
	soap_default___ns1__NotifyConnectionTimetable(soap, &soap_tmp___ns1__NotifyConnectionTimetable);
	if (!soap_get___ns1__NotifyConnectionTimetable(soap, &soap_tmp___ns1__NotifyConnectionTimetable, "-ns1:NotifyConnectionTimetable", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->NotifyConnectionTimetable(soap_tmp___ns1__NotifyConnectionTimetable.ns1__NotifyConnectionTimetable);
	if (soap->error)
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__NotifyConnectionMonitoring(struct soap *soap, SiriConsumerDocBindingService *service)
{	struct __ns1__NotifyConnectionMonitoring soap_tmp___ns1__NotifyConnectionMonitoring;
	soap_default___ns1__NotifyConnectionMonitoring(soap, &soap_tmp___ns1__NotifyConnectionMonitoring);
	if (!soap_get___ns1__NotifyConnectionMonitoring(soap, &soap_tmp___ns1__NotifyConnectionMonitoring, "-ns1:NotifyConnectionMonitoring", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->NotifyConnectionMonitoring(soap_tmp___ns1__NotifyConnectionMonitoring.ns1__NotifyConnectionMonitoring);
	if (soap->error)
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__NotifyGeneralMessage(struct soap *soap, SiriConsumerDocBindingService *service)
{	struct __ns1__NotifyGeneralMessage soap_tmp___ns1__NotifyGeneralMessage;
	soap_default___ns1__NotifyGeneralMessage(soap, &soap_tmp___ns1__NotifyGeneralMessage);
	if (!soap_get___ns1__NotifyGeneralMessage(soap, &soap_tmp___ns1__NotifyGeneralMessage, "-ns1:NotifyGeneralMessage", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->NotifyGeneralMessage(soap_tmp___ns1__NotifyGeneralMessage.ns1__NotifyGeneralMessage);
	if (soap->error)
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__NotifyFacilityMonitoring(struct soap *soap, SiriConsumerDocBindingService *service)
{	struct __ns1__NotifyFacilityMonitoring soap_tmp___ns1__NotifyFacilityMonitoring;
	soap_default___ns1__NotifyFacilityMonitoring(soap, &soap_tmp___ns1__NotifyFacilityMonitoring);
	if (!soap_get___ns1__NotifyFacilityMonitoring(soap, &soap_tmp___ns1__NotifyFacilityMonitoring, "-ns1:NotifyFacilityMonitoring", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->NotifyFacilityMonitoring(soap_tmp___ns1__NotifyFacilityMonitoring.ns1__NotifyFacilityMonitoring);
	if (soap->error)
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__NotifySituationExchange(struct soap *soap, SiriConsumerDocBindingService *service)
{	struct __ns1__NotifySituationExchange soap_tmp___ns1__NotifySituationExchange;
	soap_default___ns1__NotifySituationExchange(soap, &soap_tmp___ns1__NotifySituationExchange);
	if (!soap_get___ns1__NotifySituationExchange(soap, &soap_tmp___ns1__NotifySituationExchange, "-ns1:NotifySituationExchange", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->NotifySituationExchange(soap_tmp___ns1__NotifySituationExchange.ns1__NotifySituationExchange);
	if (soap->error)
		return soap->error;
	return soap_closesock(soap);
}
/* End of server object code */
