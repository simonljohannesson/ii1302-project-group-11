import { createRouter, createWebHistory } from 'vue-router'
import Home from '../views/Home.vue'
import About from '../views/About.vue'
import Welcome from '../views/Welcome.vue'
import Login from '../views/Login.vue'
import SearchRoom from '../views/SearchRoom.vue'
import store from '@/store/index';

const routes = [
    {
        path: '/home',
        name: 'Home',
        component: Home,
    },
    {
        path: '/welcome',
        name: 'Welcome',
        component: Welcome,
      
    },
    {
        path: '/about',
        name: 'About',
        component: About,
    },
    {
        path: '/',
        name: 'Login',
        component: Login,
    },
    {
        path: '/searchroom',
        name: 'Search Room',
        component: SearchRoom,
    }
]

const router = createRouter({
    mode: 'history',
    history: createWebHistory(process.env.BASE_URL),
    routes
})

router.beforeEach((to, from, next) => {
    const isAuthenticated = store.getters.getLoginToken;
    if (to.name !== 'Login' && !isAuthenticated) next({ name: 'Login' });
    else next();
})
export default router
