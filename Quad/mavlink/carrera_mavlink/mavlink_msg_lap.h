// MESSAGE LAP PACKING

#define MAVLINK_MSG_ID_LAP 150

typedef struct __mavlink_lap_t
{
 uint64_t time_usec; ///< Timestamp (microseconds, synced to UNIX time or since system boot)
 uint32_t time; ///< Rundenzeit [ms]
 uint8_t racenumber; ///< Rennzaehler
 uint8_t racetrack; ///< Bahn 1 oder 2
 uint8_t lapNumber; ///< Runde
} mavlink_lap_t;

#define MAVLINK_MSG_ID_LAP_LEN 15
#define MAVLINK_MSG_ID_150_LEN 15



#define MAVLINK_MESSAGE_INFO_LAP { \
	"LAP", \
	5, \
	{  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_lap_t, time_usec) }, \
         { "time", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_lap_t, time) }, \
         { "racenumber", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_lap_t, racenumber) }, \
         { "racetrack", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_lap_t, racetrack) }, \
         { "lapNumber", NULL, MAVLINK_TYPE_UINT8_T, 0, 14, offsetof(mavlink_lap_t, lapNumber) }, \
         } \
}


/**
 * @brief Pack a lap message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec Timestamp (microseconds, synced to UNIX time or since system boot)
 * @param racenumber Rennzaehler
 * @param racetrack Bahn 1 oder 2
 * @param lapNumber Runde
 * @param time Rundenzeit [ms]
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_lap_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint64_t time_usec, uint8_t racenumber, uint8_t racetrack, uint8_t lapNumber, uint32_t time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[15];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_uint32_t(buf, 8, time);
	_mav_put_uint8_t(buf, 12, racenumber);
	_mav_put_uint8_t(buf, 13, racetrack);
	_mav_put_uint8_t(buf, 14, lapNumber);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 15);
#else
	mavlink_lap_t packet;
	packet.time_usec = time_usec;
	packet.time = time;
	packet.racenumber = racenumber;
	packet.racetrack = racetrack;
	packet.lapNumber = lapNumber;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 15);
#endif

	msg->msgid = MAVLINK_MSG_ID_LAP;
	return mavlink_finalize_message(msg, system_id, component_id, 15, 156);
}

/**
 * @brief Pack a lap message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec Timestamp (microseconds, synced to UNIX time or since system boot)
 * @param racenumber Rennzaehler
 * @param racetrack Bahn 1 oder 2
 * @param lapNumber Runde
 * @param time Rundenzeit [ms]
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_lap_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint64_t time_usec,uint8_t racenumber,uint8_t racetrack,uint8_t lapNumber,uint32_t time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[15];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_uint32_t(buf, 8, time);
	_mav_put_uint8_t(buf, 12, racenumber);
	_mav_put_uint8_t(buf, 13, racetrack);
	_mav_put_uint8_t(buf, 14, lapNumber);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 15);
#else
	mavlink_lap_t packet;
	packet.time_usec = time_usec;
	packet.time = time;
	packet.racenumber = racenumber;
	packet.racetrack = racetrack;
	packet.lapNumber = lapNumber;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 15);
#endif

	msg->msgid = MAVLINK_MSG_ID_LAP;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 15, 156);
}

/**
 * @brief Encode a lap struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param lap C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_lap_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_lap_t* lap)
{
	return mavlink_msg_lap_pack(system_id, component_id, msg, lap->time_usec, lap->racenumber, lap->racetrack, lap->lapNumber, lap->time);
}

/**
 * @brief Send a lap message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec Timestamp (microseconds, synced to UNIX time or since system boot)
 * @param racenumber Rennzaehler
 * @param racetrack Bahn 1 oder 2
 * @param lapNumber Runde
 * @param time Rundenzeit [ms]
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_lap_send(mavlink_channel_t chan, uint64_t time_usec, uint8_t racenumber, uint8_t racetrack, uint8_t lapNumber, uint32_t time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[15];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_uint32_t(buf, 8, time);
	_mav_put_uint8_t(buf, 12, racenumber);
	_mav_put_uint8_t(buf, 13, racetrack);
	_mav_put_uint8_t(buf, 14, lapNumber);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LAP, buf, 15, 156);
#else
	mavlink_lap_t packet;
	packet.time_usec = time_usec;
	packet.time = time;
	packet.racenumber = racenumber;
	packet.racetrack = racetrack;
	packet.lapNumber = lapNumber;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LAP, (const char *)&packet, 15, 156);
#endif
}

#endif

// MESSAGE LAP UNPACKING


/**
 * @brief Get field time_usec from lap message
 *
 * @return Timestamp (microseconds, synced to UNIX time or since system boot)
 */
static inline uint64_t mavlink_msg_lap_get_time_usec(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field racenumber from lap message
 *
 * @return Rennzaehler
 */
static inline uint8_t mavlink_msg_lap_get_racenumber(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Get field racetrack from lap message
 *
 * @return Bahn 1 oder 2
 */
static inline uint8_t mavlink_msg_lap_get_racetrack(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  13);
}

/**
 * @brief Get field lapNumber from lap message
 *
 * @return Runde
 */
static inline uint8_t mavlink_msg_lap_get_lapNumber(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  14);
}

/**
 * @brief Get field time from lap message
 *
 * @return Rundenzeit [ms]
 */
static inline uint32_t mavlink_msg_lap_get_time(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Decode a lap message into a struct
 *
 * @param msg The message to decode
 * @param lap C-struct to decode the message contents into
 */
static inline void mavlink_msg_lap_decode(const mavlink_message_t* msg, mavlink_lap_t* lap)
{
#if MAVLINK_NEED_BYTE_SWAP
	lap->time_usec = mavlink_msg_lap_get_time_usec(msg);
	lap->time = mavlink_msg_lap_get_time(msg);
	lap->racenumber = mavlink_msg_lap_get_racenumber(msg);
	lap->racetrack = mavlink_msg_lap_get_racetrack(msg);
	lap->lapNumber = mavlink_msg_lap_get_lapNumber(msg);
#else
	memcpy(lap, _MAV_PAYLOAD(msg), 15);
#endif
}
