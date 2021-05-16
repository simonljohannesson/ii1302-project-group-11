
const baseURL = "https://service.eu.apiconnect.ibmcloud.com/gws/apigateway/api/86245fabd6001646aa3167f3aaec32059fe9170e90e8fa6f6334f2020bd5b33b/bodycount";

/**
 *  Communication with API open to the backend on IBM Cloud.
 */
export const ibmAPI = {
    /**
     * Request the room count information about a room via the open API.
     * @param {String} roomName 
     * @param {String} userName 
     * @returns 
     */
    getRoomCount: (roomName, userName) => {
        const path = "/room_count" + "?user_name=" + userName + "&room_name=" + roomName
        let options = {
            method: "GET"
        }
        return fetch(baseURL + path, options)
            .then((response) => {
                if (response.ok) {
                    return response.json()
                }
                else {
                    /* Something other than a 200 code received. */
                    return { error: "Connection error." }
                }
            })
            .then((msg) => {
                if (msg["rooms"]) {
                    return msg["rooms"][0];
                } else {
                    /* some error message (but a 200 http code) is received from the backend */
                    return { error: "Could not service the request." };
                }
            })
            .catch(() => {
                return {
                    /* unforeseen issues will be caught here */
                    error: "Something went wrong."
                }
            })
    },
    updateRoomCount: (roomName, admin, newCountValue) => {
        console.log("IBMjs" + newCountValue);
        //newCountValue = 15;
        const path = "/update_room_count" + "?admin=" + admin + "&room_name=" + roomName + "&new_count_value=" + newCountValue
        console.log("IBM_path"+ path);
        let options = {
            method: "GET"
        }
        return fetch(baseURL + path, options)
            .then((response) => {
                if (response.ok) {
                    console.log("IBM_if");
                    return response.json()
                }
                else {
                    console.log("IBM_else" + newCountValue);
                    return { error: "Connection error." }
                }
            })
            .catch((e) => {
                console.log("IBM_catch: " + e);
                return {
                    
                    error: "Something went wrong."
                }
            })
    }
};