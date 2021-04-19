/**
 * prepare-new-room-data-for-save should receive a json object on the format:
 *  {
        room_name: <user-chosen-name>,
        user_name: <user-unique-databse-id>
    }
 */

function main(params){
    new_room_save_document(params)
}

function new_room_save_document(params) {
    if (!params.room_name || !params.admin) {
        return Promise.reject({ error: 'no room_name or admin'});
    }
    
    let time = new Date();

    return {
        doc: {
                created_at: new Date(),
                room_name: params.room_name,
                id_users_admin: [params.admin],
                room_public: false,
                room_visible_to:[],
                id_iot_devices: [],
                room_count: 0,
                id_room_statistics: "not available",
                last_updated: time
        }
    };
}

module.exports = new_room_save_document