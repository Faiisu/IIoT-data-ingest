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
*     PollingOneBufferedAI_TDtp.cpp
*
* Example Category:
*    AI
*
* Description:
*    This example demonstrates how to use Polling One Buffered AI with Trigger Delay
*    to Stop function.
* Instructions for Running:
*    1. Login the edge by hostName. If you'd like to handle a local device
*       (i.e. USB or PCI/PCIe interfaced device in your PC), please bypass this step.
*    2. Set the 'deviceDescription' which can get from system device manager for opening the device.
*    3. Set the 'profilePath' to save the profile path of being initialized device.
*    4. Set the 'startChannel' as the first channel for scan analog samples
*    5. Set the 'channelCount' to decide how many sequential channels to scan analog samples.
*    6. Set the 'sectionLength' as the length of data section for Buffered AI.
*    7. Set the 'sectionCount' as the count of data section for Buffered AI.
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
#define deviceDescription L"DemoDevice,BID#0"
const wchar_t* profilePath   = L"../../profile/DemoDevice.xml";

int32          startChannel  = 0;
const int32    channelCount  = 2;
const int32    sectionLength = 1024;
const int32    sectionCount  = 1;

#define USER_BUFFER_SIZE channelCount* sectionLength* sectionCount
double Data[USER_BUFFER_SIZE];
int32  returnedCount = 0;

// Set trigger paramaters
TriggerAction triggerAction     = DelayToStop;
ActiveSignal  triggerEdge       = RisingEdge;
int           triggerDelayCount = 1000;
double        triggerLevel      = 3.0;

// Set trigger1 paramaters
TriggerAction trigger1Action     = DelayToStop;
ActiveSignal  trigger1Edge       = RisingEdge;
int           trigger1DelayCount = 1000;
double        trigger1Level      = 3.0;

// set which trigger be used for this demo, trigger0(0) or trigger1(1).
int triggerUsed = 0;

inline void waitAnyKey()
{
   do
   {
      SLEEP(1);
   } while (!kbhit());
}

int main(int argc, char* argv[])
{
   ErrorCode ret = Success;

   // Step 1: Create a 'WaveformAiCtrl' for buffered AI function.
   WaveformAiCtrl* wfAiCtrl = WaveformAiCtrl::Create();

   do
   {
      // Step 2: Login the server by hostName.
      //ret = wfAiCtrl->Login(L"IDAQ974Bid00");
      //CHK_RESULT(ret);

      // Step 3: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo(deviceDescription);
      ret = wfAiCtrl->setSelectedDevice(devInfo);
      CHK_RESULT(ret);
      ret = wfAiCtrl->LoadProfile(profilePath); //Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 4: Set necessary parameters.
      Conversion* conversion = wfAiCtrl->getConversion();

      ret = conversion->setChannelStart(startChannel);
      CHK_RESULT(ret);
      ret = conversion->setChannelCount(channelCount);
      CHK_RESULT(ret);

      Record* record = wfAiCtrl->getRecord();
      ret = record->setSectionLength(sectionLength);
      CHK_RESULT(ret);
      ret = record->setSectionCount(sectionCount); //The sectionCount is nonzero value, which means 'One Buffered' mode.
      CHK_RESULT(ret);

      // Step 5: Trigger parameters setting
      int32 trgCount = wfAiCtrl->getFeatures()->getTriggerCount();
      if (triggerUsed == 0)
      {
         if (trgCount)
         {
            Trigger* trigger = wfAiCtrl->getTrigger();
            ret = trigger->setAction(triggerAction);
            CHK_RESULT(ret);
            /******************************************************************************************/
            /*The different kinds of devices have different trigger source. The details see manual.
            /*In this example, we use the DemoDevice and set 'Ai channel 0' as the default trigger source.
            /******************************************************************************************/
            Array<SignalDrop>* srcs = wfAiCtrl->getFeatures()->getTriggerSources();
            ret = trigger->setSource(srcs->getItem(1)); //To DemoDevice, the 1 means 'Ai channel 0'.
            CHK_RESULT(ret);
            ret = trigger->setDelayCount(triggerDelayCount);
            CHK_RESULT(ret);
            ret = trigger->setEdge(triggerEdge);
            CHK_RESULT(ret);
            ret = trigger->setLevel(triggerLevel);
            CHK_RESULT(ret);
         }
         else
         {
            printf("The device can not support trigger function! \n any key to quit.");
            break;
         }
      }
      else if (triggerUsed == 1)
      {
         if (trgCount > 1)
         {
            Trigger* trigger1 = wfAiCtrl->getTrigger1();
            ret = trigger1->setAction(trigger1Action);
            CHK_RESULT(ret);
            Array<SignalDrop>* srcs = wfAiCtrl->getFeatures()->getTrigger1Sources();
            ret = trigger1->setSource(srcs->getItem(1));
            CHK_RESULT(ret);
            ret = trigger1->setDelayCount(trigger1DelayCount);
            CHK_RESULT(ret);
            ret = trigger1->setEdge(trigger1Edge);
            CHK_RESULT(ret);
            ret = trigger1->setLevel(trigger1Level);
            CHK_RESULT(ret);
         }
         else
         {
            printf("The trigger1 can not support by the device! \n any key to quit.");
            break;
         }
      }

      // Step 6: The acquisition has been started.
      printf("Polling finite acquisition is in progress.\n");
      ret = wfAiCtrl->Prepare();
      CHK_RESULT(ret);
      ret = wfAiCtrl->Start();
      CHK_RESULT(ret);

      // Step 7: GetData with Polling Style
      double startTime = 0;
      ret = wfAiCtrl->GetData(USER_BUFFER_SIZE, Data, -1, &returnedCount, &startTime); //The timeout value is -1, meaning infinite waiting.
      CHK_RESULT(ret);

      printf("Polling One Buffered AI get data count is  %d\n", returnedCount);

      if (ret == Success)
      {
         printf("The startTime = %10.6f, first sample each channel are:\n", startTime);
         for (int32 i = 0; i < channelCount; i++)
         {
            printf("channel %d: %10.6f \n", (i + startChannel), Data[i]);
         }
      }

      int32 delayCount = 0;

      if (triggerUsed == 0)
      {
         delayCount = wfAiCtrl->getTrigger()->getDelayCount();
      }
      else if (triggerUsed == 1)
      {
         delayCount = wfAiCtrl->getTrigger1()->getDelayCount();
      }

      int32 triggerPointIndex = returnedCount / channelCount - delayCount;

      printf("trigger point each channel: %d\n", triggerPointIndex);
      printf("Acquisition has completed!\n");

      // Step 8: stop the operation if it is running.
      ret = wfAiCtrl->Stop();
      CHK_RESULT(ret);
   } while (false);

   // Step 9: Release all allocated resource.
   wfAiCtrl->Release();

   // Step 10: Logout from server.
   //wfAiCtrl->Logout();

   // Step 11: close device, release any allocated resource before quit.
   wfAiCtrl->Dispose();

   // If something wrong in this execution, print the error code on screen for tracking.
   if (BioFailed(ret))
   {
      wchar_t enumString[256];
      AdxEnumToString(L"ErrorCode", (int32)ret, 256, enumString);
      printf("Some error occurred. And the last error code is 0x%X. [%ls]\n", ret, enumString);
   }
   waitAnyKey();
   return 0;
}
