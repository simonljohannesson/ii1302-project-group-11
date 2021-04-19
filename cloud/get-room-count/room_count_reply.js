/**
 * Formats the output from querying for a specific rooms information.
 * 
 * If the room exists it will return an object on the format:
 *    {
 *      "room_name": val,
 *      "room_count": val, 
 *      "last_updated": val
 *    }
 * otherwise it will return an object on the format:
 *    {
 *      "error": val
 *    }
 * 
 * 
 * Example input:
 * 
 * {
 *   "bookmark": "g2wAAAACaAJkAA5zdGFydGtleV9kb2NpZG0AAAAgMjliOTQwOGJmNWJmMDFlZWUzYmRiYzNmMGMwMTcyZWVoAmQACHN0YXJ0a2V5bAAAAAFtAAAAC2xpdmluZ19yb29tamo",
 *   "docs": [
 *     {
 *       "_id": "29b9408bf5bf01eee3bdbc3f0c0172ee",
 *       "_rev": "7-5d11a6fad0e7c3513492f72a360bde7d",
 *       "comment": "room",
 *       "created_at": "2021-04-15T15:22:46.516Z",
 *       "id_iot_devices": [],
 *       "id_room_statistics": "not available",
 *       "id_users_admin": [
 *         "frantic_maniac"
 *       ],
 *       "last_updated": "2021-04-15T15:22:46.516Z",
 *       "room_count": 0,
 *       "room_name": "living_room",
 *       "room_public": false,
 *       "room_visible_to": []
 *     }
 *   ]
 * }
 * 
 * or 
 * {
 *   "bookmark": "nil",
 *   "docs": []
 * }
 * 
 * @param {*} params 
 * @returns 
 */
function room_count_reply(params) {
  if (!params.docs.length){
      return Promise.reject({
          "error": "Could not find specified room."
      });
  }
  return {
          rooms: 
              params.docs.map((row) => {
              return {
                  "room_name": row.room_name, 
                  "room_count": row.room_count, 
                  "last_updated": row.last_updated
          }
      })
  }
}

module.exports = room_count_reply

/** Execute */
function main(params) {
  room_count_reply(params)
}