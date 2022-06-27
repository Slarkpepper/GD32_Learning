#include "gd32f4xx.h"
#include "gd32f450z_eval.h"
#include "systick.h"

#include "key_poiling.h"


int main(void) {


    systick_config();

    keyInit();

    return 0;
}
