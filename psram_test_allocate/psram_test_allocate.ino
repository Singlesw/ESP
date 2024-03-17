#include "sdkconfig.h"  //
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h" //This inclusion configures the peripherals in the ESP system.
#include "esp32-hal-psram.h"
// #include "rom/cache.h"
extern "C" 
{
#include <esp_himem.h>
#include <esp_spiram.h>
}
//extern "C" 
//{
//#include <esp_himem.h>
//}

////
const int SerialDataBits = 115200;
////
struct stuTime
{
  int iSeconds = 0;
  int iMinutes = 0;
  int iHours = 0;
};
////
void setup()
{
  // Serial.begin( SerialDataBits );
  // psramInit(); // !!!!! Not needed
//  esp_spiram_init();  // Not Needed
//   log_i("Total heap: %d", ESP.getHeapSize());
//   log_i("Free heap: %d", ESP.getFreeHeap());
   log_i("Total PSRAM: %d", ESP.getPsramSize());
   log_i("Free PSRAM: %d", ESP.getFreePsram());
//   log_i("spiram size %u", esp_spiram_get_size());
//  log_i("himem free %d", esp_himem_get_free_size());
  // log_i("himem free %u\n", esp_himem_get_free_size());
  // log_i("himem phys %u\n", esp_himem_get_phys_size());
//  log_i("himem reserved %u\n", esp_himem_reserved_area_size());
  //
   int *ptr, *ptr1;
   int n, n1, i, sum = 0;
   float *ptrFloat;
   // Get the number of elements for the array
   n = 10;
   n1 = 20;
   log_i("Number of elements ptr: %d", n);
   log_i("Number of elements ptr1: %d", n1);
   log_i("Number of elements ptr1: %d\n", n1);
   // Dynamically allocate memory using malloc()
   // ptr = (int*)ps_malloc(n * sizeof(int)); //works
   ptr = (int*)ps_calloc( n, sizeof(int) ); // works
   log_i("Free PSRAM: %d", ESP.getFreePsram());
   ptr1 = (int*)ps_calloc( n1, sizeof(int) ); // works
   log_i("Free PSRAM: %d", ESP.getFreePsram());
    // Check if the memory has been successfully
    // allocated in ps_ram
    ptrFloat = (float*)ps_calloc( n, sizeof(float) ); // works
    if (ptr == NULL) {
      log_i(" ptr memory not allocated.\n");
      exit(0);
    }
    if (ptr1 == NULL)
    {
      log_i("ptr1 memory not allocated.\n");
      exit(0);
    }
    else
    {
       // Memory has been successfully allocated
      // log_i("ps_ram memory successfully allocated using ps_calloc.");
      // put elements into ps_ram array
      for (i = 0; i < n; ++i)
      {
        ptr[i] = i + 1;
      }
      for (i = 0; i < n1; ++i)
      {
        ptr1[i] = i + 2;
      }
      for (i = 0; i < n; ++i)
      {
        ptrFloat[i] = (float)i + 1.06555f;
      }
      // Print the elements of the array
      log_i("The elements of the ptr array are: ");
      for (i = 0; i < n; ++i) {
        log_i("%d, ", ptr[i]);
      }
      log_i("The elements of the ptr1 array are: ");
      for (i = 0; i < n1; ++i) {
        log_i("%d, ", ptr1[i]);
      }
      log_i("The elements of the ptrFloat array are: ");
      for (i = 0; i < n1; ++i) {
        log_i("%f, ", ptrFloat[i]);
      }
    }
    //
    // put a structure into psram. Works.
    struct stuTime *ptrStuTime;
    log_i("size of structure: %d", sizeof(struct stuTime) );
     // 
    ptrStuTime = (struct stuTime *)ps_malloc(sizeof(struct stuTime));
    log_i("Free PSRAM after structure: %d", ESP.getFreePsram());
    ptrStuTime->iSeconds = 10;
    ptrStuTime->iMinutes = 60;
    ptrStuTime->iHours = 100;
    log_i("Seconds: %d Minutes: %d Hours: %d", ptrStuTime->iSeconds, ptrStuTime->iMinutes, ptrStuTime->iHours );
    free(ptr);
    free(ptr1);
    free(ptrStuTime);
    // works
    log_i("Free PSRAM before String: %d", ESP.getFreePsram());
    char *str;
    char OneChar = 'a';
    char TwoChar = 'b';
    char ThreeChar = 'c';
    str = (char *)ps_calloc(300, sizeof(char) );
    log_i("Free PSRAM after String: %d", ESP.getFreePsram());
    // concantenate one char variable to end of char array to the str
    strncat( str, &OneChar, 1 ); //works
    strncat( str, &TwoChar, 1 );
    strncat( str, &ThreeChar, 1 );
    //
    //*(str+0) = 'G';  // works
    //*(str+1) = 'f';
    //*(str+2) = 'G';
    //*(str+3) = '\0';
    log_i("%s", str );
    free(str);

  ///////
//size_t memfree=esp_himem_get_free_size();
//log_i( "himemFree %d", memfree );
//  int memcnt=esp_himem_get_phys_size();
  // int memfree=esp_himem_get_free_size();
//  log_i( "SpiRamPhysSize %d", memcnt );
 //  log_i( "SpiRamFree %d", memfree );
  // esp_himem_get_phys_size(void)
   // esp_himem_handle_t mh; //Handle for the address space we're using
   // esp_himem_rangehandle_t rh; //Handle for the actual RAM.
   // esp_err_t intError = esp_himem_alloc( 4095, &mh);
   // log_i( "%s", esp_err_to_name( intError) );
   // log_i("spiram size %u", esp_spiram_get_size());
   // log_i( "Handle %d", mh );


} // setup()
////
/* possible adds to the config
 * #define CONFIG_ESP32_SPIRAM_SUPPORT 1
#define CONFIG_SPIRAM_BOOT_INIT 1
#define CONFIG_SPIRAM_IGNORE_NOTFOUND 0
#define CONFIG_SPIRAM_USE_MALLOC 1
#define CONFIG_SPIRAM_TYPE_AUTO 1
#define CONFIG_SPIRAM_SIZE -1
#define CONFIG_SPIRAM_SPEED_40M 1
#define CONFIG_SPIRAM_MEMTEST 1
#define CONFIG_SPIRAM_CACHE_WORKAROUND 1
#define CONFIG_SPIRAM_BANKSWITCH_ENABLE 1
#define CONFIG_SPIRAM_BANKSWITCH_RESERVE 4
 */
void loop() {}
////
//Fill memory with pseudo-random data generated from the given seed.
//Fills the memory in 32-bit words for speed.
static void fill_mem_seed(int seed, void *mem, int len)
{
  //    uint32_t *p = (uint32_t *)mem;
  //    unsigned int rseed = seed ^ 0xa5a5a5a5;
  //    for (int i = 0; i < len / 4; i++) {
  //        *p++ = rand_r(&rseed);
  //    }
}

//Check the memory filled by fill_mem_seed. Returns true if the data matches the data
//that fill_mem_seed wrote (when given the same seed).
//Returns true if there's a match, false when the region differs from what should be there.
static bool check_mem_seed(int seed, void *mem, int len, int phys_addr)
{
  //    uint32_t *p = (uint32_t *)mem;
  //    unsigned int rseed = seed ^ 0xa5a5a5a5;
  //    for (int i = 0; i < len / 4; i++) {
  //        uint32_t ex = rand_r(&rseed);
  //        if (ex != *p) {
  //            printf("check_mem_seed: %x has 0x%08x expected 0x%08x\n", phys_addr+((char*)p-(char*)mem), *p, ex);
  //            return false;
  //        }
  //        p++;
  //    }
  return true;
}

//Allocate a himem region, fill it with data, check it and release it.
static bool test_region(int check_size, int seed)
{
  esp_himem_handle_t mh; //Handle for the address space we're using
  esp_himem_rangehandle_t rh; //Handle for the actual RAM.
  bool ret = true;

  //Allocate the memory we're going to check.
  ESP_ERROR_CHECK(esp_himem_alloc(check_size, &mh));
  //Allocate a block of address range
  //    ESP_ERROR_CHECK(esp_himem_alloc_map_range(ESP_HIMEM_BLKSZ, &rh));
  //    for (int i = 0; i < check_size; i += ESP_HIMEM_BLKSZ) {
  //        uint32_t *ptr = NULL;
  //        //Map in block, write pseudo-random data, unmap block.
  //        ESP_ERROR_CHECK(esp_himem_map(mh, rh, i, 0, ESP_HIMEM_BLKSZ, 0, (void**)&ptr));
  //        fill_mem_seed(i ^ seed, ptr, ESP_HIMEM_BLKSZ); //
  //        ESP_ERROR_CHECK(esp_himem_unmap(rh, ptr, ESP_HIMEM_BLKSZ));
  //    }
  //    vTaskDelay(5); //give the OS some time to do things so the task watchdog doesn't bark
  //    for (int i = 0; i < check_size; i += ESP_HIMEM_BLKSZ) {
  //        uint32_t *ptr;
  //        //Map in block, check against earlier written pseudo-random data, unmap block.
  //        ESP_ERROR_CHECK(esp_himem_map(mh, rh, i, 0, ESP_HIMEM_BLKSZ, 0, (void**)&ptr));
  //        if (!check_mem_seed(i ^ seed, ptr, ESP_HIMEM_BLKSZ, i)) {
  //            printf("Error in block %d\n", i / ESP_HIMEM_BLKSZ);
  //            ret = false;
  //        }
  //        ESP_ERROR_CHECK(esp_himem_unmap(rh, ptr, ESP_HIMEM_BLKSZ));
  //        if (!ret) break; //don't check rest of blocks if error occurred
  //    }
  //    //Okay, all done!
  //    ESP_ERROR_CHECK(esp_himem_free(mh));
  //    ESP_ERROR_CHECK(esp_himem_free_map_range(rh));
  return ret;
}

////
//void logMemory()
//{
//  log_d("Used PSRAM: %d", ESP.getPsramSize() - ESP.getFreePsram());
//}