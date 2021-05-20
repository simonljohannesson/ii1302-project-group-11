<template>
  <div class="login">
    <h1>Login</h1>
    <h2>Please sign in</h2>
    <button class ="button button" v-on:click="signin">Sign in</button>
  </div>
</template>

<script>
export default {
  methods: {
    signin(){
      this.$store.dispatch('LOGIN_USER');
    }   
  }
}
</script>
<style scoped>
.background {
  background-color: #fbe8a6;
}
.button {
    background-color: #303c6c;
    border: none;
     border-radius: 15px;
    color: #87888d;
    padding: 14px 40px;
    cursor: pointer;
    font-family: "Times New Roman";
    }

.button:hover {
  background-color: #465386;
  }
</style>