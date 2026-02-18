#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check if the program has received exactly one argument (for the image file)
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open the forensic image file (card.raw)
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Allocate a buffer to store 512 bytes at a time
    unsigned char *buffer = malloc(512);
    if (buffer == NULL)
    {
        printf("Memory allocation failed.\n");
        fclose(card);
        return 1;
    }

    // Allocate a fixed-size array for the filename
    char filename[8]; // "000.jpg" needs 7 characters + null terminator
    int photoCount = 0;
    FILE *imageFile = NULL;

    // Read the forensic image file 512 bytes at a time
    while (fread(buffer, sizeof(unsigned char), 512, card) == 512)
    {
        // Check for the JPEG signature (0xFF 0xD8 0xFF 0xE0 - 0xEF)
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If we found a new JPEG, close the previous one and start a new one
            if (photoCount > 0)
            {
                fclose(imageFile); // Close the previous image file
            }

            // Create a new filename for the current JPEG
            sprintf(filename, "%03i.jpg", photoCount);

            // Open a new file for the current JPEG
            imageFile = fopen(filename, "w");
            if (imageFile == NULL)
            {
                printf("Could not create file: %s\n", filename);
                free(buffer);
                fclose(card);
                return 1;
            }

            // Write the first 512 bytes (of the new image)
            fwrite(buffer, sizeof(unsigned char), 512, imageFile);
            photoCount++; // Increment the photo count for the next JPEG
        }
        else if (photoCount > 0)
        {
            // If we are in the middle of a JPEG, continue appending bytes
            fwrite(buffer, sizeof(unsigned char), 512, imageFile);
        }
    }

    // After finishing, close the last file and free memory
    if (imageFile != NULL)
    {
        fclose(imageFile);
    }
    fclose(card);
    free(buffer);

    // Print the total number of recovered photos
    printf("Recovered %i images.\n", photoCount);

    return 0;
}