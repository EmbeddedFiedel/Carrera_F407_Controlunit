// MESSAGE RACE_START PACKING

#define MAVLINK_MSG_ID_RACE_START 191

typedef struct __mavlink_race_start_t
{
 uint64_t time_usec; ///< Timestamp (microseconds, synced to UNIX time or since system boot)
 uint8_t racenumber; ///< Rennzaehler
} mavlink_race_start_t;

#define MAVLINK_MSG_ID_RACE_START_LEN 9
#define MAVLINK_MSG_ID_191_LEN 9



#define MAVLINK_MESSAGE_INFO_RACE_START { \
	"RACE_START", \
	2, \
	{  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_race_start_t, time_usec) }, \
         { "racenumber", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_race_start_t, racenumber) }, \
         } \
}


/**
 * @brief Pack a race_start message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec Timestamp (microseconds, synced to UNIX time or since system boot)
 * @param racenumber Rennzaehler
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_race_start_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint64_t time_usec, uint8_t racenumber)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[9];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_uint8_t(buf, 8, racenumber);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 9);
#else
	mavlink_race_start_t packet;
	packet.time_usec = time_usec;
	packet.racenumber = racenumber;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 9);
#endif

	msg->msgid = MAVLINK_MSG_ID_RACE_START;
	return mavlink_finalize_message(msg, system_id, component_id, 9, 230);
}

/**
 * @brief Pack a race_start message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec Timestamp (microseconds, synced to UNIX time or since system boot)
 * @param racenumber Rennzaehler
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_race_start_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint64_t time_usec,uint8_t racenumber)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[9];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_uint8_t(buf, 8, racenumber);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 9);
#else
	mavlink_race_start_t packet;
	packet.time_usec = time_usec;
	packet.racenumber = racenumber;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 9);
#endif

	msg->msgid = MAVLINK_MSG_ID_RACE_START;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 9, 230);
}

/**
 * @brief Encode a race_start struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param race_start C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_race_start_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_race_start_t* race_start)
{
	return mavlink_msg_race_start_pack(system_id, component_id, msg, race_start->time_usec, race_start->racenumber);
}

/**
 * @brief Send a race_start message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec Timestamp (microseconds, synced to UNIX time or since system boot)
 * @param racenumber Rennzaehler
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_race_start_send(mavlink_channel_t chan, uint64_t time_usec, uint8_t racenumber)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[9];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_uint8_t(buf, 8, racenumber);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RACE_START, buf, 9, 230);
#else
	mavlink_race_start_t packet;
	packet.time_usec = time_usec;
	packet.racenumber = racenumber;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RACE_START, (const char *)&packet, 9, 230);
#endif
}

#endif

// MESSAGE RACE_START UNPACKING


/**
 * @brief Get field time_usec from race_start message
 *
 * @return Timestamp (microseconds, synced to UNIX time or since system boot)
 */
static inline uint64_t mavlink_msg_race_start_get_time_usec(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field racenumber from race_start message
 *
 * @return Rennzaehler
 */
static inline uint8_t mavlink_msg_race_start_get_racenumber(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Decode a race_start message into a struct
 *
 * @param msg The message to decode
 * @param race_start C-struct to decode the message contents into
 */
static inline void mavlink_msg_race_start_decode(const mavlink_message_t* msg, mavlink_race_start_t* race_start)
{
#if MAVLINK_NEED_BYTE_SWAP
	race_start->time_usec = mavlink_msg_race_start_get_time_usec(msg);
	race_start->racenumber = mavlink_msg_race_start_get_racenumber(msg);
#else
	memcpy(race_start, _MAV_PAYLOAD(msg), 9);
#endif
}
