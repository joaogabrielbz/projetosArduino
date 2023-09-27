//joaogabrielbz_//

#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#include <string.h>

// SERVOMOTORCONFIGS
Servo myservo;
const int FECHADO = 180;
const int ABERTO = 90;

// KEYPADCONFIGS
const byte LINHAS = 4; 
const byte COLUNAS = 4; 

char hexaKeys[LINHAS][COLUNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rPins[LINHAS] = {4, 5, 6, 7};
byte cPins[COLUNAS] = {8, 9, 10, 11};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rPins, cPins, LINHAS, COLUNAS);

//PAINELCONFIGS
LiquidCrystal lcd(37, 35, 33, 31, 29, 27);

//BOTAOCONFIGS
const int botao = 2;

//BUZZERCONFIGS
const int buzzer = 8;

//VARIAVEIS
String senha; //contém a senha atual
bool senhaCriada = false; //verifica se a senha está criada

//METODOS

//QUNADO A SENHA ESTÁ ERRADA:
void trancado(){ 
  //printa informações no cursor//
    lcd.setCursor(0,1);     
    lcd.print(">>ERRADO!");
    lcd.setCursor(11,1);
    lcd.print("(");
    lcd.setCursor(13,1);
    lcd.print(")");

    //conta de 9 à 0 e sai do método//
    for (int i = 9; i > 0; i--) { 
      lcd.setCursor(12,1);
      lcd.print(i);
      delay(1000);
  }
}

//QUANDO A SENHA ESTÁ CERTA:
void aberto(){ 
    //abre o servoMotor//
    myservo.write(ABERTO);

    //printa informações no cursor//
    lcd.setCursor(0,1);
    lcd.print(">>CORRETO");
    lcd.setCursor(11,1);
    lcd.print("(");
    lcd.setCursor(13,1);
    lcd.print(")");

    //conta de 9 à 0 e sai do método//
    for (int i = 9; i > 0; i--) { 
      lcd.setCursor(12,1);
      lcd.print(i);
      delay(1000);
  }
}

//QUANDO O BOTAOAMARELO FOR CLICADO (POR DENTRO DA PORTA) NO MENU:
void abertoPorDentro(){

  //abre o myservo//
  myservo.write(ABERTO);

  //pisca "aberto" na tela por 9s//
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.write(">>ABERTO<<");
  delay(300);
  lcd.clear();
  delay(300);
  lcd.setCursor(3,0);
  lcd.write(">>ABERTO<<");
  delay(300);
  lcd.clear();
  delay(300);
  lcd.setCursor(3,0);
  lcd.write(">>ABERTO<<");
  delay(7800);

  //fecha o myservo//
  myservo.write(FECHADO);

  //reescreve o texto do menu e sai do método//
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(">>(A) ABRIR");
  lcd.setCursor(0,1);
  lcd.print(">>(B) REDEFINIR");
  return(0);
}


//VERIFICA AS OPÇÕES: ABRIR, REDEFINIR OU ABRIR POR DENTRO:
bool menu(){
  //escreve o texto do menu//
  myservo.write(FECHADO);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(">>(A) ABRIR");
  lcd.setCursor(0,1);
  lcd.print(">>(B) REDEFINIR");

        //looping de verificação de opção//

         while(true) {
           char key = customKeypad.getKey();
           //abrir//
           if(key == 'A'){
             return false;
           }

           //trocar senha//
           if(key == 'B'){
             return true;
           }

           //aberto com botao//
           if(botaoClicado()){
             abertoPorDentro();
           }             
          }
}  

//ACIONADA NO SETUP PARA CRIAR A PRIMEIRA SENHA OBRIGATÓRIA:
String criaSenha(){

  //printa campo de inserção no cursor//
  lcd.setCursor(5,1);
  lcd.print("[____]");
  lcd.setCursor(6,1);

  //pega os caracteres e escreve (#) dentro do campo de inserção a cada clique//
  while(senha.length() < 4){
      char key = customKeypad.getKey();
         if(key >= '0' && key <= '9') {
          senha += key;
          lcd.print("#");
          }
        }

  //printa tela de carregamento//
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(">>SENHA CRIADA<<");
  lcd.setCursor(1, 1);
  lcd.print("   [      ]    ");
  String txt = "======";
  lcd.setCursor(5, 1);

  //printa o carregamento dentro das chaves ("[]")//
  delay(300);
  for (byte i = 0; i < txt.length(); i++) {
    lcd.print(txt[i]);
    delay(300);
  }
  lcd.clear();

  //retorna a senha e define o senhaCriada como true//
  senhaCriada = true;
  return senha;    
}

//CONFERE A SENHA DIGITADA PELO USUÁRIO (AO TENTAR ENTRAR OU RECRIAR):
bool confereSenha(String senha){

  //gera mensagem no cursor pra receber a senha//
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(">>SENHA: [____]");
  lcd.setCursor(10,0);

  //pega os caracteres e escreve (#) dentro do campo de inserção a cada clique//
  String input = "";
  while(input.length() < 4){
      char key = customKeypad.getKey();
         if(key >= '0' && key <= '9') {
          input += key;
          lcd.print("#");
          }
        }
  
  //retorna se a senha é true(certa) ou false(errada)//
  if(input == senha){
    return true;
  }
  else{
     return false;
  }
}


//USADA PARA REDEFINIR QUANDO A OPÇÂO "B" FOR CLICADA NO MENU:
String redefinir(){

  //digita mensagem no cursor//
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print(">>NOVA SENHA<<");
  lcd.setCursor(5,1);
  lcd.print("[____]");
  lcd.setCursor(6,1);

  //reseta a senha e define novamente//
  senha = "";
  while(senha.length() < 4){
      char key = customKeypad.getKey();
         if(key >= '0' && key <= '9') {
          senha += key;
          lcd.print("#");
          }
        }

  //escreve mensagem de tela criada e tela de carregamento//
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(">SENHA RECRIADA<");
  lcd.setCursor(1, 1);
  lcd.print("   [      ]    ");
  String txt = "======";
  lcd.setCursor(5, 1);
  delay(300);
  for (byte i = 0; i < txt.length(); i++) {
    lcd.print(txt[i]);
    delay(300);
  }

  //retorna a senha e define o senhaCriada como true//
  lcd.clear();
  senhaCriada = true;
  return senha;
}


//VERIFICA SE O BOTÃO DE ABRIR POR DENTRO ESTÁ CLICADO:
bool botaoClicado(){
  //se for clicado retorna true, se não, retorna falso
  if (digitalRead(botao) == LOW){
   return true;
    
  } else{
    return false;
  }
}


//PRINCIPAL
void setup(){
  //inicia os pinos e o serial//
  Serial.begin(9600);
  lcd.begin(16, 2);
  myservo.attach(3,600,2300);
  myservo.write(FECHADO);
  pinMode(botao, INPUT_PULLUP);
  pinMode(buzzer,OUTPUT);
  
  //pisca mensagem de bemvindo//
  lcd.print("   BEM VINDO!   ");
  delay(300);
  lcd.clear();
  delay(300);
  lcd.print("   BEM VINDO!   ");
  delay(300);
  lcd.clear();
  delay(300);
  lcd.print("   BEM VINDO!   ");
  delay(300);
  lcd.clear();
  delay(300);

  //printa a mensagem "digitando no cursor"//
  lcd.setCursor(5,1);
  lcd.print("[____]");
  delay(100); 
  lcd.setCursor(1, 0);
  String txt = ">>NOVA SENHA<<";
  for (byte i = 0; i < txt.length(); i++) {
    lcd.print(txt[i]);
    delay(100);
  }
  //cria a primeira senha obrigatória//
  senha = criaSenha();
}
  
void loop(){ 
  //cria a senha caso ela nao tenha sido criada//
  if(!senhaCriada){
    senha = criaSenha();
  }
  //se a senha tiver sido criada, entra no looping do menu//
  else{
    while(true){
      //se o menu retornou falso (opção de abrir), ele confere a senha//
      if(menu() == false){
        //abre se for certo//
        if(confereSenha(senha) == true){
          aberto();
        }
        //continua trancado e mostra a mensagem se estiver errado// 
        else{          
          trancado();
        }
    }
    //se o menu retornou true (opcao de redefinir), ele confere a senha//
     else{
       //se for certo ele entra no método de redefinição//
      if(confereSenha(senha) == true){
        redefinir();
      }
      //se estiver errado ele tranca//
      else{
        trancado();
      }
    } 
  }
}
}