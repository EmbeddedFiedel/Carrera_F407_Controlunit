// MESSAGE RACE_SETUP PACKING

#define MAVLINK_MSG_ID_RACE_SETUP 190

typedef struct __mavlink_race_setup_t
{
 uint64_t time_usec; ///< Timestamp (microseconds, synced to UNIX time or since system boot)
 uint8_t lapsCount; ///< Anzahl der Runden
} mavlink_race_setup_t;

#define MAVLINK_MSG_ID_RACE_SETUP_LEN 9
#define MAVLINK_MSG_ID_190_LEN 9



#define MAVLINK_MESSAGE_INFO_RACE_SETUP { \
	"RACE_SETUP", \
	2, \
	{  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_race_setup_t, time_usec) }, \
         { "lapsCount", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_race_setup_t, lapsCount) }, \
         } \
}


/**
 * @brief Pack a race_setup message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec Timestamp (microseconds, synced to UNIX time or since system boot)
 * @param lapsCount Anzahl der Runden
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_race_setup_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint64_t time_usec, uint8_t lapsCount)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[9];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_uint8_t(buf, 8, lapsCount);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 9);
#else
	mavlink_race_setup_t packet;
	packet.time_usec = time_usec;
	packet.lapsCount = lapsCount;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 9);
#endif

	msg->msgid = MAVLINK_MSG_ID_RACE_SETUP;
	return mavlink_finalize_message(msg, system_id, component_id, 9, 199);
}

/**
 * @brief Pack a race_setup message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec Timestamp (microseconds, synced to UNIX time or since system boot)
 * @param lapsCount Anzahl der Runden
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_race_setup_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint64_t time_usec,uint8_t lapsCount)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[9];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_uint8_t(buf, 8, lapsCount);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 9);
#else
	mavlink_race_setup_t packet;
	packet.time_usec = time_usec;
	packet.lapsCount = lapsCount;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 9);
#endif

	msg->msgid = MAVLINK_MSG_ID_RACE_SETUP;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 9, 199);
}

/**
 * @brief Encode a race_setup struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param race_setup C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_race_setup_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_race_setup_t* race_setup)
{
	return mavlink_msg_race_setup_pack(system_id, component_id, msg, race_setup->time_usec, race_setup->lapsCount);
}

/**
 * @brief Send a race_setup message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec Timestamp (microseconds, synced to UNIX time or since system boot)
 * @param lapsCount Anzahl der Runden
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_race_setup_send(mavlink_channel_t chan, uint64_t time_usec, uint8_t lapsCount)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[9];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_uint8_t(buf, 8, lapsCount);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RACE_SETUP, buf, 9, 199);
#else
	mavlink_race_setup_t packet;
	packet.time_usec = time_usec;
	packet.lapsCount = lapsCount;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RACE_SETUP, (const char *)&packet, 9, 199);
#endif
}

#endif

// MESSAGE RACE_SETUP UNPACKING


/**
 * @brief Get field time_usec from race_setup message
 *
 * @return Timestamp (microseconds, synced to UNIX time or since system boot)
 */
static inline uint64_t mavlink_msg_race_setup_get_time_usec(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field lapsCount from race_setup message
 *
 * @return Anzahl der Runden
 */
static inline uint8_t mavlink_msg_race_setup_get_lapsCount(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Decode a race_setup message into a struct
 *
 * @param msg The message to decode
 * @param race_setup C-struct to decode the message contents into
 */
static inline void mavlink_msg_race_setup_decode(const mavlink_message_t* msg, mavlink_race_setup_t* race_setup)
{
#if MAVLINK_NEED_BYTE_SWAP
	race_setup->time_usec = mavlink_msg_race_setup_get_time_usec(msg);
	race_setup->lapsCount = mavlink_msg_race_setup_get_lapsCount(msg);
#else
	memcpy(race_setup, _MAV_PAYLOAD(msg), 9);
#endif
}
