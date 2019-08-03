/*Importa a biblioteca DiracEsp32.h para ser utilizada no projeto*/
#include <DiracEsp32.h>

/*Define os componentes*/
const char* WIFI = "NomeDaSuaRedeAqui"; //Nome da rede Wifi
const char* PASS = "SenhaDaSuaRedeAqui"; //Senha da rede Wifi
const char* BROKER = "mqtt.diractec.com.br"; //Broker no qual o dispositivo será conectado
uint16_t PORT = 1883; //Porta do broker
const char* TOPIC_PUB = "master"; //Tópico no qual será publicado os dados

/*Instancia os objetos*/
DiracEsp32 dirac; //Define o objeto DiracEsp32 como dirac

/*Define as variáveis*/
int last_msg; //Define a variável de contagem de tempo

/*Função se setup principal*/
void setup() {
  
  Serial.begin(115200); ///Define a comunicação serial com a taxa de 115200

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

  /*Função que efetivamente faz o dispositivo se conectar ao broker*/
  dirac.mqtt_connect();

}

void loop() {

  /*Função chamada debouncing, é responsável por fazer a contagem do tempo para o envio de cada mensagem*/
  if(millis() - last_msg >= 10000){
    last_msg = millis();
    /*Função que publica a mensagem no tópico definido*/
    dirac.mqtt_publish(TOPIC_PUB, "Olá");
  }

  /*Função obrigatória para manter a conexão com o broker*/
  dirac.mqtt_loop();
}
