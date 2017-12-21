/*
   Un sketch pour la chouette animee : 1 servo SG90 & un capteur infra Rouge sur une carte Arduino Nano
   Calibration du moteur d'apres le tuto d'Eskimon : http://eskimon.fr/287-arduino-602-un-moteur-qui-de-la-tete-le-servo-moteur
   pour le mien j'ai vu ue son min = 1250 (position "eveillee") & son max env. 2400 (position "endormie")
   mais je n'ai pas besoin de tant d'amplitude sur le jouet
   Usage du capteur d'apres l exemple en anglais  http://henrysbench.capnfatz.com/henrys-bench/arduino-sensors-and-input/arduino-ir-obstacle-sensor-tutorial-and-manual/

   Objectif :
   la chouette s'anime (== le moteur fait un cycle) quand elle détecte un mouvement à proximité
*/

#include <Servo.h> // bibliothèque moteurs

Servo monServo; // declaration du moteur
int tpsMoteur = 0; // une case pour ranger les impulsions envoyees au moteur
// et 2 autres pour se souvenir des butees de mon moteur
const int tpsMoteurMax = 2360;
const int tpsMoteurMin = 1500;

const int pinCapteur = 4; // declaration de la broche capteur IR
int valCapteur = HIGH; // une case pour ranger la valeur reçue HIGH = pas d'obstacle

void setup() {   // jouée 1 fois
  //on déclare l'entrée du servo connectée sur la broche 2
  monServo.attach(A2);
  // le capteur est une entrée :
  pinMode(pinCapteur, INPUT);
  //on oublie pas de démarrer la liaison série ;-)
  Serial.begin(9600);

}

void loop() {   // repetee à l'infini...
  // au début la chouette est endormie
  monServo.writeMicroseconds(tpsMoteurMax);

  // on lit la valeur du capteur
  valCapteur = digitalRead(pinCapteur);
  Serial.println(valCapteur); // envoi sur le moniteur de controle

  // lance une boucle si on capte un obstacle
  if (valCapteur == LOW) {
    for (int i = tpsMoteurMax; i>= tpsMoteurMin; i--) {
      monServo.writeMicroseconds(i);
      delay(5);
    } delay(5000); // on attend 5 sec eveillee
    Serial.println("HOU HOU HOU");
    // et on rendort....
    for (int i = tpsMoteurMin; i<= tpsMoteurMax; i++) {
      monServo.writeMicroseconds(i);
      delay(5);
    }
  }
}
