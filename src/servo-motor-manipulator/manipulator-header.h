///////////////
// Libraries //
///////////////
#include <Servo.h> // Biblioteca para controlar os Servo Motores
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//////////
// Pins //
//////////
const uint8_t servo_motor[] = {
    14, // Espaço 1
    15, // Espaço 2
    16, // Espaço 3
    17, // Espaço 4
    18  // Garra
};

///////////
// Macro //
///////////
// #define c180to90(x) x - 90.f // Convertendo da escala de 0~180 para -90~90
// #define c90to180(x) x + 90.f // Convertendo da escala de -90~90 para 0~180

///////////////
// Constants //
///////////////
#define BOUD_RATE       115200  // Velocidade de atualização na porta serial
#define SERIAL_TIMEOUT  10e3    // Tempo de espera pela serial

////////////////
// Global Var //
////////////////
double LIM_ANGLE_MIN = -90.f;    // Limite inferior que o servo motor pode operar
double LIM_ANGLE_MAX =  90.f;    // Limite superior que o servo motor pode operar
double links_length[3];
double last_angle[5];            // Registra o ultimo ângulo
double angles[5];

///////////////
// Functions //
///////////////
int8_t set_angles ();
int8_t moving_motors (double *_angles);
int8_t coordinates ();