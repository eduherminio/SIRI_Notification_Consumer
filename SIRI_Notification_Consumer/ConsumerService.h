#pragma once

#include "stdsoap2.h"
#include "soapSiriConsumerDocBindingService.h"
#include <mutex>
#include <memory>

class ConsumerService :
	public SiriConsumerDocBindingService
{
public:
	ConsumerService();
	ConsumerService(struct soap*);
	virtual ~ConsumerService();

	virtual	SiriConsumerDocBindingService *copy() override { return new ConsumerService(*this); }

	// Only Consumer methods
	/// Web service one-way operation 'NotifySubscriptionTerminated' (return SOAP_OK (no response) or error code, or use send_NotifySubscriptionTerminated_empty_response())
	virtual int NotifySubscriptionTerminated(ns1__WsSubscriptionTerminatedNotificationStructure *ns1__NotifySubscriptionTerminated) override;
	/// Web service one-way operation 'NotifyDataReady' (return SOAP_OK (no response) or error code, or use send_NotifyDataReady_empty_response())
	virtual int NotifyDataReady(ns1__WsDataReadyNotificationStructure *ns1__NotifyDataReady) override;
	/// Web service one-way operation 'NotifyHeartbeat' (return SOAP_OK (no response) or error code, or use send_NotifyHeartbeat_empty_response())
	virtual int NotifyHeartbeat(ns1__WsHeartbeatNotificationStructure *ns1__NotifyHeartbeat) override;
	/// Web service one-way operation 'NotifyProductionTimetable' (return SOAP_OK (no response) or error code, or use send_NotifyProductionTimetable_empty_response())
	virtual int NotifyProductionTimetable(ns1__WsProductionTimetableNotificationStructure *ns1__NotifyProductionTimetable) override;
	/// Web service one-way operation 'NotifyEstimatedTimetable' (return SOAP_OK (no response) or error code, or use send_NotifyEstimatedTimetable_empty_response())
	virtual int NotifyEstimatedTimetable(ns1__WsEstimatedTimetableNotificationStructure *ns1__NotifyEstimatedTimetable) override;
	/// Web service one-way operation 'NotifyStopTimetable' (return SOAP_OK (no response) or error code, or use send_NotifyStopTimetable_empty_response())
	virtual int NotifyStopTimetable(ns1__WsStopTimetableNotificationStructure *ns1__NotifyStopTimetable) override;
	/// Web service one-way operation 'NotifyStopMonitoring' (return SOAP_OK (no response) or error code, or use send_NotifyStopMonitoring_empty_response())
	virtual int NotifyStopMonitoring(ns1__WsStopMonitoringNotificationStructure *ns1__NotifyStopMonitoring) override;
	/// Web service one-way operation 'NotifyVehicleMonitoring' (return SOAP_OK (no response) or error code, or use send_NotifyVehicleMonitoring_empty_response())
	virtual int NotifyVehicleMonitoring(ns1__WsVehicleMonitoringNotificationStructure *ns1__NotifyVehicleMonitoring) override;
	/// Web service one-way operation 'NotifyConnectionTimetable' (return SOAP_OK (no response) or error code, or use send_NotifyConnectionTimetable_empty_response())
	virtual int NotifyConnectionTimetable(ns1__WsConnectionTimetableNotificationStructure *ns1__NotifyConnectionTimetable) override;
	/// Web service one-way operation 'NotifyConnectionMonitoring' (return SOAP_OK (no response) or error code, or use send_NotifyConnectionMonitoring_empty_response())
	virtual int NotifyConnectionMonitoring(ns1__WsConnectionMonitoringNotificationStructure *ns1__NotifyConnectionMonitoring) override;
	/// Web service one-way operation 'NotifyGeneralMessage' (return SOAP_OK (no response) or error code, or use send_NotifyGeneralMessage_empty_response())
	virtual int NotifyGeneralMessage(ns1__WsGeneralMessageNotificationStructure *ns1__NotifyGeneralMessage) override;
	/// Web service one-way operation 'NotifyFacilityMonitoring' (return SOAP_OK (no response) or error code, or use send_NotifyFacilityMonitoring_empty_response())
	virtual int NotifyFacilityMonitoring(ns1__WsFacilityMonitoringNotificationStructure *ns1__NotifyFacilityMonitoring) override;
	/// Web service one-way operation 'NotifySituationExchange' (return SOAP_OK (no response) or error code, or use send_NotifySituationExchange_empty_response())
	virtual int NotifySituationExchange(ns1__WsSituationExchangeNotificationStructure *ns1__NotifySituationExchange) override;
};