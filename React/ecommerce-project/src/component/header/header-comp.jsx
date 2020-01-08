import React from 'react'
import {Link} from 'react-router-dom'
import {ReactComponent as Logo} from '../../assets/crown.svg'
import CartIcon from '../cart-icon/cart-icon-comp'

import { connect } from 'react-redux' 
import './header-comp.styles.scss'
import { auth } from '../../firebase/firebase.util'
const Header = (currentUser) => (
    <div className = 'header'>
       <Link className='logo-container' to='/'> 
            <Logo className = 'logo'/> 
        </Link>
        <div className = 'options'>
            <Link className='option' to='/shop'> SHOP</Link>
            <Link className='option' to='aha@gmail.com'> CONTACT</Link>
            {currentUser ? 
                (<div className='option' onClick={()=>auth.signOut()}> Sign Out </div >) 
                : 
                <Link className='option' to='/signin'> SIGN IN</Link>
            }
            <CartIcon/> 
        </div>

    </div>
)
const mapStateToProps = (state) => ({
    currentUser: state.user.currentUser
})

export default connect(mapStateToProps)(Header)
