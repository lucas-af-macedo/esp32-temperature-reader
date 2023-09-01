#include <ESP.h>

void memoryUsage(){
  uint32_t flashChipSize = ESP.getFlashChipSize();
  Serial.print("Tamanho total da memória flash: ");
  Serial.print(flashChipSize);
  Serial.println(" bytes");
  uint32_t freeSketchSpace = ESP.getFreeSketchSpace();
  Serial.print("Espaço disponível para o sketch: ");
  Serial.print(freeSketchSpace);
  Serial.println(" bytes");
  float usedPercentage = 100.0 * (1.0 - (float)freeSketchSpace / flashChipSize);
  Serial.print("Porcentagem de espaço usado: ");
  Serial.print(usedPercentage);
  Serial.println("%");
}