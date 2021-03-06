
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

    float fireFlame = 15;
    float fireFlameWave2 = 50;
    float fireFlameWave3 = 50;
    float fireFlameWave4 = 100;
    float fireFlameWave5 = 100;

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
          if (countEffect1 > 250) {
            resetPlayer();
          }
          fireFirstPositionC = fireFirstPositionC + speedC;
          speedC = speedC + gravity;
          playerFireFirstC = playerFireFirstC - 0.8;
          playerFireSecondC = playerFireSecondC - 0.8 ;

          if (fireFirstPositionC > 100) {
            speedC = speedC * -1;
            countEffect1 ++;
          }

          if (fireFirstPositionC < 1) {
            fireFirstPositionC = 1;
          }
          countEffect1 ++;
        } else if (effect2 == true) {
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
            if (playerFireSecondC < 100) {
              effect1 = true;
              fireFirstPositionC = 5;
            } else if (playerFireSecondC > 100 && playerFireSecondC < 180) {
              effect3 = true;
              fireFirstPositionC = 5;
            } else if (playerFireSecondC > 180) {
              effect2 = true;
              fireFirstPositionC = 5;
            }
          }
        }
      }
      // ----------second player---------------------
      if (playerPositionC == 137) {
        if (effect1 == true) {
          if (countEffect1 > 250) {
            resetPlayer();
          }
          fireFirstPositionC = fireFirstPositionC - speedC;
          speedC = speedC + gravity;
          playerFireFirstC = playerFireFirstC - 0.8;
          playerFireSecondC = playerFireSecondC - 0.8 ;
          if (fireFirstPositionC < 40) {
            speedC = speedC * -1;
            countEffect1 ++;
          }
          if (fireFirstPositionC > 137) {
            fireFirstPositionC = 138;
          }
          countEffect1 ++;
        } else if (effect2 == true) {
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
            if (playerFireSecondC < 100) {
              effect1 = true;
            } else if (playerFireSecondC > 100 && playerFireSecondC < 180) {
              effect3 = true;
            } else if (playerFireSecondC > 180) {
              effect2 = true;
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
      if (playerPositionC == 137) {
        fireFirstPositionC = 137;
      } else {
        fireFirstPositionC = 5;
      }
      playerFireFirstC = 0;
      playerFireSecondC = 0;
      speedC = 0;
      fireFlame = 15;
      fireFlameWave2 = 50;
      fireFlameWave3 = 50;
      fireFlameWave4 = 100;
      fireFlameWave5 = 100;
      defence = false;
    }

    void resetPlayerNewGame() {
      effect1 = false;
      effect2 = false;
      effect3 = false;
      countEffect1 = 0;
      if (playerPositionC == 137) {
        fireFirstPositionC = 137;
      } else {
        fireFirstPositionC = 5;
      }
      playerFireFirstC = 0;
      playerFireSecondC = 0;
      speedC = 0;
      load = 0.4;
      energyPlayerC = 5;
      defence = false;
      fireFlame = 15;
      fireFlameWave2 = 50;
      fireFlameWave3 = 50;
      fireFlameWave4 = 100;
      fireFlameWave5 = 100;
    }
};
