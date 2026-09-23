/*******************************************************************************
Copyright (c) 1983-2024 Advantech Co., Ltd.
********************************************************************************
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

================================================================================
REVISION HISTORY
--------------------------------------------------------------------------------
$Log:  $
--------------------------------------------------------------------------------
$NoKeywords:  $
*/
/******************************************************************************
*
* Windows Example:
*    StreamingDI.c
*
* Example Category:
*    DI
*
* Description:
*    This example demonstrates how to use Streaming DI function.
*
* Instructions for Running:
*    1. Login the edge by hostName. If you'd like to handle a local device 
*       (i.e. USB or PCI/PCIe interfaced device in your PC), please bypass this step.
*    2. Set the 'deviceDescription' which can get from system device manager for opening the device.
*    3. Set the 'profilePath' to save the profile path of being initialized device.
*    4. Set the 'portEnabled' to decide which port to be used.
*    5. Set the 'sectionLength' as the length of data section for Buffered DI.
*    6. Set the 'sectionCount' as the count of data section for Buffered DI.
*
* I/O Connections Overview:
*    Please refer to your hardware reference manual.
*
******************************************************************************/
#include "../../../inc/bdaqctrl.h"
#include "../inc/compatibility.h"
#include <stdio.h>
#include <stdlib.h>
//-----------------------------------------------------------------------------------
// Configure the following parameters before running the demo
//-----------------------------------------------------------------------------------
#define deviceDescription L"iDAQ-731,BID#0"
const wchar_t* profilePath = L"../../profile/iDAQ-731_0.xml";

int8 portEnabled[] = {1, 0, 0, 0};
#define EnabledCount 1 // The value depend on portEnabled

int32 convClkRate  = 1000;
int32 sectionCount = 0;
#define SectionLength 1024

// user buffer size should be equal or greater than raw data buffer length, because data ready count
// is equal or more than smallest section of raw data buffer and up to raw data buffer length.
// users can set 'USER_BUFFER_LENGTH' according to demand.
#define USER_BUFFER_LENGTH SectionLength* EnabledCount
int8 dataBuf[USER_BUFFER_LENGTH];

void BDAQCALL OnDataReadyEvent(void* sender, BfdDiEventArgs* args, void* userParam);
void BDAQCALL OnOverRunEvent(void* sender, BfdDiEventArgs* args, void* userParam);
void BDAQCALL OnCacheOverflowEvent(void* sender, BfdDiEventArgs* args, void* userParam);
void BDAQCALL OnStoppedEvent(void* sender, BfdDiEventArgs* args, void* userParam);

void waitAnyKey()
{
   do
   {
      SLEEP(1);
   } while (!kbhit());
}

int main(int argc, char* argv[])
{
   ErrorCode     ret        = Success;
   ConvertClock* convClk    = NULL;
   ScanPort*     scanPort   = NULL;
   IArray*       dioPorts   = NULL;
   DioFeatures*  diFeatures = NULL;

   int32   i               = 0;
   int32   bufLen          = 0;
   int32   canSetDir       = 0;
   wchar_t enumString[256] = {0};

   // Step 1: Create a 'Buffered DI Control' for Streaming DI function.
   BufferedDiCtrl* bfdDiCtrl = BufferedDiCtrl_Create();

   // Step 2: Set the notification event Handler by which we can known the state of operation effectively.
   BufferedDiCtrl_addDataReadyHandler(bfdDiCtrl, OnDataReadyEvent, NULL);
   BufferedDiCtrl_addOverrunHandler(bfdDiCtrl, OnOverRunEvent, NULL);
   BufferedDiCtrl_addCacheOverflowHandler(bfdDiCtrl, OnCacheOverflowEvent, NULL);
   BufferedDiCtrl_addStoppedHandler(bfdDiCtrl, OnStoppedEvent, NULL);

   do
   {
      DeviceInformation devInfo;
      devInfo.DeviceNumber = -1;
      devInfo.DeviceMode   = ModeWrite;
      devInfo.ModuleIndex  = 0;
      wcscpy(devInfo.Description, deviceDescription);

      // Step 3: Login the server by hostName
      //ret = BufferedDiCtrl_Login(bfdDiCtrl, L"IDAQ974Bid00");
      //CHK_RESULT(ret);

      // Step 4: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      ret = BufferedDiCtrl_setSelectedDevice(bfdDiCtrl, &devInfo);
      CHK_RESULT(ret);
      ret = BufferedDiCtrl_LoadProfile(bfdDiCtrl, profilePath); // Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 5: Set necessary parameters.
      bufLen     = BufLength(portEnabled);
      diFeatures = BufferedDiCtrl_getFeatures(bfdDiCtrl);
      canSetDir  = DioFeatures_getPortProgrammable(diFeatures);

      if (canSetDir)
      {
         dioPorts = BufferedDiCtrl_getPorts(bfdDiCtrl);
         for (i = 0; i < bufLen; ++i)
         {
            if (portEnabled[i] == 0)
            {
               continue;
            }
            ret = DioPort_setDirectionMask((DioPort*)Array_getItem(dioPorts, i), Input);
            CHK_RESULT(ret);
         }
         CHK_RESULT(ret);
      }

      scanPort = BufferedDiCtrl_getScanPort(bfdDiCtrl);
      ret = ScanPort_setPortMap(scanPort, bufLen, portEnabled);
      CHK_RESULT(ret);

      ret = ScanPort_setSectionLength(scanPort, SectionLength);
      CHK_RESULT(ret);
      ret = ScanPort_setSectionCount(scanPort, sectionCount); // The 0 means setting 'streaming' mode.
      CHK_RESULT(ret);

      convClk = BufferedDiCtrl_getConvertClock(bfdDiCtrl);
      ret = ConvertClock_setSource(convClk, SigInternalClock);
      CHK_RESULT(ret);
      ret = ConvertClock_setRate(convClk, convClkRate);
      CHK_RESULT(ret);

      // Step 6: The operation has been started.
      ret = BufferedDiCtrl_Prepare(bfdDiCtrl);
      CHK_RESULT(ret);
      ret = BufferedDiCtrl_Start(bfdDiCtrl);
      CHK_RESULT(ret);

      // Step 7: The device is acquiring data.
      printf("Streaming DI is in progress.\nplease wait...  any key to quit!\n\n");
      do
      {
         SLEEP(1);
      } while (!kbhit());

      // Step 8: Stop the operation if it is running.
      ret = BufferedDiCtrl_Stop(bfdDiCtrl);
      CHK_RESULT(ret);
   } while (FALSE);

   // Step 9: Release all allocated resource.
   BufferedDiCtrl_Release(bfdDiCtrl);

   // Step 10: Logout from server.
   //BufferedDiCtrl_Logout(bfdDiCtrl);

   // Step 11: Close device, release any allocated resource.
   BufferedDiCtrl_Dispose(bfdDiCtrl);

   // If something wrong in this execution, print the error code on screen for tracking.
   if (BioFailed(ret))
   {
      AdxEnumToString(L"ErrorCode", (int32)ret, 256, enumString);
      printf("Some error occurred. And the last error code is 0x%X. [%ls]\n", ret, enumString);
      waitAnyKey(); // wait any key to quit!
   }
   return 0;
}

// This function is used to deal with 'DataReady' Event.
void BDAQCALL OnDataReadyEvent(void* sender, BfdDiEventArgs* args, void* userParam)
{
   int             data = 0;
   int32           i = 0, getDataCount = 0, returnedCount = 0;
   int32           remainingCount = args->Count;
   BufferedDiCtrl* bfdDiCtrl = (BufferedDiCtrl*)sender;

   do
   {
      getDataCount = MinValue(USER_BUFFER_LENGTH, remainingCount);
      printf("\nGetDataCount[ %d ]\n", getDataCount);
      BufferedDiCtrl_GetData(bfdDiCtrl, getDataCount, dataBuf, 0, &returnedCount, NULL, NULL, NULL);
      remainingCount -= returnedCount;
   } while (remainingCount > 0);

   // Show each channel's new data
   printf("the port data:\n");
   for (i = 0; i < BufLength(portEnabled); ++i)
   {
      if (portEnabled[i] == 0)
      {
         continue;
      }
      data = dataBuf[i];
      printf("Port %d: 0x%x \n", i, data);
   }
}

// This function is used to deal with 'OverRun' Event.
// Notice: The Overrun events indicate there was data loss (could be misaligned)
// during the acquisition. We strongly recommend keeping these events monitored in your application.
// Losing these event notifications could lead you to misunderstand the acquisition status.
void BDAQCALL OnOverRunEvent(void* sender, BfdDiEventArgs* args, void* userParam)
{
   printf(" Buffered DI Overrun: offset = %d, count = %d\n", args->Offset, args->Count);
   // Please consider if it's necessary to stop the application in your application when this event is triggered.
   // BufferedDiCtrl * bfdDiCtrl = (BufferedDiCtrl *)sender;
   // bfdDiCtrl_Stop();
}

// This function is used to deal with 'CacheOverflow' Event.
// Notice: The CacheOverflow events indicate there was data loss (could be misaligned, and discontinuous)
// during the acquisition. We strongly recommend keeping these events monitored in your application.
// Losing these event notifications could lead you to misunderstand the acquisition status.
void BDAQCALL OnCacheOverflowEvent(void* sender, BfdDiEventArgs* args, void* userParam)
{
   printf(" Buffered DI Cache Overflow: offset = %d, count = %d\n", args->Offset, args->Count);
   // Please consider if it's necessary to stop the application in your application when this event is triggered.
   // BufferedDiCtrl * bfdDiCtrl = (BufferedDiCtrl *)sender;
   // bfdDiCtrl_Stop();
}

// This function is used to deal with 'Stopped' Event.
void BDAQCALL OnStoppedEvent(void* sender, BfdDiEventArgs* args, void* userParam)
{
   int32           i = 0, getDataCount = 0, returnedCount = 0, returnedSumCount = 0;
   int32           remainingCount = args->Count;
   BufferedDiCtrl* bfdDiCtrl = (BufferedDiCtrl*)sender;

   do
   {
      getDataCount = MinValue(USER_BUFFER_LENGTH, remainingCount);
      BufferedDiCtrl_GetData(bfdDiCtrl, getDataCount, dataBuf, 0, &returnedCount, NULL, NULL, NULL);
      remainingCount -= returnedCount;
      returnedSumCount += returnedCount;
   } while (remainingCount > 0);
   printf("Buffered DI Stopped Event get data count is  %d，argsCount is %d\n", returnedSumCount, args->Count);
}
