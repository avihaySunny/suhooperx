import React from 'react';
import {Switch, Route} from 'react-router-dom'

import HomePage from './pages/homepage/homepage-comp'
import ShopPage from './pages/shoppage/shop-comp'
import './App.css';

function App() {
  return (
    <div>
      <Switch>
        <Route exact path='/' component={HomePage}/>  
        <Route exact path='/shop' component={ShopPage}/>
      </Switch>
    </div>
  );
}

export default App;
