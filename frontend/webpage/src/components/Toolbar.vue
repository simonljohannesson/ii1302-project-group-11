<template >
    <div class="sidebar">
        <router-link class="no-active" :to="{ name: 'Welcome' }">
            <img src="../assets/logo-b.png" alt="" />
        </router-link>
        <ToolbarItem link="Home" iconClass="fa fa-home" />
        <ToolbarItem link="About" iconClass="fa fa-info" />
    </div>
</template>
<script>
import ToolbarItem from "./ToolbarItem.vue";
export default {
    name: "Toolbar",
    components: {
        ToolbarItem,
    },
};
</script>
<style scoped>
img {
    width: 60%;
    height: auto;
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