import { mutations, actions } from '../../src/store'
// import { startMirage } from "../../src/mirage"


test("test mutate setSearchResult", ()=>{
    let mock_store = {
        userName: "someadmin",
        searchResult: null,
        storedSearchResults: []
    };
    const info = {last_updated: "mm", room_count: "nn", room_name: "ss"};
    mutations.setSearchResult(mock_store, info);

    expect(mock_store.searchResult).toStrictEqual(info)
});

// Unable to get test to work as intended.
//
// test("test action SEARCH_ROOM_COUNT", ()=> {
    
//     const commit = jest.fn()

//     // let server = startMirage({ environment: "test" })
//     let server = startMirage({ environment: "development" })
//     server.logging = true 


//     const state = {
//         userName: "one username"
//     }
//     const roomName = "a name";
//     let exp = {
//         last_updated:"33",
//         room_count:"mumma",
//         room_name:"badabing"
//     };
//     actions.SEARCH_ROOM_COUNT({commit, state}, roomName)

//     expect(commit).toHaveBeenCalled()

//     server.shutdown()
// });