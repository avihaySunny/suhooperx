import CartActionTypes from './cart.types'

function toggleCartHidden(){
    return ({
        type:CartActionTypes.TOOGLE_CART_HIDDEN
    })
}

export const addItem = item => ({
    type:CartActionTypes.ADD_ITEM, 
    payload:item 
})
export default toggleCartHidden; 