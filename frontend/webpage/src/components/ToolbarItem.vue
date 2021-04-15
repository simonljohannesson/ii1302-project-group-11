<template>
    <div>
        <router-link :to="{ name: link}">
            <i :class="this.iconClass"></i> {{link}}
        </router-link>
    </div>
</template>
<script>
export default {
    name: 'ToolbarItem',
    props: {
        link: String,       //link to router component passed as prop
        iconClass: String,  //icon class name on font awesome, pass full class name
    }
}
</script>
<style >
    i {
        padding-right: 10px;
    }
</style>