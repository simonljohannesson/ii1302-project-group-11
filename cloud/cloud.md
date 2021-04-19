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

## Sequence: ``create-new-room``

### API definition
Not yet defined.

### Action: ``prepare-new-room-data-for-save``


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

### Action: ``format-create-room-response``
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

### Action: ``prepare-get-room-count-query``
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

### Action: ``format-get-room-count-response``
Returns:

    {
        "Error":...
    }
or:

    {
        "room_name": ..., 
        "room_count": ..., 
        "last_updated": ...
    }

---