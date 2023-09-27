// joaogabrielbz
#include <Stepper.h>

#include <LiquidCrystal.h>

#include <IRremote.h>

//Configurações do controle
const int receptor = 22;
IRrecv controle(receptor);
decode_results r;
#define tk_up 16718055
#define tk_left 16716015
#define tk_ok 16726215
#define tk_right 16734885
#define tk_down 16730805
#define tk1 16753245
#define tk2 16736925
#define tk3 16769565
#define tk4 16720605
#define tk5 16712445
#define tk6 16761405
#define tk7 16769055
#define tk8 16754775
#define tk9 16748655
#define tk_ast 16738455
#define tk0 16750695
#define tk_hash 16756815

//Configuração dos motores
const int passo = 1;
const int passosPorVolta = 64;
Stepper motorX(passosPorVolta, 8, 10, 9, 13); //branco
Stepper motorY(passosPorVolta, 43, 47, 45, 49); //cinza
float atualX = 0;
float atualY = 0;

//lcd
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

//Declaração de variaveis e constantes 
const int VMaxima = 500;
const int VMinima = 150;
const int Xmax = (4.666666 * passosPorVolta) * passosPorVolta / 2;
const int Ymax = (1 * passosPorVolta) * passosPorVolta / 2;
const int min = 0;

char az[3];
char alt[2];
int azInt = 0;
int altInt = 0;
int Xatual = 0;
int Yatual = 0;

//----------------------------------------------------------

//Metodo que converte o código do botão no char equivalente
char converterEmChar(int value) {
  switch (value) {
  case (tk1):
    return '1';
    break;
  case (tk2):
    return '2';
    break;
  case (tk3):
    return '3';
    break;
  case (tk4):
    return '4';
    break;
  case (tk5):
    return '5';
    break;
  case (tk6):
    return '6';
    break;
  case (tk7):
    return '7';
    break;
  case (tk8):
    return '8';
    break;
  case (tk9):
    return '9';
    break;
  case (tk0):
    return '0';
    break;
  default:
    return '.';
    break;
  }
}

//Metodo que volta a tela padrão do display
void telaPadrao() {
  lcd.setCursor(0, 0);
  lcd.print("**    STAR    **");
  lcd.setCursor(0, 1);
  lcd.print("*    FINDER    *");
}

void zerarMotores() {
  motorX.setSpeed(VMaxima);
  motorY.setSpeed(VMaxima);
  while (Xatual > 0 || Yatual > 0) {
    if (Xatual > 0) {
      motorX.step(-passo);
      Xatual--;
    }
    if (Yatual > 0) {
      motorY.step(-passo);
      Yatual--;
    }

  }
}

//Metodo que faz os calculos necessárias e roda os motores
void calcularRodadas(int x, int y) {
  //Volta pro 0
  zerarMotores();

  // CALCULOS PARA O MOTOR X //
  const float rodadasEqX = 4.666666; //Rodadas equivalentes do motor para rodar 360 na engrenagem principal
  const float grausX = 360; //volta no motor X em graus
  float rodadasMotorX = (rodadasEqX * x) / grausX; //icognita (numero que de passos final do motor)
  float passosX = (rodadasMotorX * passosPorVolta) * passosPorVolta / 2; // Numero FINAL de passos

  // CALCULOS PARA O MOTOR Y //
  const float rodadasEqY = 1; //Rodadas equivalentes do motor para rodar 90 na engrenagem principal
  const float grausY = 90; //volta no motor Y em graus
  float rodadasMotorY = (rodadasEqY * y) / grausY; //icognita (numero que de passos final do motor)
  float passosY = (rodadasMotorY * passosPorVolta) * passosPorVolta / 2; // Numero FINAL de passos

  // GIRANDO OS MOTORES //
  lcd.setCursor(0, 0);
  lcd.print("    GIRANDO!    ");
  while (passosX > 0 || passosY > 0) {
    if (passosX > 0) {
      motorX.step(passo);
      Xatual++;
    }
    if (passosY > 0) {
      motorY.step(passo);
      Yatual++;
    }
    passosX--;
    passosY--;
  }
  motorX.setSpeed(VMinima);
  motorY.setSpeed(VMinima);
  Serial.print(Xatual);
  //Mensagem de sucesso piscando
  lcd.setCursor(0, 0);
  lcd.print("    CONCUIDO    ");
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("                ");
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("    CONCUIDO    ");
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("                ");
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("    CONCUIDO    ");
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("                ");
  delay(500);
  telaPadrao();
}

//Metodo que pisca a mensagem inicial
void telaInicial() {
  lcd.setCursor(0, 0);
  lcd.print("**    STAR    **");
  lcd.setCursor(0, 1);
  lcd.print("*    FINDER    *");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("      STAR      ");
  lcd.setCursor(0, 1);
  lcd.print("     FINDER     ");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("**    STAR    **");
  lcd.setCursor(0, 1);
  lcd.print("*    FINDER    *");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("      STAR      ");
  lcd.setCursor(0, 1);
  lcd.print("     FINDER     ");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("**    STAR    **");
  lcd.setCursor(0, 1);
  lcd.print("*    FINDER    *");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("      STAR      ");
  lcd.setCursor(0, 1);
  lcd.print("     FINDER     ");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("**    STAR    **");
  lcd.setCursor(0, 1);
  lcd.print("*    FINDER    *");
}

//----------------------------------------------------------

void setup() {
  Serial.begin(9600);
  controle.enableIRIn();
  motorX.setSpeed(VMinima);
  motorY.setSpeed(VMinima);
  lcd.begin(16, 2);
  telaInicial();
}

void loop() {

  if (controle.decode( & r)) { //captura o clique
    switch (r.value) {

    case (tk_up):

      lcd.setCursor(0, 0);
      lcd.print("**    CIMA    **");
      lcd.setCursor(0, 1);
      lcd.print("*              *");
      while (true) {
        if (Yatual < Ymax) {
          motorY.step(passo);
          Yatual++; //soma um na pos atual                      
        } else {
          telaPadrao();
          break;
        }
        if (controle.decode( & r)) {
          if (r.value == tk_ok) {
            telaPadrao();
            break;
          }
          controle.resume();
        }

      }
      break;

    case (tk_down):

      lcd.setCursor(0, 0);
      lcd.print("**   *BAIXO   **");
      lcd.setCursor(0, 1);
      lcd.print("*              *");
      while (true) {
        if (Yatual > min) {
          motorY.step(-passo);
          Yatual--;
        } else {
          telaPadrao();
          break;
        }
        if (controle.decode( & r)) {
          if (r.value == tk_ok) {
            telaPadrao();
            break;
          }
          controle.resume();
        }
      }
      break;

    case (tk_right):
      motorX.setSpeed(VMaxima);
      lcd.setCursor(0, 0);
      lcd.print("**  *DIREITA  **");
      lcd.setCursor(0, 1);
      lcd.print("*              *");
      while (true) {
        if (Xatual < Xmax) {
          motorX.step(passo);
          Xatual++;
        } else {
          telaPadrao();
          break;
        }

        if (controle.decode( & r)) {
          if (r.value == tk_ok) {
            telaPadrao();
            break;
          }
          controle.resume();
        }
      }
      break;

    case (tk_left):
      motorX.setSpeed(VMaxima);
      lcd.setCursor(0, 0);
      lcd.print("**  ESQUERDA  **");
      lcd.setCursor(0, 1);
      lcd.print("*              *");
      while (true) {
        if (Xatual > min) {
          motorX.step(-passo);
          Xatual--;
        } else {
          telaPadrao();
          break;
        }

        if (controle.decode( & r)) {
          if (r.value == tk_ok) {
            telaPadrao();
            break;
          }
          controle.resume();
        }
      }
      break;

    case (tk_ok):
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  *COORDENADAS");
      lcd.setCursor(1, 1);
      lcd.print("Az:");
      for (int posAlg = 0; posAlg < 3; posAlg++) {
        while (true) {
          if (controle.decode( & r)) {
            char num = converterEmChar(r.value);
            if (num != '.') {
              az[posAlg] = num;
              lcd.print(az[posAlg]);
              controle.resume();
              break;
            }
            controle.resume();
          }
        }

        if (posAlg == 2) {
          int centena = az[0] - '0';
          int dezena = az[1] - '0';
          int unidade = az[2] - '0';
          azInt = (centena * 100) + (dezena * 10) + (unidade);
          if (azInt < 0 || azInt > 360) {
            delay(500);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("  *COORDENADAS");
            lcd.setCursor(0, 1);
            lcd.print(" Az:");
            posAlg = -1;
            for (int i = 0; i < 3; i++) {
              az[i] = '0';
            }
          } else {

          }
        }
      }
      lcd.setCursor(9, 1);
      lcd.print("Alt:");
      for (int posAlg = 0; posAlg < 2; posAlg++) {
        while (true) {
          if (controle.decode( & r)) {
            char num = converterEmChar(r.value);
            if (num != '.') {
              alt[posAlg] = num;
              lcd.print(alt[posAlg]);
              controle.resume();
              break;
            }
            controle.resume();
          }
        }
        if (posAlg == 1) {
          int dezena = alt[0] - '0';
          int unidade = alt[1] - '0';
          altInt = (dezena * 10) + (unidade);
          if (altInt < 0 || altInt > 90) {
            delay(500);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("  *COORDENADAS");
            lcd.setCursor(1, 1);
            lcd.print("Az:");
            for (int i = 0; i < 3; i++) {
              lcd.print(az[i]);
            }
            lcd.print("  Alt:");
            posAlg = -1;
            for (int i = 0; i < 3; i++) {
              alt[i] = '0';
            }
          } else {

          }
        }
      }
      calcularRodadas(azInt, altInt);
      break;

    case (tk0):
      lcd.setCursor(0, 0);
      lcd.print("******HORA******");
      lcd.setCursor(0, 1);
      lcd.print("****DA*FESTA****");
      bool direcao = true;

      zerarMotores();
      while (true) {

        if (Yatual < Ymax) {
          Yatual++;
          motorY.step(passo);
        }

        if (direcao) {
          if (Xatual < Xmax) {
            motorX.step(passo);
            Xatual++;
          } else {
            direcao = false;
          }
        } else {
          if (Xatual > min) {
            motorX.step(-passo);
            Xatual--;
          } else {
            direcao = true;
          }
        }
        if (controle.decode( & r)) {
          if (r.value == tk_ok) {
            telaPadrao();
            zerarMotores();
            break;
          }
          controle.resume();
        }
      }
      break;
    }
    controle.resume();
  }
}