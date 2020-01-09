
import CartActionTypes from './cart.actions' 
import { addItemToCart} from './cart.utils'

const INITIAL_STATE = {
    hidden : true, 
    cartItems:[]
}
const cartReducer = (state = INITIAL_STATE, action ) => {
    switch(action.types){
        case CartActionTypes.TOOGLE_CART_HIDDEN : 
            return {
                ...state,
                hidden:!state.hidden 
            };
        case CartActionTypes.ADD_ITEM: 
            return {
                ...state,
                CartItems:addItemToCart(state.cartItems,action.payload)
            }
        default: 
            return state; 
    }
}

export default cartReducer; 