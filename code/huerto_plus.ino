#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Encoder.h>

// -------------------- CONFIGURACIÓN LCD --------------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// -------------------- ENCODER --------------------
Encoder encoder(2, 3);
const int encoderButton = 4;
long lastPos = -1;
bool buttonPressed = false;

// -------------------- BOMBA Y SENSORES --------------------
const int bomba = 8;
int humedad = 0;

const int pinHumedadSuelo = A0;
const int pinPH = A1;
const int pinDO = 6;
const int pinTemp = 7;

// -------------------- MODO MANUAL/AUTOMÁTICO --------------------
bool modoManual = false;
int menuIndex = 0;
const int totalMenus = 6;

void setup() {
  Serial.begin(9600);
  
  // Configurar pines
  pinMode(bomba, OUTPUT); 
  pinMode(pinDO, INPUT);
  pinMode(pinTemp, INPUT);
  digitalWrite(bomba, HIGH);  // Bomba apagada inicialmente
  
  // Configurar encoder
  pinMode(encoderButton, INPUT_PULLUP);
  
  // INICIALIZAR LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  // Mensaje de inicio
  lcd.setCursor(0, 0);
  lcd.print("MACETA AUTOMATICA");
  lcd.setCursor(0, 1);
  lcd.print("Gira encoder->");
  
  Serial.println("Sistema Maceta Automática - Iniciado");
  delay(2000);
  
  mostrarMenu();
}

void loop() {
  // Lógica de sensores
  humedad = analogRead(pinHumedadSuelo); 
  int humedadPorcentaje = map(humedad, 1023, 0, 0, 100);
  
  // Control automático de bomba (solo en modo automático)
  if (!modoManual) {
    if(humedadPorcentaje <= 30) {  // Si humedad <= 30%, regar
      digitalWrite(bomba, LOW);   // Bomba ON - Regando
    } else {
      digitalWrite(bomba, HIGH);  // Bomba OFF
    }
  }
  
  // Lectura del encoder
  long newPos = encoder.read() / 4;
  if (newPos != lastPos) {
    lastPos = newPos;
    
    if (newPos > lastPos) {
      menuIndex++;
    } else {
      menuIndex--;
    }
    
    if (menuIndex < 0) menuIndex = totalMenus - 1;
    if (menuIndex >= totalMenus) menuIndex = 0;
    
    mostrarMenu();
  }

  // Botón del encoder
  if (digitalRead(encoderButton) == LOW && !buttonPressed) {
    buttonPressed = true;
    seleccionarMenu();
    delay(300);
  }
  if (digitalRead(encoderButton) == HIGH) {
    buttonPressed = false;
  }

  enviarDatosSerial();
  delay(100);
}

void mostrarMenu() {
  lcd.clear();
  
  switch(menuIndex) {
    case 0:
      lcd.print(">Humedad Tierra");
      lcd.setCursor(0, 1);
      lcd.print("  Nivel pH");
      break;
    case 1:
      lcd.print(" Humedad Tierra");
      lcd.setCursor(0, 1);
      lcd.print(">Nivel pH");
      break;
    case 2:
      lcd.print(">Oxigeno");
      lcd.setCursor(0, 1);
      lcd.print("  Temperatura");
      break;
    case 3:
      lcd.print(" Oxigeno");
      lcd.setCursor(0, 1);
      lcd.print(">Temperatura");
      break;
    case 4:
      lcd.print(">Estado Bomba");
      lcd.setCursor(0, 1);
      lcd.print("  Cambiar Modo");
      break;
    case 5:
      lcd.print(" Estado Bomba");
      lcd.setCursor(0, 1);
      lcd.print(">Cambiar Modo");
      break;
  }
}

String obtenerEstadoHumedad(int porcentaje) {
  if (porcentaje <= 20) return "SECO";
  if (porcentaje <= 50) return "MEDIO SECO";
  return "HUMEDO";
}

String obtenerEstadoPH(float ph) {
  if (ph < 7.0) return "ACIDO";
  if (ph > 7.0) return "ALCALINO";
  return "NEUTRO";
}

void seleccionarMenu() {
  lcd.clear();
  
  switch(menuIndex) {
    case 0: // Humedad Tierra
      {
        int humedadVal = analogRead(pinHumedadSuelo);
        int humedadPct = map(humedadVal, 1023, 0, 0, 100);
        String estado = obtenerEstadoHumedad(humedadPct);
        
        lcd.print("Humedad:" + String(humedadPct) + "%");
        lcd.setCursor(0, 1);
        
        if (humedadPct <= 30 && !modoManual) {
          lcd.print("NECESITA AGUA!");
        } else {
          lcd.print(estado);
        }
      }
      break;
      
    case 1: // pH
      {
        int phRaw = analogRead(pinPH);
        float voltaje = phRaw * (5.0 / 1023.0);
        float valorPH = 7.0 + ((2.5 - voltaje) / 0.18);
        String estadoPH = obtenerEstadoPH(valorPH);
        
        lcd.print("pH: " + String(valorPH, 1));
        lcd.setCursor(0, 1);
        lcd.print(estadoPH);
      }
      break;
      
    case 2: // Oxígeno
      {
        int doVal = digitalRead(pinDO);
        int oxigenoPct = doVal ? 85 : 25;
        
        lcd.print("Oxigeno:");
        lcd.setCursor(0, 1);
        lcd.print(String(oxigenoPct) + "% " + (doVal ? "ESTABLE" : "BAJO"));
      }
      break;
      
    case 3: // Temperatura
      {
        int tempVal = digitalRead(pinTemp);
        float temperatura = tempVal ? 28.5 : 22.0;
        
        lcd.print("Temperatura:");
        lcd.setCursor(0, 1);
        lcd.print(String(temperatura, 1) + " C");
      }
      break;
      
    case 4: // Estado Bomba
      {
        bool bombaEncendida = (digitalRead(bomba) == LOW);
        int humedadActual = map(analogRead(pinHumedadSuelo), 1023, 0, 0, 100);
        
        lcd.print("BOMBA:");
        lcd.setCursor(0, 1);
        
        if (bombaEncendida) {
          lcd.print("REGANDO");
        } else if (humedadActual <= 30 && !modoManual) {
          lcd.print("NECESITA AGUA");
        } else {
          lcd.print("APAGADA");
        }
      }
      break;
      
    case 5: // Modo
      {
        modoManual = !modoManual;
        lcd.print("MODO:");
        lcd.setCursor(0, 1);
        lcd.print(modoManual ? "MANUAL" : "AUTOMATICO");
        
        delay(2000);
        lcd.clear();
        lcd.print("Modo " + String(modoManual ? "MANUAL" : "AUTO"));
        lcd.setCursor(0, 1);
        lcd.print(modoManual ? "Control manual" : "Riego auto");
      }
      break;
  }
  delay(3000);
  mostrarMenu();
}

void enviarDatosSerial() {
  static unsigned long lastSend = 0;
  if (millis() - lastSend < 2000) return;
  lastSend = millis();
  
  // Leer sensores
  int humedadVal = analogRead(pinHumedadSuelo);
  int humedadPct = map(humedadVal, 1023, 0, 0, 100);
  int phRaw = analogRead(pinPH);
  float voltaje = phRaw * (5.0 / 1023.0);
  float valorPH = 7.0 + ((2.5 - voltaje) / 0.18);
  int doVal = digitalRead(pinDO);
  int tempVal = digitalRead(pinTemp);
  float temperatura = tempVal ? 28.5 : 22.0;
  int oxigenoPct = doVal ? 85 : 25;
  
  bool bombaEncendida = (digitalRead(bomba) == LOW);
  
  Serial.println("=== MACETA AUTOMATICA ===");
  Serial.print("Humedad Tierra: ");
  Serial.print(humedadPct);
  Serial.print("% - ");
  Serial.println(obtenerEstadoHumedad(humedadPct));
  
  Serial.print("Nivel pH: ");
  Serial.print(valorPH, 1);
  Serial.print(" - ");
  Serial.println(obtenerEstadoPH(valorPH));
  
  Serial.print("Oxigeno: ");
  Serial.print(oxigenoPct);
  Serial.println("%");
  
  Serial.print("Temperatura: ");
  Serial.print(temperatura, 1);
  Serial.println("°C");
  
  Serial.print("Estado Bomba: ");
  if (bombaEncendida) {
    Serial.println("REGANDO");
  } else if (humedadPct <= 30 && !modoManual) {
    Serial.println("NECESITA AGUA");
  } else {
    Serial.println("APAGADA");
  }
  
  Serial.print("Modo: ");
  Serial.println(modoManual ? "MANUAL" : "AUTOMATICO");
  Serial.println("========================");
}
