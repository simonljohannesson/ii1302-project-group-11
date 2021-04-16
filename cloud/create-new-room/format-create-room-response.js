/**
 * format-create-room-response
 * 
 * Formats the response received from the Cloudant database 
 * in a cohesive way for the caller.
 * 
 * @param {
            "id": string,
            "ok": boolean,
            "rev": string
          } params 
 * @returns room creation status
 */
function main(params) {
    if (!params.id || !params.ok) {
        return {
            "error": "Could not process request."
        };
    }

    return {
        "id": params.id,
        "ok": true
    }
}



let a = {
    "id": "29b9408bf5bf01eee3bdbc3f0c0172ee",
    "ok": true,
    "rev": "1-eb298ab18914d1b1513f4220313f317e"
}