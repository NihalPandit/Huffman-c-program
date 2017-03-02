#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void main()
{
  int a, b;

  ///I

  //1
  char Letter[27] = " abcdefghijklmnopqrstuvwxyz";

  //2
  int ASCII[27];
  for (a = 0; a <= 26; a++)

  {
    ASCII[a] = Letter[a];
  }

  //3
  int Occurrence[27];
  for (a = 0; a <= 26; a++)
  {
    Occurrence[a] = 0;
  }

  //4
  int total = 0;

  FILE *fp;
  char ch;
  fp = fopen("IronHeel.txt", "r");
  while (1)
  {
    ch = fgetc(fp);
    //3
    if (ch == ' ' || ch == ',' || ch == '.' || ch == ';' || ch == '\n') //space, comma,colon, semi-colon
    {
      Occurrence[0]++; //if it was a space
      total++;
    }
    else
    {
      for (a = 1; a <= 26; a++)
      {
        if (ch == ASCII[a])
        {
          Occurrence[a]++;
          total++;
        }
      }
    }
    if (ch == EOF)
      break;
  }
  fclose(fp);
  //4
  double Frequency[27];

  for (a = 0; a <= 26; a++)
  {
    Frequency[a] = 1.0 * Occurrence[a] / total;
  }

  //5
  double Ordered_Frequency[27];
  for (a = 0; a <= 26; a++)
  {
    Ordered_Frequency[a] = Frequency[a];
  }

  char Letter2[27] = " abcdefghijklmnopqrstuvwxyz";
  char Letter21[27] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  //simple sort
  for (a = 0; a <= 26; a++)
  {
    for (b = a + 1; b <= 26; b++)
    {
      if (Ordered_Frequency[a] < Ordered_Frequency[b])
      {
        double temp = Ordered_Frequency[a];
        Ordered_Frequency[a] = Ordered_Frequency[b];
        Ordered_Frequency[b] = temp;
        char temp2 = Letter2[a];
        Letter2[a] = Letter2[b];
        Letter2[b] = temp2;
        char temp21 = Letter21[a];
        Letter21[a] = Letter21[b];
        Letter21[b] = temp21;
      }
    }
  }

  //6
  char Huffman_Code[27][12] = {
      "100",
      "0010",
      "0011",
      "1111",
      "1110",
      "1100",
      "1011",
      "1010",
      "0110",
      "0101",
      "11011",
      "01111",
      "01001",
      "01000",
      "00011",
      "00010",
      "00001",
      "00000",
      "110101",
      "011101",
      "011100",
      "1101001",
      "110100011",
      "110100001",
      "110100000",
      "1101000101",
      "11010001000"};

  printf("1 = Display all the 6 Arrays along with the Compression Rate\n");
  printf("2 = Display the ciphered text\n");
  char response = '0';
  while (response != '1' && response != '2')
    scanf("%c", &response);

  if (response == '1')
  {
    printf("Letter\tASCII\tOccurrence\n");
    for (a = 0; a <= 26; a++)
      printf("%c\t%d\t%d\n", Letter[a], ASCII[a], Occurrence[a]);
    printf("\n\n");
    printf("Ordered_Freq\tHuffman_Code\tLetter\n");
    for (a = 0; a <= 26; a++)
      printf("%lf\t%13s%13c\n", Ordered_Frequency[a], Huffman_Code[a], Letter2[a]);

    int SizeCiphered = 0;
    int SizeClear = total * 8;

    fp = fopen("IronHeel.txt", "r");
    while (1)
    {
      ch = fgetc(fp);
      //3
      if (ch == ' ' || ch == ',' || ch == '.' || ch == ';' || ch == '\n') //space, comma,colon, semi-colon
      {
        for (a = 0; a <= 26; a++)
          if (Letter2[a] == ' ')
            SizeCiphered += strlen(Huffman_Code[a]);
      }
      else
      {
        for (a = 0; a <= 26; a++)
          if (Letter2[a] == ch)
            SizeCiphered += strlen(Huffman_Code[a]);
      }
      if (ch == EOF)
        break;
    }
    fclose(fp);
    printf("Compression Rate: %lf\n", 100 - (100 * (1.0 * SizeCiphered / SizeClear)));
  }
  else
  {
    fp = fopen("IronHeel.txt", "r");
    FILE *fout = fopen("Soutput.txt", "w");
    while (1)
    {
      ch = fgetc(fp);
      //3
      if (ch == ' ' || ch == ',' || ch == '.' || ch == ';') //space, comma,colon, semi-colon
      {
        for (a = 0; a <= 26; a++)
          if (Letter2[a] == ' ' || Letter21[a] == ch)
            //printf("%s",Huffman_Code[a]),fprintf(fout,"%s",Huffman_Code[a]);
            fprintf(fout, "%s", Huffman_Code[a]);
      }
      else
      {
        for (a = 0; a <= 26; a++)
          if (Letter2[a] == ch || Letter21[a] == ch)
            //printf("%s",Huffman_Code[a]),fprintf(fout,"%s",Huffman_Code[a]);
            fprintf(fout, "%s", Huffman_Code[a]);
      }
      if (ch == EOF)
        break;
    }
    printf("File Written\n");
    fclose(fp);
    fclose(fout);

    printf("\n");
    printf("Would you want to see the plain text (Decoding of the ciphered text)? Y/N\n");
    while (toupper(response) != 'Y' && toupper(response) != 'N')
      scanf("%c", &response);
    if (toupper(response) == 'Y')
    {
      fp = fopen("Soutput.txt", "r");
      FILE *fout = fopen("DSoutput.txt", "w");
      char temp[30]; //temp string that we will use to create huffman codes

      strcpy(temp, "");
      while (1)
      {
        ch = fgetc(fp);

        int length = strlen(temp);
        temp[length] = ch; //added ch at the end of temp
        temp[length + 1] = 0;
        for (a = 0; a <= 26; a++)
          if (strcmp(temp, Huffman_Code[a]) == 0) //if its a code from the list
          {
            //printf("%c",toupper(Letter2[a]));//print it
            fprintf(fout, "%c", toupper(Letter2[a]));

            //			bs3-40mrks
            //            hash-5
            //            tree-1q-5
            //            binar-
            //            sorting topolog 20marks

            strcpy(temp, "");
          }
        if (ch == EOF)
          break;
      }
      printf("File Written\n");

      fclose(fp);
      fclose(fout);
    }
  }
}
