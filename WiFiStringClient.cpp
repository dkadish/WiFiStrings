/*
 * WiFiStringClient.cpp
 *
 *  Created on: Mar 6, 2013
 *      Author: dkadish
 */

#include "WiFiStringClient.h"

const unsigned char WiFiStringClient::lineEnding = '\f';

WiFiStringClient::WiFiStringClient(uint8_t sock) {
	iClient = new WiFiClient(sock);
	partialMessage = String("");
	ffReceived = false;
	z = -1;
}


WiFiStringClient::WiFiStringClient(WiFiClient& aClient, uint8_t sock) {
	iClient = &aClient;
	partialMessage = String("");
	ffReceived = false;
	z = -1;
}


size_t WiFiStringClient::writeString(String str) {
	for( unsigned int i=0; i < str.length(); i++ ){
		if( iClient->write(str[i]) == 0){
			return 0;
		}
	}

	return iClient->write(WiFiStringClient::lineEnding);
}

int WiFiStringClient::available() {

	if( ffReceived ){ // If there is already a message, it's ready to be read.
		return partialMessage.length();
	}

	// Add to the message length and append to the message
	while(iClient->available() > 0){
		if( iClient->peek() == WiFiStringClient::lineEnding ){
			ffReceived = true;
			return partialMessage.length();
		}

		partialMessage += (char) iClient->read();
	}

	return 0;

//	while( iClient->available() > 0){
//		partialMessage += String((char) iClient->read());
//	}
//
//	return partialMessage.length();

/*
	int available = iClient->available();
	if( available > 0 ){//|| partialMessage.length() > 0){
		//partialMessage = String((char) WiFiClient::read());
		unsigned char buf[10];
		memset(buf, 0, sizeof(buf));
		z = WiFiClient::read(buf, sizeof(buf)-1);
		for( int i=0; i<sizeof(buf) && i<available ; i++){
			if(buf[i] == '\0')
				break;
//			char s[32];
//			itoa((int)buf[i], s, 10);
			partialMessage += buf[i];
			partialMessage += ',';
		}
	}

	return partialMessage.length();
	//return WiFiClient::available();
*/
}

String WiFiStringClient::readString() {
	if( available() > 0){
		ffReceived = false;
		String msg = partialMessage;
		partialMessage = String("");
		return msg;
	}

	return String("");
}
