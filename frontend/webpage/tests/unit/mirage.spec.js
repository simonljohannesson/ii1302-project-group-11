import { startMirage } from '../../src/mirage'
const apiEndpoint = 'https://service.eu.apiconnect.ibmcloud.com/gws/apigateway/api/86245fabd6001646aa3167f3aaec32059fe9170e90e8fa6f6334f2020bd5b33b/bodycount/room_count';
/**
 * Setup a mirage server and closing it before every run to 
 * eliminate possible interferances between tests
 */
let mirageServer;
beforeEach(() => {
    // Starting in test enviroment to remove simulated delay, speeds upp test runs
    mirageServer = startMirage({ environment: "test" });
    // Disable logging to not bloat jest test output
    mirageServer.logging = false;
})
afterEach(() => {
    mirageServer.shutdown()
})

test('Faulty request to /room_count', async() => {
    let resCode;
    await fetch(apiEndpoint, {
        method: 'get',

    }).then((res) => {
        resCode = res.status;
    })
    expect(resCode).toBe(400);
})
test('Correct request', async() => {
    let resCode;
    await fetch(apiEndpoint + '?room_name=bastu&user_name=albert', {
        method: 'get',

    }).then((res) => {
        resCode = res.status;
    })
    expect(resCode).toBe(200);
})
test('Missing room_name param', async() => {
    let resCode;
    await fetch(apiEndpoint + '?user_name=albert', {
        method: 'get',

    }).then((res) => {
        resCode = res.status;
    })
    expect(resCode).toBe(400);
})
test('Missing user_name param', async() => {
    let resCode;
    await fetch(apiEndpoint + '?room_name=bastu', {
        method: 'get',

    }).then((res) => {
        resCode = res.status;
    })
    expect(resCode).toBe(400);
})
