#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else 
static const BaseType_t app_cpu = 1;
#endif

static const int ledpin = 33;

int led_delay = 500;

void toggleLED(void *parameter){
while(1){
  digitalWrite(ledpin, HIGH);
  vTaskDelay(led_delay / portTICK_PERIOD_MS);
  digitalWrite(ledpin, LOW);
  vTaskDelay(led_delay / portTICK_PERIOD_MS);
}
}

void readserial(void *parameter){
  static int c;
  while(1){

    if(Serial.available()>0){
    c=Serial.parseInt();
    Serial.println("c");
    Serial.println(c);
    led_delay = c;
    if(c != '\n'){
    //led_delay = c;
    Serial.println("updated led_delay = ");
    Serial.println(led_delay);
    }
    }
    
  }
}

void toggleLED2(void *parameter){
  while(1){
  digitalWrite(32, HIGH);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  digitalWrite(32, LOW);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}
  
}

void setup(){
  pinMode(ledpin, OUTPUT);
  pinMode(32, OUTPUT);
  Serial.begin(115200);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println("led task");
  Serial.println("enter the led delay");

  xTaskCreatePinnedToCore(
    toggleLED,
    "toggleLED",
    1024,
    NULL,
    2,
    NULL,
    app_cpu);

  xTaskCreatePinnedToCore(
    readserial,
    "readserial",
    1024,
    NULL,
    1,
    NULL,
    app_cpu);

  xTaskCreatePinnedToCore(
    toggleLED2,
    "toggleLED2",
    1024,
    NULL,
    1,
    NULL,
    app_cpu);
      
}

void loop(){
  
}
