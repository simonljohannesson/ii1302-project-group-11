/** expects input on form:
 *  input : {
 *          url: secret,
 *          admin: ...,
 *          room_name: ...
 *  }
 * 
 */

function main(input) {
    if (!input.room_name || !input.admin) {
        return Promise.reject({ error: 'Missing room name or admin name.' });
    }
    const axios = require("axios")
    const new_room = {
        "_id": input.room_name,
        "id_users_admin": [input.admin],
        "room_public": false,
        "room_visible_to": [],
        "room_count": 0,
        "id_room_statistics": null,
        "last_updated": Date.now()
    }
    const dbPath = "/bodycount"

    const promise = axios({
        url: input.url + dbPath,
        method: "post",
        data: JSON.stringify(new_room),
        headers: { 'Content-Type': 'application/json' },
    }).then(reply => {
        if (reply.data["ok"]) {
            return {
                ok: true,
                id: reply.data.id
            }
        }
        return {error: 'An error occured.'}
    }).catch(reply => {
        return { error: "Could not create room with that name." }
    })

    return promise
}




// main(input).then(data => {
//     console.log(data)
// }).catch(error => {
//     console.log(error)
// })
