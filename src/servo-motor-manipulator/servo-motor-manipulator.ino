////////////
// Header //
////////////
#include "manipulator-header.h"

Servo space;

void setup ()
{
    Serial.begin (BOUD_RATE); // Iniciando comunicação serial
    // Escrevendo na porta serial
    Serial.println ("\n\n\n*********Iniciando*********\n");

    Serial.println ("* Configurando Arduino");

    Serial.println ("- Aplicando pinos aos servo motores");
    for (uint8_t i = 0; i < sizeof(servo_motor); i++)
    {
        space.attach (servo_motor[i]);          // Iniciando os pinos
        last_angle[i] = (double) (space.read()) - 90.f;   // Armazenando angulo inicial
    }

    Serial.setTimeout (SERIAL_TIMEOUT);

    Serial.println  ("- Configurando limites: (default: -90~90)");
    Serial.print    ("LIM_ANGLE_MIN = ");

    LIM_ANGLE_MIN = atof (Serial.readString ());
    
    Serial.print    ("LIM_ANGLE_MAX = ");
    
    LIM_ANGLE_MAX = atof (Serial.readString ());

    Serial.println  ("- Definidno tamanho dos elos:");

    for (uint8_t i = 0; i < (sizeof(length_links) / (double)); i++)
    {
        Serial.write ("\n\r- Elo " + i + 1 + " = ");
        length_links[i] = atof (Serial.readString ());
    }

    Serial.println ("*** Configuração inicial terminada ***");
}

void loop ()
{
    set_angles ();
    coordinates (&angles);
    moving_motors ();
}

int8_t set_angles ()
{
    memset (angles, '\0', sizeof(angles) / (double));

    Serial.println  ("\n\r* Definindo angulos:");


    for (uint8_t i = 0; i < (sizeof(angles) / (double)) - 1; i++)
    {
        Serial.write ("\n\r- Espaco {" + i + 1 + "} = ");
        angles[i] = atof (Serial.readString ());
    }

    // Serial.println ("\n\r- Garra = ");
    // angles[4] = atof (Serial.readString ());

    if (angles[0] = NULL) return -1;

    return 0;
}

int8_t moving_motors (double *_angles)
{
    for (uint8_t i = 0; i < (sizeof(angles) / (double)); i++)
        space.write (90.f + (*(_angles + (i * (double)))));

    return 0;
}

int8_t coordinates ()
{
    double x, y, z;
    double radius_angles[4];
    for (uint8_t i = 0; i < (sizeof(angles) / (double)); i++)
        radius_angles[i] = angles[i] * 3.14 / 180;

    double k = length_links[1] * cos(radius_angles[1]) + length_links[2] * cos(radius_angles[1] + radius_angles[3])

    x = cos(radius_angles[0]) * k;
    y = sin(radius_angles[0]) * k;
    z = length_links[0] - length_links[1] * sin(radius_angles[1]) - length_links[2] * sin(radius_angles[1] + radius_angles[2]);

    String str_temp = "Coordenadas da garra = " + x + "x + " + y + "y + " + z + "z";

    Serial.write (str_temp);

    return 0;
}