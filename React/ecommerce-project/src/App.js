import React,{Component} from 'react';
import {Switch, Route, Redirect} from 'react-router-dom'
import {connect} from 'react-redux' 

import HomePage from './pages/homepage/homepage-comp'
import ShopPage from './pages/shoppage/shop-comp'
import Header from './component/header/header-comp'
import SignInPage from './pages/signinpage/signinpage-comp'
import './App.css';
import {auth, createUserProfileDocument} from './firebase/firebase.util'
import {setCurrentUser} from './redux/user/user.actions'

class App extends Component {
  
  unsubscribeFromAuth = null;

  componentDidMount(){
    const {setCurrentUser} = this.props
    auth.onAuthStateChanged(async userAuth=> {
      if(!userAuth){
        try{
          const userRef = await createUserProfileDocument(userAuth)
          userRef.onSnapshot(snapShot=>{
            setCurrentUser({
              currentUser:{
                id: snapShot.id,
                ...snapShot.data()
              }
            })
          })
        }catch (err){
          console.log(err)
        }
        
      }
      setCurrentUser(userAuth)
    })
  }

  componentWillUnmount(){
    this.unsubscribeFromAuth();
  }
  render(){
    return (
      <div>
        <Header/>
        <Switch>
          <Route exact path='/' component={HomePage}/>  
          <Route exact path='/shop' component={ShopPage}/>
          <Route exact path='/signin' render={()=>this.props.currentUser ? (<Redirect to='/'/>) : (<SignInPage/>)}

           />
        </Switch>
      </div>
    )
  }
  
}

const mapStateToProps = ({user}) =>({
  currentUser: user.currentUser
})

const mapDispatchToProps = dispatch => ({
  setCurrentUser: user =>dispatch(setCurrentUser(user))
})

export default connect(mapStateToProps, mapDispatchToProps)(App);
