#include "esphome.h"
#include "VL53L1X.h"  // Jeśli używasz tej biblioteki, zaimportuj ją.

class VL53L1XCustomSensor : public PollingComponent, public Sensor {
 public:
  VL53L1XCustomSensor() : PollingComponent(3000) {}  // Odświeżanie co 3 sekundy

  void setup() override {
    // Inicjalizacja czujnika, np.:
    if (!vl53l1x.begin()) {
      ESP_LOGE("VL53L1X", "Czujnik nie został wykryty!");
    }
  }

  void update() override {
    // Pobranie odczytu z czujnika
    uint16_t distance = vl53l1x.readRangeSingleMillimeters();
    if (vl53l1x.timeoutOccurred()) {
      ESP_LOGW("VL53L1X", "Czas oczekiwania na dane przekroczony!");
      return;
    }
    // Zwrócenie odczytu jako stan czujnika
    publish_state(distance);
  }

 private:
  VL53L1X vl53l1x;  // Obiekt czujnika VL53L1X
};
