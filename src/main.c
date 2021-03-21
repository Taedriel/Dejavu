#include "racing_driver.h"
#include "racing_io.h"

int main()
{
    
    int row;
    int width, height;
    int round = 0;
    int gas = 0;
    char line_buffer[MAX_LINE_LENGTH];

    struct car_t cars[3];

    fgets(line_buffer, MAX_LINE_LENGTH, stdin); /* Read gas level at Start */
    sscanf(line_buffer, "%d %d %d", &width, &height, &gas);

    init_car(cars, BOOSTS_AT_START, 1, 0, 0, 0, gas);
    init_car(cars+1, BOOSTS_AT_START, 1, 0, 0, 0, gas);
    init_car(cars+2, BOOSTS_AT_START, 1, 0, 0, 0, gas);


    fprintf(stderr, "=== >Map< ===\n");
    fprintf(stderr, "Size %d x %d\n", width, height);

    for (row = 0; row < height; ++row)
    { /* Read map data, line per line */
        fgets(line_buffer, MAX_LINE_LENGTH, stdin);
        /*fputs(line_buffer, stderr);*/
    }

    RACE_START()

    while (!feof(stdin))
    {
        round++;

        RACE_ROUND(round)

        read_positions(cars);
        /* Gas consumption cannot be accurate here. */
        consum_gas(cars, 0);

        /* Write the acceleration request to the race manager (stdout). */
        post_actions(cars);

        if (0 && round > 4)
        { /* (DISABLED) Force a segfault for testing purpose */
            int *p = NULL;
            RACE_END()
            *p = 0;
        }
    }

    return EXIT_SUCCESS;
}