#include "IInterfazSOAP.h"
#include "ConsumerService.h"

class NotificationConsumer :
	public IInterfazSOAP
{
public:
	NotificationConsumer(void) {}
	~NotificationConsumer(void) {}

	virtual int process(struct soap* _soap)		// Detect connections from clients
	{
		ConsumerService sl(_soap);
		return sl.dispatch();
	}
};