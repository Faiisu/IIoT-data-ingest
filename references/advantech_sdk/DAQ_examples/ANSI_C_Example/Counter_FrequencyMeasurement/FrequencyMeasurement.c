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
* Windows Example:
*    FrequencyMeasurement.cpp
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use Frequency Measurement function.
*
* Instructions for Running:
*    1. Login the edge by hostName. If you'd like to handle a local device 
*       (i.e. USB or PCI/PCIe interfaced device in your PC), please bypass this step.
*    2. Set the 'deviceDescription' for opening the device. 
*    3. Set the 'profilePath' to save the profile path of being initialized device. 
*    4. Set the 'channelStart' as the start channel of the counter to operate
*    5. Set the 'channelCount' as the channel count of the counter to operate.
*    6. Set the 'collectionPeriod' to decide period to measure frequency.
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

void waitAnyKey()
{
   do
   {
      SLEEP(1);
   } while (!kbhit());
}

int main(int argc, char* argv[])
{
   ErrorCode     ret              = Success;
   IArray*       channels         = 0;
   FmChannel*    fmChannel        = 0;
   CntrFeatures* cntrFeatures     = 0;
   int           index            = 0;
   int           channelCountMax  = 0;
   double        collectionPeriod = 0;
   double        value            = 0;
   wchar_t       enumString[256];

   // Step 1: Create a 'FreqMeterCtrl' for Frequency Measurement function.
   FreqMeterCtrl* freqMeterCtrl = FreqMeterCtrl_Create();
   do
   {
      DeviceInformation devInfo;
      devInfo.DeviceNumber = -1;
      devInfo.DeviceMode   = ModeWrite;
      devInfo.ModuleIndex  = 0;
      wcscpy(devInfo.Description, deviceDescription);

      // Step 2: Login the server by hostName
      //ret = FreqMeterCtrl_Login(freqMeterCtrl, L"IDAQ974Bid00");
      //CHK_RESULT(ret);

      // Step 3: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      ret = FreqMeterCtrl_setSelectedDevice(freqMeterCtrl, &devInfo);
      CHK_RESULT(ret);
      ret = FreqMeterCtrl_LoadProfile(freqMeterCtrl, profilePath); // Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 4: Set necessary parameters.
      cntrFeatures    = FreqMeterCtrl_getFeatures(freqMeterCtrl);
      channelCountMax = CntrFeatures_getChannelCountMax(cntrFeatures);
      ret = FreqMeterCtrl_setChannelStart(freqMeterCtrl, channelStart);
      CHK_RESULT(ret);
      ret = FreqMeterCtrl_setChannelCount(freqMeterCtrl, channelCount);
      CHK_RESULT(ret);
      channels = FreqMeterCtrl_getChannels(freqMeterCtrl);
      for (index = channelStart; index < channelStart + channelCount; index++)
      {
         fmChannel = (FmChannel*)Array_getItem(channels, index % channelCountMax);
         ret = FmChannel_setCollectionPeriod(fmChannel, collectionPeriod); //0 means automation
         CHK_RESULT(ret);
      }
      CHK_RESULT(ret);

      // Step 5: Start Frequency Measurement
      ret = FreqMeterCtrl_setEnabled(freqMeterCtrl, TRUE);
      CHK_RESULT(ret);

      // Step 6: Read frequency value.
      printf("FrequencyMeasurement is in progress...\n");
      printf("connect the input signal to CNT%d_CLK pin if you choose external clock!\n", channelStart);
      printf("any key to quit!\n\n");
      while (!kbhit())
      {
         SLEEP(1);
         ret = FreqMeterCtrl_Read(freqMeterCtrl, 1, &value);
         CHK_RESULT(ret);
         printf("\n channel %d Current frequency: %f Hz\n", channelStart, value);
      }

      // Step 7: Stop Frequency Measurement
      ret = FreqMeterCtrl_setEnabled(freqMeterCtrl, FALSE);
      CHK_RESULT(ret);
   } while (FALSE);

   // Step 8: Logout from server.
   //FreqMeterCtrl_Logout(freqMeterCtrl);

   // Step 9: Close device and release any allocated resource.
   FreqMeterCtrl_Dispose(freqMeterCtrl);

   // If something wrong in this execution, print the error code on screen for tracking.
   if (BioFailed(ret))
   {
      AdxEnumToString(L"ErrorCode", (int32)ret, 256, enumString);
      printf("Some error occurred. And the last error code is 0x%X. [%ls]\n", ret, enumString);
      waitAnyKey();
   }
   return 0;
}
