/*
 * char[] receivedString - String that is going to be split
 * String separator - Separator character used to separate strings
 * int arrPosition - position in array of extracted strings (1-topic, 2-message)
 */
 
String splitString(char receivedString[], char separator, int arrPosition){
     int counterS = 0;
   char *strings[3];
   // Extract the first token
   char * token = strtok(receivedString, separator);
   // loop through the string to extract all other tokens
   while( token != NULL ) {
      strings[i] = token;
      i++;
      token = strtok(NULL, " ");
   }
   
   return strings[arrPosition];
  }
