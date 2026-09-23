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
*    PollingStramingAI.cpp
*
* Example Category:
*    AI
*
* Description:
*    This example demonstrates how to use Polling Streaming AI function.
*
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
const int32    sectionCount  = 0;
// user buffer size should be equal or greater than raw data buffer length, because data ready count
// is equal or more than smallest section of raw data buffer and up to raw data buffer length.
// users can set 'USER_BUFFER_SIZE' according to demand.
#define USER_BUFFER_SIZE channelCount* sectionLength
double userDataBuffer[USER_BUFFER_SIZE];
int32  returnedCount = 0;

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

   // Step 1: Create a 'WaveformAiCtrl' for Buffered AI function.
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
      ret = record->setSectionCount(sectionCount); //The 0 means setting 'streaming' mode.
      CHK_RESULT(ret);

      // Step 5: The operation has been started.
      ret = wfAiCtrl->Prepare();
      CHK_RESULT(ret);
      ret = wfAiCtrl->Start();
      CHK_RESULT(ret);

      double startTime = 0;
      // Step 6: The device is acquiring data with Polling Style.
      printf("Polling infinite acquisition is in progress.\n");
      do
      {
         ret = wfAiCtrl->GetData(USER_BUFFER_SIZE, userDataBuffer, -1, &returnedCount, &startTime); //The timeout value is -1, meaning infinite waiting.
         CHK_RESULT(ret);
         printf("Polling Streaming AI get data count is %d \n", returnedCount);
         printf("the startTime = %10.6f, first sample for each Channel are:\n", startTime);
         for (int32 i = 0; i < channelCount; ++i)
         {
            printf("channel %d:%10.6f \n", (i + startChannel), userDataBuffer[i]);
         }
      } while (!kbhit());

      // Step 7: Stop the operation if it is running.
      ret = wfAiCtrl->Stop();
      CHK_RESULT(ret);
   } while (false);

   // Step 8: Release all allocated resource.
   wfAiCtrl->Release();

   // Step 9: Logout from server.
   //wfAiCtrl->Logout();

   // Step 10: Close device, release any allocated resource.
   wfAiCtrl->Dispose();

   // If something wrong in this execution, print the error code on screen for tracking.
   if (BioFailed(ret))
   {
      wchar_t enumString[256];
      AdxEnumToString(L"ErrorCode", (int32)ret, 256, enumString);
      printf("Some error occurred. And the last error code is 0x%X. [%ls]\n", ret, enumString);
      waitAnyKey(); // wait any key to quit!
   }
   return 0;
}
