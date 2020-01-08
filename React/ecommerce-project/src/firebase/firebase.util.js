import firebase from '@firebase/app';
require ( 'firebase/firestore') 
require('firebase/app')
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

export const createUserProfileDocument = async (userAuth, additionalData) => {
    if (!userAuth) return 
    const userRef = firestore.doc(`users/${userAuth.uid}`)
    const snapShot = await userRef.get()

    if (!snapShot.exists){
        const {displayName, email} = userAuth
        const createdAt = new Date()
        try{
            await userRef.set({
                displayName,
                email,
                createdAt,
                ...additionalData
            })
        }catch(err){
            console.log('error in create user', err.message)
        }
    }
    return userRef
}

firebase.initializeApp(config)
export const auth = firebase.auth()
export const firestore = firebase.firestore()

const provider = new firebase.auth.GoogleAuthProvider()
provider.setCustomParameters({prompt: 'select_account'})
export const signInWithGoogle = () => auth.signInWithPopup(provider)

export default firebase 