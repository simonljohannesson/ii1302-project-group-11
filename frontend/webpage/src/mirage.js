import { createServer, Model, Factory, Response } from "miragejs"

export function startMirage() {
  return createServer({
    /**
     * Mocking data is stored in models. To access them from routes, the name needs to be in plural.
     * For example, the model 'room' is access by the name 'rooms' which will look like 
     * 'schema.rooms.all()' if you want to retrieve all data
     */
    models: {
      room: Model,
    },
    /**
     * Factory used to generate mocking data, each functions represent a JSON object
     */
    factories: {
        room: Factory.extend({
            last_updated(){
                return new Date(Math.floor(Math.random()*1000000000) + 1000000000000);
            },
            room_count(){
                return Math.floor(Math.random() * 10) + 1;
            },
            room_name(){
                return "test rum"
            }
        })
    },
    /**
     * Used to create mocking data upon server creation, see documentation for more details
     * @param {*} server 
     */
    seeds(server){
        server.createList('room', 20);
    },
    /**
     * Specifies api endpoint to be simulated
     */
    routes() {
        // Simulated api urls and namespace
        this.urlPrefix = 'https://service.eu.apiconnect.ibmcloud.com';
        this.namespace = '/gws/apigateway/api/86245fabd6001646aa3167f3aaec32059fe9170e90e8fa6f6334f2020bd5b33b/bodycount';
        
        // Response handler for fetching room count 
        this.get('/room_count', (schema, req) => {
            let {room_name, user_name} = req.queryParams;
            
            // Check if params are supplied
            if(!room_name || !user_name) {
                return new Response(400, { Headers: 'Mirage mocking server' }, {error: "Faulty query params!"})
            }
            return schema.rooms.all();
        })
    },
  })
}