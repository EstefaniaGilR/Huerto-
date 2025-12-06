# Pruebas de Comunicación Serial – Huerto+

Este documento describe los ensayos realizados para validar la **transmisión de datos** mediante el monitor serial del sistema **Huerto+**, utilizando el programa cargado en un **Arduino UNO**.  

Las pruebas permiten verificar el correcto funcionamiento de:  

- Lectura de sensores  
- Clasificación de estados  
- Activación de la bomba  
- Cambio entre modo **automático** y **manual**  
- Envío periódico y ordenado de datos (cada 2 segundos)  

---

## 🔧 Configuración usada para la prueba

- **LCD 16x2 I2C (0x27)**  
- **Encoder rotatorio con pulsador**  
- **Sensor FC-28** (humedad del suelo)  
- **Sensor pH analógico BNC**  
- **Entrada DO** (oxígeno disuelto)  
- **Sensor simulado de temperatura**  
- **Bomba 12V y relé**  

---

## 📡 Salida del Monitor Serial — Ejemplo real

```
=== MACETA AUTOMÁTICA ===
Humedad Tierra: 28% - SECO
Nivel pH: 6.8 - ÁCIDO
Oxígeno: 85%
Temperatura: 28.5°C
Estado Bomba: REGANDO
Modo: AUTOMÁTICO
```
```
=== MACETA AUTOMÁTICA ===
Humedad Tierra: 45% - MEDIO SECO
Nivel pH: 7.1 - ALCALINO
Oxígeno: 25%
Temperatura: 22.0°C
Estado Bomba: APAGADA
Modo: AUTOMÁTICO
```


---

## 🔍 Resultados de la prueba

### ✔ Lectura de Humedad
- El sensor se interpretó correctamente.  
- Se observaron transiciones **SECO → MEDIO SECO → HÚMEDO**.  
- La bomba se activó correctamente cuando el valor ≤ 30%.  

### ✔ pH
- La medición y conversión de voltaje → pH fue correcta.  
- Clasificación **ÁCIDO / NEUTRO / ALCALINO** funcionando según lo esperado.  

### ✔ Oxígeno (DO)
- Simulación digital funcionando correctamente.  
- Clasificación:  
  - **Señal HIGH → 85% (ESTABLE)**  
  - **Señal LOW → 25% (BAJO)**  

### ✔ Temperatura
- Simulación digital funcionando según lo esperado.  

### ✔ Envío por Serial
- Intervalo de envío: **2000 ms exactos**  
- Formato: **ordenado y legible**  
- Incluye todos los estados: humedad, pH, oxígeno, temperatura, bomba y modo activo  
