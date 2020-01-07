import React from 'react';
import {Switch, Route} from 'react-router-dom'

import HomePage from './pages/homepage/homepage-comp'
import ShopPage from './pages/shoppage/shop-comp'
import Header from './component/header/header-comp'
import SignInPage from './pages/signinpage/signinpage-comp'
import './App.css';

function App() {
  return (
    <div>
      <Header/>
      <Switch>
        <Route exact path='/' component={HomePage}/>  
        <Route exact path='/shop' component={ShopPage}/>
        <Route exact path='/signin' component={SignInPage}/>
      </Switch>
    </div>
  );
}

export default App;
