<template >
    <div class="container">
        <div class="room">{{roomName}}</div>
        <div class="room">{{roomCount}}</div>
        <div class="room">{{lastUpdated}}</div>
        <button v-on:click="test">Update</button>
    </div>
</template>
<script>
export default {

  
    name: "RoomCount",
    computed: {
      roomName() {return  this.room_info["room_name"]},
      roomCount() {return  this.room_info["room_count"]},
      lastUpdated() {
        let time =  new Date(this.room_info["last_updated"])
        let y = time.getFullYear()
        let M = time.getMonth()
        let d = time.getDay()
        let h = time.getHours()
        let m = time.getMinutes()
        let s = time.getSeconds()
        return `${y}-${M}-${d} ${h}:${m}:${s}`
      },
    },
    data() { return { 
      room_info: {
                  "last_updated": "2021-04-21T07:01:48.387Z",
                  "room_count": 14,
                  "room_name": "somename"
      }
    }},
       methods:{
        test() {
          console.log("test works")
        }
    }
};
</script>
<style scoped>

.container {
  color: #303c6c;
  font-size: 20px;
  display: flex;
  flex-wrap: nowrap;
  justify-content: center;
  align-items: center;
  align-content: center;
  width: fit-content;
  background-color: #f4976c;
  height: fit-content;
  overflow: auto;
  flex-direction: column;
  border-radius:15px;
  -moz-border-radius:15px;
  -webkit-border-radius:15px;

}

.room {
  width: 200px;
  height: 100px;
  margin: 0px;
  background-color:  transparent;
  display:flex;
  justify-content:center;
  align-items:center;
}

.btn{
    display: flex;
    flex-wrap: wrap;
    max-height: 250px;
    text-align: center;
    transition: .2s;
    background-color: tomato;
}
.btn:hover{
  background-color: teal;
}

</style>
    // methods:{
    //     getRoomCount: (roomName, userName) => {
    //         let baseURL = "https://service.eu.apiconnect.ibmcloud.com/gws/apigateway/api/86245fabd6001646aa3167f3aaec32059fe9170e90e8fa6f6334f2020bd5b33b/bodycount/room_count"
    //         let options = {
    //             method: "GET",
    //             headers: {
    //                 "user_name": userName,
    //                 "room_name": roomName
    //             }
    //         }
    //         let prom = fetch(baseURL, options)
    //         return prom.then((response) => response[0]).catch(()=> {error: "No room found"})
    //     }
    // }

