/**
  ******************************************************************************
  * File Name          :  stmicroelectronics_x-cube-mems1_6_2_0.c
  * Description        : This file provides code for the configuration
  *                      of the STMicroelectronics.X-CUBE-MEMS1.6.2.0 instances.
  ******************************************************************************
  *
  * COPYRIGHT 2019 STMicroelectronics
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  ******************************************************************************
  */

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "main.h"
#include "app_x-cube-mems1.h"
#include "iks01a3_env_sensors.h"
#include "iks01a3_motion_sensors.h"



int32_t MX_MEMS_Init(void)
{
    int ret;

    /*env sensor init*/
#if (USE_IKS01A3_ENV_SENSOR_HTS221_0 == 1)
    ret = IKS01A3_ENV_SENSOR_Init(IKS01A3_HTS221_0, ENV_TEMPERATURE);
    if (BSP_ERROR_NONE == ret) {
        ret = IKS01A3_ENV_SENSOR_Enable(IKS01A3_HTS221_0, ENV_TEMPERATURE);
        if (BSP_ERROR_NONE != ret) {
            goto exit;
        }
    } else {
        goto exit;
    }

    ret = IKS01A3_ENV_SENSOR_Init(IKS01A3_HTS221_0, ENV_HUMIDITY);
    if (BSP_ERROR_NONE == ret) {
        ret = IKS01A3_ENV_SENSOR_Enable(IKS01A3_HTS221_0, ENV_HUMIDITY);
        if (BSP_ERROR_NONE != ret) {
            goto exit;
        }
    } else {
        goto exit;
    }
#endif

#if (USE_IKS01A3_ENV_SENSOR_LPS22HH_0 == 1)
    ret = IKS01A3_ENV_SENSOR_Init(IKS01A3_LPS22HH_0, ENV_PRESSURE);
    if (BSP_ERROR_NONE == ret) {
        ret = IKS01A3_ENV_SENSOR_Enable(IKS01A3_LPS22HH_0, ENV_PRESSURE);
        if (BSP_ERROR_NONE != ret) {
            goto exit;
        }
    } else {
        goto exit;
    }
#endif

#if (USE_IKS01A3_ENV_SENSOR_STTS751_0 == 1)
    ret = IKS01A3_ENV_SENSOR_Init(IKS01A3_STTS751_0, ENV_TEMPERATURE);
    if (BSP_ERROR_NONE == ret) {
        ret = IKS01A3_ENV_SENSOR_Enable(IKS01A3_STTS751_0, ENV_TEMPERATURE);
        if (BSP_ERROR_NONE != ret) {
            goto exit;
        }
    } else {
        goto exit;
    }
#endif

    /*motion sensor init*/
#if (USE_IKS01A3_MOTION_SENSOR_LSM6DSO_0 == 1)
    ret = IKS01A3_MOTION_SENSOR_Init(IKS01A3_LSM6DSO_0, MOTION_ACCELERO);
    if (BSP_ERROR_NONE == ret) {
        ret = IKS01A3_MOTION_SENSOR_Enable(IKS01A3_LSM6DSO_0, MOTION_ACCELERO);
        if (BSP_ERROR_NONE != ret) {
            goto exit;
        }
    } else {
        goto exit;
    }

#endif

#if (USE_IKS01A3_MOTION_SENSOR_LIS2DW12_0 == 1)
    ret = IKS01A3_MOTION_SENSOR_Init(IKS01A3_LIS2DW12_0, MOTION_ACCELERO);
    if (BSP_ERROR_NONE == ret) {
        ret = IKS01A3_MOTION_SENSOR_Enable(IKS01A3_LIS2DW12_0, MOTION_ACCELERO);
        if (BSP_ERROR_NONE != ret) {
            goto exit;
        }
    } else {
        goto exit;
    }
#endif

#if (USE_IKS01A3_MOTION_SENSOR_LIS2MDL_0 == 1)
    ret = IKS01A3_MOTION_SENSOR_Init(IKS01A3_LIS2MDL_0, MOTION_MAGNETO);
    if (BSP_ERROR_NONE == ret) {
        ret = IKS01A3_MOTION_SENSOR_Enable(IKS01A3_LIS2MDL_0, MOTION_MAGNETO);
        if (BSP_ERROR_NONE != ret) {
            goto exit;
        }
    } else {
        goto exit;
    }
#endif


exit:

    return ret;
}
/*
 * LM background task
 */
void MX_MEMS_Process(void)
{
    int ret;
    float temp;
    float hum;
    float press;

    /*env sensor*/
#if (USE_IKS01A3_ENV_SENSOR_HTS221_0 == 1)
    ret = IKS01A3_ENV_SENSOR_GetValue(IKS01A3_HTS221_0, ENV_TEMPERATURE, &temp);
    ret |= IKS01A3_ENV_SENSOR_GetValue(IKS01A3_HTS221_0, ENV_HUMIDITY, &hum);
    if (BSP_ERROR_NONE == ret) {
        printf("\n\rHTS221_Temp:%f HTS221_Hum:%f", temp, hum);
    }
#endif

#if (USE_IKS01A3_ENV_SENSOR_LPS22HH_0 == 1)
    ret = IKS01A3_ENV_SENSOR_GetValue(IKS01A3_LPS22HH_0, ENV_PRESSURE, &press);
    if (BSP_ERROR_NONE == ret) {
        printf("\n\rLPS22_press:%f", press);
    }
#endif

#if (USE_IKS01A3_ENV_SENSOR_STTS751_0 == 1)
    ret = IKS01A3_ENV_SENSOR_GetValue(IKS01A3_STTS751_0, ENV_TEMPERATURE, &temp);
    if (BSP_ERROR_NONE == ret) {
        printf("\n\rSTTS751_Temp:%f ", temp);
    }
#endif

    /*motion sensor*/
#if (USE_IKS01A3_MOTION_SENSOR_LSM6DSO_0 == 1)
    IKS01A3_MOTION_SENSOR_Axes_t asex;
    ret = IKS01A3_MOTION_SENSOR_GetAxes(IKS01A3_LSM6DSO_0, MOTION_ACCELERO, &asex);
    if (BSP_ERROR_NONE == ret) {
        printf("\n\rLSM6_asex_x:%d y:%d z:%d", asex.x, asex.y, asex.z);
    }
#endif


}

#ifdef __cplusplus
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
