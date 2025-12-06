# Huerto+ : Sistema Automatizado de Riego y Control de Variables Ambientales

Proyecto desarrollado para el curso **Integrador I: Diseño Electrónico**, cuyo propósito es implementar un sistema autónomo de monitoreo y control para cultivos agrícolas, optimizando el uso de agua, energía y fertilizantes mediante sensores, actuadores y alimentación solar.

---

## 🌱 Descripción General del Proyecto

Huerto+ es un sistema diseñado para automatizar procesos críticos en el cultivo del rabanito (*Raphanus sativus*). A través de sensores de humedad del suelo, pH, temperatura y humedad ambiental, el sistema evalúa continuamente las condiciones del cultivo y activa actuadores como bombas de agua o dosificadores correctivos.

El sistema incorpora:

- Microcontrolador **Arduino UNO**
- Sensores: **FC-28**, **DHT11**, **pH BNC**
- Actuadores: bomba de agua 12V, relé

El objetivo es lograr un cultivo más eficiente, sostenible y con mejor rendimiento mediante control automatizado.

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

1. Conecta sensores a los pines definidos en el código.  
2. Enciende el sistema.  
3. Usa el encoder para navegar entre las opciones.  
4. Pulsa el botón para ver cada categoría.  
5. Cambia el modo de riego desde el menú.  
6. Revisa lecturas en pantalla o en el monitor serial.

---





