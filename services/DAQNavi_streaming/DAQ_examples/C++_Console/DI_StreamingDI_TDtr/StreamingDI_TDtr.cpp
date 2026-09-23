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
*    StreamingDI_TDtr.cpp
*
* Example Category:
*    DI
*
* Description:
*    This example demonstrates how to use Streaming DI with Trigger Delay to Start function.
*
* Instructions for Running:
*    1. Login the edge by hostName. If you'd like to handle a local device 
*       (i.e. USB or PCI/PCIe interfaced device in your PC), please bypass this step.
*    2. Set the 'deviceDescription' which can get from system device manager for opening the device.
*    3. Set the 'profilePath' to save the profile path of being initialized device.
*    4. Set the 'portEnabled' to decide which port to be used.
*    5. Set the 'sectionLength' as the length of data section for Buffered DI.
*    6. Set the 'sectionCount' as the count of data section for Buffered DI.
*    7. Set the 'trigger parameters' to decide trigger property.
*
* I/O Connections Overview:
*    Please refer to your hardware reference manual.
*
******************************************************************************/
#include "../../../inc/bdaqctrl.h"
#include "../inc/compatibility.h"
#include <stdio.h>
#include <stdlib.h>
using namespace Automation::BDaq;
//-----------------------------------------------------------------------------------
// Configure the following parameters before running the demo
//-----------------------------------------------------------------------------------
#define       deviceDescription  L"iDAQ-731,BID#0"
const wchar_t* profilePath = L"../../profile/iDAQ-731_0.xml";

int8        portEnabled[] = {1, 0, 0, 0};
const int32 enabledCount  = 1; // The value depend on portEnabled

int32       convClkRate   = 1000;
const int32 sectionLength = 1024;
const int32 sectionCount  = 0;

int32 trgUsed = 0; // 0: trigger0, 1: trigger1

// user buffer size should be equal or greater than raw data buffer length, because data ready count
// is equal or more than smallest section of raw data buffer and up to raw data buffer length.
// users can set 'USER_BUFFER_SIZE' according to demand.
#define USER_BUFFER_LENGTH sectionLength* enabledCount
int8 dataBuf[USER_BUFFER_LENGTH];

// Set trigger parameters
TriggerAction triggerAction     = DelayToStart;
ActiveSignal  triggerEdge       = RisingEdge;
int           triggerDelayCount = 600;
double        triggerLevel      = 3.5;

// Set trigger1 parameters
TriggerAction trigger1Action     = DelayToStart;
ActiveSignal  trigger1Edge       = RisingEdge;
int           trigger1DelayCount = 600;
double        trigger1Level      = 3.5;

inline void waitAnyKey()
{
   do
   {
      SLEEP(1);
   } while (!kbhit());
}

// This function is used to deal with 'DataReady' Event.
void BDAQCALL OnDataReadyEvent(void* sender, BfdDiEventArgs* args, void* userParam)
{
   int32           returnedCount  = 0;
   int32           remainingCount = args->Count;
   BufferedDiCtrl* bfdDICtrl      = (BufferedDiCtrl*)sender;

   do
   {
      int32 getDataCount = MinValue(USER_BUFFER_LENGTH, remainingCount);
      printf("\nGetDataCount[ %d ]\n", getDataCount);
      bfdDICtrl->GetData(getDataCount, dataBuf, 0, &returnedCount);
      remainingCount -= returnedCount;
   } while (remainingCount > 0);

   // Show each channel's new data
   printf("the port data:\n");
   for (int32 i = 0; i < BufLength(portEnabled); ++i)
   {
      if (portEnabled[i] == 0)
      {
         continue;
      }
      int8 data = dataBuf[i];
      printf("Port %d: 0x%x \n", i, data);
   }
}

// This function is used to deal with 'OverRun' Event.
// Notice: The Overrun events indicate there was data loss (could be misaligned)
// during the acquisition. We strongly recommend keeping these events monitored in your application.
// Losing these event notifications could lead you to misunderstand the acquisition status.
void BDAQCALL OnOverRunEvent(void* sender, BfdDiEventArgs* args, void* userParam)
{
   printf("Buffered DI Overrun: offset = %d, count = %d\n", args->Offset, args->Count);
   // Please consider if it's necessary to stop the application in your application when this event is triggered.
   // BufferedDiCtrl* bfdDICtrl = (BufferedDiCtrl*)sender;
   // bfdDICtrl->Stop();
}

// This function is used to deal with 'CacheOverflow' Event.
// Notice: The CacheOverflow events indicate there was data loss (could be misaligned, and discontinuous)
// during the acquisition. We strongly recommend keeping these events monitored in your application.
// Losing these event notifications could lead you to misunderstand the acquisition status.
void BDAQCALL OnOverCacheOverflowEvent(void* sender, BfdDiEventArgs* args, void* userParam)
{
   printf("Buffered DI Cache Overflow: offset = %d, count = %d\n", args->Offset, args->Count);
   // Please consider if it's necessary to stop the application in your application when this event is triggered.
   // BufferedDiCtrl* bfdDICtrl = (BufferedDiCtrl*)sender;
   // bfdDICtrl->Stop();
}

// This function is used to deal with 'Stopped' Event.
void BDAQCALL OnStoppedEvent(void* sender, BfdDiEventArgs* args, void* userParam)
{
   int32           returnedCount = 0, returnedSumCount = 0;
   int32           remainingCount = args->Count;
   BufferedDiCtrl* bfdDICtrl      = (BufferedDiCtrl*)sender;

   do
   {
      int32 getDataCount = MinValue(USER_BUFFER_LENGTH, remainingCount);
      printf("\nGetDataCount[ %d ]\n", getDataCount);
      bfdDICtrl->GetData(getDataCount, dataBuf, 0, &returnedCount);
      remainingCount -= returnedCount;
      returnedSumCount += returnedCount;
   } while (remainingCount > 0);

   printf(" Buffered DI Stopped Event get data count is  %d£¬argsCount is %d\n", returnedSumCount, args->Count);
}

int main(int argc, char* argv[])
{
   ErrorCode ret = Success;

   // Step 1: Create a 'BufferedDiCtrl' for buffered DI function.
   BufferedDiCtrl* bfdDiCtrl = BufferedDiCtrl::Create();

   // Step 2: Set the notification event Handler by which we can known the state of operation effectively.
   bfdDiCtrl->addDataReadyHandler(OnDataReadyEvent, NULL);
   bfdDiCtrl->addOverrunHandler(OnOverRunEvent, NULL);
   bfdDiCtrl->addCacheOverflowHandler(OnOverRunEvent, NULL);
   bfdDiCtrl->addStoppedHandler(OnStoppedEvent, NULL);
   do
   {
      // Step 3: Login the server by hostName.
      //ret = bfdDiCtrl->Login(L"IDAQ974Bid00");
      //CHK_RESULT(ret);

      // Step 4: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo(deviceDescription);
      ret = bfdDiCtrl->setSelectedDevice(devInfo);
      CHK_RESULT(ret);
      ret = bfdDiCtrl->LoadProfile(profilePath); //Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 5: Set necessary parameters.
      int32 bufLen    = BufLength(portEnabled);
      bool  canSetDir = bfdDiCtrl->getFeatures()->getPortProgrammable();
      if (canSetDir)
      {
         Array<DioPort>* dioPorts = bfdDiCtrl->getPorts();
         for (int32 i = 0; i < bufLen; ++i)
         {
            if (portEnabled[i] == 0)
            {
               continue;
            }
            ret = dioPorts->getItem(i).setDirectionMask(Input); // Set DIO ports direction;
            CHK_RESULT(ret);
         }
         CHK_RESULT(ret);
      }

      ScanPort* scanPort = bfdDiCtrl->getScanPort();
      ret = scanPort->setPortMap(bufLen, portEnabled);
      CHK_RESULT(ret);

      ret = scanPort->setSectionLength(sectionLength);
      CHK_RESULT(ret);
      ret = scanPort->setSectionCount(sectionCount); //The 0 means setting 'streaming' mode.
      CHK_RESULT(ret);

      ConvertClock* convClk = bfdDiCtrl->getConvertClock();
      ret = convClk->setSource(SigInternalClock);
      CHK_RESULT(ret);
      ret = convClk->setRate(convClkRate);
      CHK_RESULT(ret);

      // Step 6: Trigger parameters setting
      // Set trigger0
      int32 trgCount = bfdDiCtrl->getFeatures()->getDiTriggerCount();
      if (trgCount > 0 && trgUsed == 0)
      {
         Trigger* trigger = bfdDiCtrl->getTrigger();
         ret = trigger->setAction(triggerAction);
         CHK_RESULT(ret);
         /******************************************************************************************/
         /*The different kinds of devices have different trigger source. The details see manual.
         /*In this example, we use the iDAQ-731 and set 'SigPFP0' as the default trigger source.
         /******************************************************************************************/
         Array<SignalDrop>* srcs        = bfdDiCtrl->getFeatures()->getDiTriggerSources();
         int                sourceCount = srcs->getLength(); //Uncomment this line, user can get the count of supported trigger source.
         ret = trigger->setSource(SigPFP0);
         CHK_RESULT(ret);
         ret = trigger->setDelayCount(triggerDelayCount);
         CHK_RESULT(ret);
         ret = trigger->setEdge(triggerEdge);
         CHK_RESULT(ret);
         /***********************************************************************************/
         /* If the triggerSource is 'SigPFP', 'setLevel' will not work.*/
         /* If not, please uncomment it.
         /***********************************************************************************/
         //ret = trigger->setLevel(triggerLevel);
         //CHK_RESULT(ret);
      }
      else if (trgCount > 1 && trgUsed == 1)
      {
         // Set trigger1
         Trigger* trigger1 = bfdDiCtrl->getTrigger1();
         ret = trigger1->setAction(trigger1Action);
         CHK_RESULT(ret);
         Array<SignalDrop>* srcs = bfdDiCtrl->getFeatures()->getDiTrigger1Sources();
         ret = trigger1->setSource(SigPFP1);
         CHK_RESULT(ret);
         ret = trigger1->setDelayCount(trigger1DelayCount);
         CHK_RESULT(ret);
         ret = trigger1->setEdge(trigger1Edge);
         CHK_RESULT(ret);
         /***********************************************************************************/
         /* If the triggerSource is 'SigPFP', 'setLevel' will not work.*/
         /* If not, please uncomment it.
         /***********************************************************************************/
         //ret = trigger1->setLevel(trigger1Level);
         //CHK_RESULT(ret);
      }
      else
      {
         printf("The device can not support trigger function! \n any key to quit.");
         break;
      }

      // Step 7: The operation has been started.
      // We can get samples via event handlers.
      ret = bfdDiCtrl->Prepare();
      CHK_RESULT(ret);
      ret = bfdDiCtrl->Start();
      CHK_RESULT(ret);

      // Step 8: The device is acquiring data.
      printf("Streaming DI is in progress.\nplease wait...  any key to quit!\n\n");
      do
      {
         SLEEP(1);
      } while (!kbhit());

      // Step 9: Stop the operation if it is running.
      ret = bfdDiCtrl->Stop();
      CHK_RESULT(ret);
   } while (false);

   // Step 10: Release all allocated resource.
   bfdDiCtrl->Release();

   // Step 11: Logout from server.
   //bfdDiCtrl->Logout();

   // Step 12: Close device, release any allocated resource.
   bfdDiCtrl->Dispose();

   // If something wrong in this execution, print the error code on screen for tracking.
   if (BioFailed(ret))
   {
      wchar_t enumString[256];
      AdxEnumToString(L"ErrorCode", (int32)ret, 256, enumString);
      printf("Some error occurred. And the last error code is 0x%X. [%ls]\n", ret, enumString);
      waitAnyKey(); // wait any key to quit!
   }
   return 0;
}
