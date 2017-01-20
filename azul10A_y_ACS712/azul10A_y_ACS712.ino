/*
  Comparaciòn Sensor YHDC 0-10A y Sensor ACS712

  Toma el dato del pin analògico YHDC 0-10A
  Toma el dato del pin analògico ACS712
  calcula la intensidad de la corriente con valores màximos
  durante medio segundo.

  Muestra el resultado de Irms

  modified 17 Enero 2017
  by Lucho & Andres
*/


// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A1;  // Analog input pin that the potentiometer is attached to
const int analogInPin_azul = A0;  // Analog input pin that the potentiometer is attached to
float sensibilidad = 0.066;
float sensibilidad_azul = 0.5;

float valor_reposo = 2.5;

float voltaje_sensor = 0;
float voltaje_sensor_azul = 0;
float intensidad_pico = 0;
float intensidad_pico_azul = 0;
float ruido = 0;
int ruido_anal = 4;

float sensorValue = 0;        // value read from the pot

float Intensidad_maxima = 0;
float Intensidad_minima = 0;
float Intensidad_maxima_azul = 0;
  
float val = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

void loop() {
  
  float corriente = 0;
  float corriente_azul = 0;
  long tiempo = millis();

  Intensidad_maxima = 0;
  Intensidad_minima = 0;
  Intensidad_maxima_azul = 0;

  while ((millis() - tiempo) < 500)
  {
    voltaje_sensor = (analogRead(analogInPin)-ruido_anal) * (5.0/1023.0);
    corriente = (voltaje_sensor - valor_reposo)/sensibilidad;
    if(corriente > Intensidad_maxima)Intensidad_maxima = corriente;
    if(corriente < Intensidad_minima)Intensidad_minima = corriente;

    voltaje_sensor_azul = analogRead(analogInPin_azul)*(25.0/1023.0);
    corriente_azul = (voltaje_sensor_azul)/sensibilidad_azul;
    if(corriente_azul > Intensidad_maxima_azul)Intensidad_maxima_azul = corriente_azul;    
  }

  intensidad_pico = (((Intensidad_maxima - Intensidad_minima)/2) - ruido);
  intensidad_pico_azul = (Intensidad_maxima_azul - ruido);
    

  //Mostrar valores serial
  mostrar_valores();
  
}

void mostrar_valores()
{   
  float Irms = intensidad_pico * 0.707;
  float Irms_azul =  intensidad_pico_azul * 0.707;
  Serial.print("Irms = " );                       
  Serial.print(Irms,3);   
  Serial.print("  ADC = " ); 
  Serial.print(analogRead(analogInPin)-ruido_anal);
  Serial.print("  Azul = " ); 
  Serial.println(Irms_azul,3); 
  /*
  Serial.print("  Imax = " ); 
  Serial.print(Intensidad_maxima); 
  Serial.print("  Imin = " ); 
  Serial.println(Intensidad_minima); */

  delay(100);                     
}


