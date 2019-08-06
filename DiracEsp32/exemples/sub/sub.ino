/*Importa a biblioteca DiracEsp32.h para ser utilizada no projeto*/
#include <DiracEsp32.h>

/*Define os componentes*/
const char* WIFI = "SuaRedeAqui"; //Nome da rede Wifi
const char* PASS = "SuaSenhaAqui"; //Senha da rede Wifi
const char* BROKER = "mqtt.diractec.com.br"; //Broker no qual o dispositivo será conectado
uint16_t PORT = 1883; //Porta do broker
const char* TOPIC_SUB = "master"; //Tópico no qual será publicado os dados

/*Instancia os objetos*/
DiracEsp32 dirac; //Define o objeto DiracEsp32 como dirac

/*Função se setup principal*/
void setup() {

  Serial.begin(115200); //Define a comunicação serial com a taxa de 115200

  pinMode(2, OUTPUT);  //Define o pino 2 como saída

  /*Função de conexão no Wifi*/
  dirac.connect_wifi(WIFI, PASS);

  /*Função que inicia o OTA*/
  dirac.ota();

  /*Função que seta a conexão com o broker*/
  dirac.mqtt_set(BROKER, PORT);

  /*Para qualquer dispositivo se conectar ao broker, ele necessita de
    um ID único, a função mqtt_mac() define a MAC do dispositivo como ID
    garantindo assim que nunca haverá um ID repetido*/
  dirac.mqtt_mac();

  /*Seta o tópico para se inscrever*/
  dirac.mqtt_topic(TOPIC_SUB);

  /*Passa por parametro a função callback recebe*/
  dirac.mqtt_recebe(recebe);

  /*Função que efetivamente faz o dispositivo se conectar ao broker*/
  dirac.mqtt_connect();

  /*Se inscreve no tópico setado*/
  dirac.mqtt_topic_sub();
}
/*Função que é executada repetidamente*/
void loop() {
  /*Função obrigatória para manter a conexão com o broker*/
  dirac.mqtt_loop();
}
/*Função callback que recebe as mensagens*/
void recebe(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Received message"); //Printa na serial, "Received message"
  digitalWrite(2, HIGH); //Liga o led do pino 2 e seta o pino para nível alto
}
