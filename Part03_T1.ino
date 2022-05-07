//#include "FreeRTOS.h"
//#include "task.h"

//static const int blink_led = LED_BUILTIN;

void blinkLED(void *pvParamters){
  while(1){
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay(pdMS_T_TICKS(500));
    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay(pdMS_T_TICKS(500));
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);

  xTaskCreate(blinkLED, "blinkLED", 1024, NULL, 1, NULL);
     
  }
}
void loop() {
  // put your main code here, to run repeatedly:

}
