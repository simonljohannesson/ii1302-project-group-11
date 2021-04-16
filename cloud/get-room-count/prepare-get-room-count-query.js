function main(params) {
    // if(!params.room_name || !params.user_name){
    //     return {"Error": "Missing room_name or user_name"}
    // }
    
    /* Hard coded for dev/test purposes */
    params = {
        "room_name": "living_room",
        "user_name": "frantic_maniac"
    }
    
	return {
        "query":{
            "selector": {
                /* both room name match and visibility match */
                "$and":[
                    /* room name match */
                    {
                    "room_name": {
                        "$eq": params.room_name
                        }
                    },
                    /* visibility match */
                    {
                    "$or":[
                        /* room is public */
                        {
                            "room_public": {
                                "$eq": true
                            }
                        },
                        /* user is admin of room */
                        {
                            "id_users_admin": {
                                "$all": [params.user_name]
                            }   
                        },
                        /* room is visible to user */
                        {
                            "room_visible_to":{
                                "$all": [params.user_name]
                            }
                        }
                    ]
                
                    }
            ]
                
            }
        }
    };
}