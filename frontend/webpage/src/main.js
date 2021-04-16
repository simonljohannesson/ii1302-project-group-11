import { createApp } from 'vue'
import App from './App.vue'
import router from './router'
import store from './store'
import { analytics } from './api/firebase.js'

analytics.logEvent('login');
createApp(App).use(store).use(router).mount('#app')
