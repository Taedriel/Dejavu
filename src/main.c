#include "racing_driver.h"
#include "racing_io.h"

int main()
{
    /*int row;*/
    int width, height;
    int round = 0;
    int gas = 0;
    char action[100];
    char line_buffer[MAX_LINE_LENGTH];

    struct car_t cars[3];

    fgets(line_buffer, MAX_LINE_LENGTH, stdin); /* Read gas level at Start */
    sscanf(line_buffer, "%d %d %d", &width, &height, &gas);

    init_car(cars, BOOSTS_AT_START, 1, 0, 0, 0, gas);

    #if 0
    fprintf(stderr, "=== >Map< ===\n");
    fprintf(stderr, "Size %d x %d\n", width, height);
    fprintf(stderr, "Gas at start %d \n\n", cars[0].gas_level);

    for (row = 0; row < height; ++row)
    { /* Read map data, line per line */
        fgets(line_buffer, MAX_LINE_LENGTH, stdin);
        fputs(line_buffer, stderr);
    }
    #endif

    RACE_START()

    while (!feof(stdin))
    {
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