import CartActionTypes from './cart.types'

function toggleCartHidden(){
    return ({
        type:CartActionTypes.TOOGLE_CART_HIDDEN
    })
}

export default toggleCartHidden; 