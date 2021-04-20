let input_1 = {
    "room_name": "userchosenname",
    "admin": "useruniquedatabseid"
}
let input_2 = {
    "user_name": "userchosenname",
    "no": "useruniquedatabseid"
}
let input_3 = {
    "no": "userchosenname",
    "admin": "useruniquedatabseid"
}

let expected_output_1 = {
    doc: {
            created_at: "",
            room_name: "userchosenname",
            id_users_admin: ["useruniquedatabseid"],
            room_public: false,
            room_visible_to:[],
            id_iot_devices: [],
            room_count: 0,
            id_room_statistics: "not available",
            last_updated: ""
    }
}
let expected_output_2 = { "error": 'no room_name or admin'};

let new_room_save_document = require("../../create-new-room/new_room_save_document.js")

describe("new_room_reply function", () => {
    test("document found input", () => {
        res = new_room_save_document(input_1)
        expect(res.doc.created_at).toBeTruthy();
        expect(res.doc.room_name).toMatch(expected_output_1.doc.room_name);
        expect(res.doc.id_users_admin).toMatchObject(expected_output_1.doc.id_users_admin);
        expect(res.doc.room_public).toBe(expected_output_1.doc.room_public);
        expect(res.doc.room_visible_to).toMatchObject(expected_output_1.doc.room_visible_to);
        expect(res.doc.id_iot_devices).toMatchObject(expected_output_1.doc.id_iot_devices);
        expect(res.doc.room_count).toBe(expected_output_1.doc.room_count);
        expect(res.doc.id_room_statistics).toMatch(expected_output_1.doc.id_room_statistics);
        expect(res.doc.last_updated).toBeTruthy();

    });  

    test("bad input, missing room_name", () => {
        expect.assertions(1)
        return new_room_save_document(input_2).catch(e => expect(e).toMatchObject(expected_output_2))
    });

    test("bad input, missing user_name", () => {
        expect.assertions(1)
        return new_room_save_document(input_3).catch(e => expect(e).toMatchObject(expected_output_2))
    });
})