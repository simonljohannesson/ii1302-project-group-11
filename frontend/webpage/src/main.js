import { createApp } from 'vue'
import App from './App.vue'
import router from './router'
import store from './store'
import { analytics } from './api/firebase.js'
import { startMirage } from './mirage'
import AppID from 'ibmcloud-appid-js'

const appID = new AppID();
appID.init({
    clientId: '90d4e3a8-97ac-46f6-bbc7-6f8094b8b545',
    discoveryEndpoint: 'https://eu-gb.appid.cloud.ibm.com/oauth/v4/2c92a208-70b1-4c17-9ef1-4b8e87f1a6b3/.well-known/openid-configuration'
});

// Start mirage mocking server if in development mode. aka 'npm run serve'
if(process.env.NODE_ENV === 'development'){
    console.log("Starting Mirage API mocking");
    startMirage();
}
analytics.logEvent('login');
createApp(App).use(store).use(router).mount('#app')
export{
    appID
}

