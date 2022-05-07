static int coreOne = 0;
static int coreTwo = 1;

void blinkRoutine1(void *pvParamters);
void blinkRoutine2(void *pvParamters);

void setup() {
  // put your setup code here, to run once:
    pinMode(26, OUTPUT);
    pinMode(27, OUTPUT);
       
    xTaskCreatePinnedToCore(blinkRoutine1, "Routine01", 1024,(void*)0, 1, NULL, coreOne);
    xTaskCreatePinnedToCore(blinkRoutine2, "Routine02", 1024,(void*)0, 1, NULL, coreTwo);

    vTaskStartScheduler();
}

void blinkRoutine1(void *pvParamters){
  while(1){
    digitalWrite(26, HIGH);
    vTaskDelay(pdMS_T_TICKS(500));
    digitalWrite(26, LOW);
    vTaskDelay(pdMS_T_TICKS(500));
  }
}

void blinkRoutine2(void *pvParamters){
  while(1){
    digitalWrite(27, HIGH);
    vTaskDelay(pdMS_T_TICKS(300));
    digitalWrite(27, LOW);
    vTaskDelay(pdMS_T_TICKS(300));
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
