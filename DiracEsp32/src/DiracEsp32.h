/*********************************************************************************************************
**********************************************************************************************************
								Library: dirac-iot-esp32												**
								Organizacao: Dirac Tecnologias Inteligentes								**
								Autor: Eng. Mateus Domingues Dias										**
								Email: mateusxdias@gmail.com											**
								Release: 1																**
								Data do release 03/08/2019												**
**********************************************************************************************************/
/*********************************************************************************************************/

#ifndef _dirac_esp32_h
#define _dirac_esp32_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class DiracEsp32
{
 protected:

 public:
	 void mqtt_set(const char *BROKER_MQTT, uint16_t BROKER_PORT);
	 void ota();
	 void handle();
	 int connect_wifi(const char* SSID, const char* PASS);
	 void mqtt_connect();
	 bool mqtt_connected();
	 void mqtt_loop();
	 int mqtt_state();
	 void mqtt_publish(const char* TOPIC_PUBLISH, char *payload);
	 void mqtt_receive(void(*func)(char* topic, byte* payload, unsigned int length));
	 void mac_to_topic();
	 void ip_by_host(const char * host_name);
	 void mqtt_topic(const char *TOPIC_SUBSCRIBE);
	 void mqtt_topic_sub();
	 String ip();
	 String mqtt_mac();
};
#endif
