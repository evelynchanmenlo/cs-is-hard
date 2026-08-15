#include <stdio.h>
#include <cs50.h>

int main (int argc, string argv[])
{
  // Verify correct usage
  if (argc != 3)
  {
    printf("Usage: ./copy <input file> <output file>\n");
    return 1;
  }

  // Create a file pointer to the source file, argv[1] for reading
  FILE *ptr = fopen(argv[1], "r");

  // If the file doesn't exist, (the FILE pointer is NULL) print an error message and exit by returning 1
  if (ptr == NULL)
  {
    printf("Error opening file!\n");
    return 1;
  }

  // Create a file pointer to the destination file, argv[2], for writing
  FILE *ptr2 = fopen(argv[2], "w");

  // If the pointer is NULL, print an error, close the soruce file, and exit
  if (ptr2 == NULL)
  {
    printf("Error opening file!\n");
    return 1;
  }

  // Read the contents of the source file one character at a time, and write to the destination file
  char c = fgetc(ptr);
  while (c != EOF)
  {
    fprintf(ptr2, "%c", c);
    c = fgetc(ptr);
  }

  // Close both the source and destination files
  fclose(ptr);
  fclose(ptr2);
}
