#define SENSOR_NUM      8
#define FILTER_DEPTH    10
#define ADC_BITS        12

int sensorDataRaw[SENSOR_NUM];
float linePosHist[FILTER_DEPTH];
int filterIndex = 0;

void setup() {
    Serial.begin(9600);
    analogReadResolution(ADC_BITS);   // Optional, defaults to 10 bit
}

void loop() {
    int sum = 0;
    int avg = 0;
    for (uint8_t i = 0; i < SENSOR_NUM; i++) {
        sensorDataRaw[i] = pow(2, ADC_BITS) - analogRead(i);
        
//        Uncomment for task 1
//        Serial.print(sensorDataRaw[i]);
//        Serial.print('\t');

        sum += sensorDataRaw[i];
        avg += sensorDataRaw[i] * i * pow(2, ADC_BITS);
    }
    
    float position = map(avg / sum, 0, pow(2, ADC_BITS) * SENSOR_NUM, 0, 1000);
    
    linePosHist[filterIndex] = position;
    filterIndex++;
    if (filterIndex == FILTER_DEPTH)
      filterIndex = 0;
    float filteredPos = 0;
    for (int i = 0; i < FILTER_DEPTH; i++) {
      filteredPos += linePosHist[i];
    }
    filteredPos = filteredPos / 10;
    
//    Uncomment for task 2
//    Serial.print("Raw Line Position: ");
//    Serial.print(position);
//    Serial.print('\t');

//    Uncomment for task 3
    Serial.print("Filtered Line Position: ");
    Serial.print(filteredPos);
    Serial.print('\t');

//    Uncomment for task 4
//    if (filteredPos < 500)
//      Serial.print("Turn Left");
//    else
//      Serial.print("Turn Right");
      
    Serial.println();
}
