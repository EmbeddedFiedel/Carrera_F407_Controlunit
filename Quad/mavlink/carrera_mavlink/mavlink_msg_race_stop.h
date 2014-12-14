// MESSAGE RACE_STOP PACKING

#define MAVLINK_MSG_ID_RACE_STOP 192

typedef struct __mavlink_race_stop_t
{
 uint64_t time_usec; ///< Timestamp (microseconds, synced to UNIX time or since system boot)
 uint8_t racenumber; ///< Rennzaehler
} mavlink_race_stop_t;

#define MAVLINK_MSG_ID_RACE_STOP_LEN 9
#define MAVLINK_MSG_ID_192_LEN 9



#define MAVLINK_MESSAGE_INFO_RACE_STOP { \
	"RACE_STOP", \
	2, \
	{  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_race_stop_t, time_usec) }, \
         { "racenumber", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_race_stop_t, racenumber) }, \
         } \
}


/**
 * @brief Pack a race_stop message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec Timestamp (microseconds, synced to UNIX time or since system boot)
 * @param racenumber Rennzaehler
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_race_stop_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint64_t time_usec, uint8_t racenumber)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[9];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_uint8_t(buf, 8, racenumber);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 9);
#else
	mavlink_race_stop_t packet;
	packet.time_usec = time_usec;
	packet.racenumber = racenumber;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 9);
#endif

	msg->msgid = MAVLINK_MSG_ID_RACE_STOP;
	return mavlink_finalize_message(msg, system_id, component_id, 9, 5);
}

/**
 * @brief Pack a race_stop message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec Timestamp (microseconds, synced to UNIX time or since system boot)
 * @param racenumber Rennzaehler
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_race_stop_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint64_t time_usec,uint8_t racenumber)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[9];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_uint8_t(buf, 8, racenumber);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 9);
#else
	mavlink_race_stop_t packet;
	packet.time_usec = time_usec;
	packet.racenumber = racenumber;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 9);
#endif

	msg->msgid = MAVLINK_MSG_ID_RACE_STOP;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 9, 5);
}

/**
 * @brief Encode a race_stop struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param race_stop C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_race_stop_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_race_stop_t* race_stop)
{
	return mavlink_msg_race_stop_pack(system_id, component_id, msg, race_stop->time_usec, race_stop->racenumber);
}

/**
 * @brief Send a race_stop message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec Timestamp (microseconds, synced to UNIX time or since system boot)
 * @param racenumber Rennzaehler
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_race_stop_send(mavlink_channel_t chan, uint64_t time_usec, uint8_t racenumber)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[9];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_uint8_t(buf, 8, racenumber);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RACE_STOP, buf, 9, 5);
#else
	mavlink_race_stop_t packet;
	packet.time_usec = time_usec;
	packet.racenumber = racenumber;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RACE_STOP, (const char *)&packet, 9, 5);
#endif
}

#endif

// MESSAGE RACE_STOP UNPACKING


/**
 * @brief Get field time_usec from race_stop message
 *
 * @return Timestamp (microseconds, synced to UNIX time or since system boot)
 */
static inline uint64_t mavlink_msg_race_stop_get_time_usec(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field racenumber from race_stop message
 *
 * @return Rennzaehler
 */
static inline uint8_t mavlink_msg_race_stop_get_racenumber(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Decode a race_stop message into a struct
 *
 * @param msg The message to decode
 * @param race_stop C-struct to decode the message contents into
 */
static inline void mavlink_msg_race_stop_decode(const mavlink_message_t* msg, mavlink_race_stop_t* race_stop)
{
#if MAVLINK_NEED_BYTE_SWAP
	race_stop->time_usec = mavlink_msg_race_stop_get_time_usec(msg);
	race_stop->racenumber = mavlink_msg_race_stop_get_racenumber(msg);
#else
	memcpy(race_stop, _MAV_PAYLOAD(msg), 9);
#endif
}
