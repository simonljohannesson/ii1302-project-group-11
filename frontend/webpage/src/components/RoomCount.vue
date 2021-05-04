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
    /**
     * Get room name info from prop object.
     */
    roomName() {
      if(!this.roomInfo) return null;
      return this.roomInfo["room_name"];
    },
    /**
     * Get room count info from prop object.
     */
    roomCount() {
      if(!this.roomInfo) return null;
      return this.roomInfo["room_count"];
    },
    /**
     * Get last updated info from prop object.
     * Formats time if it exists.
     */
    lastUpdated() {
      if(!this.roomInfo) return null;
      let time = this.roomInfo["last_updated"];
      if (!time) return "No time available";
      time = new Date(time);
      let y = time.getFullYear();
      /* Format number to be on format XX. */
      const addZero = (number) => number < 10 ? "0" + number : number;

      let M = addZero(time.getMonth());
      let d = addZero(time.getDay());
      let h = addZero(time.getHours());
      let m = addZero(time.getMinutes());
      let s = addZero(time.getSeconds());
      return `${y}-${M}-${d} ${h}:${m}:${s}`;
    },
  },
  data: ()=>{
    return {
      
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
  padding: 5px;
}
</style>
