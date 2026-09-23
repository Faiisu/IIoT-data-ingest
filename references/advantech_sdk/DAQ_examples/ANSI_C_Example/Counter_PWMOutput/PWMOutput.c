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
*    PWMOutput.c
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use PWM Output function.
*
* Instructions for Running:
*    1. Login the edge by hostName. If you'd like to handle a local device 
*       (i.e. USB or PCI/PCIe interfaced device in your PC), please bypass this step.
*    2. Set the 'deviceDescription' for opening the device. 
*    3. Set the 'profilePath' to save the profile path of being initialized device. 
*    4. Set the 'channelStart' as the start channel of the counter to operate
*    5. Set the 'channelCount' as the channel count of the counter to operate.
*    6. set the 'pulseWidth' to decide the period of pulse for selected channel.
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
PulseWidth     pulseWidth   = {0.08, 0.02};

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
   PoChannel*    poChannel       = 0;
   CntrFeatures* cntrFeatures    = 0;
   int           index           = 0;
   int32         channelCountMax = 0;
   wchar_t       enumString[256];

   // Step 1: Create a 'PwModulatorCtrl' for PWMOutput function.
   PwModulatorCtrl* pwMoulatorCtrl = PwModulatorCtrl_Create();

   do
   {
      DeviceInformation devInfo;
      devInfo.DeviceNumber = -1;
      devInfo.DeviceMode   = ModeWrite;
      devInfo.ModuleIndex  = 0;
      wcscpy(devInfo.Description, deviceDescription);

      // Step 2: Login the server by hostName
      //ret = PwModulatorCtrl_Login(pwMoulatorCtrl, L"IDAQ974Bid00");
      //CHK_RESULT(ret);

      // Step 3: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can ully control the device, including configuring, sampling, etc.
      ret = PwModulatorCtrl_setSelectedDevice(pwMoulatorCtrl, &devInfo);
      CHK_RESULT(ret);
      ret = PwModulatorCtrl_LoadProfile(pwMoulatorCtrl, profilePath); // Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 4: Set necessary parameters.
      cntrFeatures    = PwModulatorCtrl_getFeatures(pwMoulatorCtrl);
      channelCountMax = CntrFeatures_getChannelCountMax(cntrFeatures);
      ret = PwModulatorCtrl_setChannelStart(pwMoulatorCtrl, channelStart);
      CHK_RESULT(ret);
      ret = PwModulatorCtrl_setChannelCount(pwMoulatorCtrl, channelCount);
      CHK_RESULT(ret);
      ret = PwModulatorCtrl_setPulseWidth(pwMoulatorCtrl, &pulseWidth);
      CHK_RESULT(ret);
      channels = PwModulatorCtrl_getChannels(pwMoulatorCtrl);
      for (index = channelStart; index < channelStart + channelCount; index++)
      {
         poChannel = (PoChannel*)Array_getItem(channels, index % channelCountMax);
         ret = PoChannel_setPulseWidth(poChannel, &pulseWidth);
         CHK_RESULT(ret);
      }
      CHK_RESULT(ret);

      // Step 5: start PWMOutput
      printf(" PWMOutput is in progress...\n test signal to the Out pin !\n");
      printf(" any key to quit !\n");

      // Step 6: Stop PWMOutput
      ret = PwModulatorCtrl_setEnabled(pwMoulatorCtrl, TRUE);
      CHK_RESULT(ret);
      while (!kbhit())
      {
         SLEEP(1);
      }
      ret = PwModulatorCtrl_setEnabled(pwMoulatorCtrl, FALSE);
      CHK_RESULT(ret);
   } while (FALSE);

   // Step 7: Logout from server.
   //PwModulatorCtrl_Logout(pwMoulatorCtrl);

   // Step 8: Close device and release any allocated resource.
   PwModulatorCtrl_Dispose(pwMoulatorCtrl);

   // If something wrong in this execution, print the error code on screen for tracking.
   if (BioFailed(ret))
   {
      AdxEnumToString(L"ErrorCode", (int32)ret, 256, enumString);
      printf("Some error occurred. And the last error code is 0x%X. [%ls]\n", ret, enumString);
      waitAnyKey();
   }
   return 0;
}