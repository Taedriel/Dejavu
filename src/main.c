#include "racing_driver.h"
#include "racing_io.h"

int main()
{
    int row;
    int width, height;
    int round = 0;
    char action[100];
    char line_buffer[MAX_LINE_LENGTH];

    struct car_t player_car;

    fgets(line_buffer, MAX_LINE_LENGTH, stdin); /* Read gas level at Start */
    sscanf(line_buffer, "%d %d %d", &width, &height, &(player_car.gas_level));
    
    player_car.boosts = BOOSTS_AT_START;
    player_car.acc_x = 1;
    player_car.acc_y = 0;
    player_car.spe_x = 0;
    player_car.spe_y = 0;

    fprintf(stderr, "=== >Map< ===\n");
    fprintf(stderr, "Size %d x %d\n", width, height);
    fprintf(stderr, "Gas at start %d \n\n", player_car.gas_level);

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

        fgets(line_buffer, MAX_LINE_LENGTH, stdin); /* Read positions of pilots */

        sscanf(line_buffer, "%d %d %d %d %d %d",&myX, &myY, &secondX, &secondY, &thirdX, &thirdY);

        fprintf(stderr, "    Positions: Me(%d,%d)  A(%d,%d), B(%d,%d)\n",myX, myY, secondX, secondY, thirdX, thirdY);
        fflush(stderr);

        /* Gas consumption cannot be accurate here. */
        player_car.gas_level += gas_consumption(&player_car, 0);
        player_car.spe_x += player_car.acc_x;
        player_car.spe_y += player_car.acc_y;

        /* Write the acceleration request to the race manager (stdout). */
        post_actions(&player_car);

        fprintf(stderr, "    Action: %s   Gas remaining: %d\n", action, player_car.gas_level);
        fflush(stderr);

        if (0 && round > 4)
        { /* (DISABLED) Force a segfault for testing purpose */
            int *p = NULL;
            fprintf(stderr, "Good Bye!\n");
            fflush(stderr);
            *p = 0;
        }
    }

    return EXIT_SUCCESS;
}