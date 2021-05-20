<template >
    <div class="container" id="vue-counter">
        <h3>       Add/Remove people       </h3>
        <button class="button noselect" v-on:click="decrement">"-"Decrement</button>
        <button class="button noselect" v-on:click="increment">"+"Increment</button>
        <h2>{{newCountInput}}</h2>
        <button class="button noselect" v-on:click="updateRoom">Apply Changes</button>
        
    </div>
</template>
<script>
export default {
    name: "ApplyChanges",
    props: {
        roomInfo: Object,
    },
    computed: {
    },
    data: () => {
        return {
            newCountInput: 0
        };
    },
    methods: {
        updateRoom() {
            var newCount = parseInt(this.roomInfo["room_count"]) + this.newCountInput;
            var arg = {count: newCount, room: this.$parent.searchInput}
            this.$parent.$store.dispatch("UPDATE_ROOM_COUNT", arg);
        },
        increment() {
            this.newCountInput +=1
        },
        decrement() {
            this.newCountInput -= 1 
        },
        applyAllChanges() {
            this.updateRoom();
        },
    
    }
};
</script>
<style scoped>
.container {
    width: fit-content;
    background-color: #303c6c84;
    height: fit-content;
    border-radius: 15px;
    -moz-border-radius: 15px;
    -webkit-border-radius: 15px;
    padding: 5px;
}
.container div {
  background-color: #fbe8a6;
  border: 1px solid #eed08f;
  text-align: left;
  font-size: 20px;
  border-radius: 5px;
}
.button {
    text-decoration: none;
    background-color: var(--bc-yellow);
    color: var(--bc-blue);
    padding: 0.2em 1em;
}
/* Search button styling */
.button:hover {
    cursor: pointer;
    color: var(--bc-blue);
    background-color: var(--bc-orange);
}
</style>
