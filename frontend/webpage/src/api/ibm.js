
const baseURL = "https://service.eu.apiconnect.ibmcloud.com/gws/apigateway/api/86245fabd6001646aa3167f3aaec32059fe9170e90e8fa6f6334f2020bd5b33b/bodycount";

const fetch = require("node-fetch");

const ibmAPI = {
    getRoomCount : (roomName, userName) => {
        const path = "/room_count" + "?user_name=" + userName + "&room_name=" + roomName
        let options = {
            method: "GET"
        }
        return fetch(baseURL + path, options)
          .then((response) => {
              if (response.ok){
                  return response.json()
              }
              else {
                  return {error: "Connection error."}
            } 
          })
          .then((msg)=> {
              if (msg["rooms"]){
                return msg["rooms"][0];
              }else{
                  return msg;
              }
          })
          .catch(()=> { return {
                error: "Something went wrong."
            }
          })
    }
};

// ibmAPI.getRoomCount("somename", "someadmin").then(res=>console.log(res))


