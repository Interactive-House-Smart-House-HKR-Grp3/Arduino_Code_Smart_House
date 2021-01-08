/*
   String receivedString - String that is going to be split
   char delimiter - Separator character used to separate strings
   uint8_t index - position in array of extracted strings (0-topic, 1-message)
*/

String splitString(String receivedString, char delimiter[], uint8_t index)
{
  int d;
  char *p;
  char rcvdstr[receivedString.length()];
  String words[3];

  receivedString.toCharArray(rcvdstr, sizeof(rcvdstr));
  d = 0;
  p = strtok(rcvdstr, delimiter);
  while (p && d < 3)
  {
    words[d] = p;
    p = strtok(NULL, delimiter);
    ++d;
  }
  return words[index];
}
