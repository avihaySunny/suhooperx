import React from 'react'
import CustomButton from '../custom-button/custom-button-comp'
import CartItem from '../cart-item/cart-item-comp'
import {connect} from 'react-redux'
import './cart-dropdown-styles.scss'

const CartDropdown = ({cartItems}) => (
    <div className='cart-dropdown'>
        <div className='cart-items'>
            {
                !cartItems ? null : cartItems.map(item=> <CartItem key={item.id} item={item}/>)
            }
        </div>
        <CustomButton> GO TO CHECKOUT </CustomButton>
    </div>
);

const mapStateToProps = ({ cart: { cartItems } })=> ({
    cartItems
});


export default connect(mapStateToProps)(CartDropdown)