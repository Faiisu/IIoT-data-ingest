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
*    DelayedPulseGeneration.c
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
//-----------------------------------------------------------------------------------
// Configure the following parameters before running the demo
//-----------------------------------------------------------------------------------
#define deviceDescription L"DemoDevice,BID#0"
const wchar_t* profilePath  = L"../../profile/DemoDevice.xml";

int32          channelStart = 0;
int32          channelCount = 1;
int32          delayCount   = 50;

void waitAnyKey()
{
   do
   {
      SLEEP(1);
   } while (!kbhit());
}

int32 delayedPulseOccursCount = 0;

// This function is used to deal with 'Counter' Event.
void BDAQCALL OnCounterEvent(void* sender, CntrEventArgs* args, void* userParam);

int main(int argc, char* argv[])
{
   ErrorCode     ret             = Success;
   IArray*       channels        = 0;
   OsChannel*    osChannel       = 0;
   CntrFeatures* cntrFeatures    = 0;
   int           index           = 0;
   int32         channelCountMax = 0;
   wchar_t       enumString[256];

   // Step 1: Create a 'OneShotCtrl' for Delayed Pulse Generation function.
   OneShotCtrl* oneShotCtrl = OneShotCtrl_Create();

   // Step 2: Set the notification event Handler by which we can known the state of operation effectively.
   OneShotCtrl_addOneShotHandler(oneShotCtrl, OnCounterEvent, NULL);
   do
   {
      DeviceInformation devInfo;
      devInfo.DeviceNumber = 0;
      devInfo.DeviceMode   = ModeWrite;
      devInfo.ModuleIndex  = 0;
      wcscpy(devInfo.Description, deviceDescription);

      // Step 3: Login the server by hostName
      //ret = OneShotCtrl_Login(oneShotCtrl, L"IDAQ974Bid00");
      //CHK_RESULT(ret);

      // Step 4: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      ret = OneShotCtrl_setSelectedDevice(oneShotCtrl, &devInfo);
      CHK_RESULT(ret);
      ret = OneShotCtrl_LoadProfile(oneShotCtrl, profilePath); // Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 5: Set necessary parameters.
      cntrFeatures    = OneShotCtrl_getFeatures(oneShotCtrl);
      channelCountMax = CntrFeatures_getChannelCountMax(cntrFeatures);
      ret = OneShotCtrl_setChannelStart(oneShotCtrl, channelStart);
      CHK_RESULT(ret);
      ret = OneShotCtrl_setChannelCount(oneShotCtrl, channelCount);
      CHK_RESULT(ret);
      channels = OneShotCtrl_getChannels(oneShotCtrl);

      for (index = channelStart; index < channelStart + channelCount; index++)
      {
         osChannel = (OsChannel*)Array_getItem(channels, index % channelCountMax);
         ret = OsChannel_setDelayCount(osChannel, delayCount);
         CHK_RESULT(ret);
      }
      CHK_RESULT(ret);

      // Step 6: Start DelayedPulseGeneration.
      printf(" Delayed Pulse Generation is in progress...\n");
      printf(" give a low level signal to Gate pin and Test the pulse signal on the Out pin !\n\n");
      printf(" any key to quit !\n\n");
      ret = OneShotCtrl_setEnabled(oneShotCtrl, TRUE);
      CHK_RESULT(ret);

      // Step 7: The device is working.
      while (!kbhit())
      {
         SLEEP(1);
      }

      // Step 8: Stop DelayedPulseGeneration function
      ret = OneShotCtrl_setEnabled(oneShotCtrl, FALSE);
      CHK_RESULT(ret);
   } while (FALSE);

   // Step 9: Logout from server.
   //OneShotCtrl_Logout(oneShotCtrl);

   // Step 10: Close device and release any allocated resource.
   OneShotCtrl_Dispose(oneShotCtrl);

   // If something wrong in this execution, print the error code on screen for tracking.
   if (BioFailed(ret))
   {
      AdxEnumToString(L"ErrorCode", (int32)ret, 256, enumString);
      printf("Some error occurred. And the last error code is 0x%X. [%ls]\n", ret, enumString);
      waitAnyKey();
   }
   return 0;
}

void BDAQCALL OnCounterEvent(void* sender, CntrEventArgs* args, void* userParam)
{
   printf("\n Channel %d's Delayed Pulse occurs %d time(s)\n", args->Channel, ++delayedPulseOccursCount);
}