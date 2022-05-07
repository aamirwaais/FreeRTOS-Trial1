static int coreOne = 0;
static int coreTwo = 1;

void TaskA(void *pvParamters);
void TaskB(void *pvParamters);

void setup() {
    Serial.begin(115200);    
    xTaskCreatePinnedToCore(TaskA, "TaskA", 1024,(void*)0, 1, NULL, coreOne);
    xTaskCreatePinnedToCore(TaskB, "TaskB", 1024,(void*)0, 1, NULL, coreTwo);
    vTaskStartScheduler();
}

void TaskA(void *pvParamters){
  while(1){
     Serial.print("I am Task A I am Running on Core");
     Serial.println(xPortGetCoreID());
  }
}

void TaskB(void *pvParamters){
  while(1){
    Serial.print("I am Task A I am Running on Core");
    Serial.println(xPortGetCoreID());
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
