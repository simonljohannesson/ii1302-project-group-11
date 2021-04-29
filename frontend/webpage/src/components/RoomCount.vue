<template >
  <div class="container">
    <div>Room name: {{ roomName }}</div>
    <div>Room count: {{ roomCount }}</div>
    <div>Last updated: {{ lastUpdated }}</div>
  </div>
</template>
<script>
export default {
  name: "RoomCount",
  props: {
    roomInfo: Object,
  },
  computed: {
    roomName() {
      if(!this.roomInfo) return null;
      return this.roomInfo["room_name"];
    },
    roomCount() {
      if(!this.roomInfo) return null;
      return this.roomInfo["room_count"];
    },
    lastUpdated() {
      let time = this.roomInfo["last_updated"];
      if (!time) return "No time available";
      time = new Date(time);
      let y = time.getFullYear();
      let M = time.getMonth();
      let d = time.getDay();
      let h = time.getHours();
      let m = time.getMinutes();
      let s = time.getSeconds();
      return `${y}-${M}-${d} ${h}:${m}:${s}`;
    },
  },
  data() {
    return {
      room_info: {
        last_updated: "2021-04-21T07:01:48.387Z",
        room_count: 14,
        room_name: "somename",
      },
    };
  },
};
</script>
<style scoped>
.container {
  width: fit-content;
  background-color: #f4976c;
  height: fit-content;
  border-radius: 15px;
  -moz-border-radius: 15px;
  -webkit-border-radius: 15px;
}
</style>
