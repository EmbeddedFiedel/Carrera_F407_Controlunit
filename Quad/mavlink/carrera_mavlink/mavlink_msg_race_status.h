// MESSAGE RACE_STATUS PACKING

#define MAVLINK_MSG_ID_RACE_STATUS 193

typedef struct __mavlink_race_status_t
{
 uint64_t time_usec; ///< Timestamp (microseconds, synced to UNIX time or since system boot)
 uint8_t raceStarted; ///< Rennzaehler
 uint8_t raceCountdown; ///< Rennzaehler
} mavlink_race_status_t;

#define MAVLINK_MSG_ID_RACE_STATUS_LEN 10
#define MAVLINK_MSG_ID_193_LEN 10



#define MAVLINK_MESSAGE_INFO_RACE_STATUS { \
	"RACE_STATUS", \
	3, \
	{  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_race_status_t, time_usec) }, \
         { "raceStarted", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_race_status_t, raceStarted) }, \
         { "raceCountdown", NULL, MAVLINK_TYPE_UINT8_T, 0, 9, offsetof(mavlink_race_status_t, raceCountdown) }, \
         } \
}


/**
 * @brief Pack a race_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec Timestamp (microseconds, synced to UNIX time or since system boot)
 * @param raceStarted Rennzaehler
 * @param raceCountdown Rennzaehler
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_race_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint64_t time_usec, uint8_t raceStarted, uint8_t raceCountdown)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[10];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_uint8_t(buf, 8, raceStarted);
	_mav_put_uint8_t(buf, 9, raceCountdown);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 10);
#else
	mavlink_race_status_t packet;
	packet.time_usec = time_usec;
	packet.raceStarted = raceStarted;
	packet.raceCountdown = raceCountdown;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 10);
#endif

	msg->msgid = MAVLINK_MSG_ID_RACE_STATUS;
	return mavlink_finalize_message(msg, system_id, component_id, 10, 22);
}

/**
 * @brief Pack a race_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec Timestamp (microseconds, synced to UNIX time or since system boot)
 * @param raceStarted Rennzaehler
 * @param raceCountdown Rennzaehler
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_race_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint64_t time_usec,uint8_t raceStarted,uint8_t raceCountdown)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[10];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_uint8_t(buf, 8, raceStarted);
	_mav_put_uint8_t(buf, 9, raceCountdown);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 10);
#else
	mavlink_race_status_t packet;
	packet.time_usec = time_usec;
	packet.raceStarted = raceStarted;
	packet.raceCountdown = raceCountdown;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 10);
#endif

	msg->msgid = MAVLINK_MSG_ID_RACE_STATUS;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 10, 22);
}

/**
 * @brief Encode a race_status struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param race_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_race_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_race_status_t* race_status)
{
	return mavlink_msg_race_status_pack(system_id, component_id, msg, race_status->time_usec, race_status->raceStarted, race_status->raceCountdown);
}

/**
 * @brief Send a race_status message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec Timestamp (microseconds, synced to UNIX time or since system boot)
 * @param raceStarted Rennzaehler
 * @param raceCountdown Rennzaehler
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_race_status_send(mavlink_channel_t chan, uint64_t time_usec, uint8_t raceStarted, uint8_t raceCountdown)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[10];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_uint8_t(buf, 8, raceStarted);
	_mav_put_uint8_t(buf, 9, raceCountdown);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RACE_STATUS, buf, 10, 22);
#else
	mavlink_race_status_t packet;
	packet.time_usec = time_usec;
	packet.raceStarted = raceStarted;
	packet.raceCountdown = raceCountdown;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RACE_STATUS, (const char *)&packet, 10, 22);
#endif
}

#endif

// MESSAGE RACE_STATUS UNPACKING


/**
 * @brief Get field time_usec from race_status message
 *
 * @return Timestamp (microseconds, synced to UNIX time or since system boot)
 */
static inline uint64_t mavlink_msg_race_status_get_time_usec(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field raceStarted from race_status message
 *
 * @return Rennzaehler
 */
static inline uint8_t mavlink_msg_race_status_get_raceStarted(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Get field raceCountdown from race_status message
 *
 * @return Rennzaehler
 */
static inline uint8_t mavlink_msg_race_status_get_raceCountdown(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  9);
}

/**
 * @brief Decode a race_status message into a struct
 *
 * @param msg The message to decode
 * @param race_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_race_status_decode(const mavlink_message_t* msg, mavlink_race_status_t* race_status)
{
#if MAVLINK_NEED_BYTE_SWAP
	race_status->time_usec = mavlink_msg_race_status_get_time_usec(msg);
	race_status->raceStarted = mavlink_msg_race_status_get_raceStarted(msg);
	race_status->raceCountdown = mavlink_msg_race_status_get_raceCountdown(msg);
#else
	memcpy(race_status, _MAV_PAYLOAD(msg), 10);
#endif
}
