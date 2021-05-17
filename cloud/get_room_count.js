/** expects input on form:
 *  input : {
 *          url: secret,
 *          user_name: ...,
 *          room_name: ...
 *  }
 * 
 */
function main(input) {
    if (!input["room_name"] || !input["user_name"]) {
        return { error: "Missing room name or user name"};
    }

    const selector = {
        "selector": {
           "_id": {
              "$eq": input.room_name
           },
        }
    }

    const axios = require("axios")

    const dbPath = "/bodycount/_find"

    const promise = axios({
        url: input.url + dbPath,
        method: "post",
        data: JSON.stringify(selector),
        headers: { 'Content-Type': 'application/json' },
    }).then(reply => {
        if(reply["data"]["docs"].length > 0){
            let data = reply["data"].docs[0];
            const public = data.room_public
            const visible = data.room_visible_to.includes(input.user_name)
            const admin = data.id_users_admin.includes(input.user_name)
            if (public || visible || admin){
                return {
                    "room_name": data._id, 
                    "room_count": data.room_count, 
                    "last_updated": data.last_updated
                }
            }
        }
        return {error: "Could not access a room with that name."}
    }).catch(reply => {
        return { error: "An error occured, could not service request." }
    })

    return promise
}





// main(input).then(x => console.log(x)).catch(x=>console.log(x))

