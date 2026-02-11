#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct { double flight_time, range, apex; } Trajectory;

static Trajectory integrate(double speed, double angle, double mass, double drag) {
    const double gravity = 9.80665, timestep = 0.001;
    double radians = angle * acos(-1.0) / 180.0;
    double position[2] = {0.0, 0.0};
    double velocity[2] = {speed * cos(radians), speed * sin(radians)};
    Trajectory result = {0.0, 0.0, 0.0};
    for (int step = 0; step < 2000000; ++step) {
        double magnitude = hypot(velocity[0], velocity[1]);
        double previous_x = position[0], previous_y = position[1];
        velocity[0] -= timestep * drag * magnitude * velocity[0] / mass;
        velocity[1] -= timestep * (gravity + drag * magnitude * velocity[1] / mass);
        position[0] += timestep * velocity[0];
        position[1] += timestep * velocity[1];
        if (position[1] > result.apex) result.apex = position[1];
        if (position[1] < 0.0) {
            double fraction = previous_y / (previous_y - position[1]);
            result.flight_time = (step + fraction) * timestep;
            result.range = previous_x + fraction * (position[0] - previous_x);
            return result;
        }
    }
    fprintf(stderr, "Integration horizon exceeded\n");
    exit(EXIT_FAILURE);
}

int main(void) {
    double speed, angle, mass, drag;
    if (scanf("%lf %lf %lf %lf", &speed, &angle, &mass, &drag) != 4 ||
        !isfinite(speed) || !isfinite(angle) || !isfinite(mass) || !isfinite(drag) ||
        speed <= 0 || speed > 1000 || angle <= 0 || angle >= 90 || mass <= 0 ||
        drag < 0 || drag * speed * 0.001 / mass > 0.1) {
        fprintf(stderr, "Invalid physical inputs or unstable timestep\n");
        return EXIT_FAILURE;
    }
    Trajectory result = integrate(speed, angle, mass, drag);
    printf("flight_time_s,range_m,apex_m\n%.6f,%.6f,%.6f\n",
        result.flight_time, result.range, result.apex);
    return EXIT_SUCCESS;
}
