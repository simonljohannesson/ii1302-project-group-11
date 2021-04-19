
let input1 = {
    "bookmark": "g2wAAAACaAJkAA5zdGFydGtleV9kb2NpZG0AAAAgMjliOTQwOGJmNWJmMDFlZWUzYmRiYzNmMGMwMTcyZWVoAmQACHN0YXJ0a2V5bAAAAAFtAAAAC2xpdmluZ19yb29tamo",
    "docs": [
      {
        "_id": "29b9408bf5bf01eee3bdbc3f0c0172ee",
        "_rev": "7-5d11a6fad0e7c3513492f72a360bde7d",
        "comment": "room",
        "created_at": "2021-04-15T15:22:46.516Z",
        "id_iot_devices": [],
        "id_room_statistics": "not available",
        "id_users_admin": [
          "frantic_maniac"
        ],
        "last_updated": "2021-04-15T15:22:46.516Z",
        "room_count": 0,
        "room_name": "living_room",
        "room_public": false,
        "room_visible_to": []
      }
    ]
}

let expected_output_1 = {
  "rooms": [
    {
      "room_name": "living_room", 
      "room_count": 0, 
      "last_updated": "2021-04-15T15:22:46.516Z"
    }
  ]
}

let input2 = {
    "bookmark": "nil",
    "docs": []
}

let expected_output_2 = {
    "error": "Could not find specified room."
}

const room_count_reply = require("../../get-room-count/room_count_reply.js")

describe("room_count_reply function", () => {
    test("document found input", () => {
        expect(room_count_reply(input1)).toMatchObject(expected_output_1)
    });  

    test("document not found input", () => {
        expect(room_count_reply(input2)).toMatchObject(expected_output_2)
    });  
})