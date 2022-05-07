static int coreOne = 0;
static int coreTwo = 1;

void Task1(void *pvParamters);
void Task2(void *pvParamters);

void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.println("Mention delay needed for LED blinking");
    pinMode(LED_BUILTIN, OUTPUT);
    
    xTaskCreatePinnedToCore(Task1, "Task1", 1024,(void*)0, 0, NULL, coreOne);
    xTaskCreatePinnedToCore(Task2, "Task2", 1024, &dataIN, 0, NULL, coreTwo);

    vTaskStartScheduler();
}

void Task1(void *x1){
  int Delay = ((int) x1); 
  while(1){
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay(pdMS_T_TICKS(Delay));
    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay(pdMS_T_TICKS(Delay));
  }
}

void Task2(void *pvParamters){
  while(Serial.available() > 0){
    static int dataIN = Serial.parseInt();
    Serial.print(dataIN);
    delay(500);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
