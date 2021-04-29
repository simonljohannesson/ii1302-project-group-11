<template >
    <div>
        <div >
            <h1>Rooms</h1>
        <div>
            <div v-if="storedSearchResultsExists">Stored search results
                <span v-for="item in getStoredSearchResults" :key="item.room_name">
                    <RoomCount :roomInfo="item"/>
                </span>
            </div>
            <span v-else>No search results stored.</span>
            <span></span>
        </div>
        </div>
            <input v-model="searchInput" placeholder="Enter a room name." @keyup.enter="searchRoom">
            <a class="search noselect" v-on:click="searchRoom" >Search</a>
        <div>
        <RoomCount v-if="lastSearchExists()" :roomInfo="getLastSearch" />
        <div v-else>Search not made yet.</div>
        </div>
    </div>
</template>

<script>
import RoomCount from "@/components/RoomCount.vue";
export default {
    components: {
      RoomCount
    },
    data : ()=> {
        return  {
            searchInput: ""
        }
    },
    methods : {
        test : () => console.log(new Date()),
        lastSearchExists(){
            if(this.$store.getters.getSearchResult === null){
                return false;
            }else{
                return true;
            }
        },
        storedSearchResultsExists(){
            if(this.$store.getters.getStoredSearchResults.length > 0){
                return true;
            }else{
                return false;
            }
        },
        searchRoom(){
            console.log("calling searchRoom with room name: " + this.searchInput + " username: " + this.$store.getters.getUserName)
            this.$store.dispatch("SET_LAST_ROOM_SEARCH", this.searchInput)
        }   
    },
    computed: {
        getLastSearch(){
            return this.$store.getters.getSearchResult;
        },
        getStoredSearchResults(){
            return this.$store.getters.getStoredSearchResults;
        }
    }
}
</script>

<style scoped>

.search{
    text-decoration: none;
    background-color: var(--bc-yellow);
    color: var(--bc-blue);
    padding: 0.2em 1em;
}
.search:hover{
    cursor: pointer;
    color: var(--bc-blue);
    background-color: var(--bc-orange);
}
</style>