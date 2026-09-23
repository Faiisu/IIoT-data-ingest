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
$Log: $
 --------------------------------------------------------------------------------
$NoKeywords:  $
*/
/******************************************************************************
*
* Windows  Example:
*    PulseOutputwithTimerInterrupt.c
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use Pulse Output with Timer Interrupt function.
*
* Instructions for Running:
*    1. Login the edge by hostName. If you'd like to handle a local device 
*       (i.e. USB or PCI/PCIe interfaced device in your PC), please bypass this step.
*    2. Set the 'deviceDescription' for opening the device. 
*    3. Set the 'profilePath' to save the profile path of being initialized device. 
*    4. Set the 'channelStart' as the start channel of the counter to operate
*    5. Set the 'channelCount' as the channel count of the counter to operate.
*    6. set the 'frequency' to decide the frequency of pulse for selected channel.
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
#define deviceDescription L"DemoDevice,BID#0"
const wchar_t* profilePath  = L"../../profile/DemoDevice.xml";

int32          channelStart = 0;
int32          channelCount = 1;
double         frequency    = 10;

void waitAnyKey()
{
   do
   {
      SLEEP(1);
   } while (!kbhit());
}

int main(int argc, char* argv[])
{
   ErrorCode     ret             = Success;
   IArray*       channels        = 0;
   TmrChannel*   tmrChannel      = 0;
   CntrFeatures* cntrFeatures    = 0;
   int           index           = 0;
   int           channelCountMax = 0;
   wchar_t       enumString[256];

   // Step 1: Create a 'TimerPulseCtrl' for Pulse Output with Timer Interrupt function.
   TimerPulseCtrl* timerPulseCtrl = TimerPulseCtrl_Create();

   do
   {
      DeviceInformation devInfo;
      devInfo.DeviceNumber = 0;
      devInfo.DeviceMode   = ModeWrite;
      devInfo.ModuleIndex  = 0;
      wcscpy(devInfo.Description, deviceDescription);

      // Step 2: Login the server by hostName
      //ret = TimerPulseCtrl_Login(timerPulseCtrl, L"IDAQ974Bid00");
      //CHK_RESULT(ret);

      // Step 3: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      ret = TimerPulseCtrl_setSelectedDevice(timerPulseCtrl, &devInfo);
      CHK_RESULT(ret);
      ret = TimerPulseCtrl_LoadProfile(timerPulseCtrl, profilePath); // Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 4: Set necessary parameters.
      cntrFeatures    = TimerPulseCtrl_getFeatures(timerPulseCtrl);
      channelCountMax = CntrFeatures_getChannelCountMax(cntrFeatures);
      ret = TimerPulseCtrl_setChannelStart(timerPulseCtrl, channelStart);
      CHK_RESULT(ret);
      ret = TimerPulseCtrl_setChannelCount(timerPulseCtrl, channelCount);
      CHK_RESULT(ret);
      channels = TimerPulseCtrl_getChannels(timerPulseCtrl);
      for (index = channelStart; index < channelStart + channelCount; index++)
      {
         tmrChannel = (TmrChannel*)Array_getItem(channels, index % channelCountMax);
         ret = TmrChannel_setFrequency(tmrChannel, frequency);
         CHK_RESULT(ret);
      }
      CHK_RESULT(ret);

      // Step 5: Start PulseOutputwithTimerInterrupt
      printf(" PulseOutputwithTimerInterrupt is in progress...\n Test signal to the Out pin !\n");
      printf(" Any key to quit !\n");
      ret = TimerPulseCtrl_setEnabled(timerPulseCtrl, TRUE);
      CHK_RESULT(ret);

      while (!kbhit())
      {
         SLEEP(1);
      }

      // Step 6: Stop PulseOutputwithTimerInterrupt
      ret = TimerPulseCtrl_setEnabled(timerPulseCtrl, FALSE);
      CHK_RESULT(ret);
   } while (FALSE);

   // Step 7: Logout from server.
   //TimerPulseCtrl_Logout(timerPulseCtrl);

   // Step 8: Close device and release any allocated resource.
   TimerPulseCtrl_Dispose(timerPulseCtrl);

   // If something wrong in this execution, print the error code on screen for tracking.
   if (BioFailed(ret))
   {
      AdxEnumToString(L"ErrorCode", (int32)ret, 256, enumString);
      printf("Some error occurred. And the last error code is 0x%X. [%ls]\n", ret, enumString);
      waitAnyKey();
   }
   return 0;
}