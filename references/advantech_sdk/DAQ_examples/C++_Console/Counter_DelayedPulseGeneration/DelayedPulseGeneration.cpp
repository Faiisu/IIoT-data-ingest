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
* Windows  Example:
*    DelayedPulseGeneration.cpp
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use Delayed Pulse Generation function.
*
* Instructions for Running:
*    1. Login the edge by hostName. If you'd like to handle a local device 
*       (i.e. USB or PCI/PCIe interfaced device in your PC), please bypass this step.
*    2. Set the 'deviceDescription' for opening the device. 
*    3. Set the 'profilePath' to save the profile path of being initialized device. 
*    4. Set the 'channelStart' as the start channel of the counter to operate
*    5. Set the 'channelCount' as the channel count of the counter to operate.
*    6. set the 'delayCount' to decide delay time for selected channel.
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
const wchar_t* profilePath  = L"../../profile/DemoDevice.xml";

int32          channelStart = 0;
int32          channelCount = 1;
int32          delayCount   = 50;

inline void waitAnyKey()
{
   do
   {
      SLEEP(1);
   } while (!kbhit());
}

int32 delayedPulseOccursCount = 0;

// This function is used to deal with 'Cntr' Event.
void BDAQCALL OnCounterEvent(void* sender, CntrEventArgs* args, void* userParam)
{
   printf("\n Channel %d's Delayed Pulse occurs %d time(s)\n", args->Channel, ++delayedPulseOccursCount);
}
int main(int argc, char* argv[])
{
   ErrorCode ret = Success;
   // Step 1: Create a 'OneShotCtrl' for Delayed Pulse Generation function.
   OneShotCtrl* oneShotCtrl = OneShotCtrl::Create();

   // Step 2: Set the notification event Handler by which we can known the state of operation effectively.
   oneShotCtrl->addOneShotHandler(OnCounterEvent, NULL);
   do
   {
      // Step 3: Login the server by hostName.
      //ret = oneShotCtrl->Login(L"IDAQ974Bid00");
      //CHK_RESULT(ret);

      // Step 4: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo(deviceDescription);
      ret = oneShotCtrl->setSelectedDevice(devInfo);
      CHK_RESULT(ret);
      ret = oneShotCtrl->LoadProfile(profilePath); //Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 5: Set necessary parameters.
      int32 channelCountMax = oneShotCtrl->getFeatures()->getChannelCountMax();
      ret = oneShotCtrl->setChannelStart(channelStart);
      CHK_RESULT(ret);
      ret = oneShotCtrl->setChannelCount(channelCount);
      CHK_RESULT(ret);
      Array<OsChannel>* osChannel = oneShotCtrl->getChannels();
      for (int32 i = channelStart; i < channelStart + channelCount; i++)
      {
         ret = osChannel->getItem(i % channelCountMax).setDelayCount(delayCount);
         CHK_RESULT(ret);
      }
      CHK_RESULT(ret);

      // Step 6: Start DelayedPulseGeneration.
      printf(" Delayed Pulse Generation is in progress...\n");
      printf(" give a low level signal to Gate pin and Test the pulse signal on the Out pin !\n\n");
      printf(" any key to quit !\n\n");
      ret = oneShotCtrl->setEnabled(true);
      CHK_RESULT(ret);

      // Step 7:The device is working.
      while (!kbhit())
      {
         SLEEP(1);
      }

      // Step 8: stop DelayedPulseGeneration function
      ret = oneShotCtrl->setEnabled(false);
      CHK_RESULT(ret);
   } while (false);

   // Step 9: Logout from server.
   //oneShotCtrl->Logout();

   // Step 10: Close device and release any allocated resource.
   oneShotCtrl->Dispose();

   // If something wrong in this execution, print the error code on screen for tracking.
   if (BioFailed(ret))
   {
      wchar_t enumString[256];
      AdxEnumToString(L"ErrorCode", (int32)ret, 256, enumString);
      printf("Some error occurred. And the last error code is 0x%X. [%ls]\n", ret, enumString);
      waitAnyKey();
   }
   return 0;
}
