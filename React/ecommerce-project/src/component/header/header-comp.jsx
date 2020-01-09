import React from 'react'
import {Link} from 'react-router-dom'
import { connect } from 'react-redux' 
import { auth } from '../../firebase/firebase.util'

import {ReactComponent as Logo} from '../../assets/crown.svg'
import CartIcon from '../cart-icon/cart-icon-comp'
import CartDropdown from '../cart-dropdown/cart-dropdown-comp'

import './header-comp.styles.scss'

const Header = ({currentUser, hidden }) => (
    <div className = 'header'>
       <Link className='logo-container' to='/'> 
            <Logo className = 'logo'/> 
        </Link>
        <div className = 'options'>
            <Link className='option' to='/shop'> SHOP</Link>
            <Link className='option' to='aha@gmail.com'> CONTACT</Link>
            {currentUser ? 
                (<div className='option' onClick={()=>auth.signOut()}> Sign Out </div>) 
                : 
                <Link className='option' to='/signin'> SIGN IN</Link>
            }
            <CartIcon/> 
        </div>
        {
            hidden ? null : <CartDropdown/>
        }

    </div>
)
const mapStateToProps = ({user:{currentUser},cart:{hidden }}) => ({
    currentUser,
    hidden 
})

export default connect(mapStateToProps)(Header)
