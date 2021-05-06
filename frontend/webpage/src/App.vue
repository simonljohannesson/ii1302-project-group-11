<template>
    <div>
        <div v-if="isLoggedIn()">
            <div class="toolbar">
                <Toolbar />
            </div>
            <div class="mainContent">
                <router-view />
            </div>
        </div>
        <div v-else>
            <!-- <router-view /> -->
            <Login/>
        </div>
    </div>
</template>
<script>
import Toolbar from "@/components/Toolbar.vue";
import Login from "@/views/Login.vue";
export default {
    components: {
        Toolbar,
        Login,
    },
    methods: {
        isLoggedIn() {
            let user = this.$store.getters.getLoginToken;
            console.log("is logged in? " + user);
            // console.log(this.$store.getters.getLoginStatus);
            return user;
        }
    }
};
</script>
<style>
#app {
    font-family: Avenir, Helvetica, Arial, sans-serif;
    -webkit-font-smoothing: antialiased;
    -moz-osx-font-smoothing: grayscale;
    text-align: center;
    /* color: #2c3e50; */
    color: var(--bc-blue);
    height: 100vh;
    width: 100vw;
    background-color: var(--bc-light-turquoise);
    
}
.mainContent {
    margin-left: 15rem;
    
}
#nav {
    padding: 30px;
}

#nav a {
    font-weight: bold;
    color: #2c3e50;
}

#nav a.router-link-exact-active {
    color: #42b983;
}
/* Toolbar */
.toolbar {
    height: 100%; /* Full-height: remove this if you want "auto" height */
    width: 15rem; /* Set the width of the sidebar */
    position: fixed; /* Fixed Sidebar (stay in place on scroll) */
    z-index: 1; /* Stay on top */
    top: 0; /* Stay at the top */
    left: 0;
    background-color: var(--bc-blue);
    overflow-x: hidden; /* Disable horizontal scroll */
    padding-top: 20px;
}

/* Link styling */
.toolbar a {
    padding: 6px 8px 6px 16px;
    text-decoration: none;
    font-size: 25px;
    color: var(--bc-light-turquoise);
    display: block;
}

/* Hover effect */
.toolbar a:hover {
    background-color: var(--bc-turquoise);
    color: var(--bc-blue);
    /* color: #f1f1f1; */
}

/* custom color theme */
:root {
    --bc-yellow: #FBE8A6;
    --bc-orange: #F4976C;
    --bc-blue: #303C6C;
    --bc-turquoise: #B4DFE5;
    --bc-light-turquoise: #D2FDFF;
}

/* disable text selection */
.noselect {
  -webkit-touch-callout: none; /* iOS Safari */
    -webkit-user-select: none; /* Safari */
     -khtml-user-select: none; /* Konqueror HTML */
       -moz-user-select: none; /* Old versions of Firefox */
        -ms-user-select: none; /* Internet Explorer/Edge */
            user-select: none; /* Non-prefixed version, currently
                                  supported by Chrome, Edge, Opera and Firefox */
}


</style>
