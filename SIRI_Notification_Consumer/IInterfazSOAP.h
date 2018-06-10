#pragma once

class IInterfazSOAP
{
public:
	IInterfazSOAP() {}
	virtual ~IInterfazSOAP() {}

	virtual int process(struct soap* _soap) = 0;
};
