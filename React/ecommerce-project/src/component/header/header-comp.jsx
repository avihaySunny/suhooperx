import React from 'react'
import {Link} from 'react-router-dom'
import {ReactComponent as Logo} from '../../assets/crown.svg'
import './header-comp.styles.scss'
const Header = () => (
    <div className = 'header'>
       <Link className='logo-container' to='/'> 
            <Logo className = 'logo'/> 
        </Link>
        <div className = 'options'>
            <Link className='option' to='/shop'> SHOP</Link>
            <Link className='option' to='aha@gmail.com'> CONTACT</Link>
            <Link className='option' to='/signin'> SIGN IN</Link>
        </div>

    </div>
)
export default Header
