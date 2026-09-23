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
*     ContinueCompare_Remote.cpp
*
* Example Category:
*    Counter
*
* Description:
*    This example demonstrates how to use Continue Compare Counter function.
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
#define     deviceDescription L"PCI-1784,BID#0" 
const wchar_t* profilePath = L"../../profile/PCI-1784.xml"; 

int32          channelStart = 0;
int32          channelCount = 1;

inline void waitAnyKey()
{
   do
   {
      SLEEP(1);
   } while (!kbhit());
}

int comValueTab[2][3] = {{50, 100, 150}, {1000, 1304, 1755}};

int       conCmpOccursCount = 0;
int       tabIndex          = 0;
int const evntID[8]         = {EvtCntCompareTableEnd0, EvtCntCompareTableEnd1, EvtCntCompareTableEnd2, EvtCntCompareTableEnd3,
                       EvtCntCompareTableEnd4, EvtCntCompareTableEnd5, EvtCntCompareTableEnd6, EvtCntCompareTableEnd7};
int const evntCompID[8]     = {EvtCntPatternMatch0, EvtCntPatternMatch1, EvtCntPatternMatch2, EvtCntPatternMatch3,
                           EvtCntPatternMatch4, EvtCntPatternMatch5, EvtCntPatternMatch6, EvtCntPatternMatch7};

// This function is used to deal with 'Cntr' Event.
void BDAQCALL OnCounterEvent(void* sender, UdCntrEventArgs* args, void* userParam)
{
   UdCounterCtrl* udCounterCtrl = (UdCounterCtrl*)sender;
   int            channel       = udCounterCtrl->getChannelStart();
   if (evntCompID[channel] == args->Id)
   {
      printf("Channel %d Compare occurs %d time(times)\n", channel, ++conCmpOccursCount);
      printf("Compare value is %d\n\n", comValueTab[(conCmpOccursCount - 1) / 3][(conCmpOccursCount - 1) % 3]);
   }
   else if (evntID[channel] == args->Id) //CompareAppendTable set success
   {
      printf("Channel %d Compare end\n", channel);
      if (++tabIndex < 2)
      {
         udCounterCtrl->CompareAppendTable(channel, 3, comValueTab[tabIndex]);
      }
   }
}

int main(int argc, char* argv[])
{
   ErrorCode ret = Success;
   // Step 1: Create a 'UdCounterCtrl' for UpDown Counter function.
   UdCounterCtrl* udCounterCtrl = UdCounterCtrl::Create();

   // Step 2: Set the notification event Handler by which we can known the state of operation effectively.
   udCounterCtrl->addUdCntrEventHandler(OnCounterEvent, NULL);

   do
   {
      // Step 3: Login the server by hostName.
      ret = udCounterCtrl->Login(L"IDAQ974Bid00");
      CHK_RESULT(ret);

      // Step 4: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo(deviceDescription);
      ret = udCounterCtrl->setSelectedDevice(devInfo);
      CHK_RESULT(ret);
      ret = udCounterCtrl->LoadProfile(profilePath); //Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 5: Set necessary parameters.
      ret = udCounterCtrl->setChannelStart(channelStart);
      CHK_RESULT(ret);
      ret = udCounterCtrl->setChannelCount(channelCount);
      CHK_RESULT(ret);

      // Step 6: Set counting type for UpDown Counter
      /******************************************************************************************************************/
      /*In this example, we use the PCIE-1784 and set 'PulseDirection' as the default CountingType.The details see manual.
      /******************************************************************************************************************/
      Array<UdChannel>* udChannel = udCounterCtrl->getChannels();
      for (int32 i = channelStart; i < channelStart + channelCount; i++)
      {
         ret = udChannel->getItem(i).setCountingType(PulseDirection);
         CHK_RESULT(ret);
      }
      CHK_RESULT(ret);

      // Step 7: Set compare table
      ret = udCounterCtrl->CompareAppendTable(udCounterCtrl->getChannelStart(), 3, comValueTab[tabIndex]);
      CHK_RESULT(ret);

      // Step 8: Start UpDown Counter
      ret = udCounterCtrl->setEnabled(true);
      CHK_RESULT(ret);

      // Step 9: Read counting value: connect the input signal to channels you selected to get UpDown counter value.
      printf("UnDown counter is in progress...\nconnect the input signal to\n ");
      printf("any key will stop UnDown counter!\n\n");
      while (!kbhit())
      {
         SLEEP(1); //get event UpDown count value per second
         int32 value = 0;
         ret = udCounterCtrl->Read(value);
         CHK_RESULT(ret);
         printf("channel %d Current UpDown count: %d \n\n", channelStart, value);
      }

      // Step 10: stop UpDown Counter
      ret = udCounterCtrl->CompareClear();
      CHK_RESULT(ret);
      ret = udCounterCtrl->setEnabled(false);
      CHK_RESULT(ret);
   } while (false);

   // Step 11: Logout from server.
   udCounterCtrl->Logout();

   // Step 12: Close device and release any allocated resource.
   udCounterCtrl->Dispose();

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
