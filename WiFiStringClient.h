/*
 * WiFiStringClient.h
 *
 *  Created on: Mar 6, 2013
 *      Author: dkadish
 */

#ifndef WIFISTRINGCLIENT_H_
#define WIFISTRINGCLIENT_H_

#include "WiFiClient.h"

extern "C" {
#include "utility/wl_definitions.h"
#include "utility/wl_types.h"
#include "string.h"
#include "utility/debug.h"
}

class WiFiStringClient {
public:
	WiFiStringClient(uint8_t sock = MAX_SOCK_NUM);
	WiFiStringClient(WiFiClient& aClient, uint8_t sock = MAX_SOCK_NUM);

	virtual size_t writeString(String);
	virtual int available();
	virtual String readString();
	virtual int connect(IPAddress ip, uint16_t port) {
		return iClient->connect(ip, port);
	}
	;
	virtual int connect(const char *host, uint16_t port) {
		return iClient->connect(host, port);
	}
	;

	//friend class WiFiStringServer;
	String partialMessage;
	bool ffReceived;
	char z;
protected:
	WiFiClient* iClient;
private:
	static const unsigned char lineEnding;
};

#endif /* WIFISTRINGCLIENT_H_ */
