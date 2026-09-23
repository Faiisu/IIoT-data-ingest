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
*     PulseWidthMeasurement.cpp
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use Pulse Width Measurement function.
*
* Instructions for Running:
*    1. Login the edge by hostName. If you'd like to handle a local device 
*       (i.e. USB or PCI/PCIe interfaced device in your PC), please bypass this step.
*    2. Set the 'deviceDescription' for opening the device. 
*    3. Set the 'profilePath' to save the profile path of being initialized device. 
*    4. Set the 'channelStart' as the start channel of the counter to operate
*    5. Set the 'channelCount' as the channel count of the counter to operate.
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

int32          startChannel = 0;
int32          channelCount = 1;

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
   // Step 1: Create a 'PwMeterCtrl' for PulseWidthMeasurement function.
   PwMeterCtrl* pwMeterCtrl = PwMeterCtrl::Create();
   do
   {
      // Step 2: Login the server by hostName.
      //ret = pwMeterCtrl->Login(L"IDAQ974Bid00");
      //CHK_RESULT(ret);

      // Step 3: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo(deviceDescription);
      ret = pwMeterCtrl->setSelectedDevice(devInfo);
      CHK_RESULT(ret);
      ret = pwMeterCtrl->LoadProfile(profilePath); //Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 4: Set necessary parameters.
      ret = pwMeterCtrl->setChannelStart(startChannel);
      CHK_RESULT(ret);
      ret = pwMeterCtrl->setChannelCount(channelCount);
      CHK_RESULT(ret);

      // Step 5:Start PulseWidthMeasurement
      ret = pwMeterCtrl->setEnabled(true);
      CHK_RESULT(ret);

      // Step 6: Get Pulse Width value.
      PulseWidth pwValue;
      printf(" Pulse Width Measurement is in progress... any key to quit !\n");
      while (!kbhit())
      {
         SLEEP(1);
         pwMeterCtrl->Read(pwValue);
         printf("\n Channel %u Current Pulse Width:HiPeriod=%f s  LoPeriod=%f s \n", startChannel, pwValue.HiPeriod, pwValue.LoPeriod);
      }

      // Step 7: Stop PulseWidthMeasurement
      ret = pwMeterCtrl->setEnabled(false);
      CHK_RESULT(ret);
   } while (false);

   // Step 8: Logout from server.
   //pwMeterCtrl->Logout();

   // Step 9: Close device and release any allocated resource.
   pwMeterCtrl->Dispose();

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
