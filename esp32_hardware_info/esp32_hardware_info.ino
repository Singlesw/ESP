
// ------------------- function declarations  --------------
void logMemory ();


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  printf("\n\n");
  printf("Flash size: %d bytes\n", spi_flash_get_chip_size());

  Serial.println();
  Serial.print("Free heap:");
  Serial.println(ESP.getFreeHeap());


  uint8_t base_mac_addr[6] = {0};
  esp_err_t ret = ESP_OK;
  ret = esp_efuse_mac_get_default(base_mac_addr);
  printf("\nMAC Address = %02x:%02x:%02x:%02x:%02x:%02x (ret: %d)\n\n", 
    base_mac_addr[0],
    base_mac_addr[1],
    base_mac_addr[2],
    base_mac_addr[3],
    base_mac_addr[4],
    base_mac_addr[5],
    ret
  );


  printf("| Type | Sub |  Offset  |   Size   |       Label      |\n");
  printf("| ---- | --- | -------- | -------- | ---------------- |\n");
  
  esp_partition_iterator_t pi = esp_partition_find(ESP_PARTITION_TYPE_ANY, ESP_PARTITION_SUBTYPE_ANY, NULL);
  if (pi != NULL) {
    do {
      const esp_partition_t* p = esp_partition_get(pi);
      printf("|  %02x  | %02x  | 0x%06X | 0x%06X | %-16s |\r\n", 
        p->type, p->subtype, p->address, p->size, p->label);
    } while (pi = (esp_partition_next(pi)));
  }

  /* Print chip information */
  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);
  printf("\nThis is %s chip with %d CPU core(s), WiFi%s%s, ",
          CONFIG_IDF_TARGET,
          chip_info.cores,
          (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
          (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

  printf("silicon revision %d, ", chip_info.revision);

  printf("%d MB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
          (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

  printf("Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size());

  uint32_t chipId = 0;
  for(int i=0; i<17; i=i+8) {
	  chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
	}

	Serial.printf("ESP32 Chip model = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
	Serial.printf("This chip has %d cores\n", ESP.getChipCores());
  Serial.print("Chip ID: "); Serial.println(chipId); Serial.println();
  Serial.print("Chip Frequ. MHz: "); Serial.println(ESP.getCpuFreqMHz());
  Serial.printf("Clocks Xtal : %4d MHz\n", getXtalFrequencyMhz());
  Serial.printf("       APB  : %4d MHz\n\n", getApbFrequency() / 1000000);



  // https://thingpulse.com/esp32-how-to-use-psram/
  // Farbtiefe von 16bit auf 2 bit = 4 Farben (= 2^2) heruntersetzen = 
  // 320 x 240 x 2bit / 8(byte) == nur 19,2 kb
  Serial.printf("Total heap: %d\n", ESP.getHeapSize());
  Serial.printf("Free heap: %d\n", ESP.getFreeHeap());
  Serial.printf("Max. Alloc. Heap: %d\n", ESP.getMaxAllocHeap());
  Serial.printf("Memory Flash: %4d kB\n\n", ESP.getFlashChipSize() / 1000);

  Serial.printf("Sketch Size : %4d kB\n", ESP.getSketchSize() / 1000);
  Serial.printf("       Free : %4d kB\n\n", ESP.getFreeSketchSpace() / 1000);

  Serial.printf("Total PSRAM: %d\n", ESP.getPsramSize());
  Serial.printf("Free PSRAM: %d\n", ESP.getFreePsram());
  Serial.printf("Get Max Alloc PSRAM: %d\n", ESP.getMaxAllocPsram());



/* platformio.ini:      // ? muss hinzugefügt werden in Platformio.ini
build_flags = -DBOARD_HAS_PSRAM
              -DCONFIG_SPIRAM_USE_MALLOC
              -mfix-esp32-psram-cache-issue      */


  Serial.println();
  logMemory();
  byte* psdRamBuffer = (byte*)ps_malloc(50000);       // malloc(..) doesn´t work either
  logMemory();
  free(psdRamBuffer);
  logMemory();

  // size_t psram_size = esp_spiram_get_size();
  // Serial.printf("PSRAM size: %d bytes\n", psram_size);

  if (psramInit())                    // not ok, hier keine Ausgabe
    Serial.printf("PSRAM init OK\n");
  else
    Serial.println("No PSRAM initiated!");

}





// rotary encoder
// https://wokwi.com/projects/304919215794553409


// captive touch panel
// https://wokwi.com/projects/325329852393587282


void loop() {
  // put your main code here, to run repeatedly:
   
  delay(10); // this speeds up the simulation
}





// -------------------   logMemory -------------
void logMemory(void) {
  Serial.printf("Used PSRAM: %d \n", ESP.getPsramSize() - ESP.getFreePsram());
}


//  ----------  reboot function ------------
void reboot_device (void) {
  printf("Restarting now.\n");
  fflush(stdout);
  esp_restart();
}
