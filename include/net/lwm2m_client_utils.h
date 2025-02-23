/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

/**@file lwm2m_client_utils.h
 *
 * @defgroup lwm2m_client_utils LwM2M client utilities
 * @{
 * @brief LwM2M Client utilities to build an application
 *
 * @details The client provides APIs for:
 *  - connecting to a remote server
 *  - setting up default resources
 *    * Firmware
 *    * Connection monitoring
 *    * Device
 *    * Location
 *    * Security
 */

#ifndef LWM2M_CLIENT_UTILS_H__
#define LWM2M_CLIENT_UTILS_H__

#include <zephyr/kernel.h>
#include <zephyr/net/lwm2m.h>
#include <modem/lte_lc.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(CONFIG_LWM2M_CLIENT_UTILS_SECURITY_OBJ_SUPPORT)
/**
 * @typedef modem_mode_cb_t
 * @brief Callback to request a modem state change, being it powering off, flight mode etc.
 *
 * @return 0 if mode was set successfully
 * @return positive value to indicate seconds before retry
 * @return negative error code in case of a failure
 */
typedef int (*modem_mode_cb_t)(enum lte_lc_func_mode new_mode, void *user_data);

/**
 * @struct modem_mode_change
 * @brief Callback used for querying permission from the app to proceed when modem's state changes
 *
 * @param cb        The callback function
 * @param user_data App specific data to be fed to the callback once it's called
 */
struct modem_mode_change {
	modem_mode_cb_t cb;
	void *user_data;
};

/**
 * @brief Initialize Security object support for nrf91
 *
 * This wrapper will install hooks that allows device to do a
 * proper bootstrap and store received server settings to permanent
 * storage using Zephyr settings API. Credential are stored to
 * modem and no keys would enter the flash.
 *
 * @note This API calls settings_subsys_init() so should
 *       only be called after the settings backend (Flash or FS)
 *       is ready.
 */
int lwm2m_init_security(struct lwm2m_ctx *ctx, char *endpoint, struct modem_mode_change *mmode);

/**
 * @brief Set security object to PSK mode.
 *
 * Any pointer can be given as a NULL, which means that data related to this field is set to
 * zero legth in the engine. Effectively, it causes that relative data is not written into
 * the modem. This can be used if the given data is already provisioned to the modem.
 *
 * @param sec_obj_inst Security object ID to modify.
 * @param psk Pointer to PSK key, either in HEX or binary format.
 * @param psk_len Length of data in PSK pointer.
 *                If PSK is HEX string, should include string terminator.
 * @param psk_is_hex True if PSK points to data in HEX format. False if the data is binary.
 * @param psk_id PSK key ID in string format.
 * @return Zero if success, negative error code otherwise.
 */
int lwm2m_security_set_psk(uint16_t sec_obj_inst, const void *psk, int psk_len, bool psk_is_hex,
			   const char *psk_id);

/**
 * @brief Set security object to certificate mode.
 *
 * Any pointer can be given as a NULL, which means that data related to this field is set to
 * zero legth in the engine. Effectively, it causes that relative data is not written into
 * the modem. This can be used if the given data is already provisioned to the modem.
 *
 * @param sec_obj_inst Security object ID to modify.
 * @param cert Pointer to certificate.
 * @param cert_len Certificate length.
 * @param private_key Pointer to private key.
 * @param key_len Private key length.
 * @param ca_chain Pointer to CA certificate or server certificate.
 * @param ca_len CA chain length.
 * @return Zero if success, negative error code otherwise.
 */
int lwm2m_security_set_certificate(uint16_t sec_obj_inst, const void *cert, int cert_len,
				   const void *private_key, int key_len, const void *ca_chain,
				   int ca_len);
/**
 * @brief Check if the client credentials are already stored.
 *
 * @return true If bootstrap is needed.
 * @return false If client credentials are already available.
 */
bool lwm2m_security_needs_bootstrap(void);

#endif

#if defined(CONFIG_LWM2M_CLIENT_UTILS_DEVICE_OBJ_SUPPORT)
/**
 * @brief Initialize Device object
 */
int lwm2m_init_device(void);
#endif

#if defined(CONFIG_LWM2M_CLIENT_UTILS_LOCATION_OBJ_SUPPORT)
/**
 * @brief Initialize Location object
 */
int lwm2m_init_location(void);
#endif

#if defined(CONFIG_LWM2M_CLIENT_UTILS_FIRMWARE_UPDATE_OBJ_SUPPORT)
/**
 * @brief Firmware update state change event callback.
 *
 * @param[in] update_state LWM2M Firmware Update object states
 *
 * @return Callback returns a negative error code (errno.h) indicating
 *         reason of failure or 0 for success.
 */
typedef int (*lwm2m_firmware_get_update_state_cb_t)(uint8_t update_state);

/**
 * @brief Set event callback for firmware update changes.
 *
 * LwM2M clients use this function to register a callback for receiving the
 * update state changes when performing a firmware update.
 *
 * @param[in] cb A callback function to receive firmware update state changes.
 */
void lwm2m_firmware_set_update_state_cb(lwm2m_firmware_get_update_state_cb_t cb);

/**
 * @brief Apply the firmware update.
 *
 * By default lwm2m firmware is applied when the update resource (5/0/2) is executed.
 * If application needs to control the update, it can set its own callback for the
 * update resource calling `lwm2m_firmware_set_update_cb`. After that, the application
 * can apply the firmware update when it is ready.
 *
 * @param[in] obj_inst_id Instance id of the firmware update object.
 */
int lwm2m_firmware_apply_update(uint16_t obj_inst_id);

/**
 * @brief Firmware read callback
 */
void *firmware_read_cb(uint16_t obj_inst_id, size_t *data_len);
/**
 * @brief Verify active firmware image
 */
int lwm2m_init_firmware(void);

/**
 * @brief Initialize Image Update object
 */
int lwm2m_init_image(void);

/**
 * @brief Verifies modem firmware update
 */
void lwm2m_verify_modem_fw_update(void);
#endif

#if defined(CONFIG_LWM2M_CLIENT_UTILS_CONN_MON_OBJ_SUPPORT)
/**
 * @brief Initialize Connectivity Monitoring object
 */
int lwm2m_init_connmon(void);

/**
 * @brief Update Connectivity Monitoring object
 */
int lwm2m_update_connmon(void);
#endif

#if defined(CONFIG_LWM2M_CLIENT_UTILS_SIGNAL_MEAS_INFO_OBJ_SUPPORT)
#define ECID_SIGNAL_MEASUREMENT_INFO_OBJECT_ID 10256
int lwm2m_signal_meas_info_inst_id_to_index(uint16_t obj_inst_id);
int lwm2m_signal_meas_info_index_to_inst_id(int index);
int lwm2m_update_signal_meas_objects(const struct lte_lc_cells_info *const cells);
int lwm2m_ncell_handler_register(void);
void lwm2m_ncell_schedule_measurement(void);
#endif

#if defined(CONFIG_LWM2M_CLIENT_UTILS_LOCATION_ASSIST_OBJ_SUPPORT)
#define LOCATION_ASSIST_OBJECT_ID 50001
void location_assist_agps_request_set(uint32_t request_mask);
void location_assist_cell_request_set(void);
void location_assist_cell_inform_set(void);
#endif

#if defined(CONFIG_LWM2M_CLIENT_UTILS_CELL_CONN_OBJ_SUPPORT)
#define LWM2M_OBJECT_CELLULAR_CONNECTIVITY_ID 10
int lwm2m_init_cellular_connectivity_object(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* LWM2M_CLIENT_UTILS_H__ */

/**@} */
