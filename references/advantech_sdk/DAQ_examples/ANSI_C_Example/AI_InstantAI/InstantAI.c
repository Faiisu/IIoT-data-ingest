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
*    InstantAI.c
*
* Example Category:
*    AI
*
* Description:
*    This example demonstrates how to use Instant AI function.
*
* Instructions for Running:
*    1. Login the edge by hostName. If you'd like to handle a local device
*       (i.e. USB or PCI/PCIe interfaced device in your PC), please bypass this step.
*    2. Set the 'deviceDescription' for opening the device.
*    3. Set the 'profilePath' to save the profile path of being initialized device.
*    4. Set the 'startChannel' as the first channel for scan analog samples
*    5. Set the 'channelCount' to decide how many sequential channels to scan analog samples.
*
* I/O Connections Overview:
*    Please refer to your hardware reference manual.
*
******************************************************************************/
#include "../../../inc/bdaqctrl.h"
#include "../inc/compatibility.h"
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
//-----------------------------------------------------------------------------------
// Configure the following parameters before running the demo
//-----------------------------------------------------------------------------------
#define deviceDescription L"DemoDevice,BID#0"
#define channelCount      2
const wchar_t* profilePath  = L"../../profile/DemoDevice.xml";
int32          startChannel = 0;

void waitAnyKey()
{
   do
   {
      SLEEP(1);
   } while (!kbhit());
}

int main(int argc, char* argv[])
{
   int32     i                        = 0;
   double    scaledData[channelCount] = {0};
   int       channelCountMax          = 0;
   ErrorCode ret                      = Success;
   wchar_t   enumString[256];

   // Step 1: Create an 'instantAiCtrl' for InstantAI function.
   InstantAiCtrl* instantAiCtrl = InstantAiCtrl_Create();
   do
   {
      DeviceInformation devInfo;
      devInfo.DeviceNumber = -1;
      devInfo.DeviceMode   = ModeWrite;
      devInfo.ModuleIndex  = 0;
      wcscpy(devInfo.Description, deviceDescription);

      // Step 2: Login the server by hostName
      //ret = InstantAiCtrl_Login(instantAiCtrl, L"IDAQ974Bid00");
      //CHK_RESULT(ret);

      // Step 3: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      ret = InstantAiCtrl_setSelectedDevice(instantAiCtrl, &devInfo);
      CHK_RESULT(ret);
      ret = InstantAiCtrl_LoadProfile(instantAiCtrl, profilePath); // Loads a profile to initialize the device.
      CHK_RESULT(ret);

      printf("Acquisition is in progress, any key to quit!\n\n");

      channelCountMax = InstantAiCtrl_getChannelCount(instantAiCtrl);
      do
      {
         // read samples and save to buffer 'scaledData'.
         ret = InstantAiCtrl_ReadAny(instantAiCtrl, startChannel, channelCount, 0, scaledData);
         CHK_RESULT(ret);

         // process the acquired data. only show data here.
         for (i = startChannel; i < startChannel + channelCount; ++i)
         {
            printf("Channel %d data: %10.6f\n\n", i % channelCountMax, scaledData[i - startChannel]);
         }
         SLEEP(1);
      } while (!kbhit());
   } while (FALSE);

   // Step 4: Logout from server.
   //InstantAiCtrl_Logout(instantAiCtrl);

   // Step 5: Close device and release any allocated resource.
   InstantAiCtrl_Dispose(instantAiCtrl);

   // If something wrong in this execution, print the error code on screen for tracking.
   if (BioFailed(ret))
   {
      AdxEnumToString(L"ErrorCode", (int32)ret, 256, enumString);
      printf("Some error occurred. And the last error code is 0x%X. [%ls]\n", ret, enumString);
      waitAnyKey(); // wait any key to quit!
   }
   return 0;
}
