#include "stdafx.h"
#include "ConsumerService.h"
#include "PrintUtils.hpp"

bool siri_proxy = false;
std::string proxy_host("localhost");
int proxy_port(8888);

ConsumerService::ConsumerService()
{
}

ConsumerService::ConsumerService(struct soap* _soap)
	: SiriConsumerDocBindingService(_soap)
{
	if (siri_proxy == true)
	{
		this->soap->proxy_host = proxy_host.c_str();
		this->soap->proxy_port = proxy_port;
	}
}

ConsumerService::~ConsumerService()
{
}

std::mutex m_lock;

// Implemented
/// Web service one-way operation 'NotifyProductionTimetable' (return SOAP_OK (no response) or error code, or use send_NotifyProductionTimetable_empty_response())
int ConsumerService::NotifyProductionTimetable(ns1__WsProductionTimetableNotificationStructure *ns1__NotifyProductionTimetable)
{
	assert(ns1__NotifyProductionTimetable->Notification != nullptr);

	std::unique_lock<std::mutex> lock(m_lock);
	PrintUtils::show_productiontimetable(*ns1__NotifyProductionTimetable);
	std::cout << boost::posix_time::second_clock::universal_time() << " - PT update received" << std::endl;

	return SOAP_OK;
}

/// Web service one-way operation 'NotifyEstimatedTimetable' (return SOAP_OK (no response) or error code, or use send_NotifyEstimatedTimetable_empty_response())
int ConsumerService::NotifyEstimatedTimetable(ns1__WsEstimatedTimetableNotificationStructure *ns1__NotifyEstimatedTimetable)
{
	assert(ns1__NotifyEstimatedTimetable->Notification != nullptr);

	std::unique_lock<std::mutex> lock(m_lock);
	PrintUtils::show_estimatedtimetable(*ns1__NotifyEstimatedTimetable);
	std::cout << boost::posix_time::second_clock::universal_time() << " - ET update received" << std::endl;

	return SOAP_OK;
}

/// Web service one-way operation 'NotifyStopTimetable' (return SOAP_OK (no response) or error code, or use send_NotifyStopTimetable_empty_response())
int ConsumerService::NotifyStopTimetable(ns1__WsStopTimetableNotificationStructure *ns1__NotifyStopTimetable)
{
	assert(ns1__NotifyStopTimetable->Notification != nullptr);

	std::unique_lock<std::mutex> lock(m_lock);
	PrintUtils::show_stoptimetable(*ns1__NotifyStopTimetable);
	std::cout << boost::posix_time::second_clock::universal_time() << " - ST update received" << std::endl;

	return SOAP_OK;
}

/// Web service one-way operation 'NotifyStopMonitoring' (return SOAP_OK (no response) or error code, or use send_NotifyStopMonitoring_empty_response())
int ConsumerService::NotifyStopMonitoring(ns1__WsStopMonitoringNotificationStructure *ns1__NotifyStopMonitoring)
{
	assert(ns1__NotifyStopMonitoring->Notification != nullptr);

	std::unique_lock<std::mutex> lock(m_lock);
	PrintUtils::show_stopmonitoring(*ns1__NotifyStopMonitoring);
	std::cout << boost::posix_time::second_clock::universal_time() << " - SM update received" << std::endl;

	return SOAP_OK;
}

/// Web service one-way operation 'NotifyVehicleMonitoring' (return SOAP_OK (no response) or error code, or use send_NotifyVehicleMonitoring_empty_response())
int ConsumerService::NotifyVehicleMonitoring(ns1__WsVehicleMonitoringNotificationStructure *ns1__NotifyVehicleMonitoring)
{
	assert(ns1__NotifyVehicleMonitoring->Notification != nullptr);

	std::unique_lock<std::mutex> lock(m_lock);
	PrintUtils::show_vehiclemonitoring(*ns1__NotifyVehicleMonitoring);
	std::cout << boost::posix_time::second_clock::universal_time() << " - VM update received" << std::endl;

	return SOAP_OK;
}

/// Web service one-way operation 'NotifySubscriptionTerminated' (return SOAP_OK (no response) or error code, or use send_NotifySubscriptionTerminated_empty_response())º
int ConsumerService::NotifySubscriptionTerminated(ns1__WsSubscriptionTerminatedNotificationStructure *ns1__NotifySubscriptionTerminated)
{
	assert(ns1__NotifySubscriptionTerminated->Notification != nullptr);

	for (const auto& terminatedSubscription : ns1__NotifySubscriptionTerminated->Notification->__SubscriptionTerminatedNotificationStructure_sequence)
	{
		std::wcout << "Subscription " << terminatedSubscription.SubscriptionRef->__item << " from " <<
			terminatedSubscription.SubscriberRef->__item << " ended" << std::endl;
	}

	return SOAP_OK;
}

// Not implemented
/// Web service one-way operation 'NotifyDataReady' (return SOAP_OK (no response) or error code, or use send_NotifyDataReady_empty_response())
int ConsumerService::NotifyDataReady(ns1__WsDataReadyNotificationStructure *ns1__NotifyDataReady)
{
	return SOAP_OK;
}
/// Web service one-way operation 'NotifyHeartbeat' (return SOAP_OK (no response) or error code, or use send_NotifyHeartbeat_empty_response())
int ConsumerService::NotifyHeartbeat(ns1__WsHeartbeatNotificationStructure *ns1__NotifyHeartbeat)
{
	return SOAP_OK;
}
/// Web service one-way operation 'NotifyConnectionTimetable' (return SOAP_OK (no response) or error code, or use send_NotifyConnectionTimetable_empty_response())
int ConsumerService::NotifyConnectionTimetable(ns1__WsConnectionTimetableNotificationStructure *ns1__NotifyConnectionTimetable)
{
	return SOAP_OK;
}
/// Web service one-way operation 'NotifyConnectionMonitoring' (return SOAP_OK (no response) or error code, or use send_NotifyConnectionMonitoring_empty_response())
int ConsumerService::NotifyConnectionMonitoring(ns1__WsConnectionMonitoringNotificationStructure *ns1__NotifyConnectionMonitoring)
{
	return SOAP_OK;
}
/// Web service one-way operation 'NotifyGeneralMessage' (return SOAP_OK (no response) or error code, or use send_NotifyGeneralMessage_empty_response())
int ConsumerService::NotifyGeneralMessage(ns1__WsGeneralMessageNotificationStructure *ns1__NotifyGeneralMessage)
{
	return SOAP_OK;
}
/// Web service one-way operation 'NotifyFacilityMonitoring' (return SOAP_OK (no response) or error code, or use send_NotifyFacilityMonitoring_empty_response())
int ConsumerService::NotifyFacilityMonitoring(ns1__WsFacilityMonitoringNotificationStructure *ns1__NotifyFacilityMonitoring)
{
	return SOAP_OK;
}
/// Web service one-way operation 'NotifySituationExchange' (return SOAP_OK (no response) or error code, or use send_NotifyFacilityMonitoring_empty_response())
int ConsumerService::NotifySituationExchange(ns1__WsSituationExchangeNotificationStructure *ns1__NotifySituationExchange)
{
	return SOAP_OK;
}