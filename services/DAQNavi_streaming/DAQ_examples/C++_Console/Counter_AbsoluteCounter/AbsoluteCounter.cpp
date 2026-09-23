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
*    AbsoluteCounter.cpp
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use Absolute Counter function.
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
#define     deviceDescription L"Amax-5082,BID#1"
const wchar_t* profilePath = L"../../profile/AMAX-5082.xml";

const double   filterTime   = 0.0003;
int32          channelStart = 0;
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

   // Step 1: Create a 'AbsCounterCtrl' for Absolute Counter function.
   AbsCounterCtrl* absCounterCtrl = AbsCounterCtrl::Create();

   do
   {
      // Step 2: Login the server by hostName.
      //ret = absCounterCtrl->Login(L"IDAQ974Bid00");
      //CHK_RESULT(ret);

      // Step 3: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo(deviceDescription);
      ret = absCounterCtrl->setSelectedDevice(devInfo);
      CHK_RESULT(ret);
      //ret = absCounterCtrl->LoadProfile(profilePath);//Loads a profile to initialize the device.
      //CHK_RESULT(ret);

      // Step 4: Set necessary parameters
      ret = absCounterCtrl->setChannelStart(channelStart);
      CHK_RESULT(ret);
      ret = absCounterCtrl->setChannelCount(channelCount);
      CHK_RESULT(ret);
      ret = absCounterCtrl->setNoiseFilterBlockTime(filterTime);
      CHK_RESULT(ret);
      double time = absCounterCtrl->getNoiseFilterBlockTime();

      // Step 5: Set configuration for Absolute Counter
      /******************************************************************************************************************/
      /*In this example, we demonstrate the AMAX-5082 configuration
       /******************************************************************************************************************/
      Array<AbsChannel>* absChannel = absCounterCtrl->getChannels();
      for (int i = channelStart; i < channelStart + channelCount; i++)
      {
         //Noise Filter
         ret = absChannel->getItem(i).setNoiseFiltered(true);
         CHK_RESULT(ret);
         bool filtered = absChannel->getItem(i).getNoiseFiltered();

         //Coding Type Configuration
         ret = absChannel->getItem(i).setCodingType(GrayCode);
         CHK_RESULT(ret);
         CodingType codetype = absChannel->getItem(i).getCodingType();

         //Baudrate Configuration
         ret = absChannel->getItem(i).setBaudrate(Baudrate500KHz);
         CHK_RESULT(ret);
         Baudrate baudrate = absChannel->getItem(i).getBaudrate();

         //Error Ret Configuration
         ret = absChannel->getItem(i).setErrorRetType(ParticularValue);
         CHK_RESULT(ret);
         ErrorRetType errorType = absChannel->getItem(i).getErrorRetType();
         ret = absChannel->getItem(i).setErrorRetValue(0xFFFFFF);
         CHK_RESULT(ret);
         int32 errorRetValue = absChannel->getItem(i).getErrorRetValue();

         //Latch Function Configuration
         ret = absChannel->getItem(i).setLatchSigEdge(RisingEdge);
         CHK_RESULT(ret);
         ActiveSignal latchSigEdge = absChannel->getItem(i).getLatchSigEdge();
         int32        latchedValue = absChannel->getItem(i).getLatchedValue();

         //Compare Function Configuration
         ret = absChannel->getItem(i).setCompareValue0(0x222222);
         CHK_RESULT(ret);
         int32 compareValue0 = absChannel->getItem(i).getCompareValue0();
         ret = absChannel->getItem(i).setCompare0Enabled(true);
         bool enabled0 = absChannel->getItem(i).getCompare0Enabled();
         ret = absChannel->getItem(i).setCompareValue1(0x233333);
         CHK_RESULT(ret);
         int32 compareValue1 = absChannel->getItem(i).getCompareValue1();
         ret = absChannel->getItem(i).setCompare1Enabled(true);
         CHK_RESULT(ret);
         bool enabled1 = absChannel->getItem(i).getCompare1Enabled();
         ret = absChannel->getItem(i).setOutSignal(PositivePulse);
         CHK_RESULT(ret);
         OutSignalType signaltype = absChannel->getItem(i).getOutSignal();
      }

      // Step 6: Start Absolute Counter
      ret = absCounterCtrl->setEnabled(true);
      CHK_RESULT(ret);

      // Step 7: Read counting value: connect the input signal to channels you selected to get Absolute counter value.
      printf("Absolute counter is in progress...\nconnect the input signal to ");
      printf("any key will stop Absolute counter!\n\n");
      while (!kbhit())
      {
         SLEEP(1);
         int32 value = 0;
         ret = absCounterCtrl->Read(value);
         printf("\n Channel [%d], Current Absolute Count Value: [0x%X]\n", channelStart, value);

         //Checking status value if counter returns ParticularValue
         if (value == 0xFFFFFF)
         {
            int32 status = 0;
            ret = absCounterCtrl->StatusRead(status);
            printf("\n Channel [%d], Current Absolute Status Value: [0x%X]\n", channelStart, status);
         }
      }

      // Step 8: stop Absolute Counter
      ret = absCounterCtrl->setEnabled(false);
      CHK_RESULT(ret);
   } while (false);

   // Step 9: Logout from server.
   //absCounterCtrl->Logout();

   // Step 10: Close device and release any allocated resource.
   absCounterCtrl->Dispose();

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