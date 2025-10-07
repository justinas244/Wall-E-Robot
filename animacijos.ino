int animacija1_state = 0;
unsigned long animacija1_lastChange = 0;
bool animacija1_running = false;

int kaklas_s_target = 90;   // horizontalus servo (sukimasis)
int kaklas_v_target = 90;   // vertikalus servo (linkčiojimas)

float kaklas_s_pos = 90;    // dabartinė servo pozicija (plaukiojanti)
float kaklas_v_pos = 90;

unsigned long galva_lastChange = 0;
unsigned long galva_nextDelay = 2000;

bool galva_anim_running = false;



void startAnimacija1() {  //Antakiu kilnojimosi animacijos startas
  animacija1_state = 0;
  animacija1_lastChange = millis();
  animacija1_running = true;
}

void updateAnimacija1() {   /// Antakiu kilnojimo animacija
  if (!animacija1_running) return;

  unsigned long now = millis();

  switch (animacija1_state) {
    case 0:
      moveMotor(antakis_D, 60);
      moveMotor(antakis_L, 150);
      animacija1_lastChange = now;
      animacija1_state = 1;
      break;

    case 1:
      if (now - animacija1_lastChange >= 3000) {
        moveMotor(antakis_D, 30);
        moveMotor(antakis_L, 120);
        animacija1_lastChange = now;
        animacija1_state = 2;
      }
      break;

    case 2:
      if (now - animacija1_lastChange >= 3000) {
        moveMotor(antakis_L, 180);
        moveMotor(antakis_D, 0);
        animacija1_lastChange = now;
        animacija1_state = 3;
      }
      break;

    case 3:
      if (now - animacija1_lastChange >= 3000) {
        animacija1_running = false; // animacija baigta
      }
      break;
  }
}

void startGalvaAnimacija() {
  kaklas_s_target = 90;
  kaklas_v_target = 90;
  kaklas_s_pos = 90;
  kaklas_v_pos = 90;
  moveMotor(kaklas_s, 90);
  moveMotor(kaklas_v, 90);
  galva_lastChange = millis();
  galva_nextDelay = 2000;
  galva_anim_running = true;
}

int randomInRange(int minVal, int maxVal) {
  return minVal + random(maxVal - minVal + 1);
}

void updateGalvaAnimacija() {
  if (!galva_anim_running) return;

  unsigned long now = millis();

  // Kas kartą švelniai judam link tikslo
  float smoothSpeed = 0.1; // Kuo mažesnis - tuo lėčiau, natūraliau

  kaklas_s_pos += (kaklas_s_target - kaklas_s_pos) * smoothSpeed;
  kaklas_v_pos += (kaklas_v_target - kaklas_v_pos) * smoothSpeed;

  moveMotor(kaklas_s, (int)kaklas_s_pos);
  moveMotor(kaklas_v, (int)kaklas_v_pos);

  // Tikrinam ar laikas sugalvoti naują judesį
  if (now - galva_lastChange >= galva_nextDelay) {
    galva_lastChange = now;

    // Naujas tikslinis horizontalus kampas - atsitiktinai žvalgosi ~60-120
    kaklas_s_target = randomInRange(45, 135);

    // Naujas tikslinis vertikalus kampas - švelnus linkčiojimas ~75-105
    kaklas_v_target = randomInRange(75, 105);

    // Kita pauzė - atsitiktinė, tarsi "pagalvotų"
    galva_nextDelay = randomInRange(1000, 4000);
  }
}
