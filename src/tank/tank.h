namespace tank {
  void setup();

  struct Command {
    char *lights;
    char *sensors;
    char *motors;
  };

  struct Command parseMessage(char *msgStr);

  void handleMotors(char *cmdVal);
  boolean shouldStopMotors();
  void stopMotors();

  void handleSensors(char *cmdVal);
  void handleLEDLights(char *cmdVal);
}