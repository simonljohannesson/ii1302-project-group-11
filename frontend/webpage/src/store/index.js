import { createStore } from 'vuex'
import { ibmAPI } from "../api/ibm.js"

export default createStore({
  state: {
    /* 
      user identifyer, currently used when making api calls for the room count 
      should not be hard coded
    */
    userName: "someadmin",
    /* information about rooms */
    searchResult: null,
    /* Array with search results of the object with the format:
      {
          last_updated: '2021-04-21T07:01:48.387Z',
          room_count: 14,
          room_name: 'somename1'
      }
    */
    storedSearchResults: []
  },
  mutations: {
    setSearchResult(state, roomInfo) {
      state.searchResult = roomInfo;
    },
  },
  actions: {
    /**
     * Search for the room count information of a room.
     * 
     * Return obeject format: 
     * {
     *    last_updated: '2021-04-21T07:01:48.387Z',
     *    room_count: 14,
     *    room_name: 'somename1'
     * }
     * or 
     * {error: "..."}
     * 
     * @param {vuex context} context 
     * @param {String} roomName 
     * @returns {Object}
     */
    SEARCH_ROOM_COUNT(context, roomName) {
      ibmAPI.getRoomCount(roomName, context.state.userName)
        .then((data => {
          context.commit("setSearchResult", data)
        }))
    }
  },
  getters: {
    getSearchResult(state) {
      return state.searchResult;
    },
    getStoredSearchResults(state) {
      return state.storedSearchResults;
    },
    getUserName(state) {
      return state.userName;
    }
  },
  modules: {
  }
})
