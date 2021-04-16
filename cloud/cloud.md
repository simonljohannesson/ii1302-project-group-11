# Cloud / Backend notes

---

## TODO next: 
- Database model (see draft on paper)
- Try to create your own queries to select whichever document to receive.
- Learn to use IBM cloud CLI to speed up development & avoid buggy website interface.
- Sequences to build:
    - [x] get-room-count
    - [x] create-new-room
    - [ ] create-new-user
    - [ ] plus-minus-one-room-count
    - [ ] set-room-count
    - [ ] initialization of database including indices
- Improve create-new-room sequence to validate that name is unique


---

## Cloudant database


Example of a document:

    {
        "id": "48ff32463298267888f83e1885218baf",
        "key": "48ff32463298267888f83e1885218baf",
        "value": {
            "rev": "1-9712c8e27ba342a72ff0f5e6ebdadaa3"
        },
        "doc": {
            "_id": "48ff32463298267888f83e1885218baf",
            "_rev": "1-9712c8e27ba342a72ff0f5e6ebdadaa3",
            "comment": "Hallojsan Victor!",
            "createdAt": "2021-04-14T13:45:01.967Z",
            "email": "apa@mail.com",
            "name": "Simon"
        }
    }


Document structure idea for room (under ``"doc":``):

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

Document structure idea room statistics:

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

How to find rooms? Well thought out indexing is probably the solution.

User specific information, a document for each user to keep track of saved rooms:

    {   
        "_id": ...,
        "_rev" ...,
        
        "user-id": unique-user-id,
        "saved-rooms": [],
        "admin-rooms": []
    }


IOT-devices:

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

Likely by working with "IBM Cloudant Query" and using selector syntax. See [link](https://cloud.ibm.com/docs/Cloudant?topic=Cloudant-query).




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

## Info about CouchDB/Cloudant

### Updating
- CouchDB document update model is lockless and optimistic.
- Document edits are made by client applications loading documents, applying changes, and saving them back to the database
- If another client editing the same document saves their changes first, the client gets an edit conflict error on save. To resolve the update conflict, the latest document version can be opened, the edits reapplied and the update tried again.
- Single document updates (add, edit, delete) are all or nothing, either succeeding entirely or failing completely. The database never contains partially saved or edited documents.

### Reading
- CouchDB can guarantee transactional semantics on a per-document basis.
- each client sees a consistent snapshot of the database from the beginning to the end of the read operation
