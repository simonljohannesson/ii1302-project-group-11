<template >
    <div class="sidebar">
        <div class="links">
            <router-link class="no-active" :to="{ name: 'Welcome' }">
                <img src="../assets/logo-b.png" alt="" />
            </router-link>
            <ToolbarItem link="Home" iconClass="fa fa-home" />
            <ToolbarItem link="About" iconClass="fa fa-info" />
            <ToolbarItem link="Search Room" iconClass="fa fa-search"/>

        </div>
        <div class="logout">
            <a v-on:click="logout()" class="logout" href=""><i class="fa fa-sign-out" aria-hidden="true"></i>Sign out</a>
        </div>
    </div>
</template>
<script>
import ToolbarItem from "./ToolbarItem.vue";
export default {
    name: "Toolbar",
    components: {
        ToolbarItem,
    },
    methods: {
        logout(){
            this.$store.dispatch('LOGOUT_USER');
            this.$router.push({name: 'Login'});
        }
    },
    created() {
        this.$router.push({name: 'Welcome'});
    },
};
</script>
<style scoped>
img {
    width: 60%;
    height: auto;
}
.sidebar{
    height: 100%;
}
.links{
    height: 90%;
}
.logout{
    height:  30px;
}
/* Highlights the active menu item */
.router-link-active {
    background-color: #424b6e;
}
/* To prevent highlight on logo when clicked */
.router-link-active.no-active {
    background-color: #303c6c;
}
</style>