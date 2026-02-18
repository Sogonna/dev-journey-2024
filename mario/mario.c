#include cs50.h
#include stdio.h

int main(void)
{
    int height;

     Prompt the user for the height of the pyramid
    do
    {
        printf(Height );
        scanf(%d, &height);
    }
    while (height  1  height  8);  Ensure the height is between 1 and 8

     Print the two pyramids
    for (int i = 0; i  height; i++)
    {
         Print leading spaces for the left-aligned pyramid
        for (int j = 0; j  height - i - 1; j++)
        {
            printf( );
        }

         Print hashes for the left-aligned pyramid
        for (int j = 0; j  i + 1; j++)
        {
            printf(#);
        }

         Print the gap between the two pyramids (2 spaces)
        printf(  );

         Print hashes for the right-aligned pyramid
        for (int j = 0; j  i + 1; j++)
        {
            printf(#);
        }

         Move to the next line after each row
        printf(n);
    }

    return 0;
}