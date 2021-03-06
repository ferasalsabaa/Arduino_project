class Player {

  public:
    int playerPositionC;
    int powerPlayer;
    int farPlayer;
    int j = 0;
    Player(int playerPosition, int power, int far) {
      playerPositionC = playerPosition;
      powerPlayer = power;
      farPlayer = far;
    }
    void playShow(int& sensorValue, CRGB led[], int NUM_LEDS, int& sensorValueB, int& playerFire, int& FireCase) {
      if (sensorValueB > 7 && sensorValue < 7  && playerFire <= 200) {
        playerFire++;
      }
      if (sensorValue < 7 && sensorValueB < 7) {
        FireCase = 1;
      }
    }

    boolean defenceTest(int& sensorWertC, int& sensorWertD) {
      if (sensorWertD < 7 && sensorWertC > 7) {
        return true;
      } else {
        return false;
      }
    }
    void resetPlayer(int& playerFireSecond, int& playerFireFirst, int& fireCase, boolean& defence, boolean& defenceShow) {
      playerFireSecond = 0;
      playerFireFirst = 0;
      fireCase = 0;
      defence = false;
      defenceShow = false;
    }
};
