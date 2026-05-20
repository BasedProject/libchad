#include "grand.h"

RANDOM_CONCAT(u,GRAND_WIDTH) (*grand_next)(grand_t *) = grand_next_init;
grand_t grand_value[1];
