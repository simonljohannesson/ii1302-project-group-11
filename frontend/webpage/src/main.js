import { createApp } from 'vue'
import App from './App.vue'
import router from './router'
import store from './store'
import { analytics } from './api/firebase.js'
import { startMirage } from './mirage'

// Start mirage mocking server if in development mode. aka 'npm run serve'
if(process.env.NODE_ENV === 'development'){
    console.log("Starting Mirage API mocking");
    //startMirage();
}
analytics.logEvent('login');
createApp(App).use(store).use(router).mount('#app')
