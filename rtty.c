
#include <stdio.h>
#include <stdlib.h>
#include "sdrplay_api.h"

FILE *file;

void EventCallback(sdrplay_api_EventT eventId, sdrplay_api_TunerSelectT tuner, sdrplay_api_EventParamsT *params, void *cbContext){
    printf("EVENT: ");

    switch(eventId) {
        case sdrplay_api_GainChange:
            printf("Gain change!\n");
            break;
        case sdrplay_api_PowerOverloadChange:
            printf("Power overload change!\n");
            break;
        case sdrplay_api_DeviceRemoved:
            printf("The Device has been removed!\n");
            exit(1);
            break;
        case sdrplay_api_RspDuoModeChange:
            printf("RSP Duo Mode Change! (This shouldn't happen with an RSP1)\n");
            break;
        default:
            printf("Unknown event with ID: %hi\n!", eventId);
    }
}

void DataStreamCallback(short *xi, short *xq, sdrplay_api_StreamCbParamsT *params, unsigned int numSamples, unsigned int reset, void *cbContext){
    //printf("Data Stream Call back | Printing xi array | Num of samples: %i\n", numSamples);
    //printf("Num of samples: %i\n", numSamples);
    printf("firstSampleNum: %i, grChanged: %i, rfChanged: %i, fsChanged: %i, NumofSamples: %i, reset: %i\n", params->firstSampleNum, params->grChanged, params->rfChanged, params->fsChanged, numSamples, reset);
    //for (int i = 0; i < numSamples; i++) fprintf(file, "%hi,%hi\n", xi[i], xq[i]);
    for (unsigned int i = 0; i < numSamples; i++){
        printf("%i: %i |", i, xi[i]);
    }
    printf("\n\n\n");
    for (unsigned int i = 0; i < numSamples; i++){
        printf("%i: %i |", i, xq[i]);
    }
    printf("\n");
    exit(1);
}


int main(){
    sdrplay_api_ErrT err;       // generic error variable
    
    file = fopen("dataDump.txt", "w");

    // Open API
    if ((err = sdrplay_api_Open()) != sdrplay_api_Success)
    {
        printf("sdrplay_api_Open failed %s\n", sdrplay_api_GetErrorString(err));
    }
    else
    {
        printf("Device opened...\n");
        float apiVersion;
        sdrplay_api_ApiVersion(&apiVersion);
        printf("Running API version %.2f\n", apiVersion);
        
        if (apiVersion != SDRPLAY_API_VERSION)
        {
            printf("API version don't match (local=%.2f dll=%.2f)\n", SDRPLAY_API_VERSION, apiVersion);
        }

        //
        // Enable debug logging output
        if ((err = sdrplay_api_DebugEnable(NULL, 1)) != sdrplay_api_Success)
        {
            printf("sdrplay_api_DebugEnable failed %s\n", sdrplay_api_GetErrorString(err));
        } else {
            printf("Debugging enabled!\n");
        }
        

        // Lock API while device selection is performed
        sdrplay_api_LockDeviceApi();


        // Get Devices
        unsigned int maxDevs = 6;  // max number of devices on the device list
        unsigned int ndevs = 6;
        sdrplay_api_DeviceT devs[6];
        sdrplay_api_GetDevices(devs, &ndevs, maxDevs);
        printf("We have %i device(s)\n", ndevs);

        // Select the devices
        sdrplay_api_DeviceT *sdr = &devs[ndevs - 1];
        sdrplay_api_SelectDevice(sdr);
        printf("We have selected the device...\n");

        // Edit the device's parameters
        sdrplay_api_DeviceParamsT *params = NULL;//(1, sizeof(sdrplay_api_DeviceParamsT));
        sdrplay_api_GetDeviceParams(sdr->dev, &params);
 
        //params->devParams->fsFreq.fsHz = 400.0;
        
        params->devParams->fsFreq.fsHz = 2000000.0;// = 1000000.0;
        //params->devParams->samplesPerPkt = 512;// = 1000000.0;
        //params->devParams->fsFreq.reCal = 1;// = 1000000.0;   
        params->rxChannelA->tunerParams.bwType = sdrplay_api_BW_0_200;
        params->rxChannelA->tunerParams.rfFreq.rfHz = 102200000;//13845010;//104900000; // Frequency - default: 2000000.0
        //params->devParams->mode = sdrplay_api_BULK;
        

        // Initialise the device
        sdrplay_api_CallbackFnsT cbFns;
        cbFns.StreamACbFn = DataStreamCallback;
        cbFns.StreamBCbFn = NULL;   // RSP1 only has a single data stream
        cbFns.EventCbFn = EventCallback;

        sdrplay_api_Init(sdr->dev, &cbFns, NULL);
        printf("Intialising device...\n");

        
        /*
        // Update the device for new parameters
        if ((err = sdrplay_api_Update(sdr->dev, sdr->tuner, sdrplay_api_Update_Tuner_Frf, sdrplay_api_Update_Ext1_None)) != sdrplay_api_Success){
            printf("Unable to update the parameters\n");
        } else {
            printf("Successful parameter update!\n");
        }
        */
        
        // pReSs EnTeR tO Exit
        /*
        while('\n' != getchar()){
            sleep(5);
        }
        */
        sleep(5);

        // Unlock API whilst the device has been used
        sdrplay_api_UnlockDeviceApi();
    }


    // Close API
    if ((err =  sdrplay_api_Close()) == sdrplay_api_Success) {
        printf("Closing device...\n");
    } else {
        printf("sdrplay_api_Close failed %s - unable to close the device\n", sdrplay_api_GetErrorString(err));
    }

    fclose(file);

    return 1;
}