import firebase from '@firebase/app';
import 'firebase/firestore' 
import 'firebase/app'
require('firebase/auth');


const config = {
    apiKey: "AIzaSyCWjGEA4nkZ79mudEyjekIV3sgDNioB0Vs",
    authDomain: "ecommercedb-48da6.firebaseapp.com",
    databaseURL: "https://ecommercedb-48da6.firebaseio.com",
    projectId: "ecommercedb-48da6",
    storageBucket: "ecommercedb-48da6.appspot.com",
    messagingSenderId: "600593791243",
    appId: "1:600593791243:web:20c1b571830b0e44e6ca0e"
  };

firebase.initializeApp(config)
export const auth = firebase.auth()
export const firestore = firebase.firestore()

const provider = new firebase.auth.GoogleAuthProvider()
provider.setCustomParameters({prompt: 'select_account'})
export const signInWithGoogle = () => auth.signInWithPopup(provider)

export default firebase 