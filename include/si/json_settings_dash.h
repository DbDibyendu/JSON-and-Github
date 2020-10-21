/**
 * @file   	json_settings.h
 * @brief  	Contains prototype for functions that load the JSON settings.
 */
/*! Include Guard */
#ifndef __JSON_SETTINGS_DASH__H__
#define __JSON_SETTINGS_DASH__H__

/* --- Project Includes --- */
#include "si/influxdb.h"

/*! CPP guard */
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Get the Influxdb Settings from the JSON config file.
 * 
 * @param jsonSubName JSON object name that contains the Influxdb settings.
 * @return influxdbObj with settings loaded on SUCCESS and
 *                   NULL pointers in influxdbObj on failure
 */
extern influxdbObj getInfluxdbSettings(char *jsonSubName);


#ifdef __cplusplus
}
#endif /* End of CPP guard */

#endif  /* __JSON_SETTINGS_DASH__H__ */ /* End of Include Guard */