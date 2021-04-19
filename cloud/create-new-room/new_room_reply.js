function main(params){
    new_room_reply(params)
}
/**
 * Formats the response received from the Cloudant database 
 * for the caller.
 * 
 * @param {
            "id": string,
            "ok": boolean,
            "rev": string
          } params 
 * @returns room creation status
 */
function new_room_reply(params) {
    if (!params.id || !params.ok) {
        return Promise.reject({
            "error": "Could not process request."
        });
    }

    return {
        "id": params.id,
        "ok": true
    }
}

module.exports = new_room_reply