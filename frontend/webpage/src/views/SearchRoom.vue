<template >
    <div>
        <div>
            <h1>Rooms</h1>
            <div>
                <div v-if="storedSearchResultsExists">
                    Stored search results
                    <span
                        v-for="item in getStoredSearchResults"
                        :key="item.room_name"
                    >
                        <RoomCount :roomInfo="item" />
                       
                    </span>
                    
                </div>
                <span v-else>No search results stored.</span>
                <span></span>
            </div>
            <div>
                <div v-if="applyAllChanges">
                    <span
                        v-for="item in applyAllChanges"
                        :key="item.room_name"
                    >
                        <ApplyChanges :roomInfo="item" />
                       
                    </span>
                    
                </div>
                <span v-else>No search results stored.</span>
                <span></span>
            </div>
        </div>
        <input
            v-model="searchInput"
            placeholder="Enter a room name."
            @keyup.enter="searchRoom"
        />
        <a class="search noselect" v-on:click="searchRoom">Search</a>

        <div>
            <RoomCount
                v-if="validLastSearchExists()"
                :roomInfo="getLastSearch"
            />
              <ApplyChanges
                v-if="validLastSearchExists()"
                :roomInfo="getLastSearch"
            />
            <!-- Complicated expression to deal with possible values of getLast search if it is not valid-->
            <div v-else>
                {{
                    getLastSearch
                        ? getLastSearch["error"]
                        : false || "Search not made yet."
                }}
            </div>
        </div>
        
    </div>
</template>

<script>
import RoomCount from "@/components/RoomCount.vue";
import ApplyChanges from "@/components/ApplyChanges.vue";

export default {
    components: {
        RoomCount,
        ApplyChanges,
    },
    data: () => {
         console.log("AHHH"+RoomCount);
        return {
            /* user input in search field */
            searchInput: "",
            newCountInput: 0,
        };
    },
    methods: {
        /**
         * Check if a valid search result is present in the store.
         */
        validLastSearchExists() {
            console.log("validatesearch");
            let searchResult = this.$store.getters.getSearchResult;
            if (searchResult == null || searchResult["error"]) {
                return false;
            } else {
                return true;
            }
        },
        /**
         * Check if any search results have been stored in the store.
         */
        storedSearchResultsExists() {
            if (this.$store.getters.getStoredSearchResults.length > 0) {
                return true;
            } else {
                return false;
            }
        },
        /**
         * Search for room count information with the user input in the search field.
         */
        searchRoom() {
            console.log("searchroom -->" + RoomCount.room_count);
            this.$store.dispatch("SEARCH_ROOM_COUNT", this.searchInput);
        },
    },
    computed: {
        /**
         * Fetches the last search.
         */
        getLastSearch() {
            return this.$store.getters.getSearchResult;
        },
        /**
         * Fetches the stored search results.
         */
        getStoredSearchResults() {
            return this.$store.getters.getStoredSearchResults;
        },
    },
};
</script>

<style scoped>
/* Search button styling */
.search {
    text-decoration: none;
    background-color: var(--bc-yellow);
    color: var(--bc-blue);
    padding: 0.2em 1em;
}
/* Search button styling */
.search:hover {
    cursor: pointer;
    color: var(--bc-blue);
    background-color: var(--bc-orange);
}
</style>