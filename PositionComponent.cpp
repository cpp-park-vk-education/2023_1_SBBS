#include "PositionComponent.h"

int moving(int coordinate, int speed, float prop) {
    return coordinate + int(prop * speed);
}

int calculate_coner(const Input_vector& input_vector) {
    double cos = (base_x * input_vector.x + base_y * input_vector.y) /
        (sqrt(base_x * base_x + base_y * base_y) * sqrt(input_vector.x * input_vector.x + input_vector.y * input_vector.y));
    return acos(cos) * 180 / 3.14;
}

int calculate_angle(Input_vector a, Input_vector b) {
    double cos = (a.x * b.x + a.y * b.y) /
        (sqrt(a.x * a.x + a.y * a.y) * sqrt(b.x * b.x + b.y * b.y));
    return acos(cos) * 180 / 3.14;
}

int distance_p(Position a, Position b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
