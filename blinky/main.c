#include <ch.h>
#include <hal.h>

#include <stm32l1xx_lcd.h>

const uint8_t Hello[] = "ChibiOS";

int main(void) {
  halInit();
  chSysInit();

  /*
   * This initialization requires the OS already active because it uses delay
   * APIs inside.
   */

  int active = GPIOB_LED4;
  int inactive = GPIOB_LED3;

  palSetPadMode(GPIOB, GPIOB_LED4, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOB, GPIOB_LED3, PAL_MODE_OUTPUT_PUSHPULL);

  palSetPad(GPIOB, active);
  palClearPad(GPIOB, inactive);

  while (1) {
    if (palReadPad(GPIOA, GPIOA_BUTTON)) {
      int store = active;
      active = inactive;
      inactive = store;
      palSetPad(GPIOB, active);
      palClearPad(GPIOB, inactive);
    }

    chThdSleepMilliseconds(500);
  }
}

