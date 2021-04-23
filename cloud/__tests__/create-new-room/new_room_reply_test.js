let input_1 = {
    "id": "29b9408bf5bf01eee3bdbc3f0c0172ee",
    "ok": true,
    "rev": "1-eb298ab18914d1b1513f4220313f317e"
}

let expected_output_1 = {
    "id":"29b9408bf5bf01eee3bdbc3f0c0172ee",
    "ok": true
}

let input_2 = {
    "id": "",
    "ok": false,
    "rev": "1-eb298ab18914d1b1513f4220313f317e"
}

let expected_output_2 = {
    "error": "Could not process request."
}

const new_room_reply = require("../../create-new-room/new_room_reply.js")

describe("new_room_reply function", () => {
    test("room created successfully", () => {
        expect(new_room_reply(input_1)).toMatchObject(expected_output_1)
    });

    test("room creation failed", () => {
        expect.assertions(1)
        return new_room_reply(input_2).catch(e=>expect(e).toMatchObject(expected_output_2))
    });
})