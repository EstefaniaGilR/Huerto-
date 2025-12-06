Pruebas de Comunicación Serial – Huerto+

Este documento reúne los ensayos realizados para validar la transmisión de datos mediante el monitor serial del sistema Huerto+, utilizando el programa cargado en el Arduino UNO.
Las pruebas permiten confirmar el funcionamiento correcto de:

Lectura de sensores

Clasificación de estados

Activación de la bomba

Cambio entre modo automático y manual

Envío ordenado y periódico de datos (cada 2 segundos)

🔧 Configuración usada para la prueba

LCD 16x2 I2C (0x27)

Encoder rotatorio con pulsador

Sensor FC-28 (humedad del suelo)

Sensor pH analógico BNC

Entrada DO (oxígeno)

Sensor simulado de temperatura

Bomba 12V y relé

📡 Salida del Monitor Serial — Ejemplo real

A continuación se muestra un extracto típico capturado durante las pruebas:

=== MACETA AUTOMATICA ===
Humedad Tierra: 28% - SECO
Nivel pH: 6.8 - ACIDO
Oxigeno: 85%
Temperatura: 28.5°C
Estado Bomba: REGANDO
Modo: AUTOMATICO
========================

=== MACETA AUTOMATICA ===
Humedad Tierra: 45% - MEDIO SECO
Nivel pH: 7.1 - ALCALINO
Oxigeno: 25%
Temperatura: 22.0°C
Estado Bomba: APAGADA
Modo: AUTOMATICO
========================

🔍 Resultados de la prueba
✔ Lectura de humedad

El sensor se interpretó correctamente.

Se observaron transiciones SECO → MEDIO SECO → HUMEDO.

Cuando el valor ≤ 30%, la bomba encendió.

✔ pH

Se comprobó la medición y conversión de voltaje → pH.

La clasificación ACIDO / NEUTRO / ALCALINO fue correcta.

✔ Oxígeno (DO)

Modo digital simulado funcionando.

Clasificación:

Señal HIGH → 85% (ESTABLE)

Señal LOW → 25% (BAJO)

✔ Temperatura

Simulación según nivel digital funcionando según lo esperado.

✔ Envío por serial

Intervalo: 2000 ms exactos

Formato ordenado y legible

Estados completos incluyendo modo activo y bomba
