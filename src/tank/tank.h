namespace tank {
  struct Command {
    char *lights;
    char *sensors;
  };

  struct Command parseMessage(char *msgStr);
}