# Huerto+ : Sistema Automatizado de Riego y Control de Variables Ambientales

Proyecto desarrollado para el curso **Integrador I: Diseño Electrónico**, cuyo propósito es implementar un sistema autónomo de monitoreo y control para cultivos agrícolas, optimizando el uso de agua, energía y fertilizantes mediante sensores, actuadores y alimentación solar.

---

## 📌 Descripción del Proyecto
Huerto+ es un sistema automatizado diseñado para optimizar el uso del agua, la energía y los recursos agrícolas mediante el control inteligente de variables críticas para el cultivo del rabanito (*Raphanus sativus*).

Integra sensores de humedad del suelo, pH, temperatura y humedad ambiental, así como actuadores controlados por un microcontrolador (Arduino UNO), permitiendo mantener condiciones ideales de cultivo de forma autónoma y sostenible.

El sistema  evalúa continuamente las condiciones del cultivo y activa actuadores como bombas de agua mediante una pantalla LCD.

---

---

El sistema incorpora:

- Microcontrolador **Arduino UNO**
- Sensores: **FC-28**, **DHT11**, **pH BNC**
- Actuadores: bomba de agua 12V, relé

---
## 🎯 Objetivo del Sistema
Desarrollar un huerto automático capaz de regular el riego y el pH del suelo, monitorear las variables ambientales y garantizar un crecimiento eficiente, sostenible y controlado de los cultivos.

---


## ⚙️ Funciones principales

### ✔ Monitoreo de variables

El sistema mide:

- Humedad del suelo (0–100%)
- Nivel de pH estimado
- Oxígeno (DO) en dos niveles: estable / bajo
- Temperatura simulada

Todas las lecturas se muestran en el LCD y en el monitor serial.

---

### ✔ Riego automático

En modo automático, la bomba se activa si:

- La humedad es **≤ 30%**

Y se apaga cuando supera ese valor.

---

### ✔ Modo manual / automático

El usuario puede alternar entre:

- **Automático** → Control basado en humedad.  
- **Manual** → Modo informativo (sin control directo de botón añadido).

---

### ✔ Pantalla LCD con menú interactivo

Con el encoder se accede a 6 vistas:

1. Humedad del suelo  
2. Nivel de pH  
3. Oxígeno  
4. Temperatura  
5. Estado de la bomba  
6. Cambio de modo (manual/automático)

---

### ✔ Envío de datos por serial

Cada 2 segundos se envía:

- Humedad y clasificación  
- pH y clasificación  
- Oxígeno  
- Temperatura  
- Estado de la bomba  
- Modo activo  

---

## 🛠 Componentes utilizados

| Componente                    | Función                          |
| ----------------------------- | -------------------------------- |
| Arduino UNO                   | Procesamiento del sistema        |
| LCD 16x2 I2C                  | Visualización del menú           |
| Encoder rotatorio             | Navegación e interacción         |
| Sensor de humedad FC-28       | Lectura del suelo                |
| Sensor de pH analógico        | Medición estimada                |
| Sensor digital de temperatura | Lectura básica                   |
| Bomba + relé                  | Activación de riego              |

---

## 🔌 Esquema general de funcionamiento

1. Los sensores envían valores al Arduino.  
2. La humedad se compara con el umbral.  
3. En modo automático se activa la bomba si el suelo está seco.  
4. El LCD muestra datos mediante un menú navegable.  
5. El usuario puede cambiar el modo desde el menú.  
6. Las lecturas también se envían por serial.

## 🏗️ Esquema General del Sistema
### 🧱 Diagrama de Bloques (Descriptivo)
```
[Sensores] --> [Arduino UNO] --> [Relé] --> [Bombas]
| |
 [LCD]<--[Encoder] 
| |
Sensado → Control → Actuación → Monitoreo
```
**Sensores integrados:**
- FC-28 (humedad del suelo)
- Sensor de pH tipo BNC
- DHT11 (temperatura y humedad relativa)
- DO (oxígeno)

**Actuadores:**
- Bomba de riego 12V
- Bomba dosificadora para corrección del pH
  
---

## 📂 Estructura del repositorio

```

HuertoPlus/
│
├── README.md
├── CHANGELOG.md
│
├── /code
│ ├── huerto_plus.ino
│ └── calibraciones/
│
├── /schematics
│ ├── proteus/
│ ├── tinkercad/
│ └── diagrama_flujo/
│
├── /images
│ ├── circuito_fisico.jpg
│ ├── simulaciones.png
│ └── sensores.jpg
│
└── /manuales
├── manual_tecnico.pdf
└── manual_usuario.pdf

```
---


## ▶ Cómo usar el sistema

1. **Enciende el sistema**  
   La pantalla LCD mostrará un mensaje de inicio y luego el menú principal.

2. **Navega por el menú con el encoder**  
   - Gira el encoder para desplazarte entre las opciones.  
   - La opción seleccionada se indica con el símbolo `>`.

3. **Selecciona una opción pulsando el botón**  
   Al presionar el botón podrás ver la información detallada de cada categoría:
   - Humedad de la tierra  
   - Nivel de pH  
   - Oxígeno  
   - Temperatura  
   - Estado de la bomba  
   - Cambiar Modo (Automático / Manual)

4. **Cambia el modo de riego**  
   En *Cambiar Modo* puedes alternar entre:  
   - **Automático:** la bomba se activa cuando la humedad ≤ 30%.  
   - **Manual:** el usuario controla cuándo encender la bomba.

5. **Consulta las lecturas en la pantalla o por el monitor serial**  
   Cada 2 segundos, el sistema envía un reporte completo al monitor serial con:  
   - Humedad (%) y estado  
   - Nivel de pH  
   - Oxígeno (%)  
   - Temperatura (°C)  
   - Estado de la bomba  
   - Modo actual


---

Incluye:
- Lectura y calibración de sensores  
- Lógica automática de riego  
- Gestión de menú en LCD con encoder  
- Envío por Bluetooth  
- Control de estado de bombas  

---

## ⚙️ Requisitos Técnicos
- Arduino IDE 1.8+ o 2.0+
- Bibliotecas:
  - `LiquidCrystal_I2C`
  - `Encoder`
  - `Wire`

---

## 🔋 Sistema de Alimentación Solar
- Panel: 25W  
- Batería: 12V 18Ah  
- Controlador PWM: 10A  

**Autonomía estimada:** 18–24 h sin radiación solar (dependiendo del uso de bombas).

---

## 🧪 Pruebas y Validación
- Comparación entre simulación (Proteus) y prototipo físico.
- Medición de variables reales durante el cultivo.
- Pruebas de automatización del riego.
- Regulación del pH del sustrato.

---

## 📅 Estado del Proyecto
**Versión actual:** v1.0  
Proyecto completado para fines académicos del curso Integrador I.

---

## 👥 Autores
- Barnett Estaña, Diederick  
- Gil Rodriguez, Estefanía Gabriela  
- López Chacón, Deysi  
- Mori Álvarez, Ariam Midori  
- Segovia Mendoza, Norbert Diego  

Docente: **Bryan Motta Zorrilla**  
Facultad de Ingeniería Biomédica, Electrónica y Mecatrónica – 2025

---

## 📄 Licencia
Uso académico. Se permite modificar y distribuir citando la fuente.




