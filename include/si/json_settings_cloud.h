/**
 * @file   	json_settings.h
 * @brief  	Contains prototype for functions that load the JSON settings.
 */
/*! Include Guard */
#ifndef __JSON_SETTINGS_CLOUD__H__
#define __JSON_SETTINGS_CLOUD__H__

/* --- Project Includes --- */
#include "si/siaws.h"

/*! CPP guard */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get the AWS Settings from the JSON config file.
 * 
 * @param jsonSubName JSON object name that contains the AWS settings.
 * @return awsObj with settings loaded on SUCCESS and
 *                   NULL pointers in awsObj on failure
 */
extern awsObj getAwsSettings(char *jsonSubName);


#ifdef __cplusplus
}
#endif /* End of CPP guard */

#endif  /* __JSON_SETTINGS_CLOUD__H__ */ /* End of Include Guard */