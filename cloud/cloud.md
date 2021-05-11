# Cloud / Backend notes


---

## Cloudant database

Document structure for ``room`` (under ``"doc":``):

    {
        "_id": "room-name",
        "_rev" auto-generated-by-couchdb,

        "created_at": "2021-04-15T15:22:46.516Z",
        "room_name": "user-specific-name-for-room",
        "id_users_admin": ["unique-identifier", ...],
        "room_public": "true|false",
        "room_visible_to":["unique-identifier", ...],
        "id_iot_devices": [
            "IOT-Device-ID1",
            "IOT-Device-ID2"
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
        "_id": "generated-by-node-red",
        "_rev" auto-generated-by-couchdb,

        "device_name":"custom-name-can-be-set-by-user",
        "id_room":[
            {
                id:"room-name", 
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
## IBM IOT Platform
### How devices works 
A *device type* on the platform can be seen as a type of sensor. For example a *device* could be a `temperature` sensor or a `revolutionaryNewSensingUnit`. You can then assign real devices to the *device type*. Each instance of the device is then given a unique *Device ID* which is how we can identify each sensor. When creating a new device we specify which type of sensor it is, for example `temperature` and giving it the unique id of `coolTemperatureSensor-1` or whatever we want. This will then open up a device which we can post and read data from using MQTT. IOT Platform will generate something like this for the example device:
```
Organization ID: f35rw3
Device Type: temperature
Device ID: coolTemperatureSensor-1
Authentication Method: use-token-auth
Authentication Token: "Device unique token will be generated here"
```
When posting to this specific sensor with MQTT we use `Authentication Method` as user name, and `Authentication Token` as password. 

---
## Sending MQTT via console
You can use the `mosquitto_pub` terminal client to send commands.
### Commands
Send sample data to mqtt server of device type `device` with device id `d1` 

``` 
mosquitto_pub -h f35rw3.messaging.internetofthings.ibmcloud.com -p 8883 -u use-token-auth -P 'Authentication Token' -i 'd:f35rw3:device:d1' -t 'iot-2/evt/1/fmt/JSON' -m '{"Send":"your data here, doesn't need to be JSON"}' 
```
---
## MQTT Messaging in this project
### Publishing to IOT Platform 
All data sent to the IOT Platform should be sent to this **MQTT topic** ``` iot-2/evt/1/fmt/JSON```. With this **host** ``` f35rw3.messaging.internetofthings.ibmcloud.com ``` on **port** ``` 8883```.

### Data design
The data sent to the IOT Platform should be structured in the following way. The most important key-value-pair to **NOT** alter is ```{"type":"increment|decrement"}```, other data can be added below. Like this:
```
{
    "type":"increment|decrement",
    "someOtherData":123,
    "pointlessInformation":"This just used more data becuase we can!"
}
```
### Important note about sending data
The JSON data itself might need to be surounded by quotes or ticks, this depends on how the MQTT library is implemented. for example in `mosquitto_pub` this is the result:
#### This will work
```
'{"data":"whoooooo"}'
```
#### This wont work 
```
{"data":"whoooooo"}
```
This has to do with how the specific MQTT implementation decides to interpret given inputs, so check this when it's time to send data. 
