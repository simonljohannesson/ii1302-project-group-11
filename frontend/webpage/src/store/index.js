import { createStore } from 'vuex'
import { ibmAPI } from "../api/ibm.js"

export default createStore({
  state: {
    userName: "someadmin",
    /* information about rooms */
    searchResult: null,
    storedSearchResults: [
      {
        last_updated: '2021-04-21T07:01:48.387Z',
        room_count: 14,
        room_name: 'somename1'
      },
      {
        last_updated: '2021-04-21T07:01:48.387Z',
        room_count: 14,
        room_name: 'somename2'
      },
      {
        last_updated: '2021-04-21T07:01:48.387Z',
        room_count: 14,
        room_name: 'somename3'
      }
    ]
  },
  mutations: {
    setSearchResult(state, roomInfo) {
      state.searchResult = roomInfo;
    }
  },
  actions: {
    GET_ROOM_COUNT(state, roomName, userName) {
      ibmAPI.getRoomCount(roomName, userName)
        .then((data => {
          state.commit("setSearchResult", res)
        }))
    },
    SET_LAST_ROOM_SEARCH(state, roomName) {
      console.log('Setting the last room search manually.')
      state.commit("setSearchResult", { last_updated: '2277-11-22T07:00:00.017Z', room_count: 66, room_name: roomName })
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
