/*
    Need to know:
    1. room id/room_name
    2. user_id/user name

    Process:
    1. Fetch room document
        a. if not exist return error
    2. Check visibility of room
        a. if room_public == true -> allow access
        b. if user in id_users_admin -> allow access
        c. if user in room_visible_to -> allow access
        d. else deny access -> return error
    3. Return room_name, room_count, last_updated
    
    Biggest issue: 
        Validate user access
    
    Solution:
        1. Perform some validation in selector query.
        or
        2. Write completely custom query.
*/