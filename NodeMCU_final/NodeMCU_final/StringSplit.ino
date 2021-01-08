/*
   char[] receivedString - String that is going to be split
   String separator - Separator character used to separate strings
   int arrPosition - position in array of extracted strings (1-topic, 2-message)
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
