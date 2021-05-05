<template>
  <div class="login">
    <h1>This is a protected page</h1>
    <h2>hello: {{ hello }}</h2>
    <button v-on:click="signin">ButtonHello</button>
  </div>
</template>

<script>
import {appID} from "../main.js"
export default {
  methods: {
    signin(){
      const tokens = appID.signin();
    }   
  }
}
</script>