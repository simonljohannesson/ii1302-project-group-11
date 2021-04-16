import firebase from 'firebase/app';
import 'firebase/analytics';
// import 'firebase/database';

const firebaseConfig = {
    apiKey: "AIzaSyA89Gxz5FJFCKyKYAMS3aUtzwIw_aUi3S4",
    authDomain: "dackpatrullen-vue-2.firebaseapp.com",
    databaseURL: "https://dackpatrullen-vue-2-default-rtdb.firebaseio.com",
    projectId: "dackpatrullen-vue-2",
    storageBucket: "dackpatrullen-vue-2.appspot.com",
    messagingSenderId: "536811432140",
    appId: "1:536811432140:web:69c996405fd6122b977a69",
    measurementId: "G-G939VKDM7P"
};
// Initialize Firebase
firebase.initializeApp(firebaseConfig);

const analytics = firebase.analytics();
// const database = firebase.database();

export {
    analytics
}