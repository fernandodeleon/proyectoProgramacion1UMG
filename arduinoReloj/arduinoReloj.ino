#include <LiquidCrystal.h>
#include <DHT.h>

#define COLS 16 // Columnas del LCD
#define ROWS 2 // Filas del LCD
#define VELOCIDAD 100 // Velocidad a la que se mueve el texto

// Inicializar los pins de la interfaz
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int sensorDHT = A1;
int temp, humedad;
DHT dht (sensorDHT,DHT11);

char caracter;
String comando;
 
String textoIntro = "HOLA, BIENVENIDO!";

void temperatura(){
  dht.begin(); 
  lcd.begin(16, 2);
  humedad = dht.readHumidity(); //Funcion incluida en la libreria. Permite leer la humedad.
  temp = dht.readTemperature(); //Permite leer la temperatura.
  lcd.setCursor(0,0);
  lcd.print("TEMPERATURA:");
  lcd.print(temp);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("HUMEDAD:");
  lcd.print(humedad);
  lcd.print("%");
  delay(1000);
}

void hora(int h, int m, int seg){
    lcd.setCursor(3, 0);
    lcd.print("LA HORA ES");
    
    for(int s = seg; s < 61; s++){      
        if (s == 60) {
          lcd.clear();
          lcd.setCursor(3, 0);
          lcd.print("LA HORA ES");
          s = 0;
          m++;
        }
        if (m == 60) {
          m = 0;
          h++;
        }
        if (h == 24) {
          h = 0;
        }
        String a = String(h);
        String b = String(m);
        String c = String(s);
        String todo = a+":"+b+":"+c;
        lcd.setCursor(4, 1);
        lcd.print(todo);

        delay(1000);
    }
}

void cronometro(){
    lcd.setCursor(3, 0);
    lcd.print("CRONOMETRO");
    int m, h, s; 
    m = 0;
    h = 0;
    s = 0;
    for(int cs = 0; cs < 101; cs++){
        if (cs == 100) {
          lcd.clear();
          lcd.setCursor(3, 0);
          lcd.print("CRONOMETRO");
          cs = 0;
          s++;
        }
        if (s == 60) {
          s = 0;
          m++;
        }
        if (m == 60) {
          m = 0;
          h++;
        }
        if (h == 24) {
          h = 0;
        }
        String a = String(h);
        String b = String(m);
        String c = String(s);
        String d = String(cs);
        String todo = a+":"+b+":"+c+":"+cs;
        lcd.setCursor(3, 1);
        lcd.print(todo);
  
        delay(10);
    } 
}

void temporizador(int h, int m, int s){
    lcd.setCursor(2, 0);
    lcd.print("TEMPORIZADOR");  
    
    for(int c = s; c > -2; c--){
          if (c == -1){
              lcd.clear();
              lcd.setCursor(2, 0);
              lcd.print("TEMPORIZADOR");
              c = 59;
              m--;
          }
          if (m == -1) {
              m = 59;
              h--;
          }
          if(h < 0){
              lcd.clear();
              lcd.setCursor(2, 0);
              lcd.print("FIN TIEMPO!"); 
            break;
          }
          String a = String(h);
          String b = String(m);
          String d = String(c);
          String todo = a+":"+b+":"+d;
          lcd.setCursor(4, 1);
          lcd.print(todo);   
          delay(1000);
    }    
}

void setup() {
  Serial.begin(115200); 
  lcd.begin(COLS, ROWS);
    
  int tamTexto = textoIntro.length();
  
  for(int i=16; i>-1; i--)
  {
    lcd.clear();
    lcd.setCursor(i, 0);
    lcd.print(textoIntro);
    delay(VELOCIDAD);
  }
 
  // Mostramos salida del texto por la izquierda
  for(int i=0; i<tamTexto + 2 ; i++)
  {
    String texto = textoIntro.substring(i-1);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(texto);
    delay(VELOCIDAD);
  }


  
}

void loop() {
  while (Serial.available() > 0){
    caracter = Serial.read();
    comando.concat(caracter);     
    delay(20);
  }

  if (comando.equals("reloj") == true){
    hora(5, 40, 05);
  }
  
  if (comando.equals("cronometro") == true){
    cronometro();
  }

  if (comando.equals("temporizador") == true){
    temporizador(2, 5, 15);
  }
  
  if (comando.equals("temperatura") == true){
    temperatura();
  }

  if (comando.equals("salir") == true){
    setup();
  }
  comando = "";
}
