/*********************************************************************************************************
**********************************************************************************************************
								Library: DiracEsp32				    									**
								Organizacao: Dirac Tecnologias Inteligentes								**
								Autor: Eng. Mateus Domingues Dias										**
								Email: mateusxdias@gmail.com											**
								Release: 1																**
								Data do release 03/08/2019												**
**********************************************************************************************************/
/*********************************************************************************************************/
#include "DiracEsp32.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <ArduinoOTA.h>

const char *SSID_Class;
const char *PASS_Class;
char *ID_MQTT_Class;
const char *TOPIC_PUBLISH_Class;
const char *TOPIC_SUBSCRIBE_Class;
uint16_t BROKER_PORT_Class;
const char *BROKER_MQTT_Class;

String mac;
WiFiClient wifi_Client;
PubSubClient MQTT(wifi_Client);

void DiracEsp32::mqtt_set(const char *BROKER_MQTT, uint16_t BROKER_PORT)
{
	BROKER_PORT_Class = BROKER_PORT;
	BROKER_MQTT_Class = BROKER_MQTT;
	MQTT.setServer(BROKER_MQTT_Class, BROKER_PORT_Class);
}
void DiracEsp32::mqtt_topic(const char *TOPIC_SUBSCRIBE)
{
	TOPIC_SUBSCRIBE_Class = TOPIC_SUBSCRIBE;
}
void DiracEsp32::mqtt_topic_sub()
{
	MQTT.subscribe(TOPIC_SUBSCRIBE_Class);
}
void DiracEsp32::ota()
{
	ArduinoOTA.setPassword((const char *)"positiva_password");

	ArduinoOTA
		.onStart([]() {
			String type;
			if (ArduinoOTA.getCommand() == U_FLASH)
				type = "sketch";
			else
				type = "filesystem";
		})

		.onError([](ota_error_t error) {
			Serial.printf("Error[%u]: ", error);
			if (error == OTA_AUTH_ERROR)
				Serial.println("Auth Failed");
			else if (error == OTA_BEGIN_ERROR)
				Serial.println("Begin Failed");
			else if (error == OTA_CONNECT_ERROR)
				Serial.println("Connect Failed");
			else if (error == OTA_RECEIVE_ERROR)
				Serial.println("Receive Failed");
			else if (error == OTA_END_ERROR)
				Serial.println("End Failed");
		});

	ArduinoOTA.begin();
	Serial.println(WiFi.localIP());
}
void DiracEsp32::handle()
{
	ArduinoOTA.handle();
}
int DiracEsp32::connect_wifi(const char *SSID, const char *PASS)
{
	SSID_Class = SSID;
	PASS_Class = PASS;

	while (WiFi.status() != WL_CONNECTED)
	{
		WiFi.begin(SSID_Class, PASS_Class);
		Serial.print(".");
		delay(5000);
	}
	return WL_CONNECTED;
}
void DiracEsp32::mqtt_connect()
{
	if (!MQTT.connected())
	{

		Serial.print("Connecting to Broker MQTT: ");
		Serial.println(BROKER_MQTT_Class);
		if (!MQTT.connect(ID_MQTT_Class))
		{
			Serial.println("Connect fail");
			delay(1000);
		}
		else
		{

			Serial.println("Connected");
			delay(1000);
		}
	}
}
bool DiracEsp32::mqtt_connected()
{
	return MQTT.connected();
}
void DiracEsp32::mqtt_loop()
{
	MQTT.loop();
}
int DiracEsp32::mqtt_state()
{
	return MQTT.state();
}
void DiracEsp32::mqtt_publish(const char *TOPIC_PUBLISH, char *payload)
{
	TOPIC_PUBLISH_Class = TOPIC_PUBLISH;
	Serial.println(payload);
	MQTT.publish(TOPIC_PUBLISH_Class, payload);
}
void DiracEsp32::mqtt_recebe(void (*func)(char *topic, byte *payload, unsigned int length))
{
	MQTT.setCallback(func);
}
String DiracEsp32::ip()
{
	String _ip;
	_ip = WiFi.localIP().toString();
	return _ip;
}
String DiracEsp32::mqtt_mac()
{
	mac = WiFi.macAddress();
	ID_MQTT_Class = (char *)malloc(sizeof(char) * mac.length() + 1);
	for (int i = 0; i < mac.length(); i++)
	{
		ID_MQTT_Class[i] = mac.charAt(i);
	}
	ID_MQTT_Class[mac.length()] = '\0';
	return mac;
}
void DiracEsp32::mac_to_topic()
{
	TOPIC_SUBSCRIBE_Class = ID_MQTT_Class;
}
