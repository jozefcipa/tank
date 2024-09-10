struct TankCommand {
  char *lights;
  char *sensors;
};

struct TankCommand TANK_parseMessage(char *msgStr);

