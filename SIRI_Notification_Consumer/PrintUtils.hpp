#pragma once

#include "soapSiriConsumerDocBindingService.h"
#include <boost/filesystem.hpp>

class PrintUtils
{
public:
	static void show_vehiclemonitoring(const ns1__WsVehicleMonitoringNotificationStructure& response)
	{
#ifdef UNICODE
		std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);
#else
		std::locale loc(std::locale::classic());
#endif

		_tstring path = _T("c:/temp/siri/sub_vehiclemonitoring.txt");
		const boost::filesystem::path p = path;

		_ofstream ofs(p.string(), std::ios::app);
		ofs.imbue(loc);



		ofs << "\n\n\n*****************************\n" << "Vehicle Monitoring subscription: " << std::endl << std::endl;

		if (response.ServiceDeliveryInfo->ProducerRef)
			ofs << "ProducerRef: " << response.ServiceDeliveryInfo->ProducerRef->__item << std::endl;
		if (response.ServiceDeliveryInfo->RequestMessageRef)
			ofs << "RequestMessageRef: " << response.ServiceDeliveryInfo->RequestMessageRef->__item << std::endl;
		if (response.ServiceDeliveryInfo->ResponseMessageIdentifier)
			ofs << "ResponseMessageIdentifier: " << response.ServiceDeliveryInfo->ResponseMessageIdentifier->__item << std::endl;
		if (response.ServiceDeliveryInfo->Address)
			ofs << "Address: " << response.ServiceDeliveryInfo->Address << std::endl;

		unsigned cont = 0;
		for (const auto& sub : response.Notification->VehicleMonitoringDelivery)
		{
			ofs << "sub #" << ++cont << ",  ";
			ofs << "valid until: " << GSOAP::to_ptime(*sub->ValidUntil) << std::endl;
			ofs << "SubscriptionRef:\t" << sub->SubscriptionRef->__item << std::endl;
			ofs << "SubscriberRef:\t" << sub->SubscriberRef->__item << std::endl;

			for (const auto& activity : sub->VehicleActivity)
			{
				ofs << std::endl;
				ofs << "LineRef: " << activity->MonitoredVehicleJourney.LineRef->__item << ", ";
				ofs << "DirectionRef: " << activity->MonitoredVehicleJourney.DirectionRef->__item << ", ";
				ofs << "VehicleJourneyName: " << activity->MonitoredVehicleJourney.VehicleJourneyName.front()->__item << std::endl;
				ofs << "Long. tramo: " << *activity->ProgressBetweenStops->LinkDistance << " m" << std::endl;
				ofs << "% Recorrido: " << *activity->ProgressBetweenStops->Percentage << " %" << std::endl;
				ofs << "Service ID: " << *activity->ItemIdentifier << " " << activity->VehicleMonitoringRef->__item << std::endl;
				boost::posix_time::time_duration delay = boost::posix_time::milliseconds(*activity->MonitoredVehicleJourney.Delay);
				ofs << "Delay: " << delay << std::endl;
				ofs << "Speed: " << *activity->MonitoredVehicleJourney.Velocity << " km/h - ";
				ofs << "Bearing: " << *activity->MonitoredVehicleJourney.Bearing << " degrees" << std::endl;
				for (const auto& future_stop : activity->MonitoredVehicleJourney.OnwardCalls->OnwardCall)
				{
					ofs << *future_stop->Order << ". ";
					ofs << future_stop->StopPointName.front()->__item << " - ";
					if (activity->MonitoredVehicleJourney.__VehicleActivityStructure_MonitoredVehicleJourney_sequence__&& activity->MonitoredVehicleJourney.__VehicleActivityStructure_MonitoredVehicleJourney_sequence__->HeadwayService == true)
					{
						ofs << future_stop->StopPointRef->__item << " - frequency: ";
						ofs << *future_stop->AimedHeadwayInterval / (1000 * 60) << " minutes" << std::endl;
					}
					else
					{
						ofs << future_stop->StopPointRef->__item << " -  from: ";
						ofs << GSOAP::to_ptime(*future_stop->AimedArrivalTime) << " to: ";
						ofs << GSOAP::to_ptime(*future_stop->AimedDepartureTime) << std::endl;
					}
				}
			}

			for (const auto& stopcandellation : sub->VehicleActivityCancellation)
			{

			}
			ofs << "\nResponse time: " << GSOAP::to_ptime(sub->ResponseTimestamp);
		}
	}

	static void show_stopmonitoring(const ns1__WsStopMonitoringNotificationStructure& response)
	{
#ifdef UNICODE
		std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);
#else
		std::locale loc(std::locale::classic());
#endif

		_tstring path = _T("c:/temp/siri/sub_stopmonitoring.txt");
		const boost::filesystem::path p = path;

		_ofstream ofs(p.string(), std::ios::app);
		ofs.imbue(loc);


		ofs << "\n\n\n*****************************\n" << "Stop Monitoring subscription: " << std::endl << std::endl;

		if (response.ServiceDeliveryInfo->ProducerRef)
			ofs << "ProducerRef: " << response.ServiceDeliveryInfo->ProducerRef->__item << std::endl;
		if (response.ServiceDeliveryInfo->RequestMessageRef)
			ofs << "RequestMessageRef: " << response.ServiceDeliveryInfo->RequestMessageRef->__item << std::endl;
		if (response.ServiceDeliveryInfo->ResponseMessageIdentifier)
			ofs << "ResponseMessageIdentifier: " << response.ServiceDeliveryInfo->ResponseMessageIdentifier->__item << std::endl;
		if (response.ServiceDeliveryInfo->Address)
			ofs << "Address: " << response.ServiceDeliveryInfo->Address << std::endl;

		unsigned cont = 0;
		for (const auto& sub : response.Notification->StopMonitoringDelivery)
		{
			ofs << "sub #" << ++cont << ",  ";
			ofs << "valid until: " << GSOAP::to_ptime(*sub->ValidUntil) << std::endl;
			ofs << "SubscriptionRef:\t" << sub->SubscriptionRef->__item << std::endl;
			ofs << "SubscriberRef:\t" << sub->SubscriberRef->__item << std::endl;
			for (const auto& stopvisit : sub->MonitoredStopVisit)
			{
				ofs << std::endl;
				ofs << "MonitoringRef: " << stopvisit->__MonitoredStopVisitStructure_sequence->MonitoringRef->__item << ", ";
				ofs << "LineRef: " << stopvisit->MonitoredVehicleJourney->LineRef->__item << ", ";
				ofs << "DirectionRef: " << stopvisit->MonitoredVehicleJourney->DirectionRef->__item << ", ";
				ofs << "VehicleJourneyName: " << stopvisit->MonitoredVehicleJourney->VehicleJourneyName.front()->__item << std::endl;

				ofs << *stopvisit->MonitoredVehicleJourney->MonitoredCall->Order << ". ";
				ofs << stopvisit->MonitoredVehicleJourney->MonitoredCall->StopPointName.front()->__item << " - ";
				if (stopvisit->MonitoredVehicleJourney->__MonitoredVehicleJourneyStructure_sequence__ && stopvisit->MonitoredVehicleJourney->__MonitoredVehicleJourneyStructure_sequence__->HeadwayService == true)
				{
					ofs << stopvisit->MonitoredVehicleJourney->MonitoredCall->StopPointRef->__item << " - frequency: ";
					ofs << *stopvisit->MonitoredVehicleJourney->MonitoredCall->AimedHeadwayInterval / (1000 * 60) << " minutes" << std::endl;
				}
				else
				{
					ofs << stopvisit->MonitoredVehicleJourney->MonitoredCall->StopPointRef->__item << " -  from: ";
					ofs << GSOAP::to_ptime(*stopvisit->MonitoredVehicleJourney->MonitoredCall->AimedArrivalTime) << " to: ";
					ofs << GSOAP::to_ptime(*stopvisit->MonitoredVehicleJourney->MonitoredCall->AimedDepartureTime) << std::endl;
				}

				boost::posix_time::time_duration delay = boost::posix_time::milliseconds(*stopvisit->MonitoredVehicleJourney->Delay);
				ofs << "delay: " << delay << std::endl;
			}

			for (const auto& stopcancellation : sub->MonitoredStopVisitCancellation)
			{

			}
			ofs << "\nResponse time: " << GSOAP::to_ptime(sub->ResponseTimestamp);
		}
	}

	static void show_stoptimetable(const ns1__WsStopTimetableNotificationStructure& response)
	{
#ifdef UNICODE
		std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);
#else
		std::locale loc(std::locale::classic());
#endif

		_tstring path = _T("c:/temp/siri/sub_stoptimetable.txt");
		const boost::filesystem::path p = path;

		_ofstream ofs(p.string(), std::ios::app);
		ofs.imbue(loc);


		ofs << "\n\n\n*****************************\n" << "Stop Timetable subscription: " << std::endl << std::endl;

		ofs << "Valid until: " << GSOAP::to_ptime(*response.Notification->StopTimetableDelivery->ValidUntil) << std::endl;
		for (const auto& stopvisit : response.Notification->StopTimetableDelivery->TimetabledStopVisit)
		{
			ofs << std::endl;
			ofs << "MonitoringRef: " << stopvisit->MonitoringRef->__item << ", ";
			ofs << "LineRef: " << stopvisit->TargetedVehicleJourney->LineRef->__item << ", ";
			ofs << "DirectionRef: " << stopvisit->TargetedVehicleJourney->DirectionRef->__item << std::endl;

			ofs << *stopvisit->TargetedVehicleJourney->TargetedCall->Order << ". ";

			if (stopvisit->TargetedVehicleJourney->__TargetedVehicleJourneyStructure_sequence__ &&
				true == stopvisit->TargetedVehicleJourney->__TargetedVehicleJourneyStructure_sequence__->HeadwayService)
			{
				ofs << stopvisit->TargetedVehicleJourney->TargetedCall->StopPointRef->__item << " - frequency: ";
				ofs << *stopvisit->TargetedVehicleJourney->TargetedCall->AimedHeadwayInterval / (1000 * 60) << " minutes" << std::endl;
			}
			else
			{
				ofs << stopvisit->TargetedVehicleJourney->TargetedCall->StopPointRef->__item << " -  from: ";
				ofs << GSOAP::to_ptime(*stopvisit->TargetedVehicleJourney->TargetedCall->AimedArrivalTime) << " to: ";
				ofs << GSOAP::to_ptime(*stopvisit->TargetedVehicleJourney->TargetedCall->AimedDepartureTime) << std::endl;
			}
		}

		for (const auto& stopcancellation : response.Notification->StopTimetableDelivery->TimetabledStopVisitCancellation)
		{

		}

		ofs << "\nResponse time: " << GSOAP::to_ptime(response.Notification->StopTimetableDelivery->ResponseTimestamp);
	}

	static void show_productiontimetable(const ns1__WsProductionTimetableNotificationStructure& response)
	{
#ifdef UNICODE
		std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);
#else
		std::locale loc(std::locale::classic());
#endif

		_tstring path = _T("c:/temp/siri/sub_productiontimetable.txt");
		const boost::filesystem::path p = path;

		_ofstream ofs(p.string(), std::ios::app);
		ofs.imbue(loc);


		ofs << "\n\n\n*****************************\n" << "Production Timetable subscription: " << std::endl << std::endl;

		int cont_line = 0;
		for (const auto& line : response.Notification->ProductionTimetableDelivery)
		{
			ofs << "Line number " << ++cont_line;
			ofs << "\t(valid until: " << GSOAP::to_ptime(*line->ValidUntil) << ")" << std::endl;
			for (const auto& trajectory : line->DatedTimetableVersionFrame)
			{
				ofs << "\nL" << trajectory->LineRef->__item << ", ";
				ofs << "Trajectory: " << trajectory->RouteRef->__item << ", ";
				ofs << "Direction: " << trajectory->DirectionRef->__item << std::endl;

				for (const auto& expedition : trajectory->DatedVehicleJourney)
				{
					ofs << "\nExpedition code: " << expedition->DatedVehicleJourneyCode << " - ";
					ofs << "(road to: " << expedition->DestinationDisplay[0]->__item << ")" << std::endl;

					for (const auto& stop : expedition->DatedCalls.DatedCall)
					{
						if (expedition->HeadwayService && *expedition->HeadwayService == true)
						{
							ofs << stop->StopPointRef->__item << " - frequency: ";
							ofs << *stop->AimedHeadwayInterval / (1000 * 60) << " minutes" << std::endl;
						}
						else
						{
							ofs << stop->StopPointRef->__item << " -  from: ";
							ofs << GSOAP::to_ptime(*stop->AimedArrivalTime) << " to: ";
							ofs << GSOAP::to_ptime(*stop->AimedDepartureTime) << std::endl;
						}
					}
				}
			}
		}

		ofs << "\nResponse time: " << GSOAP::to_ptime(response.ServiceDeliveryInfo->ResponseTimestamp) << std::endl;
	}

	static void show_estimatedtimetable(const ns1__WsEstimatedTimetableNotificationStructure& response)
	{
#ifdef UNICODE
		std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);
#else
		std::locale loc(std::locale::classic());
#endif

		_tstring path = _T("c:/temp/siri/sub_estimatedtimetable.txt");
		const boost::filesystem::path p = path;

		_ofstream ofs(p.string(), std::ios::app);
		ofs.imbue(loc);


		ofs << "\n\n\n*****************************\n" << "Estimated Timetable subscription: " << std::endl << std::endl;

		int cont_line = 0;
		for (const auto& line : response.Notification->EstimatedTimetableDelivery)
		{
			ofs << "Line number " << ++cont_line;
			ofs << "\t(valid until: " << GSOAP::to_ptime(*line->ValidUntil) << ")" << std::endl;
			for (const auto& trajectory : line->EstimatedJourneyVersionFrame)
			{
				for (const auto& expedition : trajectory->EstimatedVehicleJourney)
				{
					ofs << "\nExpedition code: " << expedition->VehicleJourneyRef->__item << " - " << std::endl;
					ofs << "From: " << expedition->OriginName.front()->__item << "(" << expedition->OriginRef->__item << ")" << std::endl;
					ofs << "To: " << expedition->DestinationName.front()->__item << "(" << expedition->DestinationRef->__item << ")" << std::endl;

					for (const auto& stop : expedition->EstimatedCalls->EstimatedCall)
					{
						if (expedition->__EstimatedVehicleJourneyStructure_sequence___->HeadwayService && expedition->__EstimatedVehicleJourneyStructure_sequence___->HeadwayService == true)
						{
							ofs << stop->StopPointRef->__item << " - frequency: ";
							ofs << *stop->AimedHeadwayInterval / (1000 * 60) << " minutes" << std::endl;
						}
						else
						{
							ofs << stop->StopPointRef->__item << " -  from: ";
							ofs << GSOAP::to_ptime(*stop->AimedArrivalTime) << " to: ";
							ofs << GSOAP::to_ptime(*stop->AimedDepartureTime) << std::endl;
						}
					}
				}
			}
		}

		ofs << "\nResponse time: " << GSOAP::to_ptime(response.ServiceDeliveryInfo->ResponseTimestamp) << std::endl;
	}
};
