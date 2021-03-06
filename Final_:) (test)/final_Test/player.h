
class Player {

  public:
    int playerPositionC;

    float fireFirstPositionC;

    float playerFireFirstC;
    float playerFireSecondC;

    boolean defence;

    int energyPlayerC;


    float speedC = 0;
    float gravity = 0.009;

    boolean effect1 = false;
    int countEffect1 = 0;


    boolean effect2 = false;

    boolean effect3 = false;

    float load = 0.4;

    float fireFlame = 35;
    float fireFlameWave2 = 116;
    float fireFlameWave3 = 116;
    float fireFlameWave4 = 280;
    float fireFlameWave5 = 280;

    boolean defenceStrong;

    Player(int playerPosition, float fireFirstPosition, float playerFireFirst, float playerFireSecond, int energyPlayer) {
      playerPositionC = playerPosition;

      fireFirstPositionC = fireFirstPosition;

      playerFireFirstC = playerFireFirst;
      playerFireSecondC = playerFireSecond;

      energyPlayerC = energyPlayer;
      load = 0.4;

    }
    void playShow(int& sensorValue, int& sensorValueB) {
      // ----------first player---------------------
      if (playerPositionC == 6) {

        if (effect1 == true) {
          /*  if (countEffect1 > 250) {
              resetPlayer();
            } */
          fireFirstPositionC = fireFirstPositionC + speedC;
          speedC = speedC + gravity;
          playerFireFirstC = playerFireFirstC - 0.8;
          playerFireSecondC = playerFireSecondC - 0.8 ;

          if (fireFirstPositionC > 100) {
            resetPlayer();
            //   speedC = speedC * -1;
            //   countEffect1 ++;
          }

          /* if (fireFirstPositionC < 1) {
             fireFirstPositionC = 1;
            }
            countEffect1 ++;*/
        } else if (effect2 == true) {
          playerFireFirstC = playerFireFirstC - 1.8;
          playerFireSecondC = playerFireSecondC - 1.8 ;
          fireFirstPositionC = fireFirstPositionC + speedC + 0.5;
          speedC = speedC + gravity;
          if (fireFirstPositionC > 140) {
            resetPlayer();
          }
        } else if (effect3 == true) {

        } else {
          if (sensorValueB > 7 && sensorValue < 7  && playerFireFirstC <= 200) {
            playerFireFirstC = playerFireFirstC + 0.6;
          } else if (sensorValueB > 7 && sensorValue < 7  && playerFireFirstC >= 200 && playerFireSecondC < 200) {
            playerFireSecondC = playerFireSecondC + 0.6;
          } else if (sensorValueB < 7 && sensorValue > 7  && playerFireFirstC <= 10) {
            defence = true;
          }
          if (sensorValue < 7 && sensorValueB < 7 && playerFireSecondC > 10) {
            if (playerFireSecondC <= 90) {
              effect3 = true;
              fireFirstPositionC = 5;
            } else if (playerFireSecondC > 90 && playerFireSecondC <= 180) {
              effect3 = true;
              fireFirstPositionC = 5;
            } else if (playerFireSecondC > 180) {
              effect3 = true;
              fireFirstPositionC = 5;
            }
          }
        }
      }
      // ----------second player---------------------
      if (playerPositionC == 143) {
        if (effect1 == true) {
          if (countEffect1 > 250) {
            resetPlayer();
          }
          fireFirstPositionC = fireFirstPositionC - speedC;
          speedC = speedC + gravity;
          playerFireFirstC = playerFireFirstC - 0.8;
          playerFireSecondC = playerFireSecondC - 0.8 ;
          if (fireFirstPositionC < 40) {
            /*speedC = speedC * -1;
              countEffect1 ++;*/
            resetPlayer(); //****
          }
          /*     if (fireFirstPositionC > 137) {
                 fireFirstPositionC = 138;
               }
               countEffect1 ++;*/
        } else if (effect2 == true) {
          playerFireFirstC = playerFireFirstC - 1.8;
          playerFireSecondC = playerFireSecondC - 1.8 ;
          fireFirstPositionC = fireFirstPositionC - speedC - 0.5;
          speedC = speedC + gravity;
          if (fireFirstPositionC < 4) {
            resetPlayer();
          }
        } else if (effect3 == true) {

        } else {
          if (sensorValueB > 7 && sensorValue < 7  && playerFireFirstC <= 200) {
            playerFireFirstC = playerFireFirstC + 0.6;
          } else if (sensorValueB > 7 && sensorValue < 7  && playerFireFirstC >= 200 && playerFireSecondC < 200) {
            playerFireSecondC = playerFireSecondC + 0.6;
          } else if (sensorValueB < 7 && sensorValue > 7  && playerFireFirstC <= 10) {
            defence = true;
          }
          if (sensorValue < 7 && sensorValueB < 7 && playerFireSecondC > 10) {
            if (playerFireSecondC <= 90) {
              effect3 = true;
            } else if (playerFireSecondC > 90 && playerFireSecondC <= 190) {
              effect3 = true;
            } else if (playerFireSecondC > 190) {
              effect3 = true;
            }
          }
        }
      }
    }

    void resetPlayer() {
      effect1 = false;
      effect2 = false;
      effect3 = false;
      countEffect1 = 0;
      if (playerPositionC == 143) {
        fireFirstPositionC = 143;
      } else {
        fireFirstPositionC = 5;
      }
      playerFireFirstC = 0;
      playerFireSecondC = 0;
      speedC = 0;
   
     fireFlame = 35;
     fireFlameWave2 = 116;
     fireFlameWave3 = 116;
     fireFlameWave4 = 280;
     fireFlameWave5 = 280;
      defence = false;
    }

    void resetPlayerNewGame() {
      effect1 = false;
      effect2 = false;
      effect3 = false;
      countEffect1 = 0;
      if (playerPositionC == 143) {
        fireFirstPositionC = 143;
      } else {
        fireFirstPositionC = 5;
      }
      playerFireFirstC = 0;
      playerFireSecondC = 0;
      speedC = 0;
      load = 0.4;
      energyPlayerC = 5;
      defence = false;

     fireFlame = 35;
     fireFlameWave2 = 116;
     fireFlameWave3 = 116;
     fireFlameWave4 = 280;
     fireFlameWave5 = 280;
    }

    void resetPlayerAttack() {

      defence = false;
    }
};
