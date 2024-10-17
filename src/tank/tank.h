namespace tank {
  struct Command {
    char *lights;
    char *sensors;
    char *motors;
  };

  struct Command parseMessage(char *msgStr);
}