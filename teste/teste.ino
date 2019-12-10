/**
   Projeto de controle autônomo de temperatura do galpão do aviário da zootecnia.
   @Authors: Derik, Cleiton, e as vezes, Caio.
   @Data: Oct, 2019
*/


/*OBS : qualquer código relacionado a válvula solenoide está comentado pois a mesma está em falta.
*/
//Carregando as bibliotecas
//=========================  Inclusão das bibliotecas  =======================================
 #include <DHT.h>
 #include <LiquidCrystal.h>
 #include <OneWire.h>
 #include <DallasTemperature.h>
//=======================  Constantes globais  ===============================================
 #define DHTPIN  10
 #define DHTPIN2 6
 #define ATUADOR A4
// #define ATUADORVALVULA A5
// #define DS18B20 A3

 #define selectButton A0
 #define buttonUp A2 
 #define buttonDown A1
 #define DHTTYPE DHT22   // Sensor DHT 22  (AM2302)
//======================= Inicialização dos sensores  ========================================
DHT dht(DHTPIN, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
//OneWire ourWire(DS18B20);
//DallasTemperature sensors(&ourWire);
//======================= Inicialização do display  ========================================

//Pinos do LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 9);
//======================= Variáveis globais  ========================================

 int menuSelection;        // Variável que indica qual o menu selecionado
 int selection;            // Variável que indica se está no modo de edição ou mostrar
 int ajusteTempAtivar;     // Temperatura de disparo do ventilador
 //int ajusteTempAtivarAgua; // Temperatura de disparo da solenoide
 //int estadoValvula;        // Estado atual da válvula
 int blinkCtr;             // Variável de controle para o blink
 
//=======================  Configurações iniciais  ===========================================
void setup()
{
  blinkCtr = 1;
  ajusteTempAtivar     = 20;
 // ajusteTempAtivarAgua = 20;
  menuSelection        =  0;
//  estadoValvula        =  0;
  
  Serial.begin(9600);
  pinMode(buttonUp, INPUT);
  pinMode(buttonDown, INPUT);
  //pinMode(ATUADORVALVULA, OUTPUT);
  
  //Inicializa o display
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.write("Aguarde....");
  delay(1500);
  lcd.clear();

  pinMode (ATUADOR,      OUTPUT);     //VENTILADOR
  //pinMode (ATUADOR,      OUTPUT);     // FUTURO VÁLVULO
  pinMode (buttonUp,     INPUT);
  pinMode (buttonDown,   INPUT);

  selection = 1;
  menuSelection = 2;
  dht.begin();
  dht2.begin();75;
}

void loop(){
 // lcd.clear();
  if (digitalRead(buttonUp)){
    if (menuSelection == 1 && selection == 0){ ajusteTempAtivar++;     }
//    else if (menuSelection == 3 && selection == 0){ ajusteTempAtivarAgua++; }
    else{ menuSelection ++; }
  }
  if (digitalRead(buttonDown)){
    if (menuSelection == 1 && selection == 0){ ajusteTempAtivar--;     }
//    else  if (menuSelection == 3 && selection == 0){ ajusteTempAtivarAgua--; }
    else{ menuSelection --; }
  }
  
  ArTempListener();

 
  if (digitalRead(selectButton)){
    if (menuSelection == 4){
//      Serial.println (estadoValvula); 
  //    if (estadoValvula == 0){ startValvula(); estadoValvula = 1; }
    //  else { stopValvula(); estadoValvula = 0; }
    }
    if (selection == 0){ selection = 1; }
    else{ selection = 0; }
  }
  menu();
  
  delay(200);
}
