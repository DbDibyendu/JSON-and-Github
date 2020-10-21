/**
 * @file   	json_settings.h
 * @brief  	Contains prototype for functions that load the JSON settings.
 */
/*! Include Guard */
#ifndef __JSON_SETTINGS_CONN__H__
#define __JSON_SETTINGS_CONN__H__

/* --- Project Includes --- */
#include "si/mqtt.h"

/*! CPP guard */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get the Mqtt Settings from the JSON config file.
 * 
 * @param jsonSubName JSON object name that contains the MQTT settings.
 * @return mqttObj with settings loaded on SUCCESS and
 *                   NULL pointers in twilioObj on failure
 */
extern mqttObj getMqttSettings(char *jsonSubName);


#ifdef __cplusplus
}
#endif /* End of CPP guard */

#endif  /* __JSON_SETTINGS_CONN__H__ */ /* End of Include Guard */