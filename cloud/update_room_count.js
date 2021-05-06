/**
 *  format of input: {
 *      url: "secret",
 *      room_name: String,
 *      admin: String,
 *      new_count_value: Integer
 *  }
 * 
 */


const axios = require("axios")


async function getDocument(input, dbPath, recCount){
    const selector = {
        "selector": {
           "_id": {
              "$eq": input.room_name
           },
        }
    }
    
    return await axios({
        url: input.url + dbPath + "/_find",
        method: "post",
        data: JSON.stringify(selector),
        headers: { 'Content-Type': 'application/json' },
    }).then(reply => {
        if(reply["data"]["docs"].length > 0){
            let data = reply["data"].docs[0];
            /* update room count */
            data["room_count"] = input.new_count_value
            const admin = data.id_users_admin.includes(input.admin)
            if (admin){

                /* write updated document */
                return writeDocument(input, dbPath, data, recCount)
            }
        }
        return Promise.reject({error: "Could not access a room with that name."})
    }).catch(reply => {
        return Promise.reject({ error: "An error occured, could not service request." })
    })
}

async function writeDocument(input, dbPath, updatedRoom, recCount){
    console.log("write")
    return await axios({
        url: input.url + dbPath,
        method: "post",
        data: JSON.stringify(updatedRoom),
        headers: { 'Content-Type': 'application/json' },
    }).then(reply => {
        if (reply.data["ok"]) {
            return Promise.resolve({
                ok: true,
                id: reply.data.id
            })
        }
        return Promise.reject({error: 'An error occured.'})
    }).catch(reply => {

        /* conflict resolution */ 
        if(recCount > 5) return Promise.reject({ error: "Could not update room, try again later." })
        return getDocument(input, dbPath, recCount + 1)
        
    })

}

async function main(input) {
    if (!input.room_name || !input.admin) {
        return Promise.reject({ error: 'Missing room name or admin name.' });
    }

    const dbPath = "/bodycount"

    return await getDocument(input, dbPath)
}


main(input)
.then(x=> console.log(x)).catch(x=>console.log(x))


