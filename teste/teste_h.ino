/* Esta função realiza uma operção básica de média aritmética
 *  entre dois numeros e retorna esse valor.
 *   @params :
 * Dois valores do tipo Float, onde cada um é o valor que os sensores estão lendo.
*/
float avarege(float a, float b){
  return (a+b)/2;
}

// ============================================================================================
/* Esta função é um Switch para navegar entre os menus mostrados no LCD.
 *  @params:
 *  NULL
*/
void menu(){
  switch(menuSelection){
    case -1: menuSelection = 1; break;
    case 0: TempAr();           break;
  //  case 1: TempAgua();         break;
    case 1: RegularAr();        break;
   // case 3: RegularAgua();      break;
   // case 4: AcionarValvula();   break;
    default: menuSelection = 0; break;
  }
}

// ============================================================================================
/* Esta função é um dos dados que estará amostra no display LCD,
 * O objetivo da mesma é mostrar qual é a temperatura da água que
 * o sensor DS18B20 está lendo.
 *  @params :
 *  NULL
*/

/*
void TempAgua(){
    sensors.requestTemperatures();
    lcd.setCursor(0, 0);
    lcd.print("[  Temp. Agua  ]");
    lcd.setCursor(5,1);
    lcd.print(sensors.getTempCByIndex(0));
}
*/

/*
float watherTempListener(){
  sensors.requestTemperatures();
  if (sensors.getTempCByIndex(0) > ajusteTempAtivarAgua){
    startValvula();
  }else{
    stopValvula();
  }
}
*/

// ============================================================================================
/* Esta função é um dos dados que estará amostra no display LCD,
 * O objetivo da mesma é mostrar qual é o valor que está selecionado para
 * e podendo fazer a regulagem desse valor. Onde o esse valor é o máximo 
 * que a temperatura do ar pode chegar antes de ligar o atuador.
 *  @params :
 *  NULL
*/
void RegularAr(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("[  Regular Ar  ]");
  lcd.setCursor(0,1);
  if (selection == 0){
    if (blinkCtr <= 2){
      manageDisplay(ajusteTempAtivar);
      blinkCtr ++; 
    }else{
      blinkCtr = 0; 
    }
  }else{
    manageDisplay(ajusteTempAtivar);
  }  
}

// ============================================================================================
/* Esta função é um dos dados que estará amostra no display LCD,
 * O objetivo da mesma é mostrar qual é o valor que está selecionado para
 * e podendo fazer a regulagem desse valor. Onde esse valor é o máximo que 
 * a temperatura da água pode chegar antes de ligar o atuador.
 *  @params :
 *  NULL
*/
void RegularAgua(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("[ Regular Agua ]");
  lcd.setCursor(0,1);
  if (selection == 0){
    if (blinkCtr <= 2){
//      manageDisplay(ajusteTempAtivarAgua);
      blinkCtr ++; 
    }else{
      blinkCtr = 0; 
    }
  }else{
//    manageDisplay(ajusteTempAtivarAgua);
  }  
}

// ============================================================================================
/*  Esta função é um dos dados que estará amostra no display LCD,
 * O objetivo da mesma é deixar o usuário acionar a válvula e informar
 * se a mesma está ligada ou desligada.

void AcionarValvula(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("[ Acionar Valv.]");
}
*/
// ============================================================================================
/* Esta função é uma função que o usuário não acessa,
 *  ela é chamada por outras funções mas o intuito dela é
 *  configurar o display para ser printado um valor em determinada posição do display
 *  @params :
 *  Um valor do tipo Float, que será o valor imprimido onde a função 
 *  está configurada no display
*/
float manageDisplay(float a){
  
  lcd.setCursor(5,1);
  lcd.print(a);
}

// ============================================================================================
/* Funçao que é chamada quando o sistema está com algum defeito quanto a leitura dos sensores.
 *  @parms :
 *  NULL
*/
void loadingScreen(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("Loading...");
} 

// ============================================================================================
/* Esta função tem o objetivo de verificar se os valores que os sensores individualmente
 *  está mandando é menor ou igual ao numero regulado pelo usuário nas funçoes de regulagem.
 *  @params :
 *  dois valores como parâmetros :
 *  valor float, é a temperatura dada pelos sensores.
 *  valor int é o numero que será passado para a verificar se o mesmo é maior que a leitura dos sensores.
*/
void isGreterThanNormal(float temp, int norm){
  if(temp >= norm)
    startAtuator();
  else
    stopAtuador();
}

// ============================================================================================
/*Esta função tem como objetivo desligar o ventilador e apagar o indicador que estará mostrando
 * que o mesmo está ligado.
 * @params :
 * NULL
*/
void stopAtuador(){
  digitalWrite(ATUADOR, LOW);
  lcd.setCursor(15,1);
  lcd.write(" ");
}

// ============================================================================================
/*Esta função tem como objetivo ligar o ventilador e mostrar o indicador que estará mostrando
 * que o mesmo está ligado.
 * @params :
 * NULL
*/
void startAtuator(){
  digitalWrite(ATUADOR, HIGH);
  lcd.setCursor(15, 1);
  lcd.write("*");
}



//  FUNÇOES VÁLVULA
// ============================================================================================
/*Esta função tem como objetivo desligar a válvula e mostrar no display que a mesma está desligada.
 * @params :
 * NULL
*/

/*
void stopValvula(){
  digitalWrite(ATUADORVALVULA, LOW);
  if (menuSelection == 4){
    lcd.setCursor(0, 1);
    lcd.write("    DESLIGADA");
  }
}
*/

// ============================================================================================
/*Esta função tem como objetivo ligar a válvula e mostrar no display que a mesma está ligada.
 * @params :
 * NULL
*/

/*
void startValvula(){
  digitalWrite(ATUADORVALVULA, HIGH);
  if (menuSelection == 4){
    lcd.setCursor(0, 1);
    lcd.write("    LIGADA");
  }
}
*/

// ============================================================================================
/* Esta função é um dos dados que estará amostra no display LCD,
 * O objetivo da mesma é mostrar qual é a temperatura do ar que
 * os sensores DHT 22 estão lendo.
 *  @params :
 *  NULL
*/
void TempAr(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("[   Temp. Ar   ]");
  manageDisplay(ArTempListener());
}


float ArTempListener(){
  //Leitura da temperatura 1 (Celsius)
  float temp1 = dht.readTemperature();
  
  //Leitura da temperatura 2 (Celsius)
  float temp2 = dht2.readTemperature();
  
  if(temp1>=0 && temp2>=0){

    float temp  = avarege(temp1, temp2);
    
    isGreterThanNormal(temp,ajusteTempAtivar);
    return temp;
  }
  else{
    loadingScreen();
  }
}

