let input_1 = {
    "room_name": "living_room",
    "user_name": "lunatic"
}
let expected_output_1 = {
    "query": {
        "selector": {
            "$and": [
                {
                    "room_name": {
                        "$eq": "living_room"
                    }
                },
                {
                    "$or": [
                        {
                            "room_public": {
                                "$eq": true
                            }
                        },
                        {
                            "id_users_admin": {
                                "$all": ["lunatic"]
                            }
                        },
                        {
                            "room_visible_to": {
                                "$all": ["lunatic"]
                            }
                        }
                    ]

                }
            ]

        }
    }
}
let input_2 = {"room_name": "living_room"}
let input_3 = {"user_name": "living_room"}
let expected_output_2 = {"error": "Missing room_name or user_name"}

const room_count_selector = require("../../get-room-count/room_count_selector.js")

describe("room_count_selector function", () => {
    test("document found input", () => {
        expect(room_count_selector(input_1)).toMatchObject(expected_output_1)
    });
    test("no user_name input", () => {
        expect(room_count_selector(input_2)).toMatchObject(expected_output_2)
    });
    test("no room_name input", () => {
        expect(room_count_selector(input_3)).toMatchObject(expected_output_2)
    });
})
