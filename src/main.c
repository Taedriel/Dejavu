#include "racing_driver.h"
#include "racing_io.h"

int main()
{
    int row;
    int width, height;
    int round = 0;
    char action[100];
    char line_buffer[MAX_LINE_LENGTH];

    struct car_t cars[3];

    fgets(line_buffer, MAX_LINE_LENGTH, stdin); /* Read gas level at Start */
    sscanf(line_buffer, "%d %d %d", &width, &height, &(cars[0].gas_level));
    
    cars[0].boosts = BOOSTS_AT_START;
    cars[0].acc_x = 1;
    cars[0].acc_y = 0;
    cars[0].spe_x = 0;
    cars[0].spe_y = 0;

    fprintf(stderr, "=== >Map< ===\n");
    fprintf(stderr, "Size %d x %d\n", width, height);
    fprintf(stderr, "Gas at start %d \n\n", cars[0].gas_level);

    for (row = 0; row < height; ++row)
    { /* Read map data, line per line */
        fgets(line_buffer, MAX_LINE_LENGTH, stdin);
        fputs(line_buffer, stderr);
    }

    RACE_START()

    while (!feof(stdin))
    {
        int myX, myY, secondX, secondY, thirdX, thirdY;
        round++;

        RACE_ROUND(round)

        read_positions(cars);

        /* Gas consumption cannot be accurate here. */
        cars[0].gas_level += gas_consumption(&cars[0], 0);
        cars[0].spe_x += cars[0].acc_x;
        cars[0].spe_y += cars[0].acc_y;

        /* Write the acceleration request to the race manager (stdout). */
        post_actions(&cars[0]);

        RACE_BRIEF(action, cars[0].gas_level)

        if (0 && round > 4)
        { /* (DISABLED) Force a segfault for testing purpose */
            int *p = NULL;
            RACE_END()
            *p = 0;
        }
    }

    return EXIT_SUCCESS;
}