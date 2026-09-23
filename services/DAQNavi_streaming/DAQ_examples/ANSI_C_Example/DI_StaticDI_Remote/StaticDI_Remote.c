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
*    StaticDI_Remote.cpp
*
* Example Category:
*    DIO
*
* Description:
*    This example demonstrates how to use Static DI function.
*
* Instructions for Running:
*    1. Login the edge by hostName. If you'd like to handle a local device 
*       (i.e. USB or PCI/PCIe interfaced device in your PC), please bypass this step.
*    2. Set the 'deviceDescription' for opening the device. 
*    3. Set the 'profilePath' to save the profile path of being initialized device. 
*    4. Set the 'startPort' as the first port for Di scanning.
*    5. Set the 'portCount' to decide how many sequential ports to operate Di scanning.
*
* I/O Connections Overview:
*    Please refer to your hardware reference manual.
*
******************************************************************************/
#include "../../../inc/bdaqctrl.h"
#include "../inc/compatibility.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
//-----------------------------------------------------------------------------------
// Configure the following parameters before running the demo
//-----------------------------------------------------------------------------------
typedef unsigned char byte;
#define deviceDescription L"DemoDevice,BID#0"
const wchar_t* profilePath = L"../../profile/DemoDevice.xml";

int32          startPort   = 0;
int32          portCount   = 1;

void waitAnyKey()
{
   do
   {
      SLEEP(1);
   } while (!kbhit());
}

int main(int argc, char* argv[])
{
   int   i;
   uint8 dataBuffer[64] = {0}; // The first element of this array is used for start port
   //uint8 data = 0;//data is used to the 'InstantDiCtrl_ReadBit'.
   //int   bit = 0;//bit is used to the 'InstantDiCtrl_ReadBit'.
   IArray*   dioPort = NULL;
   ErrorCode ret     = Success;
   wchar_t   enumString[256];

   // Step 1: Create a 'InstantDiCtrl' for DI function.
   InstantDiCtrl* instantDiCtrl = InstantDiCtrl_Create();
   do
   {
      DeviceInformation devInfo;
      devInfo.DeviceNumber = -1;
      devInfo.DeviceMode   = ModeWrite;
      devInfo.ModuleIndex  = 0;
      wcscpy(devInfo.Description, deviceDescription);

      // Step 2: Login the server by hostName
      ret = InstantDiCtrl_Login(instantDiCtrl, L"IDAQ974Bid00");
      CHK_RESULT(ret);

      // Step 3: select a device by device number or device description and specify the access mode.
      // in this example we use ModeWrite mode so that we can fully control the device, including configuring, sampling, etc.
      ret = InstantDiCtrl_setSelectedDevice(instantDiCtrl, &devInfo);
      CHK_RESULT(ret);
      ret = InstantDiCtrl_LoadProfile(instantDiCtrl, profilePath); // Loads a profile to initialize the device.
      CHK_RESULT(ret);

      // Step 4: Read DI ports' status and show.
      // Set port dircetion
      //dioPort = InstantDiCtrl_getPorts(instantDiCtrl);
      //ret = DioPort_setDirectionMask((DioPort*)Array_getItem(dioPort, 0), Input);// Setting port0 direction
      //CHK_RESULT(ret);

      printf(" Reading ports' status is in progress, any key to quit !\n\n");

      do
      {
         ret = InstantDiCtrl_ReadAny(instantDiCtrl, startPort, portCount, dataBuffer);
         /************************************************************************/
         //ret = InstantDiCtrl_ReadBit(instantDiCtrl, startPort, bit, &data);
         //NOTE:
         //argument2:which port you want to contrl? For example, startPort is 0.
         //argument3:which bit you want to control? You can write 0--7, any number you want.
         //argument4:data is used to save the result.
         /************************************************************************/
         CHK_RESULT(ret);
         //Show ports' status
         for (i = startPort; i < startPort + portCount; ++i)
         {
            printf(" DI port %d status is: 0x%X\n\n", i, dataBuffer[i - startPort]);
            //printf(" DI port %d status is: 0x%X\n\n", i, data);//for 'InstantDiCtrl_ReadBit'
         }
         SLEEP(1);
      } while (!kbhit());
   } while (FALSE);

   // Step 5 : Logout from server.
   InstantDiCtrl_Logout(instantDiCtrl);

   // Step 6: Close device and release any allocated resource.
   InstantDiCtrl_Dispose(instantDiCtrl);

   // If something wrong in this execution, print the error code on screen for tracking.
   if (BioFailed(ret))
   {
      AdxEnumToString(L"ErrorCode", (int32)ret, 256, enumString);
      printf("Some error occurred. And the last error code is 0x%X. [%ls]\n", ret, enumString);
      waitAnyKey();
   }
   return 0;
}