#include <string.h>
#include "src/calculator/user_app.h"
#include "src/calculator/protocol.h"
#include "src/calculator/neuton/neuton.h"

#include <Arduino_HTS221.h>

#define LED_RED   22
#define LED_GREEN 23
#define LED_BLUE 24

static bool initialised = 0;

PerformanceReport report;
ModelInfo info;

float temperature = 0.0;
float humidity = 0.0;

static void led(uint8_t pin, bool state)
{
  digitalWrite(pin, state ? HIGH : LOW);
}

extern "C" void led_red(bool state)
{
  led(LED_RED, state);
}

extern "C" void led_green(bool state)
{
  led(LED_GREEN, state);
}

extern "C" void led_blue(bool state)
{
  led(LED_BLUE, state);
}

extern "C" void print_result(float val)
{
  Serial.print(val);
}


void setup()
{
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  Serial.begin(9600);

  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }
}

void loop()
{
  initialised = app_init();
  info = app_model_info();
  Serial.print("Input size: ");
  Serial.println(app_inputs_size());
  report.ramUsage = NBytesAllocatedTotal();
  report.flashUsage = app_model_size();
  Serial.println(report.ramUsage);
  Serial.println(report.flashUsage);
  Serial.println("---------------------------------------------------");
  delay(200);
  Serial.println(info.rowsCount);
  Serial.println(info.taskType);
  Serial.println("---------------------------------------------------");
  delay(500);

  temperature = HTS.readTemperature();
  humidity    = HTS.readHumidity();

  // print each of the sensor values
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity    = ");
  Serial.print(humidity);
  Serial.println(" %");

  // print an empty line
  Serial.println();

  float sample[3] = {
    humidity,                //humid
    temperature,                //temp
    1.0,                   //bias
  };

  //
  float* result = app_run_inference(sample);
  
  float* value = result[0] >= result[1] ? &result[0] : &result[1];
  if (*value > 0.5)
  {
    if (value == &result[0])
    {
      // 0
      Serial.println("Okay");
      
    }
    else
    {
      // 1
      Serial.println("Bad Condition");
    }
  }
  else
  {
    // unknown
    Serial.println("Unknown");
  }


  app_nn_free();
  delay(2000);

}
