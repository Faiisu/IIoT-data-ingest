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
*    AsynchronousOneBufferedAI.cpp
*
* Example Category:
*    AI
*
* Description:
*    This example demonstrates how to use Asynchronous One Buffered AI function.
*
* Instructions for Running:
*    1. Login the edge by hostName. If you'd like to handle a local device
*       (i.e. USB or PCI/PCIe interfaced device in your PC), please bypass this step.
*    2. Set the 'deviceDescription' for opening the device.
*    3. Set the 'profilePath' to save the profile path of being initialized device.
*    4. Set the 'startChannel' as the first channel for scan analog samples
*    5. Set the 'channelCount' to decide how many sequential channels to scan analog samples.
*    6. Set the 'sectionLength' as the length of data section for Buffered AI.
*    7 Set the 'sectionCount' as the count of data section for Buffered AI.
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

#define startChannel  0
#define channelCount  2
#define sectionLength 1024
#define sectionCount  1

// user buffer size should be equal or greater than raw data buffer length, because data ready count
// is equal or more than smallest section of raw data buffer and up to raw data buffer length.
// users can set 'USER_BUFFER_SIZE' according to demand.
#define USER_BUFFER_SIZE (channelCount * sectionLength * sectionCount)
double Data[USER_BUFFER_SIZE];

void BDAQCALL OnStoppedEvent(void* sender, BfdAiEventArgs* args, void* userParam);

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
   wchar_t     enumString[256];

   // Step 1: Create a 'WaveformAiCtrl' for buffered AI function.
   WaveformAiCtrl* wfAiCtrl = WaveformAiCtrl_Create();

   // Step 2: Set the notification event Handler by which we can known the state of operation effectively.
   WaveformAiCtrl_addStoppedHandler(wfAiCtrl, OnStoppedEvent, NULL);
   do
   {
      DeviceInformation devInfo;
      devInfo.DeviceNumber = -1;
      devInfo.DeviceMode   = ModeWrite;
      devInfo.ModuleIndex  = 0;
      wcscpy(devInfo.Description, deviceDescription);

      // Step 3: Login the server by hostName
      //ret = WaveformAiCtrl_Login(wfAiCtrl, L"IDAQ974Bid00");
      //CHK_RESULT(ret);

      // Step 4: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      ret = WaveformAiCtrl_setSelectedDevice(wfAiCtrl, &devInfo);
      CHK_RESULT(ret);
      ret = WaveformAiCtrl_LoadProfile(wfAiCtrl, profilePath); // Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 5: Set necessary parameters
      conversion = WaveformAiCtrl_getConversion(wfAiCtrl);
      ret = Conversion_setChannelStart(conversion, startChannel);
      CHK_RESULT(ret);
      ret = Conversion_setChannelCount(conversion, channelCount);
      CHK_RESULT(ret);

      record = WaveformAiCtrl_getRecord(wfAiCtrl);
      ret = Record_setSectionCount(record, sectionCount); // The sectionCount is nonzero value, which means 'One Buffered' mode.
      CHK_RESULT(ret);
      ret = Record_setSectionLength(record, sectionLength);
      CHK_RESULT(ret);

      printf("Asynchronous finite acquisition is in progress.\n");
      printf("Please wait... any key to quit !\n\n");

      // Step 6: start Asynchronous Buffered AI, 'Asynchronous' means the method returns immediately
      // after the acquisition has been started. The StoppedHandler's 'BfdAiEvent' method will be called
      // after the acquisition is completed.
      ret = WaveformAiCtrl_Prepare(wfAiCtrl);
      CHK_RESULT(ret);
      ret = WaveformAiCtrl_Start(wfAiCtrl);
      CHK_RESULT(ret);

      // Step 7: The device is acquiring data.
      do
      {
         SLEEP(1);
      } while (!kbhit());

      // Step 8: Stop the operation if it is running.
      ret = WaveformAiCtrl_Stop(wfAiCtrl);
      CHK_RESULT(ret);
   } while (FALSE);

   // Step 9: Release all allocated resource.
   WaveformAiCtrl_Release(wfAiCtrl);

   // Step 10: Logout from server.
   //WaveformAiCtrl_Logout(wfAiCtrl);

   // Step 11: close device, release any allocated resource before quit.
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

// This function is used to deal with 'Stoppped Event'
void BDAQCALL OnStoppedEvent(void* sender, BfdAiEventArgs* args, void* userParam)
{
   int32           i = 0, returnedCount = 0, getDataCount = 0;
   int32           remainingCount = args->Count;
   WaveformAiCtrl* waveformAiCtrl = (WaveformAiCtrl*)sender;
   printf("Asynchronous One Buffered AI Stopped: data count = %d\n", remainingCount);

   do
   {
      getDataCount = MinValue(USER_BUFFER_SIZE, remainingCount);
      WaveformAiCtrl_GetDataF64(waveformAiCtrl, getDataCount, Data, 0, &returnedCount, NULL, NULL, NULL);
      remainingCount -= returnedCount;
   } while (remainingCount > 0);

   // Show each channel's new data
   for (i = 0; i < channelCount; ++i)
   {
      printf("channel %d:%10.6f \n", i + startChannel, Data[i]);
   }
}
