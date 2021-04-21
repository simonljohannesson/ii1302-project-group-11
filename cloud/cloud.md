# Cloud / Backend notes


---

## Cloudant database

Document structure for ``room`` (under ``"doc":``):

    {
        "_id": ...,
        "_rev" ...,

        "created_at": "2021-04-15T15:22:46.516Z",
        "room_name": "unique-identifier",
        "id_users_admin": ["unique-identifier", ...],
        "room_public": "true|false",
        "room_visible_to":["unique-identifier", ...],
        "id_iot_devices": [
            "unique-database-id-1",
            "unique-databse-id-2"
        ],
        "room_count": "integer-value",
        "id_room_statistics": ...,
        "last_updated": date/time
    }

Document structure ``room_statistics``:

    {
        "_id": ...,
        "_rev" ...,
        
        "statistics": {
            "diagram-values": [
                "Monday 08:00": "average-count",
                "Monday 09:00": "average-count",
                "Monday 10:00": "average-count",
                .
                .
                .
            ],
            "raw-data":[
                "date-and-time": "count",
                "date-and-time": "count",
                "date-and-time": "count",
                .
                .
                .
            ]
        }
    }
    

To collect data an action could be run a few times per hour and save the current count at each room and store the value in the ``raw-data`` list together with the date and time of the collection.

To generate the ``diagram-values`` an action could be run a few times per day (or week) which would calculate the average values that are of interest in the diagram.


Document structure ``user``:

    {   
        "_id": ...,
        "_rev" ...,
        
        "user-id": unique-user-id,
        "saved-rooms": [],
        "admin-rooms": []
    }


Document structure ``IOT-devices``:

    {
        "_id": ...,
        "_rev" ...,

        "device_name":unique-id,
        "id_room":[
            {
                id:..., 
                direction:in/out
            },
             ...]

    }

How to perform specific querying with cloudant functions/sequences/actions?

By working with "IBM Cloudant Query" and using selector syntax. See [link](https://cloud.ibm.com/docs/Cloudant?topic=Cloudant-query).



---

## IBM Cloud

Logging in:

1. Start ibm cloud cli tool, in cloud or on local machine.
2. Run ``ibmcloud login`` and follow the instructions.
3. Make sure that the correct region (eu-gb), org (vpetters@kth.se), resource group (Default) and space (project) is chosen.

---

## Sequence: ``create-new-room``

To create/setup:

1. Log into ibm cloud.
2. In the directory ``cloud/`` run the below commands.
    Note, so far the binding does not seem to work.

    
    ```
    ibmcloud fn action create new_room_save_document create-new-room/new_room_save_document.js
    ibmcloud fn action create new_room_create_document create-new-room/new_room_create_document.js
    ibmcloud fn action create new_room_reply create-new-room/new_room_reply.js
    ibmcloud fn service bind cloudantnosqldb new_room_create_document --instance node-red-avtdl-2021--cloudant-1618917170683 --keyname cloud-functions
    ibmcloud fn action create new_room_sequence --sequence new_room_save_document,new_room_create_document,new_room_reply
    ```

### API definition
Not yet defined.

### Action: ``prepare-new-room-data-for-save`` -> ``new_room_save_document``


Input data format:

    {
        room-name: user-chosen-name,
        admin: user-unique-databse-id
    }


### Action: ``create-document``
Output format:

    {
        "id": "29b9408bf5bf01eee3bdbc3f0c0172ee",
        "ok": true,
        "rev": "1-eb298ab18914d1b1513f4220313f317e"
    }

### Action: ``format-create-room-response`` -> ``new_room_reply``
Output format:

    {
        "error": "Could not process request."
    }
    or
    {
        "id": string,
        "ok": true
    }

---

## Sequence: ``get-room-count``

To create/setup:

1. Log into ibm cloud.
2. In the directory ``cloud/`` run the below commands.
    Note, so far the binding does not seem to work.
    
    ```
    ibmcloud fn action create room_count_selector get-room-count/room_count_selector.js
    ibmcloud fn action create room_count_reply get-room-count/room_count_reply.js
    ibmcloud fn action create room_count_exec_query_find get-room-count/exec-query-find.js
    ibmcloud fn action create room_count_sequence --sequence room_count_selector,room_count_exec_query_find,room_count_reply
    ibmcloud fn service bind cloudantnosqldb room_count_exec_query_find --instance node-red-avtdl-2021--cloudant-1618917170683 --keyname cloud-functions
    ```

### Action: ``prepare-get-room-count-query`` --> Refactored: ``room_count_selector``
Input:

    {
        room_name: <user-chosen-name>,
        user_name: <user-unique-databse-id>
    }

### Action: ``exec-query-find``
Does a query for the room and returns it if:
>1. It exists.
>2. And:
>    a. room is public, or
>    b. user is admin of room, or
>    c. room is visible to user

### Action: ``format-get-room-count-response`` -> Refactored: ``room_count_reply``
Returns:

    {
        "error":...
    }
or:

    {
        "room_name": ..., 
        "room_count": ..., 
        "last_updated": ...
    }

---