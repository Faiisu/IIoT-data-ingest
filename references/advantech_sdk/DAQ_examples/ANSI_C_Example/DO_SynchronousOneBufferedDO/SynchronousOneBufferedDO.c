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
*    SynchronousOneBufferedDO.c
*
* Example Category:
*    DO
*
* Description:
*    This example demonstrates how to use Synchronous One Buffered DO function.
*
* Instructions for Running:
*    1. Login the edge by hostName. If you'd like to handle a local device 
*       (i.e. USB or PCI/PCIe interfaced device in your PC), please bypass this step.
*    2. Set the 'deviceDescription' which can get from system device manager for opening the device. 
*    3. Set the 'profilePath' to save the profile path of being initialized device. 
*    4. Set the 'portEnabled' to decide which port to be used.
*    5. Set the 'sectionLength' as the length of data section for Buffered DO.
*    6. Set the 'sectionCount' as the count of data section for Buffered DO.
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
#define deviceDescription L"iDAQ-731,BID#0"
const wchar_t* profilePath = L"../../profile/iDAQ-731_0.xml";

int8  portEnabled[] = {1, 0, 0, 0};
int32 convClkRate   = 1000;
int32 sectionCount  = 1;
int32 sectionLength = 1024;

void waitAnyKey()
{
   do
   {
      SLEEP(1);
   } while (!kbhit());
}

int main(int argc, char* argv[])
{
   ErrorCode     ret        = Success;
   ConvertClock* convClk    = NULL;
   ScanPort*     scanPort   = NULL;
   IArray*       dioPorts   = NULL;
   int8*         dataBuf    = NULL;
   DioFeatures*  doFeatures = NULL;

   int32   i               = 0;
   int32   bufLen          = 0;
   int32   bufCapacity     = 0;
   int32   canSetDir       = 0;
   wchar_t enumString[256] = {0};
   int8    data            = 0;

   // Step 1: Create a 'Buffered DO Control' for Buffered DO function.
   BufferedDoCtrl* bfdDoCtrl = BufferedDoCtrl_Create();

   do
   {
      DeviceInformation devInfo;
      devInfo.DeviceNumber = -1;
      devInfo.DeviceMode   = ModeWrite;
      devInfo.ModuleIndex  = 0;
      wcscpy(devInfo.Description, deviceDescription);

      // Step 2: Login the server by hostName
      //ret = BufferedDoCtrl_Login(bfdDoCtrl, L"IDAQ974Bid00");
      //CHK_RESULT(ret);

      // Step 3: Select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      ret = BufferedDoCtrl_setSelectedDevice(bfdDoCtrl, &devInfo);
      CHK_RESULT(ret);
      //ret = BufferedDoCtrl_LoadProfile(bfdDoCtrl, profilePath);// Loads a profile to initialize the device.
      //CHK_RESULT(ret);

      // Step 4: Set necessary parameters.
      bufLen     = BufLength(portEnabled);
      doFeatures = BufferedDoCtrl_getFeatures(bfdDoCtrl);
      canSetDir  = DioFeatures_getPortProgrammable(doFeatures);
      if (canSetDir)
      {
         dioPorts = BufferedDoCtrl_getPorts(bfdDoCtrl);
         for (i = 0; i < bufLen; ++i)
         {
            if (portEnabled[i] == 0)
            {
               continue;
            }
            ret = DioPort_setDirectionMask((DioPort*)Array_getItem(dioPorts, i), Output);
            CHK_RESULT(ret);
         }
         CHK_RESULT(ret);
      }

      scanPort = BufferedDoCtrl_getScanPort(bfdDoCtrl);
      ret = ScanPort_setPortMap(scanPort, bufLen, portEnabled);
      CHK_RESULT(ret);

      ret = ScanPort_setSectionLength(scanPort, sectionLength);
      CHK_RESULT(ret);
      ret = ScanPort_setSectionCount(scanPort, sectionCount); // The non-zero means setting 'one-buffered' mode.
      CHK_RESULT(ret);

      convClk = BufferedDoCtrl_getConvertClock(bfdDoCtrl);
      ret = ConvertClock_setSource(convClk, SigInternalClock);
      CHK_RESULT(ret);
      ret = ConvertClock_setRate(convClk, convClkRate);
      CHK_RESULT(ret);

      // Step 5: The operation has been started.
      ret = BufferedDoCtrl_Prepare(bfdDoCtrl);
      CHK_RESULT(ret);

      bufCapacity = BufferedDoCtrl_getBufferCapacity(bfdDoCtrl);
      dataBuf     = (int8*)malloc(bufCapacity);
      if (NULL == dataBuf)
      {
         printf("Insufficient memory available\n");
         break;
      }

      //fill user data buffer
      for (i = 0; i < bufCapacity; i++)
      {
         dataBuf[i] = data;
         data       = ~data;
      }
      ret = BufferedDoCtrl_SetData(bfdDoCtrl, bufCapacity, dataBuf);
      CHK_RESULT(ret);

      free(dataBuf);

      // Step 6: Start Synchronous One Buffered DO, 'Synchronous' indicates using synchronous mode,
      // which means the method will not return until the operation is completed.
      printf("Synchronous finite acquisition is in progress.\n");
      printf("Please wait, until acquisition complete.\n");
      ret = BufferedDoCtrl_RunOnce(bfdDoCtrl);
      CHK_RESULT(ret);
      printf("\nBuffered DO is over, any key to quit !\n");
   } while (0);

   // Step 7: Release all allocated resource.
   BufferedDoCtrl_Release(bfdDoCtrl);

   // Step 8: Logout from server.
   //BufferedDoCtrl_Logout(bfdDoCtrl);

   // Step 9: Close device, release any allocated resource.
   BufferedDoCtrl_Dispose(bfdDoCtrl);

   // If something wrong in this execution, print the error code on screen for tracking.
   if (BioFailed(ret))
   {
      AdxEnumToString(L"ErrorCode", (int32)ret, 256, enumString);
      printf("Some error occurred. And the last error code is 0x%X. [%ls]\n", ret, enumString);
   }
   waitAnyKey(); // wait any key to quit!
   return 0;
}

// This function is used to deal with 'Stopped' Event.
void BDAQCALL OnStoppedEvent(void* sender, BfdDoEventArgs* args, void* userParam)
{
   printf("\nBuffered DO stopped: offset = %d, count = %d\n", args->Offset, args->Count);
}
