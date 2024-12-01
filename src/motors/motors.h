namespace motors {
  extern boolean motorsRunning;
  void drive(char motorA, char directionA, char motorB, char directionB);
  void stop(char motorId);
}