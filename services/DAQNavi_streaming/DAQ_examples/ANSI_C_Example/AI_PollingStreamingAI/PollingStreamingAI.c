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
*    PollingStreamingAI.c
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
*    2. Set the 'deviceDescription' for opening the device. 
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
//-----------------------------------------------------------------------------------
// Configure the following parameters before running the demo
//-----------------------------------------------------------------------------------
#define deviceDescription L"DemoDevice,BID#0"
const wchar_t* profilePath = L"../../profile/DemoDevice.xml";

#define startChannel  0
#define channelCount  2
#define sectionLength 1024
#define sectionCount  0

#define USER_BUFFER_SIZE channelCount* sectionLength
double Data[USER_BUFFER_SIZE];
int32  returnedCount = 0;

void waitAnyKey()
{
   do
   {
      SLEEP(1);
   } while (!kbhit());
}

int main(int argc, char* argv[])
{
   ErrorCode   ret        = Success;
   Conversion* conversion = NULL;
   Record*     record     = NULL;
   int32       i          = 0;
   wchar_t     enumString[256];

   // Step 1: Create a 'WaveformAiCtrl' for Buffered AI function.
   WaveformAiCtrl* wfAiCtrl = WaveformAiCtrl_Create();
   do
   {
      DeviceInformation devInfo;
      devInfo.DeviceNumber = -1;
      devInfo.DeviceMode   = ModeWrite;
      devInfo.ModuleIndex  = 0;
      wcscpy(devInfo.Description, deviceDescription);

      // Step 2: Login the server by hostName
      //ret = WaveformAiCtrl_Login(wfAiCtrl, L"IDAQ974Bid00");
      //CHK_RESULT(ret);

      // Step 3: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      ret = WaveformAiCtrl_setSelectedDevice(wfAiCtrl, &devInfo);
      CHK_RESULT(ret);
      ret = WaveformAiCtrl_LoadProfile(wfAiCtrl, profilePath); // Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 4: Set necessary parameters.
      conversion = WaveformAiCtrl_getConversion(wfAiCtrl);
      ret = Conversion_setChannelStart(conversion, startChannel);
      CHK_RESULT(ret);
      ret = Conversion_setChannelCount(conversion, channelCount);
      CHK_RESULT(ret);

      record = WaveformAiCtrl_getRecord(wfAiCtrl);
      ret = Record_setSectionCount(record, sectionCount); // The 0 means setting 'streaming' mode.
      CHK_RESULT(ret);
      ret = Record_setSectionLength(record, sectionLength);
      CHK_RESULT(ret);

      // Step 5: The operation has been started.
      ret = WaveformAiCtrl_Prepare(wfAiCtrl);
      CHK_RESULT(ret);
      ret = WaveformAiCtrl_Start(wfAiCtrl);
      CHK_RESULT(ret);

      // Step 6: The device is acquiring data with Polling Style.
      printf("Polling AI is in progress.\nplease wait...  any key to quit!\n\n");
      do
      {
         ret = WaveformAiCtrl_GetDataF64(wfAiCtrl, USER_BUFFER_SIZE, Data, -1, &returnedCount, NULL, NULL, NULL); // The timeout value is -1, meaning infinite waiting.
         printf("Polling Streaming AI get data count is  %d\n", returnedCount);
         printf("the first sample for each Channel are:\n");
         for (i = 0; i < channelCount; ++i)
         {
            printf("channel %d:%10.6f \n", (i + startChannel), Data[i]);
         }
      } while (!kbhit());

      // Step 7: Stop the operation if it is running.
      ret = WaveformAiCtrl_Stop(wfAiCtrl);
      CHK_RESULT(ret);
   } while (FALSE);

   // Step 8: Release all allocated resource.
   WaveformAiCtrl_Release(wfAiCtrl);

   // Step 9: Logout from server.
   //WaveformAiCtrl_Logout(wfAiCtrl);

   // Step 10: Close device, release any allocated resource.
   WaveformAiCtrl_Dispose(wfAiCtrl);

   // If something wrong in this execution, print the error code on screen for tracking.
   if (BioFailed(ret))
   {
      AdxEnumToString(L"ErrorCode", (int32)ret, 256, enumString);
      printf("Some error occurred. And the last error code is 0x%X. [%ls]\n", ret, enumString);
      waitAnyKey(); // wait any key to quit!
   }
   return 0;
}
